#ifndef SDEVICEGPIB_GLOBAL_H
#define SDEVICEGPIB_GLOBAL_H

#include <QtCore/qglobal.h>

#ifdef SDEVICEGPIB_LIB
# define SDEVICEGPIB_EXPORT Q_DECL_EXPORT
#else
# define SDEVICEGPIB_EXPORT Q_DECL_IMPORT
#endif

#endif // SDEVICEGPIB_GLOBAL_H
