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


// __GI___libc_malloc - &main_arena
#define OFF_MAIN_ARENA -0x1378f0

struct ptm2v_info *
heap_init (void)
{
    struct ptm2v_info   * info;
    void                * heap_base;

    heap_base = sbrk (0);
    ptasserte (heap_base != (void *) -1);

    info = (struct ptm2v_info *) malloc (sizeof (struct ptm2v_info));
    ptasserte (info != NULL);

    info->heap_base = heap_base;
    info->free      = _ptm2v_info_free;

    return info;
}

int
heap_view (struct ptm2v_info * info)
{
    int    err;
    void   *(*r_malloc) (size_t);
    long   *main_arena;

    char buf[65];
    fgets(buf, 65, stdin);

    err = 0;
    r_malloc = NULL;
    r_malloc = dlsym(RTLD_NEXT, "malloc");
    ptassertdl(r_malloc != NULL);

    main_arena = r_malloc + OFF_MAIN_ARENA;
    printf("malloc: %p\nmain_arena: %p\n", r_malloc, main_arena);
    for (int i = 0; i < 10; i++)
        printf("*main_arena+%d = 0x%08lx\n", i, main_arena[i]);
/*    for (addr_t ptr = info->heap_base; ptr < info->heap_base + 1000; ptr += sizeof(addr_t))
    {
        print_mem(ptr, (addr_t) *(long long *)ptr);
    }*/

    return err;
}

void
heap_end (struct ptm2v_info ** info)
{
    struct ptm2v_info *tmp = *info;
    tmp->free(tmp);
    free(info);
}

void
_ptm2v_info_free (struct ptm2v_info * info)
{
    /* nothing ftm */
}
