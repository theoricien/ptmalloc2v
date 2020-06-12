#include "printer.h"

int
print_mem (addr_t addr,
           addr_t value)
{
    int res;

    res = printf("\t%p - %p\n", addr, value);
    return res;
}

void
print_malloc_chunk (struct malloc_chunk *chunk)
{
    printf("chunk = {\n\tmchunk_prev_size = %lu,\n\tmchunk_size = %lu,\n\tfd = %p,\n\tbk = %p,\n\tfd_nextsize = %p,\n\tbk_nextsize = %p\n}\n",
        chunk->mchunk_prev_size,
        chunk->mchunk_size,
        chunk->fd,
        chunk->bk,
        chunk->fd_nextsize,
        chunk->bk_nextsize);
}

void
print_malloc_state (struct malloc_state *state)
{
    printf("state = {\n\tmutex = %d,\n\tflags = %d,\n\thave_fastchunks = %d,\n\tfastbinsY[10] = ",
        state->mutex,
        state->flags,
        state->have_fastchunks);

    // state->fastbinsY
    printf("{");
    for (size_t i = 0; i < 10; i++)
    {
        printf("\n\t\t[%lu] = %p,", i, state->fastbinsY[i]);
    }
    printf("\n\t}");

    printf("\n\ttop = %p,\n\tlast_remainder = %p\n\tbins = ",
        state->top,
        state->last_remainder);

    // state->bins
    printf("{");
    for (size_t i = 0; i < 254; i++)
    {
        printf("\n\t\t[%lu] = %p,", i, state->bins[i]);
    }
    printf("\n\t}");

    printf("\n\tbinmap = ");

    // state->binmap
    printf("{");
    for (size_t i = 0; i < 4; i++)
    {
        printf("\n\t\t[%lu] = %u,", i, state->binmap[i]);
    }
    printf("\n\t}");

    printf("\n\tnext = %p,\n\tnext_free = %p,\n\tattached_threads = %lu,\n\tsystem_mem = %lu,\n\tmax_system_mem = %lu",
        state->next,
        state->next_free,
        state->attached_threads,
        state->system_mem,
        state->max_system_mem);

    printf("\n}\n");
}
