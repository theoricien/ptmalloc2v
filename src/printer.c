#include "printer.h"

int
print_mem (addr_t addr,
           addr_t value)
{
    int res;

    res = fprintf(__PRINTING_FILE, "\t%p - %p\n", addr, value);
    return res;
}

void
print_chunk (long *chunk)
{
    /* These variables are obtained from malloc.c documentation */
    long *real_chunk    = chunk - 1;
    int prev_inuse      = *real_chunk & 0x1;
    int is_mmapped      = *real_chunk & 0x2;
    int non_main_arena  = *real_chunk & 0x4;
    size_t size         = *real_chunk - 0x11;

    fprintf(__PRINTING_FILE, "%p\t[size: %lu, N: %d, M: %d, P: %d]\n",
        chunk,
        size,
        non_main_arena,
        is_mmapped,
        prev_inuse);

    for (size_t i = 0; i < size; i += sizeof(chunk))
    {
        fprintf(__PRINTING_FILE, "\t\t");
        fprintf(__PRINTING_FILE, "[0x%.*lx]", 16, chunk[i]);
        if (i == sizeof(chunk) * 0) fprintf(__PRINTING_FILE, " <= fd");
        if (i == sizeof(chunk) * 1) fprintf(__PRINTING_FILE, " <= bk");
        if (i == sizeof(chunk) * 2) fprintf(__PRINTING_FILE, " <= fd_nextsize");
        if (i == sizeof(chunk) * 3) fprintf(__PRINTING_FILE, " <= bk_nextsize");
        fprintf(__PRINTING_FILE, "\n");
    }
}

void
print_malloc_chunk (struct malloc_chunk *chunk)
{
    fprintf(__PRINTING_FILE, "chunk = {\n\tmchunk_prev_size = %lu,\n\tmchunk_size = %lu,\n\tfd = %p,\n\tbk = %p,\n\tfd_nextsize = %p,\n\tbk_nextsize = %p\n}\n",
        chunk->mchunk_prev_size,
        chunk->mchunk_size,
        chunk->fd,
        chunk->bk,
        chunk->fd_nextsize,
        chunk->bk_nextsize);
}

void
print_malloc_state (struct malloc_state * state,
                    flag_t              minimalist_arrays)
{
    fprintf(__PRINTING_FILE, "state = {\n\tmutex = %d,\n\tflags = %d,\n\thave_fastchunks = %d,\n\tfastbinsY[10] = ",
        state->mutex,
        state->flags,
        state->have_fastchunks);

    // state->fastbinsY
    fprintf(__PRINTING_FILE, "{");
    for (size_t i = 0; i < 10; i++)
    {
        fprintf(__PRINTING_FILE, "\n\t\t[%lu] = %p,", i, state->fastbinsY[i]);
    }
    fprintf(__PRINTING_FILE, "\n\t}");

    fprintf(__PRINTING_FILE, "\n\ttop = %p,\n\tlast_remainder = %p\n\tbins = ",
        state->top,
        state->last_remainder);

    // state->bins
    fprintf(__PRINTING_FILE, "{");
    if (minimalist_arrays)
    {
        fprintf(__PRINTING_FILE, "%p [254] ...", state->bins);
        fprintf(__PRINTING_FILE, "}");
    }
    else
    {
        for (size_t i = 0; i < 254; i++)
        {
            fprintf(__PRINTING_FILE, "\n\t\t[%lu] = %p,", i, state->bins[i]);
        }
        fprintf(__PRINTING_FILE, "\n\t}");
    }

    fprintf(__PRINTING_FILE, "\n\tbinmap = ");

    // state->binmap
    fprintf(__PRINTING_FILE, "{");
    for (size_t i = 0; i < 4; i++)
    {
        fprintf(__PRINTING_FILE, "\n\t\t[%lu] = %u,", i, state->binmap[i]);
    }
    fprintf(__PRINTING_FILE, "\n\t}");

    fprintf(__PRINTING_FILE, "\n\tnext = %p,\n\tnext_free = %p,\n\tattached_threads = %lu,\n\tsystem_mem = %lu,\n\tmax_system_mem = %lu",
        state->next,
        state->next_free,
        state->attached_threads,
        state->system_mem,
        state->max_system_mem);

    fprintf(__PRINTING_FILE, "\n}\n");
}
