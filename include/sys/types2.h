

#ifndef _SYS_TYPES2_H
#define _SYS_TYPES2_H

#ifndef _PID_T_
#define	_PID_T_
#ifndef _WIN64
typedef int	_pid_t;
#else
__MINGW_EXTENSION
typedef __int64	_pid_t;
#endif

#endif
