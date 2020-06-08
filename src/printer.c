#include "printer.h"

int
print_mem (addr_t addr,
           addr_t value)
{
    int res;

    res = printf("\t%p - %p\n", addr, value);
    return res;
}
