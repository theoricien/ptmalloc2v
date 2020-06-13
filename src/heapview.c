#include "heapview.h"

/**
 * heapview.c file regroup the 3 functions heap_init, heap_view and heap_end.
 * heap_init functions is here to retrieve informations about the heap, like
 * the start of the heap data, the static variables that we cannot access to
 * normally, and other stuff that catch heap informations.
 *
 * heap_view consist of display all informations about the current heap. The
 * goal of this function is to display the more pertinent information to the
 * less one, like displaying main_arena in first, and at the end display
 * macros values.
 *
 * heap_end is just free()-ing all the stuff allocated by heap_init.
 */

// From include/printer.h
extern FILE * __PRINTING_FILE;

struct ptm2v_info *
heap_init (void)
{
    struct ptm2v_info   * info;
    void                *(*r_malloc) (size_t);
    void                * heap_base;

    // As a default value
    __PRINTING_FILE = DEFAULT_PRINTING_FILE;

    // We get the base of the heap with that
    // DONT MALLOC BEFORE THIS
    heap_base = sbrk (0);
    ptasserte (heap_base != (void *) -1);

    // Get the real_malloc address (in libc mmapped region)
    r_malloc = NULL;
    r_malloc = dlsym(RTLD_NEXT, "malloc");
    ptassertdl(r_malloc != NULL);

    info = (struct ptm2v_info *) malloc (sizeof (struct ptm2v_info));
    ptasserte (info != NULL);

    printf("----> %p\n", r_malloc);
    printf("main_arena = r_malloc + 0x%x\n", OFF_MAIN_ARENA);
    info->main_arena    = r_malloc + OFF_MAIN_ARENA;
    info->heap_base     = heap_base;
    info->free          = _ptm2v_info_free;

    return info;
}

int
heap_view (struct ptm2v_info    * info,                 // struct returned by heap_init
           struct ptm2v_flags   flags,                  // flags for customizable printing
           addr_t               * array_of_chunks,     // chunks you want to print, NULL else
           size_t               len_array_of_chunks,    // length of the array above
           FILE                 * fd)                   // printing file, NULL/stdout for stdout
{
    int    err;

    if (fd != NULL)
        __PRINTING_FILE = fd;

    err = 0;

    // Dump the heap from info->heap_base to info->main_arena->top
    // (which is all the user heap dedicated area)
    if (flags.dump_heap)
    {
        for (long *i = info->heap_base;
             i < info->main_arena->top;
             i += 1) // incrementing the address
        {
            print_mem((addr_t)i, (addr_t)(*i));
        }
    }

    // Dump the main_arena variable
    if (flags.main_arena)
        print_malloc_state(info->main_arena, flags.minimalist_arrays);

    // Print all the chunks you refers to (from array_of_chunks argument)
    for (size_t i = 0; i < len_array_of_chunks; i++)
    {
        print_chunk(array_of_chunks[i]);
    }

    return err;
}

void
heap_end (struct ptm2v_info ** info)
{
    struct ptm2v_info *tmp = *info;
    tmp->free(tmp);
    free(tmp);
}

void
_ptm2v_info_free (struct ptm2v_info * info)
{
    /* nothing */
}
