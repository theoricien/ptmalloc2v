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
        fprintf(stderr, "[Errno]: %s\n", strerror(errno));
        perror("[Perror]: ");
		exit(2);
	}
}

void
ptassertdl (int expr)
{
	if (!expr)
	{
        fprintf(stderr, "[DLError]: %s\n", dlerror(errno));
		exit(2);
	}
}