/*
 * filefch.h -- A function to open file.
 */
#ifndef _filefch_h
#define _filefch_h

int open_file( 
  FILE **fp, 
  char *fname, 
  char *mode,
  int line, 
  char *file
);



#endif /* _filefch_h */
