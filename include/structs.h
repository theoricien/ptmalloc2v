#ifndef _STRUCTS_H
#define _STRUCTS_H

extern const int __ADDR_SIZE;

typedef void * addr_t;

struct ptm2v_info
{
    addr_t heap_base;

    void (*free) (struct ptm2v_info *);
};

#endif // _STRUCTS_H
