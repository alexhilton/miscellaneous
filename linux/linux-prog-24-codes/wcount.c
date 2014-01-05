/*
 * count characters, words and lines in a text file.
 * wcount.c
 * Hitlion Warrior King.
 * Nov 25, 2008.
 */
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <getopt.h>

#define IN 1 /* inside a word */
#define OUT 0 /* outside of any word */

int countword( FILE *in );
int countchar( FILE *in );
int countline( FILE *in );
void help();
void version();

int main( int argc, char *argv[] ) {
  int i;
  int cmdx; /* long_opts index */
  int cmdopt_c = 0; /* flag of -c option */
  int cmdopt_w = 0; /* flag of -w option */
  int cmdopt_l = 0; /* flag of -l option */
  int wcnt; /* word count */
  int ccnt; /* character count */
  int lcnt; /* line count */
  int total_word; /* word count in sum of files */
  int total_char; /* char count in sum of files */
  int total_line; /* line count in sum of files */
  char optstring[] = "hvwcl";
  FILE *in;
  char ch;
  struct option long_opts[] = {
    { "help", 0, 0, 'h' }, /* help option */
    { "version", 0, 0, 'v' },
    { "character", 0, 0, 'c' },
    { "word", 0, 0, 'w' },
    { "line", 0, 0, 'l'},
    { 0, 0, 0, 0 }
  };

  /* process options */
  while ( (ch = 
	   getopt_long( argc, argv, optstring, long_opts, &cmdx )) != -1 ) {
    switch ( ch ) {
    case 'h':
      help();
      return 0;
    case 'v':
      version();
      return 0;
    case 'c':
      cmdopt_c = 1;
      break;
    case 'w':
      cmdopt_w = 1;
      break;
    case 'l':
      cmdopt_l = 1;
      break;
    default:
      fprintf( stderr, "Unkown options; Try -h or --help for help\n" );
      exit( EXIT_FAILURE );
    }
  }

  /* checking for missing input file(s). */
  if ( argc - optind < 1 ) {
    fprintf( stderr, "Missing input file(s).\n" );
    fprintf( stderr, "Use -h or --help for help.\n" );
    exit( EXIT_FAILURE );
  }

  /*if ( cmdopt_h ) {
    help();
  }
  if ( cmdopt_v ) {
    version();
  }*/

  total_word = total_char = total_line = 0;
  for ( i = optind; i < argc; i++ ) {
    wcnt = ccnt = lcnt = 0;
    in = fopen( argv[ i ], "r" );
    if ( in == NULL ) {
      perror( argv[ i ] );
      continue;
    }
    ccnt = countchar( in );
    rewind( in );
    wcnt = countword( in );
    rewind( in );
    lcnt = countline( in );
    if ( cmdopt_c+cmdopt_w+cmdopt_l == 0 ||
	 cmdopt_c+cmdopt_w+cmdopt_l == 3 ) {
      printf( "%s: %d character(s) %d word(s) %d line(s)\n",
	      argv[ i ], ccnt, wcnt, lcnt );
      total_word += wcnt;
      total_char += ccnt;
      total_line += lcnt;
    } else if ( cmdopt_c == 1 && cmdopt_w+cmdopt_l == 0 ) {
      printf( "%s: %d character(s)\n", argv[ i ], ccnt );
      total_char += ccnt;
    } else if ( cmdopt_w == 1 && cmdopt_c+cmdopt_l == 0 ) {
      printf( "%s: %d word(s)\n", argv[ i ], wcnt );
      total_word += wcnt;
    } else if ( cmdopt_l == 1 && cmdopt_c+cmdopt_w == 0 ) {
      printf( "%s: %d line(s)\n", argv[ i ], lcnt );
      total_line += lcnt;
    } else if ( cmdopt_c+cmdopt_w == 2 && cmdopt_l == 0 ) {
      printf( "%s: %d character(s) %d word(s)\n", 
	      argv[ i ], ccnt, wcnt );
      total_char += ccnt;
      total_word += wcnt;
    } else if ( cmdopt_c+cmdopt_l == 2 && cmdopt_w == 0 ) {
      printf( "%s: %d character(s) %d line(s)\n", 
	      argv[ i ], ccnt, lcnt );
      total_char += ccnt;
      total_line += lcnt;
    } else if ( cmdopt_w+cmdopt_l == 2 && cmdopt_c == 0 ) {
      printf( "%s: %d word(s) %d line(s)\n",
	      argv[ i ], wcnt, lcnt );
      total_word += wcnt;
      total_line += lcnt;
    } 
    fclose( in );
  }
  if ( argc >= 3 ) {
	  if ( total_char != 0 ) {
	    printf( "\t%d character(s)", total_char );
	  }
	  if ( total_word != 0 ) {
	    printf( "\t%d word(s)", total_word );
	  }
	  if ( total_line != 0 ) {
	    printf( "\t%d line(s)", total_line );
	  }
	  printf( " in sum\n" );
  }

  return 0;
}

void help() {
  printf( "Usage: [-h|--help] [-v|--version] [-c|character]"
	  " [-w|--word] [-l|--line]\n" );
  printf( "\t-h (or --help)\tGives this help display.\n" );
  printf( "\t-v (or --version)\tDisplays program version.\n" );
  printf( "\t-c (or --character)\tSpecifies counting characters only.\n" );
  printf( "\t-w (or --word)\tSpecifies counting words only.\n" );
  printf( "\t-l (or --line)\tSpecifies counting lines only.\n" );
}

void version() {
  printf( "Version 1.1\n" );
}

int countword( FILE *in ) {
  int count = 0;
  char ch;
  int state = OUT;
  while ( (ch = fgetc( in )) != EOF ) {
    if ( isspace( ch ) ) {
      state = OUT;
    } else if ( state == OUT ) {
      state = IN;
      count++;
    }
  }
  return count;
}

int countchar( FILE *in ) {
  int count = 0;
  char ch;
  while ( (ch = fgetc( in )) != EOF ) {
    count++;
  }
  return count;
}

int countline( FILE *in ) {
  int count = 0;
  char ch;
  while ( (ch = fgetc( in )) != EOF ) {
    if ( ch == '\n' ) {
      count++;
    }
  }
  return count;
}
