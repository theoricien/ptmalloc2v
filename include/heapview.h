#ifndef _HEAPVIEW_H
#define _HEAPVIEW_H

// For RTLD_NEXT
#define _GNU_SOURCE

// For malloc, free
#include <stdlib.h>

// For NULL
#include <stdio.h>
#include <unistd.h>

// For dlsym() 
#include <dlfcn.h>

#include "ptassert.h"
#include "printer.h"
#include "structs.h"

struct ptm2v_info * heap_init   (void);
int                 heap_view   (struct ptm2v_info *);
void                heap_end    (struct ptm2v_info **);

void _ptm2v_info_free (struct ptm2v_info *);

#endif // _HEAPVIEW_H
