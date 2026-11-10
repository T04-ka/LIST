#include <stdio.h>
#include "list.h"
#include "myformat.cpp"
int main() {

    list_t list = {};
    list_ctor(&list, 10);



    list_dump(&list);

    list_add_front(&list, 100);
    list_dump(&list);

    list_add_front(&list, 200);
    list_dump(&list);

    list_add_front(&list, 300);
    list_dump(&list);

    list_add_front(&list, 400);
    list_dump(&list);

    list_del(&list, 2);
    list_dump(&list);


    FILE* html_file = fopen("list.html", "w");

    html_dump(&list, html_file, "1");

    html_dump(&list, html_file, "2"),
    // png_dump(&list, "hui.png");

    fclose(html_file);


    list_dtor(&list);
}
