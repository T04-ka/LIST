#include <stdio.h>
#include "list.h"

int main() {

    list_t list = {};
    list_ctor(&list, 10);

    list_dump(&list);

    list_push_elem_after_current_index_and_return_array_pos(&list, 0, 100);
    list_dump(&list);

    list_push_elem_after_current_index_and_return_array_pos(&list, 1, 200);
    list_dump(&list);

    list_push_elem_after_current_index_and_return_array_pos(&list, 2, 300);
    list_dump(&list);

    list_push_elem_after_current_index_and_return_array_pos(&list, 0, 400);
    list_dump(&list);

    list_pop_elem_after_pointed_with_current_index(&list, 1);
    list_dump(&list);

    list_dtor(&list);
}
