/*
 * ex0505.c
 * ----------------that is not the point, either--------------------
 * prefix of tmpnam is restricted to five char, because some systems have a
 * short name convention, say they permmit six characters of file name only.
 * When you specify a prefix to tmpname, all tmpfiles you create have the same
 * prefixes. So if some system has six-char-file-name restrict, you will create
 * a bunch of files with same name, which is an illeagal operation.
 * -----------------the point is------------------
 *  the temp name contains 5-char prefix, 4-char process unique identifier(not
 *  pid), and 5-char system unique(pid). Summing it makes 14. While some system
 *  has NAME_MAX as 14. This is for portability.
 */
#include <stdio.h>

int main( int argc, char **argv ) {
  tempnam( NULL, NULL );
  return 0;
}
