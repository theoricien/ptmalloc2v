#include "printer.h"

int
print_mem (addr_t addr,
           addr_t value)
{
        int res;

        res = fprintf(__PRINTING_FILE, "\t0x%.*x - 0x%.*x\n", __ADDR_SIZE, addr, __ADDR_SIZE, value);
        return res;
}

void
print_chunk_header (addr_t chunk,
                    size_t * len)
{
        /* These variables are obtained from malloc.c documentation */
        long *real_chunk        = chunk - 1;
        int prev_inuse          = *real_chunk & 0x1;
        int is_mmapped          = *real_chunk & 0x2;
        int non_main_arena  = *real_chunk & 0x4;
        size_t size                 = *real_chunk - 0x11;

        *len = size;
        #ifdef AMD64
        if (size == 0) size = 0x10;
        fprintf(__PRINTING_FILE, "%p\t[size: %lu, N: %d, M: %d, P: %d]\n",
                chunk,
                size,
                non_main_arena,
                is_mmapped,
                prev_inuse);
        #else
        #ifdef I386
        if (size == 0) size = 0x8;
        fprintf(__PRINTING_FILE, "%p\t[size: %u, N: %d, M: %d, P: %d]\n",
                chunk,
                size,
                non_main_arena,
                is_mmapped,
                prev_inuse);
        #endif // I386
        #endif // AMD64
}

void
print_inuse_chunk (addr_t chunk,
                   flag_t prevision)
{
        size_t  size;

        print_chunk_header(chunk, &size);
        for (size_t i = 0; i < size/sizeof(chunk); i += 1)
        {
                fprintf(__PRINTING_FILE, "\t\t");
                fprintf(__PRINTING_FILE, "[0x%.*lx]", __ADDR_SIZE, chunk[i]);
                // Future values of undefined variables
                if (prevision)
                {
                        if (i == 0) fprintf(__PRINTING_FILE, " <= fd");
                        if (i == 1) fprintf(__PRINTING_FILE, " <= bk");
                        
                        if (size >= MIN_LARGE_SIZE)
                        {
                                if (i == 2) fprintf(__PRINTING_FILE, " <= fd_nextsize");
                                if (i == 3) fprintf(__PRINTING_FILE, " <= bk_nextsize");
                        }
                }
                fprintf(__PRINTING_FILE, "\n");
        }
}

void
print_free_chunk (addr_t chunk)
{
        size_t  size;

        print_chunk_header(chunk, &size);
        for (size_t i = 0; i < size/sizeof(chunk); i += 1)
        {
                fprintf(__PRINTING_FILE, "\t\t");
                fprintf(__PRINTING_FILE, "[0x%.*lx", __ADDR_SIZE, chunk[i]);
                if (i == 0) fprintf(__PRINTING_FILE, " : fd");
                if (i == 1) fprintf(__PRINTING_FILE, " : bk");

                if (size >= MIN_LARGE_SIZE)
                {
                        if (i == 2) fprintf(__PRINTING_FILE, " : fd_nextsize");
                        if (i == 3) fprintf(__PRINTING_FILE, " : bk_nextsize");
                }
                fprintf(__PRINTING_FILE, "]\n");
        }
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
                fprintf(__PRINTING_FILE, "\n\t\t[%lu] = 0x%.*x - %u,", i, __ADDR_SIZE, state->binmap[i], state->binmap[i]);
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
