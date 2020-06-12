#include <stdio.h>
#include <stdlib.h>
#include <dlfcn.h>
#include "heapview.h"

int
main (int   argc,
      char  * argv [])
{
    struct ptm2v_info * tmp = heap_init();

    heap_view(tmp);
    // stuff

    heap_end(&tmp);
    return EXIT_SUCCESS;
}
