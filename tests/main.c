#include <stdio.h>
#include <stdlib.h>
#include <dlfcn.h>

#include "libptm2v.h"

int
main (int   argc,
      char  * argv [])
{
    struct ptm2v_info * tmp = heap_init();

    int *a = malloc(4);
    *a = 0x41424344;

    int *b = malloc(8);
    *b = 0xAAAAAAAA;

    int *e = malloc(16);

    int *c = malloc(32);
    for (int i = 0; i < 32/sizeof(int); i++)
    {
        c[i] = 0xBBBBBBBB;
    }

    int *f = malloc(64);

    heap_view(tmp, ALL_FLAGS, ptm2v_array(a, b, c, e, f), 5, NULL, 0, stdout);

    heap_end(&tmp);
    return EXIT_SUCCESS;
}
