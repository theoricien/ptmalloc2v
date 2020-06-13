#ifndef _PRINTER_H
#define _PRINTER_H

#include <stdio.h>
#include <stdlib.h>
#include "structs.h"

// Yes.. this is a global.. I don't want to have a lot of useless arguments
FILE * __PRINTING_FILE;

int print_mem (addr_t, addr_t);
void print_chunk (long *);
void print_malloc_chunk (struct malloc_chunk *);
void print_malloc_state (struct malloc_state *, flag_t);

#endif // _PRINTER_H
