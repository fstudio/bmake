/**/

#ifndef SIGNAL2_H
#define SIGNAL2_H
#include <signal.h>
#include <time.h>
#include <unistd.h>

#define	SA_ONSTACK	0x0001	/* take signal on signal stack */
#define	SA_RESTART	0x0002	/* restart system call on signal return */
#define	SA_RESETHAND	0x0004	/* reset to SIG_DFL when taking signal */
#define	SA_NODEFER	0x0010	/* don't mask the signal we're delivering */
#define	SA_NOCLDWAIT	0x0020	/* don't keep zombies around */
#define	SA_SIGINFO	0x0040	/* signal handler with SA_SIGINFO args */

union sigval {
	/* Members as suggested by Annex C of POSIX 1003.1b. */
	int	sival_int;
	void	*sival_ptr;
	/* 6.0 compatibility */
	int     sigval_int;
	void    *sigval_ptr;
};
typedef union sigval sigval_t;

typedef int uid_t;

typedef struct siginfo_t{
	int      si_signo;    /* Signal number */
	int      si_errno;    /* An errno value */
	int      si_code;     /* Signal code */
	int      si_trapno;   /* Trap number that caused hardware-generated signal (unused on most architectures) */
	pid_t    si_pid;      /* Sending process ID */
	uid_t    si_uid;      /* Real user ID of sending process */
	int      si_status;   /* Exit value or signal */
	clock_t  si_utime;    /* User time consumed */
	clock_t  si_stime;    /* System time consumed */
	sigval_t si_value;    /* Signal value */
	int      si_int;      /* POSIX.1b signal */
	void    *si_ptr;      /* POSIX.1b signal */

	int      si_overrun;  /* Timer overrun count; POSIX.1b timers */

	int      si_timerid;  /* Timer ID; POSIX.1b timers */
	void    *si_addr;     /* Memory location which caused fault */
	long     si_band;     /* Band event (was int in
						  glibc 2.3.2 and earlier) */
	int      si_fd;       /* File descriptor */
	short    si_addr_lsb; /* Least significant bit of address
						  (since kernel 2.6.32) */
}siginfo_t;

#define	_SIG_WORDS	4
#define	_SIG_MAXSIG	128
#define	_SIG_IDX(sig)	((sig) - 1)
#define	_SIG_WORD(sig)	(_SIG_IDX(sig) >> 5)
#define	_SIG_BIT(sig)	(1 << (_SIG_IDX(sig) & 31))
#define	_SIG_VALID(sig)	((sig) <= _SIG_MAXSIG && (sig) > 0)

typedef struct __sigset {
	uint32_t __bits[_SIG_WORDS];
} __sigset_t;

typedef __sigset_t sigset_t;

struct sigaction
{
	void(*sa_handler)(int);
	void(*sa_sigaction)(int, siginfo_t *, void *);
	sigset_t  sa_mask;
	int       sa_flags;
	void(*sa_restorer)(void);
};



struct sigqueue{

	struct sigqueue *next;

	siginfo_t info;

};


#ifdef __cplusplus
extern "C" {
#endif
/// Send POSIX Signal to Process
int kill(pid_t pid, int sig);

#ifdef __cplusplus
}
#endif

#endif