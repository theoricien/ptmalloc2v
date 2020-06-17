#ifndef _STRUCTS_H
#define _STRUCTS_H

#include <stdio.h>
#include <stdlib.h>
#include "arch/config.h"

/* ptmalloc2 structs re-implementation from malloc.c source code */

// Useless in the code for the moment..
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

// arenas
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

    struct malloc_state * next;
    struct malloc_state * next_free;

    size_t  attached_threads;
    size_t  system_mem;
    size_t  max_system_mem;
};

// tcache
struct tcache_entry
{
    struct tcache_entry                 * next;
    struct tcache_perthread_struct      * key;
};

struct tcache_perthread_struct
{
    char counts[64];

    struct tcache_entry * entries[64];
};

/* own structs for easier representation & manipulation */

// Define the needed heap informations
struct ptm2v_info
{
    addr_t heap_base;                   // Base address of the heap, obtained by a sbrk(0)

    struct malloc_state * main_arena;   // main_arena struct, manage the heap globally
    struct tcache_perthread_struct * tcache; // Thread Local Cache structure, glibc >= 2.26

    void (*free) (struct ptm2v_info *); // function to free the struct itself
};

// flag_t is just for know if a flag is enable(y) or disable(n)
typedef enum {n = 0, y = 1} flag_t;

struct ptm2v_flags
{
    flag_t main_arena;          /* Print main_arena values */
    flag_t tcache;              /* Print tcache values */
    flag_t minimalist_arrays;   /* Print only if the array size is <= 10 */
    flag_t dump_heap;           /* Print from heap_base to main_arena->top */
    flag_t previsions;          /* Print the future value of a non-declared/defined variable like fd & bk on an allocated chunk */
};

#endif // _STRUCTS_H
