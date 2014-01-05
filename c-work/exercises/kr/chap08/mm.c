/**
 * mm.c
 * implementation of memory storage interface mm.h
 */
#include <stdlib.h>
#include <stdio.h>
#include "mm.h"

#define NALLOC 1024 /* minimum number of units to request */
#define MAX_MEMORY (1024 * 1024 * 1024)

static Header base; /* empty list to get started */
static Header *freep = NULL; /* start of free list */

/**
 * func: morecore
 * param: nu -- number of bytes requested
 * return: pointer to memory blocked
 * desc: ask system for more memory
 */
static Header *morecore( unsigned nu );

void *mymalloc( unsigned nbytes ) {
  Header *p, *prevp;

  /* check plausibility of size of ap */
  if ( nbytes <= 0 || nbytes > MAX_MEMORY ) {
    printf( "error in mymalloc: bad  requeste size: %u\n", nbytes );
    return NULL;
  }
  
  /*
   * Because of alignment, the number of bytes allocated must be integer
   * multiple of sizeof(Header) which is the number of bytes forced to
   * alignment. First part is to calculate how many units we need. +1 is for the
   * header itself.
   */
  unsigned nunits = (nbytes+sizeof(Header)-1) / sizeof(Header) + 1;
  if ( (prevp = freep) == NULL ) { /* no free list yet */
    /* start from base and do some initializations */
    base.s.next = freep = prevp = &base;
    base.s.size = 0;
  }

  for ( p = prevp->s.next; ; prevp = p, p = p->s.next ) {
    if ( p->s.size >= nunits ) { /* big enough */
      if ( p->s.size == nunits ) { /* exactly */
	prevp->s.next = p->s.next;
      } else { /* allocate tail end */
	/*
	 * If we found a bigger block, we cut the requested block from end in
	 * order to reduce fragement.
	 */
        /* p is the current node, we minus requested size */
	p->s.size -= nunits;
	/* now we change p into header of returned block */
	p += p->s.size;
	p->s.size = nunits;
      }
      freep = prevp;
      return (void *) (p + 1 );
    }
    if ( p == freep ) { /* wrapped around free list */
      if ( (p = morecore( nunits )) == NULL ) {
	return NULL; /* none left */
      }
    }
  }
}

void myfree( void *ap ) {
  Header *bp, *p;

  /* check plausibility of size of ap */
  bp = (Header *) ap - 1; /* points back to header */
  if ( bp->s.size < 0 || bp->s.size > MAX_MEMORY ) {
    printf( "error in myfree: bad  requeste size: %u\n", bp->s.size );
    return;
  }
  /*
   * This will spin bp back to a sizeof(Header) rather than a byte 
   * after releasing, the header of ap should be freed too by combining it to
   * its neighbors
   */
  /*
   * For return a block whose header is bp, we can put it anywhere. But to keep
   * it homogenous, we have to make the addresses in increasing order. As a
   * result we have to put bp in rightful position in the list. We have to
   * insert bp between its neighbors which one of them is lower than bp and the
   * other is higher than bp. If p is any header in list, we have to found such
   * a p, which p < bp < p->next. Of couse, you cannot forget abnormal
   * condition, such as bp < freep or bp > last, where start or end are better
   * place to put bp.
   * When we found bp > p && bp < p->s.next, then we quit the searching, because
   * we have found the proper position for bp
   */
  for ( p = freep; !(bp > p && bp < p->s.next); p = p->s.next ) {
    /*
     * when in the list(not at start or end), p is lower than p->next or p <
     * p->next. If p is at end, then p > p->next; when p is to base and there is
     * no blocks yet(only a base exists), p == p->next.
     */
    if ( p >= p->s.next && (bp > p || bp < p->s.next) ) {
      break; /* freed block at start or end of arena */
    }
  }

  /* now */
  if ( bp + bp->s.size == p->s.next ) { /* join to upper neighbor */
    /*
     * block led by bp is right-down adjacent to p->s.next, as a result, we
     * merge it into p->next. (or merge p->next into bp, which is more precise)
     */
    bp->s.size += p->s.next->s.size;
    bp->s.next = p->s.next->s.next;
  } else {
    /* there are no right-down adjacent, just joint block into list */
    bp->s.next = p->s.next;
  }

  if ( p + p->s.size == bp ) { /* join to lower neighbor */
    /*
     * Block is left-up adjacent to p, merge block into p
     */
    p->s.size += bp->s.size;
    p->s.next = bp->s.next;
  } else {
    /* not left-up adjacent, joint block into list */
    p->s.next = bp;
  }
  freep = p;
}

static Header *morecore( unsigned nu ) {
  char *cp;
  Header *up;

  if ( nu < NALLOC ) {
    nu = NALLOC;
  }
  /*
   * we should have used system version of memory request function, but we don't
   * know which one to use and which header includes it. So here we use C's.
   */
  //cp = sbrk( nu * sizeof( Header ) );
  cp = malloc( nu * sizeof( Header ) );
  /* 
   * cp == NULL might be a better solution 
   * but with that, we have a compatibility problem, because different system
   * has different NULL definition
   */
  if ( cp == (char *) -1 ) { /* no space at all */
    return NULL;
  }
  /*
   * the following codes are obscure, which take some thinking to comprehend
   * cp is allocated in the unit of Header, so cp points to a bunch of Header
   * objects. Thus casting up with (Header *)cp is leagal and has no flaws.
   * Also, we can access up's field, since we have allocate space for it.
   */
  up = (Header *) cp;
  up->s.size = nu;
  /*
   * We got a big block memory from system is the same to release a block. We
   * use function free to insert it in the right place
   */
  myfree( (void *)(up + 1) );
  return freep;
}


void bfree( char *p, unsigned n ) {
  /* first we need to check whether n is enough for a unit */
  if ( n < sizeof( Header ) ) {
    return; /* too small to be useful */
  }
  /* first we need to convert n bytes into aligned units */
  Header *hp = (Header *) p;
  /* fill field size with available number of units */
  /*
   * this seems impossible, size(=sizeof( Header )) bytes of memory is enough to
   * hold a structure Header, but it is not a struture, so we cannot access its
   * fields.
   * Here taught us a lesson: it is easy and possible to cast one type pointer
   * into another. But that does not make sense and work all the time. You have
   * to make yourself understood each pointer's type. block of n bytes cannot be
   * used as a structure though a structure needs n bytes too.
   * This is a problem which we need to make clear.
   */
  //hp->s.size = n / sizeof( Header );
  free( (void *)(hp + 1) );
}
