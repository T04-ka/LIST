#ifndef LIST_H
#define LIST_H

#define LIST_SANITIZE

#ifdef LIST_SANITIZE
#define ONDEBUG(...) __VA_ARGS__
#else
#define ONDEBUG(...)
#endif

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#ifndef list_elem_t
typedef double list_elem_t;
#endif

enum list_err_n
{
    LIST_ERR_OK                     = 0,
    LIST_ERR_NULLPTR                = 1,
    LIST_ERR_DATABUF_NULLPTR        = 2,
    LIST_ERR_NEXT_NULLPTR           = 3,
    LIST_ERR_PREV_NULLPTR           = 4,
    LIST_ERR_SIZE_GREATER_CAPACITY  = 5,
    LIST_ERR_WRONG_HEAD             = 6,
    LIST_ERR_WRONG_TAIL             = 7,
    LIST_ERR_NEXT_HOLE              = 8,
    LIST_ERR_PREV_HOLE              = 9,
};

struct list_err_t
{
    list_err_n errn;
    int hole_pointer;
};

struct list_t
{
    list_elem_t* data_buf;
    int* next;
    int* prev;

    size_t capacity;
    size_t size;
    size_t head;
    size_t tail;

    ONDEBUG(list_err_t list_ok;)
};


//-----------------------------------------------------------------------------------------------------------------------------

int list_ctor(list_t* list_ptr, size_t nmemb);

//-----------------------------------------------------------------------------------------------------------------------------

int list_dtor(list_t* list_ptr);

//-----------------------------------------------------------------------------------------------------------------------------

size_t get_tail(list_t* list_ptr);

//-----------------------------------------------------------------------------------------------------------------------------

size_t get_head(list_t* list_ptr);

//-----------------------------------------------------------------------------------------------------------------------------

void set_elem(list_t* list_ptr, size_t cur_index, list_elem_t value);

//-----------------------------------------------------------------------------------------------------------------------------

list_elem_t get_elem(list_t* list_ptr, size_t index);

//-----------------------------------------------------------------------------------------------------------------------------

void list_dump(list_t* list_ptr);

//-----------------------------------------------------------------------------------------------------------------------------

size_t list_insertl(list_t* list_ptr, size_t current_index, list_elem_t value);

//-----------------------------------------------------------------------------------------------------------------------------

size_t list_insertr(list_t* list_ptr, size_t current_index, list_elem_t value);

//-----------------------------------------------------------------------------------------------------------------------------

size_t list_insert(list_t* list_ptr, size_t current_index, list_elem_t value);

//-----------------------------------------------------------------------------------------------------------------------------

void list_pop(list_t* list_ptr, size_t current_index);

//-----------------------------------------------------------------------------------------------------------------------------

size_t list_push_front(list_t* list_ptr, list_elem_t value);

//-----------------------------------------------------------------------------------------------------------------------------

size_t list_push_back(list_t* list_ptr, list_elem_t value);

//-----------------------------------------------------------------------------------------------------------------------------

void list_pop_front(list_t* list_ptr);

//-----------------------------------------------------------------------------------------------------------------------------

void list_pop_back(list_t* list_ptr);

//-----------------------------------------------------------------------------------------------------------------------------

size_t list_push_after(list_t* list_ptr, size_t current_index, list_elem_t value);

//-----------------------------------------------------------------------------------------------------------------------------

size_t list_push_before(list_t* list_ptr, size_t current_index, list_elem_t value);

//-----------------------------------------------------------------------------------------------------------------------------

void make_list_dump(list_t* list_ptr, const char* dot_filename, const char* png_filename);

//-----------------------------------------------------------------------------------------------------------------------------

#endif
