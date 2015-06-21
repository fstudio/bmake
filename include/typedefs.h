
#ifndef TYPEDEFS_H
#define TYPEDEFS_H

#ifndef _SSIZE_T_DEFINED
#define _SSIZE_T_DEFINED
#undef ssize_t
#ifdef _WIN64
 typedef __int64 ssize_t;
#else
typedef int ssize_t;
#endif /* _WIN64 */
#endif /* _SSIZE_T_DEFINED */

typedef unsigned int u_int;

#endif
