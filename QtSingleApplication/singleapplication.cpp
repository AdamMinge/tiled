/*-----------------------------------------------------------------------------------------------------------*/
#include <cstdlib>
#include <QtCore/QDir>
#include <QtCore/QProcess>
#include <QtCore/QByteArray>
#include <QtCore/QSemaphore>
#include <QtCore/QStandardPaths>
#include <QtCore/QCryptographicHash>
/*-----------------------------------------------------------------------------------------------------------*/
#ifdef Q_OS_UNIX
    #include <signal.h>
    #include <unistd.h>
#endif
/*-----------------------------------------------------------------------------------------------------------*/
#ifdef Q_OS_WIN
    #include <windows.h>
    #include <lmcons.h>
#endif
/*-----------------------------------------------------------------------------------------------------------*/
#include "singleapplication.h"
#include "singleapplication_p.h"
/*-----------------------------------------------------------------------------------------------------------*/
static const char NewInstance = 'N';
static const char SecondaryInstance = 'S';
static const char Reconnect =  'R';
static const char InvalidConnection = '\0';
/*-----------------------------------------------------------------------------------------------------------*/
SingleApplicationPrivate::SingleApplicationPrivate( SingleApplication *q_ptr ) : 
	memory(nullptr),
	q_ptr(q_ptr), 
	instanceNumber(0)
{
	server = nullptr;
	socket = nullptr;
}
/*-----------------------------------------------------------------------------------------------------------*/
SingleApplicationPrivate::~SingleApplicationPrivate()
{
    if( socket != nullptr ) 
	{
        socket->close();
        delete socket;
    }

    memory->lock();
    auto inst = static_cast<InstancesInfo*>(memory->data());
    if( server != nullptr ) 
	{
        server->close();
        delete server;
        inst->primary = false;
        inst->primaryPid = -1;
    }
    memory->unlock();

    delete memory;
}
/*-----------------------------------------------------------------------------------------------------------*/
void SingleApplicationPrivate::genBlockServerName( int timeout )
{
    QCryptographicHash appData( QCryptographicHash::Sha256 );
    appData.addData( "SingleApplication", 17 );
    appData.addData( SingleApplication::app_t::applicationName().toUtf8() );
    appData.addData( SingleApplication::app_t::organizationName().toUtf8() );
    appData.addData( SingleApplication::app_t::organizationDomain().toUtf8() );

    if( ! (options & SingleApplication::Mode::ExcludeAppVersion) )
	{
        appData.addData( SingleApplication::app_t::applicationVersion().toUtf8() );
    }

    if( ! (options & SingleApplication::Mode::ExcludeAppPath) ) 
	{
#ifdef Q_OS_WIN
        appData.addData( SingleApplication::app_t::applicationFilePath().toLower().toUtf8() );
#else
        appData.addData( SingleApplication::app_t::applicationFilePath().toUtf8() );
#endif
    }

    if( options & SingleApplication::Mode::User ) 
	{
#ifdef Q_OS_WIN
        Q_UNUSED(timeout);
        wchar_t username [ UNLEN + 1 ];

        DWORD usernameLength = UNLEN + 1;
        if( GetUserNameW( username, &usernameLength ) ) 
		{
            appData.addData( QString::fromWCharArray(username).toUtf8() );
        } else 
		{
            appData.addData( QStandardPaths::standardLocations( QStandardPaths::HomeLocation ).join("").toUtf8() );
        }
#endif
#ifdef Q_OS_UNIX
        QProcess process;
        process.start( "whoami" );
        if( process.waitForFinished( timeout ) &&
            process.exitCode() == QProcess::NormalExit)
		{
            appData.addData( process.readLine() );
        } else 
		{
            appData.addData(
                QDir(
                    QStandardPaths::standardLocations( QStandardPaths::HomeLocation ).first()
                ).absolutePath().toUtf8()
            );
        }
#endif
    }

    blockServerName = appData.result().toBase64().replace("/", "_");
}
/*-----------------------------------------------------------------------------------------------------------*/
void SingleApplicationPrivate::startPrimary( bool resetMemory )
{
    Q_Q(SingleApplication);

#ifdef Q_OS_UNIX
    crashHandler();
#endif

    QLocalServer::removeServer( blockServerName );
    server = new QLocalServer();

    if( options & SingleApplication::Mode::User ) 
	{
      server->setSocketOptions( QLocalServer::UserAccessOption );
    } else 
	{
      server->setSocketOptions( QLocalServer::WorldAccessOption );
    }

    server->listen( blockServerName );
    QObject::connect(
        server,
        &QLocalServer::newConnection,
        this,
        &SingleApplicationPrivate::slotConnectionEstablished
    );

    memory->lock();
    auto inst = static_cast<InstancesInfo*>(memory->data());

    if( resetMemory ) 
	{
        inst->secondary = 0;
    }

    inst->primary = true;
    inst->primaryPid = q->applicationPid();

    memory->unlock();

    instanceNumber = 0;
}
/*-----------------------------------------------------------------------------------------------------------*/
void SingleApplicationPrivate::startSecondary()
{
#ifdef Q_OS_UNIX
    crashHandler();
#endif
}
/*-----------------------------------------------------------------------------------------------------------*/
void SingleApplicationPrivate::connectToPrimary( int msecs, char connectionType )
{
    if( socket == nullptr ) 
	{
        socket = new QLocalSocket();
    }

    if( socket->state() == QLocalSocket::ConnectedState )
        return;

    if( socket->state() == QLocalSocket::UnconnectedState ||
        socket->state() == QLocalSocket::ClosingState ) 
	{
        socket->connectToServer( blockServerName );
    }

    if( socket->state() == QLocalSocket::ConnectingState ) 
	{
        socket->waitForConnected( msecs );
    }

    if( socket->state() == QLocalSocket::ConnectedState ) 
	{
        auto initMsg = blockServerName.toLatin1();

        initMsg.append( connectionType );
        initMsg.append( reinterpret_cast<const char *>(&instanceNumber), sizeof(quint32) );
        initMsg.append( QByteArray::number( qChecksum( initMsg.constData(), initMsg.length() ), 256) );

        socket->write( initMsg );
        socket->flush();
        socket->waitForBytesWritten( msecs );
    }
}
/*-----------------------------------------------------------------------------------------------------------*/
qint64 SingleApplicationPrivate::primaryPid()
{
	memory->lock();
    auto inst = static_cast<InstancesInfo*>(memory->data());
    auto pid = inst->primaryPid;
    memory->unlock();

    return pid;
}
/*-----------------------------------------------------------------------------------------------------------*/
#ifdef Q_OS_UNIX
    void SingleApplicationPrivate::crashHandler()
    {
        // Handle any further termination signals to ensure the
        // QSharedMemory block is deleted even if the process crashes
        signal( SIGHUP,  SingleApplicationPrivate::terminate ); // 1
        signal( SIGINT,  SingleApplicationPrivate::terminate ); // 2
        signal( SIGQUIT, SingleApplicationPrivate::terminate ); // 3
        signal( SIGILL,  SingleApplicationPrivate::terminate ); // 4
        signal( SIGABRT, SingleApplicationPrivate::terminate ); // 6
        signal( SIGFPE,  SingleApplicationPrivate::terminate ); // 8
        signal( SIGBUS,  SingleApplicationPrivate::terminate ); // 10
        signal( SIGSEGV, SingleApplicationPrivate::terminate ); // 11
        signal( SIGSYS,  SingleApplicationPrivate::terminate ); // 12
        signal( SIGPIPE, SingleApplicationPrivate::terminate ); // 13
        signal( SIGALRM, SingleApplicationPrivate::terminate ); // 14
        signal( SIGTERM, SingleApplicationPrivate::terminate ); // 15
        signal( SIGXCPU, SingleApplicationPrivate::terminate ); // 24
        signal( SIGXFSZ, SingleApplicationPrivate::terminate ); // 25
    }

    void SingleApplicationPrivate::terminate( int signum )
    {
        delete ((SingleApplication*)QCoreApplication::instance())->d_ptr;
        ::exit( 128 + signum );
    }
#endif
/*-----------------------------------------------------------------------------------------------------------*/
void SingleApplicationPrivate::slotConnectionEstablished()
{
    Q_Q(SingleApplication);

   auto nextConnSocket = server->nextPendingConnection();

    auto connectionType = InvalidConnection;
    quint32 instanceId = 0;

	if( nextConnSocket->waitForReadyRead( 100 ) ) 
	{
        auto tmp = nextConnSocket->read( blockServerName.length() );

        if( tmp == blockServerName.toLatin1() ) 
		{
            auto initMsg = tmp;
            connectionType = nextConnSocket->read( 1 )[0];

            switch( connectionType ) {
            case NewInstance:
            case SecondaryInstance:
            case Reconnect:
            {
                initMsg += connectionType;
                tmp = nextConnSocket->read( sizeof(quint32) );
                auto data = tmp.constData();
                instanceId = static_cast<quint32>(*data);
                initMsg += tmp;

                auto checksum = QByteArray::number(
                    qChecksum( initMsg.constData(), initMsg.length() ),
                    256
                );
                tmp = nextConnSocket->read( checksum.length() );
                if( checksum == tmp )
                    break; 
            }
            default:
                connectionType = InvalidConnection;
            }
        }
    }

    if( connectionType == InvalidConnection ) {
        nextConnSocket->close();
        delete nextConnSocket;
        return;
    }

    QObject::connect(
        nextConnSocket,
        &QLocalSocket::aboutToClose,
        this,
        [nextConnSocket, instanceId, this]() {
            Q_EMIT this->slotClientConnectionClosed( nextConnSocket, instanceId );
        }
    );

    QObject::connect(
        nextConnSocket,
        &QLocalSocket::readyRead,
        this,
        [nextConnSocket, instanceId, this]() {
            Q_EMIT this->slotDataAvailable( nextConnSocket, instanceId );
        }
    );

    if( connectionType == NewInstance || (
            connectionType == SecondaryInstance &&
            options & SingleApplication::Mode::SecondaryNotification
        )
    ) {
        Q_EMIT q->instanceStarted();
    }

    if( nextConnSocket->bytesAvailable() > 0 ) {
        Q_EMIT this->slotDataAvailable( nextConnSocket, instanceId );
    }
}
/*-----------------------------------------------------------------------------------------------------------*/
void SingleApplicationPrivate::slotDataAvailable( QLocalSocket *dataSocket, quint32 instanceId )
{
    Q_Q(SingleApplication);
    Q_EMIT q->receivedMessage( instanceId, dataSocket->readAll() );
}
/*-----------------------------------------------------------------------------------------------------------*/
void SingleApplicationPrivate::slotClientConnectionClosed( QLocalSocket *closedSocket, quint32 instanceId )
{
    if( closedSocket->bytesAvailable() > 0 )
        Q_EMIT slotDataAvailable( closedSocket, instanceId  );
    closedSocket->deleteLater();
}
/*-----------------------------------------------------------------------------------------------------------*/
SingleApplication::SingleApplication( int &argc, char *argv[], bool allowSecondary, Options options, int timeout )
    : app_t( argc, argv ), d_ptr( new SingleApplicationPrivate( this ) )
{
    Q_D(SingleApplication);

    d->options = options;

    d->genBlockServerName( timeout );

#ifdef Q_OS_UNIX
    d->memory = new QSharedMemory( d->blockServerName );
    d->memory->attach();
    delete d->memory;
#endif
    d->memory = new QSharedMemory( d->blockServerName );

    if( d->memory->create( sizeof( InstancesInfo ) ) ) {
        d->startPrimary( true );
        return;
    } else {
        if( d->memory->attach() ) {
            d->memory->lock();
            auto inst = static_cast<InstancesInfo*>(d->memory->data());

            if( ! inst->primary ) {
                d->startPrimary( false );
                d->memory->unlock();
                return;
            }

            if( allowSecondary ) {
                inst->secondary += 1;
                d->instanceNumber = inst->secondary;
                d->startSecondary();
                if( d->options & Mode::SecondaryNotification ) {
                    d->connectToPrimary( timeout, SecondaryInstance );
                }
                d->memory->unlock();
                return;
            }

            d->memory->unlock();
        }
    }

    d->connectToPrimary( timeout, NewInstance );
    delete d;
    ::exit( EXIT_SUCCESS );
}
/*-----------------------------------------------------------------------------------------------------------*/
SingleApplication::~SingleApplication()
{
    Q_D(SingleApplication);
    delete d;
}
/*-----------------------------------------------------------------------------------------------------------*/
bool SingleApplication::isPrimary()
{
    Q_D(SingleApplication);
    return d->server != nullptr;
}
/*-----------------------------------------------------------------------------------------------------------*/
bool SingleApplication::isSecondary()
{
    Q_D(SingleApplication);
    return d->server == nullptr;
}
/*-----------------------------------------------------------------------------------------------------------*/
quint32 SingleApplication::instanceId()
{
    Q_D(SingleApplication);
    return d->instanceNumber;
}
/*-----------------------------------------------------------------------------------------------------------*/
qint64 SingleApplication::primaryPid()
{
    Q_D(SingleApplication);
    return d->primaryPid();
}
/*-----------------------------------------------------------------------------------------------------------*/
bool SingleApplication::sendMessage( QByteArray message, int timeout )
{
    Q_D(SingleApplication);

    if( isPrimary() ) return false;

    d->connectToPrimary( timeout,  Reconnect );

    d->socket->write( message );
    auto dataWritten = d->socket->flush();
    d->socket->waitForBytesWritten( timeout );
    return dataWritten;
}
/*-----------------------------------------------------------------------------------------------------------*/