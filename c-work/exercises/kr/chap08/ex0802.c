/**
 * simio.h
 * an simple implementation of stdio.h
 */
#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>

//#define NULL 0
#define EOF (-1) /* avoid side-effect */
#define BUFSIZE 1024
#define OPEN_MAX 20 /* max number of files opened at once */

/* 
 * Most important part of this file, those flags and
 * the operations about them require some thinking.
 * We use octal number to represent read, write, error
 * eof or other status.
 */
//enum _flags {
// _READ = 01, /* file opened for reading */
//_WRITE = 02, /* file opend for writing */
//  _UNBUF = 04, /* file is unbuffered when reading and writing */
//  _EOF = 010, /* EOF has occured on this file */
//  _ERR = 020 /* error occured on this file */
//};
typedef struct flag_field FLAG;
struct flag_field {
  unsigned is_read : 1; /* file opened for reading */
  unsigned is_write : 1; /* file opened for writing */
  unsigned is_unbuf : 1; /* file is unbuffered when reading and writing */
  unsigned is_buf : 1; 
  unsigned is_eof : 1; /* eof reached */
  unsigned is_err : 1; /* error occurred */
};

typedef struct _iobuf FILE;
struct _iobuf {
  int cnt; /* characters left */
  char *ptr; /* next character position */
  char *base; /* location of buffer */
  FLAG flag; /* mode of file access */
  int fd; /* file decriptor */
};

/*
 * there are already some FILE structures.
 * Every time you open a new file, it doesnot create a new
 * FILE structure, but find a free slot from this array of
 * structure.
 */
static FILE _iob[ OPEN_MAX ] = {
  { 0, (char *) 0, (char *) 0, {1, 0, 0, 0, 0, 0}, 0 }, /* stdin */
  { 0, (char *) 0, (char *) 0, {0, 1, 0, 0, 0, 0}, 1 }, /* stdou */
  { 0, (char *) 0, (char *) 0, {1, 1, 0, 0, 0, 0}, 2 } /* stderr */
};

#define stdin (&_iob[0])
#define stdout (&_iob[1])
#define stderr (&_iob[2])

/* return 1 if p has not reached end-of-file */
#define feof( p ) ((p)->flag.is_eof != 0 )
/* return 1 if p has no error occured */
#define ferror( p ) ((p)->flag.is_err != 0 )
/* return file decriptior */
#define fileno( p ) ( (p)->fd )

/*
 * getc
 * decrement the count, advance the poiter(p->ptr), and return
 * the character.
 */
#define getc( p ) ( --(p)->cnt >= 0 \
		      ? (unsigned char) *(p)->ptr++ : _fillbuf( p ) )
/*
 * putc
 * decrement the count, assign the char to p->ptr and advance
 * the pointer.
 */
#define putc( x, p ) ( --(p)->cnt >= 0 \
			 ? *(p)->ptr++ = (x) : _flushbuf( (x), p ) )

#define getchar() getc(stdin)
#define putchar(x) putc( (x), stdout )

/*
 * other functions exported to extern usage
 */
/*
 * func: fopen
 * param: name -- file name to open
 * param: mode -- write, read or append "w", "r" or "a"
 * return: pointer to FILE structure.
 * desc: open file, return file pointer 
 */
extern FILE *fopen( char *name, char *mode );
/* permission to new file */
static int perms = 0644;

extern FILE *fopen( char *name, char *mode ) {
  int fd;
  FILE *fp;

  if ( *mode != 'r' && *mode != 'w' && *mode != 'r' ) {
    /* mode is wrong */
    return NULL; 
  }

  /* 
   * Now that the mode is right, we have to open a file
   * no matter write, read or append. Before that we have
   * to find a free FILE structure to hold the file we are
   * gonna open.
   */
  for ( fp = _iob; fp < _iob+OPEN_MAX; fp++ ) {
    /* Now test whether the structure is being used */
    if ( fp->flag.is_read == 0 || fp->flag.is_write == 0 ) {
      break; /* free slot */
    }
  }
  if ( fp > _iob + OPEN_MAX ) {
    /* no free slot found */
    return NULL;
  }

  /*
   * Now we have found the pointer to hold things,
   * we must open the right file according to the right mode 
   */
  if ( *mode == 'w' ) {
    /* create a new file, though the file might exist */
    fd = creat( name, perms );
  } else if ( *mode == 'a' ) {
    if ( (fd = open( name, O_WRONLY, perms )) == -1 ) {
      /* open failed, we create a new one */
      fd = creat( name, perms );
    } else {
      /* jump to end of file */
      lseek( fd, 0L, 2 );
    }
  } else {
    fd = open( name, O_RDONLY, 0 );
  }

  /* we handle the error together in here */
  if ( fd == -1 ) {
    return NULL;
  }

  /* now everything is ready, initialize the struture and exit */
  fp->fd = fd;
  fp->ptr = fp->base = NULL;
  fp->cnt = 0;
  if ( *mode == 'r' ) {
    fp->flag.is_read = 1;
  } else {
    fp->flag.is_write = 1;
  }
  return fp;
}


/*
 * func: _fillbuf
 * param: pointer to FILE structure
 * return: first char on buffer after filling
 * desc: allocate and fill input buffer
 */
extern int _fillbuf( FILE *fp ) {
  int bufsize; /* used to read bytes, changed with flag _UNBUF  */

  /* if this fp is for read, and there is no error or eof occured */
  //if ( (fp->flag & (_READ | _EOF | _ERR)) != _READ ) {
  //if ( (fp->flag.is_eof != 1 || fp->flag.is_err != 1) && fp->flag.is_read == 0 ) {
  if ( fp->flag.is_read == 0 || fp->flag.is_eof == 1 || fp->flag.is_err == 1 ) {
    return EOF;
  }

  //bufsize = (fp->flag & _UNBUF) ? 1 : BUFSIZE;
  if ( fp->flag.is_unbuf == 1 ) {
    bufsize = 1;
  } else {
    bufsize = BUFSIZE;
  }

  if ( fp->base == NULL ) { /* no buffer yet */
    if ( (fp->base = (char *) malloc( bufsize )) == NULL ) {
      /* TODO: */
      return EOF; /* no memory, but might not EOF */
    }
  }
  fp->ptr = fp->base;
  /* fill the buffer */
  fp->cnt = read( fp->fd, fp->ptr, bufsize );
  
  /* now return a char, decrement cnt and advance the pointer */
  if ( --fp->cnt < 0 ) {
    if ( fp->cnt == -1 ) {
      /* end-of-file */
      fp->flag.is_eof = 1;
    } else {
      fp->flag.is_err = 1;
    }
    fp->cnt = 0;
    /* this is a little obscure */
    /* TODO: */
    return EOF; 
  }
  return (unsigned char) *fp->ptr++;
}


/* main program: test fopen, getc, putc */
int main( int argc, char **argv ) {
  /* implement copy */
  FILE *fp1, *fp2;
  if ( argc != 3 ) {
    return 0;
  }
  if ( (fp1 = fopen( *++argv, "r" )) == NULL || (fp2 = fopen( *++argv, "w" )) == NULL ) {
    return 0;
  }

  char ch;
  while ( (ch = getc( fp1 )) != EOF ) {
    putc( ch, fp2 );
  }
  return 0;
}
