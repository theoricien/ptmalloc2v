#ifndef _X86_H
#define _X86_H

#define I386

#define __ADDR_SIZE 8
#define MIN_CHUNK_SIZE 8

// __GI___libc_malloc + OFFSET = &main_arena
#define OFF_MAIN_ARENA 0x15e8f0

/*
 * In 32 bits, size_t = unsigned int = 4 bytes.
 * And MALLOC_ALIGNEMENT == 2 * sizeof(size_t)
 * So logically, NSMALLBINS = 64 = (NSMALLBINS - MALLOC_ALIGNEMENT > 2 * sizeof(size_t))
 * So the min larg size of a large bin is of 64 * 8 = 512
 */
// (NSMALLBINS - SMALLBIN_CORRECTION) * SMALLBIN_WIDTH)
#define MIN_LARGE_SIZE 512

// Define the address type, we just can't read the referenced value
typedef int * addr_t;

#endif // _X86_H
