#include "heapview.h"

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

    err = 0;
    for (addr_t ptr = info->heap_base; ptr < info->heap_base + 1000; ptr += sizeof(addr_t))
    {
        print_mem(ptr, (addr_t) *(long long *)ptr);
    }

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
