#include "utils.h"

/*
 * This function is used to return an array of (long **)
 * because in C we can't do a foo({e0, e1, ..., en}) array
 * definition, so "do" this function
 */
addr_t *
ptm2v_array (addr_t e0,
             ...)
{
    addr_t  * arr;
    size_t  len;
    va_list ei;

    len = sizeof(addr_t);
    arr = (addr_t *) malloc (len);
    va_start(ei, e0);

    // Put in the array, and reallocate for the next iteration
    for (size_t i = 0; e0 != NULL; i++, e0 = va_arg(ei, long *))
    {
        arr[i] = e0;
        len += sizeof(addr_t);
        arr = (addr_t *) realloc (arr, len);
    }
    va_end(ei);

    return arr;
}
