#ifndef _STRUCTS_H
#define _STRUCTS_H

#include <stdio.h>
#include <stdlib.h>

extern const int __ADDR_SIZE;

typedef void * addr_t;

/* ptmalloc2 structs re-implementation */

struct malloc_chunk
{
    size_t  mchunk_prev_size;
    size_t  mchunk_size;

    struct malloc_chunk *fd;
    struct malloc_chunk *bk;
    struct malloc_chunk *fd_nextsize;
    struct malloc_chunk *bk_nextsize;
};

typedef struct malloc_chunk *mfastbinptr;
typedef struct malloc_chunk *mchunkptr;

struct malloc_state
{
    int             mutex;
    int             flags;
    int             have_fastchunks;
    mfastbinptr     fastbinsY[10];
    mchunkptr       top;
    mchunkptr       last_remainder;
    mchunkptr       bins[254];
    unsigned int    binmap[4];

    struct malloc_state *next;
    struct malloc_state *next_free;

    size_t  attached_threads;
    size_t  system_mem;
    size_t  max_system_mem;
};

/* own structs for easier representation & manipulation */

struct ptm2v_info
{
    addr_t heap_base;

    struct malloc_state * main_arena;

    void (*free) (struct ptm2v_info *);
};

typedef enum {n = 0, y = 1} flag_t;

struct ptm2v_flags
{
    flag_t main_arena;          /* Print main_arena values */
    flag_t minimalist_arrays;   /* Print only if the array size is <= 10 */
    flag_t dump_heap;           /* Print from heap_base to main_arena->top */
};

#endif // _STRUCTS_H
