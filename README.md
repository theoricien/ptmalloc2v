# ptmalloc2v

ptmalloc2v is a tool for those who like to use printf function to debug their code.  
This little library is really simple to use and just print some heap info.  
  
There are 3 functions:  
#
`
heap_init() -> struct ptm2v_info *: Just initialize and setup everything to get all the informations before any malloc
`
#
`
heap_view(struct ptm2v_info *, struct ptm2v_flag, long **chunks, size_t len_chunks, FILE *fd):
It is the very big function that print all the data you want to print"
`
#
`
heap_end(struct ptm2v_info *): Just free properly what's in the structure
`

## Installation

```bash
git clone https://github.com/theoricien/ptmalloc2v
make
```  
Your `.a` file will be in `libs/` directory.

## Example (from tests/main.c)

```C
#include <stdio.h>
#include <stdlib.h>
#include "libptm2v.h"

int
main (int   argc,
      char  * argv [])
{
    // Init stuff
    struct ptm2v_info * tmp = heap_init();

    // code
    heap_view(tmp, DEFAULT_FLAGS, NULL, 0, stdout);
    // code

    // End/free stuff
    heap_end(&tmp);

    return EXIT_SUCCESS;
}
```
