#ifndef LIST_H
#define LIST_H

#ifdef LIST_SANITIZE
#define ONDEBUG(...) ##__VA_ARGS__
#else
#define ONDEBUG(...) void(0)
#endif

#include <stdio.h>

#ifndef list_elem_t
typedef double list_elem_t;
#endif

struct list_t
{
    list_elem_t* data_buf;
    int* next;
    // size_t* prev;

    int size;
    int head;
    int tail;
};

#endif
