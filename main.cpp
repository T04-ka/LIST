#include <stdio.h>
#include "list.h"

int main() {

    list_t list = {};
    list_ctor(&list, 10);
    list_dump(&list);


    list_push_front(&list, 100);
    list_dump(&list);

    list_push_front(&list, 200);
    list_dump(&list);

    list_push_front(&list, 300);
    list_dump(&list);

    list_push_front(&list, 400);
    list_dump(&list);



    list_dtor(&list);
}
