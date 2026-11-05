#include <stdio.h>
#include "list.h"

int main() {

    list_t list = {};
    list_ctor(&list, 10);



    list_dtor(&list);
}
