/*
 * hist.h
 *
 * an interface to draw histogram
 */
#ifndef _hist_h
#define _hist_h

#define MAX_HIST 100 /* max height of the histogram */

extern int vhist( FILE *out, int a[ ], int size, int step );

extern int hhist( FILE *out, int a[ ], int size, int step );

#endif
