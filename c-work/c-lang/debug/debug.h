#ifndef _debug_h
#define _debug_h "debug.h"

#ifdef DEBUG
#define log_debug( ... ) mylog( __VA_ARGS__ )
#else 
#define log_debug( ... )
#endif

void mylog( const char *fmt, ... );

#endif
