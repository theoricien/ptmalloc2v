#include "utils.h"

/*
 * This function is used to return an array of (long **)
 * because in C we can't do a foo({e0, e1, ..., en}) array
 * definition, so "do" this function
 */
long **
ptm2v_array (long * e0,
             ...)
{
    long    ** arr;
    size_t  len;
    va_list ei;

    len = sizeof(long *);
    arr = (long **) malloc (len);
    va_start(ei, e0);

    // Put in the array, and reallocate for the next iteration
    for (size_t i = 0; e0 != NULL; i++, e0 = va_arg(ei, long *))
    {
        arr[i] = e0;
        len += sizeof(long *);
        arr = (long **) realloc (arr, len);
    }
    va_end(ei);

    return arr;
}
