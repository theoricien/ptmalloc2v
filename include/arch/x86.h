#ifndef _X86_H
#define _X86_H

#define I386

#define __ADDR_SIZE 8

// __GI___libc_malloc + OFFSET = &main_arena
#define OFF_MAIN_ARENA 0x15e8f0

// Define the address type, we just can't read the referenced value
typedef int * addr_t;

#endif // _X86_H
