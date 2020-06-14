# How to use

The usage of this library is pretty easy, it is resumed in main 3 functions

## heap_init
Initial function, use only once and ALWAYS before any malloc/possible use of heap
### Prototype
```C
struct ptm2v_info * heap_init   (void);
```
### Usage example
Easiest and classic one
```C
struct ptm2v_info * info = heap_init();
```

## heap_view
The function that will print all the informations you want.
### Prototype
```C
int
heap_view (struct ptm2v_info	* info,                         // struct returned by heap_init
           struct ptm2v_flags   flags,                          // flags for customizable printing
           addr_t               * array_of_inuse_chunks,        // in-use chunks you want to print, NULL else
           size_t               len_array_of_inuse_chunks,      // length of the array above
           addr_t               * array_of_free_chunks,         // free chunks you want to print, NULL else
           size_t               len_array_of_free_chunks,       // length of the array above
           FILE                 * fd)                           // printing file, NULL/stdout for stdout

```

### Usage example
```C
heap_view(info, ONLY_CHUNKS, ptm2v_array(a, b, c, e, f), 5, NULL, 0, stdout);
```
```C
heap_view(info, ALL, ptm2v_array(a, b, c, e, f), 5, NULL, 0, stderr);
```
```C
struct pt2mv_flags flags = {1, 0, 1, 0, 1};
heap_view(info, flags, ptm2v_array(a, b, c, e, f), 5, NULL, 0, stdout);
```

## heap_end
That will just free all the content allocated by the structure and the structure itself
### Prototype
```C
void heap_end (struct ptm2v_info **);
```
### Usage example
You juste need to pass the address of your variable
```C
heap_end(&info);
```
