/**
 * simio.c
 * implementation of simio.h
 */
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <stdlib.h>
#include "simio.h"

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

extern int _fillbuf( FILE *fp ) {
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

extern int _flushbuf( char ch, FILE *fp ) {
  int n, bufsize;
  char *tmp;

  if ( (fp->flag & (_READ|_WRITE|_EOF|_ERR)) != (_READ|_WRITE) ) {
    return -1;
  }
  bufsize = (fp->flag & _UNBUF) ? 1 : BUFSIZE;

  if ( (fp->flag & _READ) != 0 ) {
    /* this file is open for reading */
    tmp = (char *) malloc( bufsize );
    /*
     * if the buffer is empty, then we fill it reading data from
     * file. If not, then we need to read data up to the buffer is
     * full
     */
    if ( fp->cnt <= 0 ) {
      fp->cnt = read( fp->fd, fp->base, bufsize );
      fp->ptr = fp->base;
      return 0; /* we are done */
    }
    /* 
     * the buffer is not empty, we need to fil it.
     * the problem is that we can not override the previous bytes in buffer.
     * so we need a auxillary buffer.
     * the strategy is that copy the remaining bytes into another buffer.
     * then read needed bytes into original buffer
     */
    /* first copy the remaing bytes into auxillary buffer */
    strncpy( tmp, fp->ptr, fp->cnt );
    n = read( fp->fd, fp->base, bufsize - fp->cnt );
    strncpy( tmp + fp->cnt, fp->base, n );

    /* re-initialize the fields */
    fp->cnt += n;
    /* release the old buffer, and make it point to tmp */
    free( fp->base );
    fp->base = tmp;
    fp->ptr = fp->base;
    return 0;
  }
  if ( (fp->flag & _WRITE) != 0 ) {
    if ( fp->cnt > 0 && fp->cnt < bufsize) {
      /* the buffer is not empty, write it to file */
      n = bufsize - fp->cnt;
      if ( n != write( fp->fd, fp->ptr, n) ) {
	return -1;
      }
    }
    fp->cnt = bufsize - 1;
    fp->ptr = fp->base;
    *fp->ptr++ = ch;
  }
  return 0;
}

extern int fclose( FILE *fp ) {
  if ( (fp->flag & (_EOF | _ERR)) != 0 ) {
    return -1; /* error occured */
  }
  int bufsize = (fp->flag & _UNBUF) ? 1 : BUFSIZE;
  if ( (fp->flag & _WRITE) != 0 ) {
    int n = bufsize - fp->cnt;
    if ( n != write( fp->fd, fp->base, n ) ) {
      return -1;
    }
  }
  free( fp->base );
  fp->cnt = bufsize;
  fp->ptr = NULL;
  fp->base = NULL;
  fp->flag = 0;
  close( fp->fd );
  return 0;
}


extern int fflush( FILE *fp ) {
  return 0;
}

extern char *fgets( char *str, int limit, FILE *fp ) {
  if ( (fp->flag & (_EOF | _ERR | _READ)) != _READ ) {
    return NULL;
  }
  int bufsize = (fp->flag & _UNBUF) ? 1 : BUFSIZE;
  char *tmp = str;
  while ( limit > fp->cnt ) {
    strncpy( tmp, fp->ptr, fp->cnt );
    tmp += fp->cnt;
    limit -= fp->cnt;
    fp->cnt = read( fp->fd, fp->base, bufsize );
    fp->ptr = fp->base;
  }
  strncpy( tmp, fp->ptr, limit );
  tmp += limit;
  *tmp = '\0';
  fp->ptr += limit;
  fp->cnt -= limit;
  return str;
}

extern char *fputs( char *str, FILE *fp ) {
  int size = strlen( str );
  if ( (fp->flag & (_EOF | _ERR | _WRITE)) != _WRITE ) {
    return NULL;
  }
  int bufsize = (fp->flag & _UNBUF) ? 1 : BUFSIZE;
  char *tmp = str;
  while ( size > fp->cnt ) {
    strncpy( fp->ptr, tmp, fp->cnt );
    tmp += fp->cnt;
    size -= fp->cnt;
    write( fp->fd, fp->base, fp->cnt );
    fp->ptr = fp->base;
    fp->cnt = bufsize;
  }
  strncpy( fp->ptr, tmp, size );
  fp->ptr += size;
  fp->cnt -= size;
  return str;
}

extern int fseek( FILE *fp, long offset, int origin ) {
  return 0;
}
