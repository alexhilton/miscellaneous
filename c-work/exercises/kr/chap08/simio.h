/**
 * simio.h
 * an simple implementation of stdio.h
 */
#ifndef _simio_h
#define _simio_h "simio.h"

#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

//#define NULL 0
//#define EOF (-1) /* avoid side-effect */
#define BUFSIZE 1024
#define OPEN_MAX 20 /* max number of files opened at once */

/* 
 * Most important part of this file, those flags and
 * the operations about them require some thinking.
 * We use octal number to represent read, write, error
 * eof or other status.
 */
enum _flags {
  _READ = 01, /* file opened for reading */
  _WRITE = 02, /* file opend for writing */
  _UNBUF = 04, /* file is unbuffered when reading and writing */
  _EOF = 010, /* EOF has occured on this file */
  _ERR = 020 /* error occured on this file */
};

typedef struct _iofilebuf File;

struct _iofilebuf {
  int cnt; /* characters left */
  char *ptr; /* next character position */
  char *base; /* location of buffer */
  int flag; /* mode of file access */
  int fd; /* file decriptor */
};

/*
 * there are already some File structures.
 * Every time you open a new file, it doesnot create a new
 * File structure, but find a free slot from this array of
 * structure.
 */
extern File _iofile[ OPEN_MAX ] = {
  { 0, (char *) 0, (char *) 0, _READ, 0 }, /* stdin */
  { 0, (char *) 0, (char *) 0, _WRITE, 1 }, /* stdout */
  { 0, (char *) 0, (char *) 0, _WRITE | _UNBUF, 2 }, /* stderr */
};

/* those macro are toys, they cannot work */
#define stdinput (&_iofile[0])
#define stdoutput (&_iofile[1])
#define stderror (&_iofile[2])

/* return 1 if p has not reached end-of-file */
#define fileeof( p ) ( ((p)->flag & _EOF) != 0 )
/* return 1 if p has no error occured */
#define fileerror( p ) ( ((p)->flag & _ERR) != 0 )
/* return file decriptior */
#define fileno( p ) ( (p)->fd )

/*
 * getc
 * decrement the count, advance the poiter(p->ptr), and return
 * the character.
 */
#define filegetc( p ) ( --(p)->cnt >= 0 \
		      ? (unsigned char) *(p)->ptr++ : _fillbuf( p ) )
/*
 * putc
 * decrement the count, assign the char to p->ptr and advance
 * the pointer.
 */
#define fileputc( x, p ) ( --(p)->cnt >= 0 \
			 ? *(p)->ptr++ = (x) : _flushbuf( (x), p ) )

#define getch() filegetc(stdinput)
#define putch(x) fileputc( (x), stdoutput )

/*
 * other functions exported to extern usage
 */
/*
 * func: fileopen
 * param: name -- file name to open
 * param: mode -- write, read or append "w", "r" or "a"
 * return: pointer to File structure.
 * desc: open file, return file pointer 
 */

/* permission to new file */
static int perms = 0644;
static int nobuffer = 0;

extern File *fileopen( char *name, char *mode ) {
  int fd;
  File *fp;

  if ( *mode != 'r' && *mode != 'w' && *mode != 'r' ) {
    /* mode is wrong */
    return NULL; 
  }

  /* 
   * Now that the mode is right, we have to open a file
   * no matter write, read or append. Before that we have
   * to find a free File structure to hold the file we are
   * gonna open.
   */
  for ( fp = _iofile; fp < _iofile+OPEN_MAX; fp++ ) {
    /* Now test whether the structure is being used */
    if ( (fp->flag & (_READ | _WRITE)) == 0 ) {
      break; /* free slot */
    }
  }
  if ( fp > _iofile + OPEN_MAX ) {
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
  fp->flag = (*mode == 'r') ? _READ : _WRITE;
  return fp;
}

/*
 * func: _fillbuf
 * param: pointer to File structure
 * return: first char on buffer after filling
 * desc: allocate and fill input buffer
 * note: this function is for reading only. Only does reading need fill the
 * buffer, of course.
 */
extern int _fillbuf( File *fp ) {
  int bufsize; /* used to read bytes, changed with flag _UNBUF  */

  /* if this fp is for read, and there is no error or eof occured */
  if ( (fp->flag & (_READ | _EOF | _ERR)) != _READ ) {
    return EOF;
  }

  bufsize = (fp->flag & _UNBUF) ? 1 : BUFSIZE;

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
      fp->flag |= _EOF;
    } else {
      fp->flag |= _ERR;
    }
    fp->cnt = 0;
    /* this is a little obscure */
    /* TODO: */
    return EOF; 
  }
  return (unsigned char) *fp->ptr++;
}

/*
 * func: _flushbuf
 * param: pointer to File structure
 * return 0 -- success, -1 -- failure
 * desc: flush the buffer in fp. 
 * note: this is for writing only. Only does writing need to flush the buffer,
 * of course.
 */
extern int _flushbuf( char ch, File *fp ) {
  int bufsize;

  if ( (fp->flag & (_READ|_WRITE|_EOF|_ERR)) != _WRITE ) {
    return -1;
  }
  bufsize = (fp->flag & _UNBUF) ? 1 : BUFSIZE;

  /*
   * since this function applies to writing only,
   * so we handle writing only, too.
   */
  /* if there is no buffer, we need to create one */
  if ( fp->base == NULL ) {
    if ( (fp->base = (char *) malloc( bufsize )) == NULL ) {
      fp->flag |= _ERR;
      return -1;
    }
  } else {
    /* the buffer is full, write it to file */
    if ( bufsize != write( fp->fd, fp->base, bufsize ) ) {
      fp->flag |= _ERR;
      return -1;
    }
  }
  fp->cnt = bufsize - 1;
  fp->ptr = fp->base;
  *fp->ptr++ = ch;
  return 0;
}

/* 
 * func: fileclose
 * param: pointer to file structure
 * return 0 -- success, -1 -- failure
 * desc: disconnect the file pointer to actual file, release resource and
 * re-initialize file pointer fields
 */
extern int fileclose( File *fp ) {
  if ( (fp->flag & (_EOF | _ERR)) != 0 ) {
    return -1; /* error occured */
  }
  int bufsize = (fp->flag & _UNBUF) ? 1 : BUFSIZE;
  if ( (fp->flag & _WRITE) != 0 ) {
    if ( fp->cnt < 0 ) {
      fp->cnt = 0;
    }
    if ( fp->cnt > bufsize ) {
      fp->cnt = bufsize;
    }
    if ( fp->base != NULL ) {
      int n = bufsize - fp->cnt;
      if ( n != write( fp->fd, fp->base, n ) ) {
	return -1;
      }
    }
  }
  if ( fp->base != NULL ) {
    free( fp->base );
  }
  fp->cnt = 0;
  fp->ptr = NULL;
  fp->base = NULL;
  fp->flag = 0;
  close( fp->fd );
  return 0;
}

/*
 * func: fileflush
 * param: pointer to file structure
 * return 0 -- success, -1 -- failure
 * desc: flush the file structure, export to user
 */
extern int fileflush( File *fp ) {
  if ( fp->flag & _ERR ) {
    return -1;
  }
  int bufsize = ( fp->flag & _UNBUF ) ? 1 : BUFSIZE;
  if ( fp->base == NULL ) {
    if ( (fp->base = (char *) malloc( bufsize )) == NULL ) {
      return -1;
    }
    fp->ptr = fp->base;
    fp->cnt = 0;
  }

  if ( fp->flag & _READ ) {
    /* if it is for reading, we fill the buffer */
    if ( fp->cnt >= 0 && fp->cnt < bufsize ) {
      int n = bufsize - fp->cnt;
      int tmp  = read( fp->fd, fp->base, n );
      if ( tmp < n ) {
	nobuffer = 1;
      }
      char *tmpbuf = (char *) malloc( bufsize );
      strncpy( tmpbuf, fp->ptr, fp->cnt );
      strncpy( tmpbuf+fp->cnt, fp->base, tmp );
      free( fp->base );
      fp->base = tmpbuf;
      fp->ptr = fp->base;
      fp->cnt += tmp;
    }
  } else {
    /* 
     * if it is for writing, we write the remaining bytes into file or empty the
     * buffer 
     */
    if ( fp->cnt >= 0 && fp->cnt < bufsize ) {
      int n = bufsize - fp->cnt;
      if ( n != write( fp->fd, fp->base, n ) ) {
	return -1;
      }
      fp->ptr = fp->base;
      fp->cnt = bufsize;
    }
  }
  return 0;
}

extern char *filegets( char *str, int limit, File *fp ) {
  printf( "before doing 0x%x\n", fp->flag );
  int tmpflag = fp->flag;
  if ( (fp->flag & (_EOF | _ERR | _READ)) != _READ ) {
    printf( "stop here 0\n" );
    printf( "after doing 0x%x\n", fp->flag );
    return NULL;
  }
  int bufsize = (fp->flag & _UNBUF) ? 1 : BUFSIZE;
  if ( fp->base == NULL ) {
    if ( (fp->base = (char *) malloc(bufsize)) == NULL ) {
      return NULL;
    }
    fp->ptr = fp->base;
    fp->cnt = 0;
  }

  char *tmp = str;
  *tmp = '\0';
  while ( limit > fp->cnt && !nobuffer ) {
    strncpy( tmp, fp->ptr, fp->cnt );
    printf( "here 1\n" );
    tmp += fp->cnt;
    limit -= fp->cnt;
    fp->cnt = read( fp->fd, fp->base, bufsize );
    printf( "limit = %d, fp->cnt = %d, here 2\n", limit, fp->cnt );
    if ( fp->cnt < bufsize ) {
      /* end-of-file occured */
      printf( "here 3\n" );
      nobuffer = 1;
    }
    fp->ptr = fp->base;
  }
  if ( fp->cnt > 0 ) {
    printf( "here 4\n" );
    strncpy( tmp, fp->ptr, limit );
    *(tmp + limit) = '\0';
    fp->ptr += limit;
    fp->cnt -= limit;
    printf( "limit = %d, fp->cnt = %d, here 5\n", limit, fp->cnt );
    return str;
  } else {
    printf( "here 6\n" );
    fp->flag = tmpflag;
    fp->flag |= _EOF;
    return NULL;
  }
}

extern char *fileputs( char *str, File *fp ) {
  int size = strlen( str );
  if ( (fp->flag & (_EOF | _ERR | _WRITE)) != _WRITE ) {
    return NULL;
  }
  int bufsize = (fp->flag & _UNBUF) ? 1 : BUFSIZE;
  if ( fp->base == NULL ) {
    if ( (fp->base = (char *) malloc(bufsize)) == NULL ) {
      return NULL;
    }
    fp->ptr = fp->base;
    fp->cnt = bufsize;
  }
  if ( fp->cnt < bufsize && fp->cnt > 0 ) {
    write( fp->fd, fp->base, bufsize-fp->cnt );
    fp->ptr = fp->base;
    fp->cnt = bufsize;
  }
  char *tmp = str;
  while ( size > fp->cnt ) {
    strncpy( fp->ptr, tmp, fp->cnt );
    tmp += fp->cnt;
    size -= fp->cnt;
    write( fp->fd, fp->base, bufsize );
    fp->ptr = fp->base;
    fp->cnt = bufsize;
  }
  strncpy( fp->ptr, tmp, size );
  fp->ptr += size;
  fp->cnt -= size;
  return str;
}

extern int fileseek( File *fp, long offset, int origin ) {
  if ( (fp->flag & _ERR) != 0 ) {
    return -1;
  }
  int bufsize = ( fp->flag & _UNBUF ) ? 1 : BUFSIZE;
  if ( fp->cnt >= 0 && fp->cnt <= bufsize ) {
    if ( (fp->flag & _READ) != 0 ) {
      offset -= fp->cnt;
    } else if ( (fp->flag & _WRITE ) != 0 ) {
      offset -= (bufsize - fp->cnt);
    }
  }
  printf( "offset is %ld\n", offset );
  lseek( fp->fd, offset, origin );
  return 0;
}

#endif
