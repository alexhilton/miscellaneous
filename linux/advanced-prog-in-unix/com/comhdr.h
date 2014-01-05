/**
 * comhdr.h
 * This file contains all the common functions or interfaces needed in this
 * book. We have collected those functions or macros into this file for
 * convineince.
 */
#ifndef __comhdr_h
#define __comhdr_h

#define MAXLINE 4096 /* max line length */

/* default file access permissions for new files */
#define FILE_MODE (S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH)

/* default permissions for new directories */
#define DIR_MODE (FILE_MODE | S_IXUSR | S_IXGRP | S_IXOTH)

/*
 * Fatal error related to a system call.
 * Print a message, dump core, and terminates
 */
void err_dump( const char *fmt, ... );

/*
 * Nonfatal error unrelated to a system call.
 * Print a message and return
 */
void err_msg( const char *fmt, ... );

/*
 * fatal error unrelated to a system call
 * Print a message and terminates
 */
void err_quit( const char *fmt, ... );

/*
 * fatal error unrelated to a system call, print a message and
 * terminates.
 */
void err_exit( int error, const char *fmt, ... );

/*
 * Nonfatal error relates to a system call.
 * Print a message and return.
 */
void err_ret( const char *fmt, ... );

/*
 * Fatal error related to a system call.
 * Print a message and termintates
 */
void err_sys( const char *fmt, ... );

/* The following interfaces are for daemon process */

/*
 * Nonfatal error unrelated to a system call 
 * Print a message and return
 */
void log_msg( const char *fmt, ... );

/*
 * Initialize syslog(), if running as a daemon 
 */
void log_open( const char *fmt, int option, int facility );

/*
 * Fatal error unrelated to a system call.
 * Print a message and terminates
 */
void log_quit( const char *fmt, ... );
/*
 * Nonfatal error related to a system call
 * Print a message with the system's errno value and return
 */
void log_ret( const char *fmt, ... );

/*
 * Fatal error related to a system call.
 * Print a message and terminates
 */
void log_sys( const char *fmt, ... );

#endif /* __comhdr_h */
