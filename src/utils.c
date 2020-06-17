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

/* Replace in string all occurence of from by to */
char *
strreplace (char * string,
            char * from,
            char * to)
{
        char    * res; // The new string to return
        size_t  i, k;  // Indexs
        size_t  occ;   // Occurence
        size_t  from_len = strlen(from);
        size_t  to_len   = strlen(to);

        // Searching the right new length
        // How many times "from" occurs ?
        occ = 0;
        for (i = 0; string[i] != '\0'; i++)
        {
                // if i is at a "from"
                if (strstr (&string[i], from) == &string[i])
                {
                        occ++;
                        // we can skip the word
                        i += from_len - 1;
                }
        }

        res = (char *) malloc (i + occ * (to_len - from_len) + 1);
        ptasserte (res != NULL);

        // Replace "from" by "to"
        for (i = 0, k = 0; string[k] != '\0'; i++, k++)
        {
                if (strstr (&string[k], from) == &string[k])
                {
                        // The great function !
                        strcpy(&res[i], to);
                        i += to_len - 1;
                        k += from_len - 1;
                } else
                        res[i] = string[k];
        }
        res[i] = '\0';

        return  res;
}

/*
 * This function is used to return a char *
 * that represent the right printf string format
 * made for the current bit system representation
 */
char *
multi_fmt (const char * fmt)
{
        char * res;

#ifdef AMD64
        res = strreplace((char *) fmt, "%u", "%lu");
#else // I386
        res = strreplace((char *) fmt, "%lu", "%u");
#endif // AMD64

        return  res;
}
