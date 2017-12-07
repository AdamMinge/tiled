/*-----------------------------------------------------------------------------------------------------------*/
#pragma once
/*-----------------------------------------------------------------------------------------------------------*/
#include <QtCore/QSharedMemory>
#include <QtNetwork/QLocalServer>
#include <QtNetwork/QLocalSocket>
#include "singleapplication.h"
/*-----------------------------------------------------------------------------------------------------------*/
struct InstancesInfo {
    bool primary;
    quint32 secondary;
    qint64 primaryPid;
};
/*-----------------------------------------------------------------------------------------------------------*/
class SingleApplicationPrivate : public QObject 
{
Q_OBJECT

public:
    Q_DECLARE_PUBLIC(SingleApplication)

    explicit SingleApplicationPrivate( SingleApplication *q_ptr );
     ~SingleApplicationPrivate();

    void genBlockServerName( int msecs );
    void startPrimary( bool resetMemory );
    void startSecondary();
    void connectToPrimary( int msecs, char connectionType );
    qint64 primaryPid();

#ifdef Q_OS_UNIX
    void crashHandler();
    static void terminate( int signum );
#endif

    QSharedMemory *memory;
    SingleApplication *q_ptr;
    QLocalSocket *socket;
    QLocalServer *server;
    quint32 instanceNumber;
    QString blockServerName;
    SingleApplication::Options options;

public Q_SLOTS:
    void slotConnectionEstablished();
    void slotDataAvailable( QLocalSocket*, quint32 );
    void slotClientConnectionClosed( QLocalSocket*, quint32 );
};
/*-----------------------------------------------------------------------------------------------------------*/
