/**
 * error.h
 * implement a function to report errors.
 */
#ifndef _error_h
#define _error_h "error.h"

/*
 * func: error( char *fmt, va_list args );
 * param: char *fmt -- the fprintf format
 * param: va_list args -- arguments corresponding to fmt
 * desc: output the args according to fmt
 */
extern void error( char *fmt, ... );

#endif
