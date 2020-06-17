#ifndef _LIBPTM2V_H
#define _LIBPTM2V_H

#include "heapview.h"

/*
struct ptm2v_flags
{
    flag_t main_arena;          Print main_arena values
    flag_t tcache;              Print tcache values
    flag_t minimalist_arrays;   Print only if the array size is <= 10
    flag_t dump_heap;           Print from heap_base to main_arena->top
    flag_t previsions;          Print the future value of a non-declared/defined variable like fd & bk on an allocated chunk
}
*/

const struct ptm2v_flags DEFAULT_FLAGS = {1, 1, 1, 0, 0};
const struct ptm2v_flags ALL_FLAGS     = {1, 1, 0, 1, 1};
const struct ptm2v_flags ONLY_CHUNKS   = {0, 0, 0, 0, 0};

#endif // _LIBPTM2V_H
