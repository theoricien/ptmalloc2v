#ifndef _PRINTER_H
#define _PRINTER_H

#include <stdio.h>
#include <stdlib.h>
#include "structs.h"
#include "arch/config.h"

/*
 * printer.h header file consist of
 * different type of printing for better
 * code comprehension
 */

// Yes.. this is a global.. I don't want to have a lot of useless arguments
FILE * __PRINTING_FILE;

// Print a memory cell: [address, value]
int print_mem (addr_t, addr_t);

// Print an allocated chunk with future fd & bk value if needed
void print_inuse_chunk (addr_t, flag_t);

// Print the usual free chunk as described in malloc.c
void print_free_chunk (addr_t);

// Print the malloc_state structure with flag_t flag for printing bins[254]
void print_malloc_state (struct malloc_state *, flag_t);

#endif // _PRINTER_H
