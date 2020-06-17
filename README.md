# ptmalloc2v

ptmalloc2v is a tool for those who like to use printf function to debug their code.  
This little library is really simple to use and just print some heap info.  
  
## Installation

```bash
git clone https://github.com/theoricien/ptmalloc2v
sudo make install && make
```  
Your `.a` file will be in `libs/` directory.

## Usage

You can refer to `doc/` directory, there is some useful explainations about the library  
The principle is simple, there are 3 functions: `heap_init`, `heap_view` and `heap_end`:  
`heap_init` needs to be call before any use of the heap  
`heap_view` can be used undefinitely to print heap content you want  
`heap_end` is optional, but free the ptm2v_info structure properly  

## Example

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
    heap_view(tmp, DEFAULT_FLAGS, NULL, 0, NULL, 0, stdout);
    // code

    // End/free stuff
    heap_end(&tmp);

    return EXIT_SUCCESS;
}
```
