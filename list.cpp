#include "list.h"
#define DEBUG
#include "myformat.cpp"

#include <stdlib.h>
// проверка верификатора
//
// next == -1; prev != -1
//

void set_current_indexed_elem_in_next(list_t* list_ptr, size_t cur_index, int new_value);
void set_current_indexed_elem_in_prev(list_t* list_ptr, size_t cur_index, int new_value);
void set_head(list_t* list_ptr, size_t value);
void set_tail(list_t* list_ptr, size_t value);
int get_current_indexed_elem_from_next(list_t* list_ptr, size_t index);
int get_current_indexed_elem_from_prev(list_t* list_ptr, size_t index);

size_t free_elem_find(list_t* list_ptr);
size_t free_elem_find(list_t* list_ptr) {

    // verif

    size_t i = 0;
    for (i = 0; i < list_ptr->capacity; i++) {

        if (list_ptr->next[i] == -1) {

           return i;
        }
    }

    // if net svobodnih => resize
    $;
    return 0;
}

//-----------------------------------------------------------------------------------------------------------------------------

size_t list_push_elem_in_current_index_and_return_array_pos(list_t* list_ptr, size_t current_index, list_elem_t elem) {

    // verif

    if (current_index == 0) {

        // ERROR
        return -1u;
    }

    size_t free_index = free_elem_find(list_ptr);

    size_t next_elem = get_current_indexed_elem_from_next(list_ptr, current_index);
    size_t prev_elem = get_current_indexed_elem_from_prev(list_ptr, current_index);

    if (current_index == get_head(list_ptr)) {

        /
    }

    if (current_index == get_tail(list_ptr)) {


    }


}

size_t list_push_elem_after_current_index_and_return_array_pos(list_t* list_ptr, size_t current_index, list_elem_t elem) {

    // verif

    size_t next_index = free_elem_find(list_ptr);
    $zu(next_index);

    if (current_index == 0) {

        set_current_indexed_elem_in_next(list_ptr, next_index, (int) get_tail(list_ptr));
        set_tail(list_ptr, next_index);
        set_current_indexed_elem_in_next(list_ptr, 0, (int) next_index);


    }
    else {
        set_current_indexed_elem_in_next(list_ptr, next_index, get_current_indexed_elem_from_next(list_ptr, current_index));
        set_current_indexed_elem_in_next(list_ptr, current_index, (int) next_index);
    }

    change_value_of_list_elem_after_pointed_with_current_index(list_ptr, (size_t) current_index, elem);

    if (get_current_indexed_elem_from_next(list_ptr, next_index) == 0) {

        set_head(list_ptr, next_index);
    }

    list_ptr->size++;
    return next_index;
}

//-----------------------------------------------------------------------------------------------------------------------------


void set_current_indexed_elem_in_next(list_t* list_ptr, size_t cur_index, int new_value) {

    // verif

    list_ptr->next[cur_index] = new_value;
}

//-----------------------------------------------------------------------------------------------------------------------------


void set_current_indexed_elem_in_prev(list_t* list_ptr, size_t cur_index, int new_value) {

    // verif

    list_ptr->prev[cur_index] = new_value;
}

//-----------------------------------------------------------------------------------------------------------------------------

void list_pop_elem_after_pointed_with_current_index(list_t* list_ptr, size_t current_index) {
    //
    // cur_next = next[current_index]
    // теперь next[current_index] = next[cur_next]
    // ставим -1 в массив next next[cur_next] = -1
    //
    // если cur_ind == 0
    // cur_next = next[tail]
    // теперь tail = next[current_index]
    // next[[tail]] = -1
    //
    // если next[cur_ind] == 0 - ошибка

    // verif

    size_t next_index = 0;
    if (current_index == 0) {

        next_index = get_tail(list_ptr);
        set_tail(list_ptr, (size_t) get_current_indexed_elem_from_next(list_ptr, next_index));
    }
    else {

        next_index = (size_t) get_current_indexed_elem_from_next(list_ptr, current_index);
    }

    set_current_indexed_elem_in_next(list_ptr, current_index, \
                                    get_current_indexed_elem_from_next(list_ptr, next_index));
    set_current_indexed_elem(list_ptr, next_index, 0);
    set_current_indexed_elem_in_next(list_ptr, next_index, -1);
    list_ptr->size--;
}

//-----------------------------------------------------------------------------------------------------------------------------

void poizon_int_arr(int* array, size_t n);
void poizon_int_arr(int* array, size_t n) {

    //verif

    for (size_t i = 0; i < n; i++) {

        array[i] = -1;
    }
}

//-----------------------------------------------------------------------------------------------------------------------------

int change_value_of_list_elem_after_pointed_with_current_index(list_t* list_ptr, size_t cur_index, list_elem_t new_value) {

    // verif

    int next_index = 0;
    if (cur_index == 0) {

        next_index = (int) get_tail(list_ptr);
    }
    else {

        next_index = get_current_indexed_elem_from_next(list_ptr, cur_index);
    }

    list_ptr->data_buf[next_index] = new_value;


    return 0;
}

//-----------------------------------------------------------------------------------------------------------------------------

int list_ctor(list_t* list_ptr, size_t nmemb) {

    // verif

    list_ptr->capacity = nmemb;
    list_ptr->data_buf = (list_elem_t*) calloc(nmemb, sizeof(list_elem_t));
    list_ptr->next     = (int*) calloc(nmemb, sizeof(int));
    list_ptr->prev     = (int*) calloc(nmemb, sizeof(int));
    poizon_int_arr(list_ptr->next, nmemb);
    poizon_int_arr(list_ptr->prev, nmemb);
    change_value_of_list_elem_after_pointed_with_current_index(list_ptr, 0, 69);
    set_current_indexed_elem_in_next(list_ptr, 0, 0);
    set_current_indexed_elem_in_prev(list_ptr, 0, 0);
    set_head(list_ptr, 0);
    set_tail(list_ptr, 0);
    list_ptr->size = 0;

    return 0;
}

//-----------------------------------------------------------------------------------------------------------------------------

int list_dtor(list_t* list_ptr) {

    // verif

    free(list_ptr->data_buf);
    free(list_ptr->next);
    free(list_ptr->prev);
    set_head(list_ptr, 0);
    set_tail(list_ptr, 0);
    list_ptr->size = 0;

    return 0;
}

//-----------------------------------------------------------------------------------------------------------------------------

void set_head(list_t* list_ptr, size_t val) {

    // verif

    list_ptr->head = val;
}

//-----------------------------------------------------------------------------------------------------------------------------

void set_tail(list_t* list_ptr, size_t val) {

    // verif

    list_ptr->tail = val;
}

//-----------------------------------------------------------------------------------------------------------------------------

size_t get_tail(list_t* list_ptr) {

   return list_ptr->tail;
}

//-----------------------------------------------------------------------------------------------------------------------------

size_t get_head(list_t* list_ptr) {

   return list_ptr->head;
}

//-----------------------------------------------------------------------------------------------------------------------------

int get_current_indexed_elem_from_next(list_t* list_ptr, size_t index) {

    return list_ptr->next[index];
}

//-----------------------------------------------------------------------------------------------------------------------------

int get_current_indexed_elem_from_prev(list_t* list_ptr, size_t index) {

    return list_ptr->prev[index];
}

//-----------------------------------------------------------------------------------------------------------------------------

list_elem_t get_current_indexed_elem(list_t* list_ptr, size_t index) {

    return list_ptr->data_buf[index];
}

//-----------------------------------------------------------------------------------------------------------------------------

void set_current_indexed_elem(list_t* list_ptr, size_t cur_index, list_elem_t value) {

    // verif

    list_ptr->data_buf[cur_index] = value;
}

//-----------------------------------------------------------------------------------------------------------------------------
#define LOG(FORMAT, ...) fprintf(stdout, FORMAT, ##__VA_ARGS__)
#define LOG_NLINE        fprintf(stdout, "\n")
#define LOG_FORMAT       fprintf(stdout, "===================================================================================\n")

void list_dump(list_t* list_ptr) {

    // verif

    LOG_FORMAT;
    LOG_NLINE;
    LOG(FAT "%29sLIST DUMP\n" DEF, "");
    LOG_NLINE;

    LOG("%5stail = %zu %5shead = %zu %5ssize = %zu %5scapacity = %zu\n", \
        "", list_ptr->tail, "", list_ptr->head, "", list_ptr->size, "", list_ptr->capacity);

    LOG_NLINE;

    LOG("%4s", "");
    for (size_t i = 0; i < list_ptr->capacity; i++) {

        LOG("%5zu", i);
    }
    LOG_NLINE;

    //todo сделать под он дебаг принт в логфайл
    LOG("data");
    for (size_t i = 0; i < list_ptr->capacity; i++) {
        // TODO: сделать универсальный под любой тип
        LOG("%5lg", list_ptr->data_buf[i]);
        //      ^
    }
    LOG_NLINE;


    LOG("next");
    for (size_t i = 0; i < list_ptr->capacity; i++) {

        LOG("%5d", list_ptr->next[i]);
    }
    LOG_NLINE;

    LOG("prev");
    for (size_t i = 0; i < list_ptr->capacity; i++) {

        LOG("%5d", list_ptr->prev[i]);
    }
    LOG_NLINE;


    LOG_NLINE;
    LOG_FORMAT;
    LOG_NLINE;
}
#undef LOG
#undef LOG_NLINE
