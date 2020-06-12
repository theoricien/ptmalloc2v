#include <stdio.h>
#include <stdlib.h>
#include <dlfcn.h>
#include "heapview.h"

int
main (int   argc,
      char  * argv [])
{
    struct ptm2v_info * tmp = heap_init();

    int *a = malloc(sizeof(int));
    *a = 0x41424344;

    int *b = malloc(sizeof(int));
    *b = 0xAAAAAAAA;

    int *c = malloc(sizeof(int));
    *c = 0xBBBBBBBB;

    heap_view(tmp);
    // stuff

    print_chunk((long *)a);
    print_chunk((long *)b);
    print_chunk((long *)c);

    heap_end(&tmp);
    return EXIT_SUCCESS;
}
