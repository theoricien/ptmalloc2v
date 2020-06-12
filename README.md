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
heap_view(struct ptm2v_info *): Print everything, in the future there'll be some constants and just binary-OR them to get the results you want, like "heap_view(info, MAIN_ARENA | BINS_ALL | ...);"
`
#
`
heap_end(struct ptm2v_info *): Just free properly what's in the structure
`

## ! Warning !

For the moment, the library isn't installing hisself.  
The Makefile is only for tests/ programs.  
In the future, you'll juste need to do a `make` to install everything.

## Installation

```bash
git clone https://github.com/theoricien/ptmalloc2v
```

## Example (from tests/main.c)

```C
#include <stdio.h>
#include <stdlib.h>
#include "heapview.h"

int
main (int   argc,
      char  * argv [])
{
    // Init stuff
    struct ptm2v_info * tmp = heap_init();

    // code
    heap_view(tmp);
    // code

    // End/free stuff
    heap_end(&tmp);

    return EXIT_SUCCESS;
}
```
