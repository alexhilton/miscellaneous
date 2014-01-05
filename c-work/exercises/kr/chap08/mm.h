/**
 * mm.h
 * interface of memory management.
 * along with simple implemmentation of malloc and free of 
 * standard library.
 */
#ifndef _mm_h
#define _mm_h

typedef long Align; /* for alignment to long boundary */

union header {
  struct {
    union header *next; /* next block if on free list */
    unsigned size; /* size of this block */
  } s;
  Align x; /* force alignment of blocks */
};

typedef union header Header;

/**
 * func: mymalloc
 * param: nbytes -- the number of bytes requested.
 * return: pointer of void type to memory block
 * desc: general-purpose storage allocator
 */ 
void *mymalloc( unsigned nbytes );

/**
 * func: myfree
 * param: next -- void type pointer to memory block
 * return: void
 * desc: put block of memory pointed by next back to Operating system
 */
void myfree( void *ap );

/* ex0808.c */
/**
 * func: bfree
 * param: n -- number of bytes
 * param: p -- pointer to n-byte block
 * return:
 * desc: free an arbitrary block p of n characters into the free list maintained
 * by mymalloc and myfree.
 */
void bfree( char *p, unsigned n );
#endif /* mm.h */
