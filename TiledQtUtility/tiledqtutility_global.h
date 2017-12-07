/*-----------------------------------------------------------------------------------------------------------*/
#pragma once
/*-----------------------------------------------------------------------------------------------------------*/
#include <QtCore/qglobal.h>
/*-----------------------------------------------------------------------------------------------------------*/
#ifndef TILEDQTUTILITY_BUILD_STATIC
# if defined(TILEDQTUTILITY_LIB)
#  define TILEDQTUTILITY_EXPORT Q_DECL_EXPORT
# else
#  define TILEDQTUTILITY_EXPORT Q_DECL_IMPORT
# endif
#else
# define TILEDQTUTILITY_EXPORT
#endif
/*-----------------------------------------------------------------------------------------------------------*/