/*-----------------------------------------------------------------------------------------------------------*/
#pragma once
/*-----------------------------------------------------------------------------------------------------------*/
#include <QtCore/qglobal.h>
/*-----------------------------------------------------------------------------------------------------------*/
#ifndef QTSINGLEAPPLICATION_BUILD_STATIC
# if defined(QTSINGLEAPPLICATION_LIB)
#  define QTSINGLEAPPLICATION_EXPORT Q_DECL_EXPORT
# else
#  define QTSINGLEAPPLICATION_EXPORT Q_DECL_IMPORT
# endif
#else
# define QTSINGLEAPPLICATION_EXPORT
#endif
/*-----------------------------------------------------------------------------------------------------------*/