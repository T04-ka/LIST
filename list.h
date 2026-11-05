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

    int capacity;
    int size;
    int head;
    int tail;
};




int list_add_elem_after_current_index_and_return_array_pos(list_t* list_ptr, int current_index, list_elem_t elem);
void list_pop_elem_after_pointed_with_current_index(list_t* list_ptr, int current_index, list_elem_t elem);
int change_value_of_list_elem_after_pointed_with_current_index(list_t* list_ptr, size_t index, int new_value);
int list_ctor(list_t* list_ptr, size_t nmemb);
int list_dtor(list_t* list_ptr);

#endif
