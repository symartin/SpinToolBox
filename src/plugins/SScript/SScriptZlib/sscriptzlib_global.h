#ifndef SSCRIPTZLIB_GLOBAL_H
#define SSCRIPTZLIB_GLOBAL_H

#include <QtCore/qglobal.h>

#ifdef SSCRIPTZLIB_LIB
# define SSCRIPTZLIB_EXPORT Q_DECL_EXPORT
#else
# define SSCRIPTZLIB_EXPORT Q_DECL_IMPORT
#endif

#endif // SSCRIPTZLIB_GLOBAL_H
