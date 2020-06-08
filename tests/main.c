#include <stdio.h>
#include <stdlib.h>
#include "heapview.h"

int
main (int   argc,
      char  * argv [])
{
    struct ptm2v_info * tmp = heap_init();

    printf("MALLOC_RET: %p\n", malloc(4));
    heap_view(tmp);
    // stuff

    heap_end(&tmp);
    return EXIT_SUCCESS;
}
