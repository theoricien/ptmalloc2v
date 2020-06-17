#include "printer.h"

void
__print_indent (size_t indent)
{
        for (size_t i = 0; i < indent; i++)
                fprintf(__PRINTING_FILE, "\t");
}

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
        int non_main_arena      = *real_chunk & 0x4;
        size_t size             = *real_chunk - 0x11;

        *len = size;
        #ifdef AMD64
        if (size == 0) size = 0x10;
        fprintf(__PRINTING_FILE, "%p\t[.size: %lu, N: %d, M: %d, P: %d]\n",
                chunk,
                size,
                non_main_arena,
                is_mmapped,
                prev_inuse);
        #else
        #ifdef I386
        if (size == 0) size = 0x8;
        fprintf(__PRINTING_FILE, "%p\t[.size: %u, N: %d, M: %d, P: %d]\n",
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
                        if (i == 0) fprintf(__PRINTING_FILE, " <= .fd");
                        if (i == 1) fprintf(__PRINTING_FILE, " <= .bk");

                        if (size >= MIN_LARGE_SIZE)
                        {
                                if (i == 2) fprintf(__PRINTING_FILE, " <= .fd_nextsize");
                                if (i == 3) fprintf(__PRINTING_FILE, " <= .bk_nextsize");
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
                if (i == 0) fprintf(__PRINTING_FILE, " : .fd");
                if (i == 1) fprintf(__PRINTING_FILE, " : .bk");

                if (size >= MIN_LARGE_SIZE)
                {
                        if (i == 2) fprintf(__PRINTING_FILE, " : .fd_nextsize");
                        if (i == 3) fprintf(__PRINTING_FILE, " : .bk_nextsize");
                }
                fprintf(__PRINTING_FILE, "]\n");
        }
}

void
__print_tcache_entry (struct tcache_entry * entry,
                      struct ptm2v_info   * info,
                      flag_t              minimalist_arrays,
                      size_t              indent)
{
        // .next
        __print_indent(indent);
        fprintf(__PRINTING_FILE, ".next = %p", entry->next);
        if (entry->next >= info->heap_base &&
            entry->next <= info->main_arena->top)
        {
                fprintf(__PRINTING_FILE, " = {\n");
                __print_tcache_entry(entry->next, info, minimalist_arrays, indent + 1);
                __print_indent(indent);
                fprintf(__PRINTING_FILE, "}\n");
        } else
        { fprintf(__PRINTING_FILE, "\n"); }

        // .key
        __print_indent(indent);
        fprintf(__PRINTING_FILE, ".key = %p", entry->key);
        if (entry->key >= info->heap_base &&
            entry->key <= info->main_arena->top)
        {
                fprintf(__PRINTING_FILE, " = {\n");
                __print_tcache(entry->key, info, minimalist_arrays, indent + 1);
                __print_indent(indent);
                fprintf(__PRINTING_FILE, "}\n");
        } else
        { fprintf(__PRINTING_FILE, "\n"); }
}

void
__print_tcache (struct tcache_perthread_struct * tcache,
                struct ptm2v_info              * info,
                flag_t                         minimalist_arrays,
                size_t                         indent)
{
        if (tcache < info->heap_base ||
            tcache > info->main_arena->top)
        {
                __print_indent(indent);
                fprintf(__PRINTING_FILE, "%p,\n", tcache);
                return;
        }

        __print_indent(indent);
        fprintf(__PRINTING_FILE, "%p = {\n", tcache);
        if (minimalist_arrays)
        {
                __print_indent(indent + 1);
                fprintf(__PRINTING_FILE, ".counts = %p\n", tcache->counts);
                __print_indent(indent + 1);
                fprintf(__PRINTING_FILE, ".entries = %p\n", tcache->entries);
        }
        else
        {
                // .counts
                __print_indent(indent + 1);
                fprintf(__PRINTING_FILE, ".counts [%lu] = { ", sizeof(tcache->counts)/sizeof(tcache->counts[0]));
                for (size_t i = 0; i < sizeof(tcache->counts)/sizeof(tcache->counts[0]) - 1; i++)
                {
                        fprintf(__PRINTING_FILE, "%02x, ", (unsigned int) tcache->counts[i]);
                }
                fprintf(__PRINTING_FILE, "%02x", tcache->counts[sizeof(tcache->counts) - 1]);
                fprintf(__PRINTING_FILE, " }\n");

                // .entries
                __print_indent(indent + 1);
                fprintf(__PRINTING_FILE, ".entries = {\n");
                for (size_t i = 0; i < sizeof(tcache->entries)/sizeof(tcache->entries[0]); i++)
                {
                        if (tcache->entries[i] >= info->heap_base &&
                            tcache->entries[i] <= info->main_arena->top)
                        {
                                __print_indent(indent + 2);
                                fprintf(__PRINTING_FILE, "[%lu] %p = {\n", i, (addr_t) tcache->entries[i]);
                                __print_tcache_entry(tcache->entries[i], info, minimalist_arrays, indent + 3);
                                __print_indent(indent + 2);
                                fprintf(__PRINTING_FILE, "}\n");
                        }
                        else if (!minimalist_arrays)
                        {
                                __print_indent(indent + 2);
                                fprintf(__PRINTING_FILE, "[%lu] <skip>\n", i);
                        }
                }
                __print_indent(indent + 1);
                fprintf(__PRINTING_FILE, "}\n");
        }
        __print_indent(indent);
        fprintf(__PRINTING_FILE, "}\n");
}

void
print_tcache (struct ptm2v_info * info,
              flag_t            minimalist_arrays)
{
        __print_tcache(info->tcache, info, minimalist_arrays, 0);
}

void
print_malloc_state (struct malloc_state * state,
                    flag_t              minimalist_arrays)
{
        fprintf(__PRINTING_FILE, "%p = {\n\t.mutex = %d,\n\t.flags = %d,\n\t.have_fastchunks = %d,\n\t.fastbinsY[10] = ",
                state,
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

        fprintf(__PRINTING_FILE, "\n\t.top = %p,\n\t.last_remainder = %p\n\t.bins = ",
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

        fprintf(__PRINTING_FILE, "\n\t.binmap = ");

        // state->binmap
        fprintf(__PRINTING_FILE, "{");
        for (size_t i = 0; i < 4; i++)
        {
                fprintf(__PRINTING_FILE, "\n\t\t[%lu] = 0x%.*x - %u,", i, __ADDR_SIZE, state->binmap[i], state->binmap[i]);
        }
        fprintf(__PRINTING_FILE, "\n\t}");

        fprintf(__PRINTING_FILE, "\n\t.next = %p,\n\t.next_free = %p,\n\t.attached_threads = %lu,\n\t.system_mem = %lu,\n\t.max_system_mem = %lu",
                state->next,
                state->next_free,
                state->attached_threads,
                state->system_mem,
                state->max_system_mem);

        fprintf(__PRINTING_FILE, "\n}\n");
}
