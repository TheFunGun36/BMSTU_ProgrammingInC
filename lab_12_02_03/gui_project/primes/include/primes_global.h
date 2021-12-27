#ifndef PRIMES_GLOBAL_H
#define PRIMES_GLOBAL_H

#include <QtCore/qglobal.h>

#if defined(PRIMES_LIBRARY)
#  define PRIMES_EXPORT Q_DECL_EXPORT
#else
#  define PRIMES_EXPORT Q_DECL_IMPORT
#endif

#endif // PRIMES_GLOBAL_H
