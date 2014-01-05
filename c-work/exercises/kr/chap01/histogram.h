/*
 * histogram.h
 *
 * interfaces to print vertical and horizontal histograms
 */
#ifndef _histogram_h
#define _histogram_h 

extern int vhistogram( FILE *out, int a[ ], int size, int start, int end );

extern int hhistogram( FILE *out, int a[ ], int size, int start, int end );

extern int vshistogram( FILE *out, int a[ ], int size, char *name[ ] );

extern int hshistogram( FILE *out, int a[ ], int size, char *name[ ] );

#endif
