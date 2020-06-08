#include "ptassert.h"

void
ptassert (int 	     expr,
          const char * fmt,
          ...)
{
	if (!expr)
	{
		fprintf(stderr, "[AssertionError]: ");
		va_list arg;
        va_start(arg, fmt);
        vfprintf(stdout, fmt, arg);
        va_end(arg);
		exit(2);
	}
}

void
ptasserte (int expr)
{
	if (!expr)
	{
        printf("[Errno]: %s\n", strerror(errno));
        perror("[Perror]: ");
		exit(2);
	}
}
