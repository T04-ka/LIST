#include <stdio.h>
#include "list.h"
#include "myformat.cpp"
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


    FILE* html_file = fopen("list.html", "w");

    html_dump(&list, html_file);

    // png_dump(&list, "hui.png");

    fclose(html_file);


    list_dtor(&list);
}
