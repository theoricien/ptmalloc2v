#include "printer.h"

void
__print_indent (size_t indent)
{
        for (size_t i = 0; i < indent; i++)
                fprintf(__PRINTING_FILE, "\t");
}

// indented print format
void
ivprintf (size_t     indent,
          const char * fmt,
          ...)
{
        va_list args;
        char * new_fmt;

        __print_indent(indent);
        va_start(args, fmt);
        new_fmt = multi_fmt(fmt);
        vfprintf(__PRINTING_FILE, new_fmt, args);
        va_end(args);
        free(new_fmt);
}

void
print_mem (addr_t addr,
           addr_t value)
{
        ivprintf(0, "\t%.*p - %.*p\n", __ADDR_SIZE, addr, __ADDR_SIZE, value);
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
        if (size < MIN_CHUNK_SIZE) size = MIN_CHUNK_SIZE;
        ivprintf(0, "%p\t[.size: %lu, N: %d, M: %d, P: %d]\n",
                chunk,
                size,
                non_main_arena,
                is_mmapped,
                prev_inuse);
}

void
print_inuse_chunk (addr_t chunk,
                   flag_t prevision)
{
        size_t  size;

        print_chunk_header(chunk, &size);
        for (size_t i = 0; i < size/sizeof(chunk); i += 1)
        {
                ivprintf(2, "[0x%.*lx]", __ADDR_SIZE, chunk[i]);
                // Future values of undefined variables
                if (prevision)
                {
                        if (i == 0) ivprintf(0, " <= .fd");
                        if (i == 1) ivprintf(0, " <= .bk");

                        if (size >= MIN_LARGE_SIZE)
                        {
                                if (i == 2) ivprintf(0, " <= .fd_nextsize");
                                if (i == 3) ivprintf(0, " <= .bk_nextsize");
                        }
                }
                ivprintf(0, "\n");
        }
}

void
print_free_chunk (addr_t chunk)
{
        size_t  size;

        print_chunk_header(chunk, &size);
        for (size_t i = 0; i < size/sizeof(chunk); i += 1)
        {
                ivprintf(2, "[0x%.*lx", __ADDR_SIZE, chunk[i]);
                if (i == 0) ivprintf(0, " : .fd");
                if (i == 1) ivprintf(0, " : .bk");

                if (size >= MIN_LARGE_SIZE)
                {
                        if (i == 2) ivprintf(0, " : .fd_nextsize");
                        if (i == 3) ivprintf(0, " : .bk_nextsize");
                }
                ivprintf(0, "]\n");
        }
}

void
__print_tcache_entry (struct tcache_entry * entry,
                      struct ptm2v_info   * info,
                      flag_t              minimalist_arrays,
                      size_t              indent)
{
        // .next
        ivprintf(indent, ".next = %p", entry->next);
        if (entry->next >= info->heap_base &&
            entry->next <= info->main_arena->top)
        {
                ivprintf(0, " = {\n");
                __print_tcache_entry(entry->next, info, minimalist_arrays, indent + 1);
                ivprintf(indent, "}\n");
        } else
        { ivprintf(0, "\n"); }

        // .key
        ivprintf(indent, ".key = %p", entry->key);
        if (entry->key >= info->heap_base &&
            entry->key <= info->main_arena->top)
        {
                ivprintf(0, " = {\n");
                __print_tcache(entry->key, info, minimalist_arrays, indent + 1);
                ivprintf(indent, "}\n");
        } else
        { ivprintf(0, "\n"); }
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
                ivprintf(indent, "%p,\n", tcache);
                return;
        }

        ivprintf(indent, "%p = {\n", tcache);
        if (minimalist_arrays)
        {
                ivprintf(indent + 1, ".counts = %p\n", tcache->counts);
                ivprintf(indent + 1, ".entries = %p\n", tcache->entries);
        }
        else
        {
                // .counts
                ivprintf(indent + 1, ".counts [%lu] = { ", sizeof(tcache->counts)/sizeof(tcache->counts[0]));
                for (size_t i = 0; i < sizeof(tcache->counts)/sizeof(tcache->counts[0]) - 1; i++)
                {
                        ivprintf(0, "%02x, ", (unsigned int) tcache->counts[i]);
                }
                ivprintf(0, "%02x", tcache->counts[sizeof(tcache->counts) - 1]);
                ivprintf(0, " }\n");

                // .entries
                ivprintf(indent + 1, ".entries = {\n");
                for (size_t i = 0; i < sizeof(tcache->entries)/sizeof(tcache->entries[0]); i++)
                {
                        if (tcache->entries[i] >= info->heap_base &&
                            tcache->entries[i] <= info->main_arena->top)
                        {
                                ivprintf(indent + 2, "[%lu] %p = {\n", i, (addr_t) tcache->entries[i]);
                                __print_tcache_entry(tcache->entries[i], info, minimalist_arrays, indent + 3);
                                ivprintf(indent + 2, "}\n");
                        }
                        else if (!minimalist_arrays)
                        {
                                ivprintf(indent + 2, "[%lu] <skip>\n", i);
                        }
                }
                ivprintf(indent + 1, "}\n");
        }
        ivprintf(indent, "}\n");
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
        ivprintf(0, "%p = {\n\t.mutex = %d,\n\t.flags = %d,\n\t.have_fastchunks = %d,\n\t.fastbinsY[10] = ",
                state,
                state->mutex,
                state->flags,
                state->have_fastchunks);

        // state->fastbinsY
        ivprintf(0, "{\n");
        for (size_t i = 0; i < 10; i++)
        {
                ivprintf(2, "[%lu] = %p,\n", i, state->fastbinsY[i]);
        }
        ivprintf(1, "}\n");

        ivprintf(1, ".top = %p,\n\t.last_remainder = %p\n\t.bins = ",
                state->top,
                state->last_remainder);

        // state->bins
        ivprintf(0, "{");
        if (minimalist_arrays)
                ivprintf(0, "%p [254] ...}", state->bins);
        else
        {
                for (size_t i = 0; i < 254; i++)
                {
                        ivprintf(0, "\n\t\t[%lu] = %p,", i, state->bins[i]);
                }
                ivprintf(0, "\n\t}");
        }

        ivprintf(0, "\n\t.binmap = ");

        // state->binmap
        ivprintf(0, "{");
        for (size_t i = 0; i < 4; i++)
        {
                ivprintf(0, "\n\t\t[%lu] = 0x%.*x - %u,", i, __ADDR_SIZE, state->binmap[i], state->binmap[i]);
        }
        ivprintf(0, "\n\t}");

        ivprintf(0, "\n\t.next = %p,\n\t.next_free = %p,\n\t.attached_threads = %lu,\n\t.system_mem = %lu,\n\t.max_system_mem = %lu",
                state->next,
                state->next_free,
                state->attached_threads,
                state->system_mem,
                state->max_system_mem);

        ivprintf(0, "\n}\n");
}
