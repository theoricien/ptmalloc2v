#ifndef _X86_64_H
#define _X86_64_H

#define AMD64

#define __ADDR_SIZE 16

// __GI___libc_malloc + OFFSET = &main_arena
#define OFF_MAIN_ARENA 0x1378f0

// Define the address type, we just can't read the referenced value
typedef long * addr_t;

#endif // _X86_64_H
