#ifndef _PRINTER_H
#define _PRINTER_H

#include <stdio.h>
#include "structs.h"

int print_mem (addr_t, addr_t);
void print_malloc_chunk (struct malloc_chunk *);
void print_malloc_state (struct malloc_state *);

#endif // _PRINTER_H
