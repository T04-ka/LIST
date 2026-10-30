#include "list.h"


int free_elem_find(list_t* list_ptr);

int list_add_elem_after_current_index(list_t* list_ptr, int current_index, list_elem_t elem) {

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

    return 0;
}
