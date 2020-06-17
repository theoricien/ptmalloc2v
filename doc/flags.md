# Flags and Pre-defined Flags

This will teach you how to use easily the `heap_view`function

## What the code shows us

(from `include/structs.h`)
```C
// flag_t is just for know if a flag is enable(y) or disable(n)
typedef enum {n = 0, y = 1} flag_t;

struct ptm2v_flags
{
    flag_t main_arena;          /* Print main_arena values */
    flag_t tcache;              /* Print tcache values */
    flag_t minimalist_arrays;   /* Print only if the array size is <= 10 */
    flag_t dump_heap;           /* Print from heap_base to main_arena->top */
    flag_t previsions;          /* Print the future value of a non-declared/defined variable like fd & bk on an allocated chunk */
};
```

(from `include/libptm2v.h`)
```C
const struct ptm2v_flags DEFAULT_FLAGS = {1, 1, 1, 0, 0};
const struct ptm2v_flags ALL_FLAGS     = {1, 1, 0, 1, 1};
const struct ptm2v_flags ONLY_CHUNKS   = {0, 0, 0, 0, 0};
```

Easy to understand, there is a structure for all the flags, they are commented, and we have constants that don't need to be explicitly commented.

## Usage Example

This is two examples for flag usage

```C
// With constants
#include <ptm2v/libptm2v.h>

// ...
heap_view (info_struct, ONLY_CHUNKS, NULL, 0, ptm2v_array (chunk0, chunk 1), 2, stdout);
```

```C
// By hand
#include <ptm2v/libptm2v.h>

struct ptm2v_flags flags = {1, 0, 0, 1};
heap_view (info_struct, flags, NULL, 0, ptm2v_array (chunk0, chunk 1), 2, stdout);
```
