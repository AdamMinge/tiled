/*-----------------------------------------------------------------------------------------------------------*/
#pragma once
/*-----------------------------------------------------------------------------------------------------------*/
#include <QtCore/QtGlobal>
#include "qtsingleapplication_global.h"
/*-----------------------------------------------------------------------------------------------------------*/
class SingleApplicationPrivate;
/*-----------------------------------------------------------------------------------------------------------*/
#ifndef QAPPLICATION_CLASS
#define QAPPLICATION_CLASS QApplication
#endif
/*-----------------------------------------------------------------------------------------------------------*/
#include QT_STRINGIFY(QAPPLICATION_CLASS)
/*-----------------------------------------------------------------------------------------------------------*/
class QTSINGLEAPPLICATION_EXPORT SingleApplication : public QAPPLICATION_CLASS
{
    Q_OBJECT

    using app_t = QAPPLICATION_CLASS;

public:
    enum Mode {
        User                    = 1 << 0,
        System                  = 1 << 1,
        SecondaryNotification   = 1 << 2,
        ExcludeAppVersion       = 1 << 3,
        ExcludeAppPath          = 1 << 4
    };
    Q_DECLARE_FLAGS(Options, Mode)

    explicit SingleApplication( int &argc, char *argv[], bool allowSecondary = false, Options options = Mode::User, int timeout = 100 );
    ~SingleApplication();

    bool isPrimary();
    bool isSecondary();
    quint32 instanceId();
    qint64 primaryPid();
    bool sendMessage( QByteArray message, int timeout = 100 );

signals:
    void instanceStarted();
    void receivedMessage( quint32 instanceId, QByteArray message );

private:
    SingleApplicationPrivate *d_ptr;
    Q_DECLARE_PRIVATE(SingleApplication)
};
/*-----------------------------------------------------------------------------------------------------------*/
Q_DECLARE_OPERATORS_FOR_FLAGS(SingleApplication::Options)
/*-----------------------------------------------------------------------------------------------------------*/
