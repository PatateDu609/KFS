#ifndef LIBC_SIGNAL_H
#define LIBC_SIGNAL_H

#define SIG_DFL ((void (*)(int))0)
#define SIG_IGN ((void (*)(int))1)
#define SIG_ERR ((void (*)(int))-1)

#define SIGHUP 1			// Hangup detected on controlling terminal or death of controlling process
#define SIGINT 2			// Interrupt from keyboard (Ctrl+C)
#define SIGQUIT 3			// Quit from keyboard (Ctrl+\)
#define SIGILL 4			// Illegal instruction
#define SIGTRAP 5			// Trace/breakpoint trap
#define SIGABRT 6			// Abort signal from abort(3)
#define SIGIOT 6			// IOT trap
#define SIGBUS 7			// BUS error (bad memory access)
#define SIGFPE 8			// Floating-point exception
#define SIGKILL 9			// Kill signal
#define SIGUSR1 10			// User-defined signal 1
#define SIGSEGV 11			// Segmentation violation
#define SIGUSR2 12			// User-defined signal 2
#define SIGPIPE 13			// Broken pipe: write to pipe with no readers
#define SIGALRM 14			// Alarm clock
#define SIGTERM 15			// Termination signal
#define SIGSTKFLT 16		// Stack fault on coprocessor (unused)
#define SIGCHLD 17			// Child status has changed
#define SIGCONT 18			// Continue executing, if stopped
#define SIGSTOP 19			// Stop executing (signal)
#define SIGTSTP 20			// Stop typed at terminal
#define SIGTTIN 21			// Terminal input for background process
#define SIGTTOU 22			// Terminal output for background process
#define SIGURG 23			// Urgent condition on socket (4.2BSD)
#define SIGXCPU 24			// CPU limit exceeded (4.2BSD)
#define SIGXFSZ 25			// File size limit exceeded (4.2BSD)
#define SIGVTALRM 26		// Virtual alarm clock (4.2BSD)
#define SIGPROF 27			// Profiling alarm clock (4.2BSD)
#define SIGWINCH 28			// Window size change (4.3BSD, Sun)
#define SIGIO 29			// I/O now possible (4.2BSD)
#define SIGPOLL SIGIO		// Pollable event occurred (System V)
#define SIGPWR 30			// Power failure restart (System V)
#define SIGSYS 31			// Bad system call
#define SIGUNUSED 31		// Unused

#endif
