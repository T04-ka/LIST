#include "list.h"

#include <stdlib.h>
// проверка верификатора
//
// next == -1; prev != -1
//

int free_elem_find(list_t* list_ptr);
int free_elem_find(list_t* list_ptr) {

    // verif

    int i = 0;
    for (i = 0; i < list_ptr->capacity; i++) {

        if (list_ptr->next[i] == -1) {

           return i;
        }
    }

    // if net svobodnih => resize

    return 0;
}

//-----------------------------------------------------------------------------------------------------------------------------

int list_add_elem_after_current_index_and_return_array_pos(list_t* list_ptr, int current_index, list_elem_t elem) {

    // verif

    int next_index = free_elem_find(list_ptr);

    if (current_index == 0) {

        list_ptr->next[next_index] = list_ptr->tail;
        list_ptr->tail = next_index;
    }
    else {
        list_ptr->next[next_index] = list_ptr->next[current_index];
        list_ptr->next[current_index] = next_index;
    }

    list_ptr->data_buf[next_index] = elem;

    if (list_ptr->next[next_index] == 0) {

        list_ptr->head = next_index;
    }

    list_ptr->size++;
    return next_index;
}

//-----------------------------------------------------------------------------------------------------------------------------

void set_next_index(list_t* list_ptr, size_t index, int value) {

    // verif

    list_ptr->next[index] = value;
}

//-----------------------------------------------------------------------------------------------------------------------------
// TODO: убрть строки присваивания и сделать через функции
void list_pop_elem_after_pointed_with_current_index(list_t* list_ptr, int current_index, list_elem_t elem) {
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

    if (current_index == 0) {

        int next_index = list_ptr->next[list_ptr->tail];
        list_ptr->tail = list_ptr->next[next_index];
        list_ptr->next[next_index] = -1;
    }
    else {

        int current_next_index = list_ptr->next[current_index];
        list_ptr->next[current_index] = list_ptr->next[current_next_index];
        list_ptr->next[current_next_index] = -1;
    }

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

int change_value_of_list_elem_after_pointed_with_current_index(list_t* list_ptr, size_t index, int new_value) {

    // verif

    if (index >= list_ptr->size) {

        return 1; //error
    }

    int next_index = list_ptr->next[index];
    list_ptr->data_buf[next_index] = new_value;

    return 0;
}

//-----------------------------------------------------------------------------------------------------------------------------

int list_ctor(list_t* list_ptr, size_t nmemb) {

    // verif

    list_ptr->data_buf = (list_elem_t*) calloc(nmemb, sizeof(list_elem_t));
    list_ptr->next     = (int*) calloc(nmemb, sizeof(int));
    poizon_int_arr(list_ptr->next, nmemb);
    change_value_of_list_elem_after_pointed_with_current_index(list_ptr, 0, 0);
    list_ptr->head = 0;
    list_ptr->tail = 0;
    list_ptr->size = 0;

    return 0;
}

//-----------------------------------------------------------------------------------------------------------------------------

int list_dtor(list_t* list_ptr) {

    // verif

    free(list_ptr->data_buf);
    free(list_ptr->next);
    list_ptr->head = 0;
    list_ptr->tail = 0;
    list_ptr->size = 0;

    return 0;
}

//-----------------------------------------------------------------------------------------------------------------------------
#define LOG(FORMAT, ...) fprintf(stdout, FORMAT, ##__VA_ARGS__)
void list_dump(list_t* list_ptr) {
    //todo сделать под он дебаг принт в логфайл
    LOG("data %.5s", "");


}
