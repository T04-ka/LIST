#include "list.h"
#include <algorithm>
#include <iterator>
#define DEBUG
#include "myformat.cpp"

#include <stdlib.h>
#include <string.h>

#define MAX_FILENAME_LEN 100

//-----------------------------------------------------------------------------------------------------------------------------
size_t list_push_elem_in_current_index_from_LEFT_and_return_array_pos(list_t* list_ptr, size_t current_index, list_elem_t elem);
//-----------------------------------------------------------------------------------------------------------------------------
size_t list_push_elem_in_current_index_from_RIGHT_and_return_array_pos(list_t* list_ptr, size_t current_index, list_elem_t elem);
//-----------------------------------------------------------------------------------------------------------------------------
void list_pop_elem_from_current_index(list_t* list_ptr, size_t current_index);
//-----------------------------------------------------------------------------------------------------------------------------

//-----------------------------------------------------------------------------------------------------------------------------
void set_current_indexed_elem_in_next(list_t* list_ptr, size_t cur_index, int new_value);
//-----------------------------------------------------------------------------------------------------------------------------
void set_current_indexed_elem_in_prev(list_t* list_ptr, size_t cur_index, int new_value);
//-----------------------------------------------------------------------------------------------------------------------------
int get_current_indexed_elem_from_next(list_t* list_ptr, size_t index);
//-----------------------------------------------------------------------------------------------------------------------------
int get_current_indexed_elem_from_prev(list_t* list_ptr, size_t index);
//-----------------------------------------------------------------------------------------------------------------------------
size_t free_elem_find(list_t* list_ptr);
//-----------------------------------------------------------------------------------------------------------------------------
void set_current_indexed_elem(list_t* list_ptr, size_t cur_index, list_elem_t value);
//-----------------------------------------------------------------------------------------------------------------------------
list_elem_t get_current_indexed_elem(list_t* list_ptr, size_t current_index);
//-----------------------------------------------------------------------------------------------------------------------------
list_err_n list_verifier(list_t* list_ptr);
//-----------------------------------------------------------------------------------------------------------------------------
void err_print(list_t* list_ptr, const char* _file, const char* _func, int _nline);
//-----------------------------------------------------------------------------------------------------------------------------
int find_next_free(list_t* list_ptr, int ptr);
//-----------------------------------------------------------------------------------------------------------------------------

#ifdef LIST_SANITIZE
#define LIST_OK(ERRT)   list_verifier(list_ptr);        \
                        $d(list_ptr->list_ok.errn); \
                        $; \
                        if (list_ptr->list_ok.errn) {   \
                                                        \
                            err_print(list_ptr, __FILE_NAME__, __PRETTY_FUNCTION__, __LINE__);        \
                            return ERRT;                \
                        }
#else
#define LIST_OK(ERRT)  void(0);
#endif
//-----------------------------------------------------------------------------------------------------------------------------

size_t list_push_elem_in_current_index_from_LEFT_and_return_array_pos(list_t* list_ptr, size_t current_index, list_elem_t elem) {

    LIST_OK(-1u);

    if (current_index == 0) {

        // error
        return -1u;
    }

    size_t free_index = free_elem_find(list_ptr);

    set_current_indexed_elem(list_ptr, free_index, elem);

    // size_t next_index = get_current_indexed_elem_from_next(list_ptr, current_index);
    size_t prev_index = (size_t) get_current_indexed_elem_from_prev(list_ptr, current_index);

    set_current_indexed_elem_in_next(list_ptr, free_index, (int) current_index);
    set_current_indexed_elem_in_prev(list_ptr, free_index, (int) prev_index);

    set_current_indexed_elem_in_next(list_ptr, prev_index, (int) free_index);
    set_current_indexed_elem_in_prev(list_ptr, current_index, (int) free_index);

    list_ptr->size ++;

    return free_index;
}

//-----------------------------------------------------------------------------------------------------------------------------

size_t list_push_elem_in_current_index_from_RIGHT_and_return_array_pos(list_t* list_ptr, size_t current_index, list_elem_t elem) {

    LIST_OK(-1u);
//     if (list_ptr->list_ok.errn) {
//
//         return -1u;
//     }

    size_t free_index = free_elem_find(list_ptr);

    set_current_indexed_elem(list_ptr, free_index, elem);

    size_t next_index = (size_t) get_current_indexed_elem_from_next(list_ptr, current_index);
    // size_t prev_index = get_current_indexed_elem_from_prev(list_ptr, current_index);

    set_current_indexed_elem_in_next(list_ptr, free_index, (int) next_index);
    set_current_indexed_elem_in_prev(list_ptr, free_index, (int) current_index);

    set_current_indexed_elem_in_next(list_ptr, current_index, (int) free_index);
    set_current_indexed_elem_in_prev(list_ptr, next_index, (int) free_index);

    list_ptr->size ++;

    return free_index;
}

//-----------------------------------------------------------------------------------------------------------------------------

void list_pop_elem_from_current_index(list_t* list_ptr, size_t current_index) {

    LIST_OK();


    if (current_index == 0) {

        // error
        return;
    }

    size_t prev_index = (size_t) get_current_indexed_elem_from_prev(list_ptr, current_index);
    size_t next_index = (size_t) get_current_indexed_elem_from_next(list_ptr, current_index);

    set_current_indexed_elem_in_prev(list_ptr, next_index, (int) prev_index);
    set_current_indexed_elem_in_next(list_ptr, prev_index, (int) next_index);

    set_current_indexed_elem(list_ptr, current_index, 0);
    set_current_indexed_elem_in_next(list_ptr, current_index, -1);
    set_current_indexed_elem_in_prev(list_ptr, current_index, -1);

    list_ptr->size --;
}

//-----------------------------------------------------------------------------------------------------------------------------

size_t list_insertl(list_t* list_ptr, size_t current_index, list_elem_t value) {

    return list_push_elem_in_current_index_from_LEFT_and_return_array_pos(list_ptr, current_index, value);
}

//-----------------------------------------------------------------------------------------------------------------------------

size_t list_insertr(list_t* list_ptr, size_t current_index, list_elem_t value) {

    return list_push_elem_in_current_index_from_RIGHT_and_return_array_pos(list_ptr, current_index, value);
}

//-----------------------------------------------------------------------------------------------------------------------------

size_t list_insert(list_t* list_ptr, size_t current_index, list_elem_t value) {

    return list_insertr(list_ptr, current_index, value);
}

//-----------------------------------------------------------------------------------------------------------------------------

void list_pop(list_t* list_ptr, size_t current_index) {

    list_pop_elem_from_current_index(list_ptr, current_index);
}

//-----------------------------------------------------------------------------------------------------------------------------

size_t list_push_front(list_t* list_ptr, list_elem_t value) {

    return list_push_elem_in_current_index_from_RIGHT_and_return_array_pos(list_ptr, get_head(list_ptr), value);
}

//-----------------------------------------------------------------------------------------------------------------------------

size_t list_push_back(list_t* list_ptr, list_elem_t value) {

    return list_push_elem_in_current_index_from_RIGHT_and_return_array_pos(list_ptr, 0, value);
}

//-----------------------------------------------------------------------------------------------------------------------------

size_t list_push_after(list_t* list_ptr, size_t current_index, list_elem_t value) {

    return list_push_elem_in_current_index_from_RIGHT_and_return_array_pos(list_ptr, \
            (size_t) get_current_indexed_elem_from_next(list_ptr, current_index), value);
}

//-----------------------------------------------------------------------------------------------------------------------------

size_t list_push_before(list_t* list_ptr, size_t current_index, list_elem_t value) {

    return list_push_elem_in_current_index_from_LEFT_and_return_array_pos(list_ptr, \
           (size_t) get_current_indexed_elem_from_prev(list_ptr, current_index), value);
}

//-----------------------------------------------------------------------------------------------------------------------------

void list_pop_front(list_t* list_ptr) {

    list_pop_elem_from_current_index(list_ptr, get_head(list_ptr));
}

//-----------------------------------------------------------------------------------------------------------------------------

void list_pop_back(list_t* list_ptr) {

    list_pop_elem_from_current_index(list_ptr, get_tail(list_ptr));
}

//-----------------------------------------------------------------------------------------------------------------------------

void set_elem(list_t* list_ptr, size_t current_index, list_elem_t value) {

    set_current_indexed_elem(list_ptr, current_index, value);
}

//-----------------------------------------------------------------------------------------------------------------------------

list_elem_t get_elem(list_t* list_ptr, size_t index) {

    return get_current_indexed_elem(list_ptr, index);
}

//-----------------------------------------------------------------------------------------------------------------------------

size_t free_elem_find(list_t* list_ptr) {

    LIST_OK(-1u);

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

void set_current_indexed_elem_in_next(list_t* list_ptr, size_t cur_index, int new_value) {

    // LIST_OK();

    list_ptr->next[cur_index] = new_value;
}

//-----------------------------------------------------------------------------------------------------------------------------


void set_current_indexed_elem_in_prev(list_t* list_ptr, size_t cur_index, int new_value) {

   // LIST_OK();

    list_ptr->prev[cur_index] = new_value;
}

//-----------------------------------------------------------------------------------------------------------------------------

void poizon_int_arr(int* array, size_t n);
void poizon_int_arr(int* array, size_t n) {

    for (size_t i = 0; i < n; i++) {

        array[i] = -1;
    }
}

//-----------------------------------------------------------------------------------------------------------------------------

void list_ctor(list_t* list_ptr, size_t nmemb) {

    list_ptr->capacity = nmemb;
    list_ptr->data_buf = (list_elem_t*) calloc(nmemb, sizeof(list_elem_t));
    list_ptr->next     = (int*) calloc(nmemb, sizeof(int));
    list_ptr->prev     = (int*) calloc(nmemb, sizeof(int));
    poizon_int_arr(list_ptr->next, nmemb);
    poizon_int_arr(list_ptr->prev, nmemb);
    set_current_indexed_elem(list_ptr, 0, 69);
    set_current_indexed_elem_in_next(list_ptr, 0, 0);
    set_current_indexed_elem_in_prev(list_ptr, 0, 0);
    list_ptr->size = 0;

    LIST_OK();
}

//-----------------------------------------------------------------------------------------------------------------------------

void list_dtor(list_t* list_ptr) {

    free(list_ptr->data_buf);
    free(list_ptr->next);
    free(list_ptr->prev);
    list_ptr->size = 0;
}

//-----------------------------------------------------------------------------------------------------------------------------

size_t get_tail(list_t* list_ptr) {

    LIST_OK(-1u);

    return (size_t) list_ptr->next[0];
    // return list_ptr->tail;
}

//-----------------------------------------------------------------------------------------------------------------------------

size_t get_head(list_t* list_ptr) {

    LIST_OK(-1u);
    // return list_ptr->Data
    return (size_t) list_ptr->prev[0];
}

//-----------------------------------------------------------------------------------------------------------------------------

int get_current_indexed_elem_from_next(list_t* list_ptr, size_t index) {

    LIST_OK(-2);

    return list_ptr->next[index];
}

//-----------------------------------------------------------------------------------------------------------------------------

int get_current_indexed_elem_from_prev(list_t* list_ptr, size_t index) {

    LIST_OK(-2);

    return list_ptr->prev[index];
}

//-----------------------------------------------------------------------------------------------------------------------------

list_elem_t get_current_indexed_elem(list_t* list_ptr, size_t index) {

    LIST_OK(NAN);

    return list_ptr->data_buf[index];
}

//-----------------------------------------------------------------------------------------------------------------------------

void set_current_indexed_elem(list_t* list_ptr, size_t cur_index, list_elem_t value) {

    // LIST_OK();

    list_ptr->data_buf[cur_index] = value;
}

//-----------------------------------------------------------------------------------------------------------------------------
// TODO: доделать
list_err_n list_verifier(list_t* list_ptr) {

    #ifdef LIST_SANITIZE
    if (list_ptr == NULL) {
        $;
        list_ptr->list_ok.errn = LIST_ERR_NULLPTR;
        return LIST_ERR_NULLPTR;
    }

    if (list_ptr->data_buf == NULL) {

        list_ptr->list_ok.errn = LIST_ERR_DATABUF_NULLPTR;
        return LIST_ERR_DATABUF_NULLPTR;
    }

    if (list_ptr->next == NULL) {

        list_ptr->list_ok.errn = LIST_ERR_NEXT_NULLPTR;
        return LIST_ERR_NEXT_NULLPTR;
    }

    if (list_ptr->prev == NULL) {

        list_ptr->list_ok.errn = LIST_ERR_PREV_NULLPTR;
        return LIST_ERR_PREV_NULLPTR;
    }

    if (list_ptr->size > list_ptr->capacity) {

        list_ptr->list_ok.errn = LIST_ERR_SIZE_GREATER_CAPACITY;
        return LIST_ERR_SIZE_GREATER_CAPACITY;
    }

//     if (list_ptr->head != list_ptr->prev[0]) {
//
//         list_ptr->list_ok.errn = LIST_ERR_WRONG_HEAD;
//         return LIST_ERR_WRONG_HEAD;
//     }
//
//     if (list_ptr->tail != list_ptr->next[0]) {
//
//         list_ptr->list_ok.errn = LIST_ERR_WRONG_TAIL;
//         return LIST_ERR_WRONG_TAIL;
//     }


    int counter = 0;
    int pointer = 0;

    while (counter < list_ptr->size) {

        if (list_ptr->next[pointer] == -1 || list_ptr->next[pointer] == 0) {

            list_ptr->list_ok.next_hole_pointer = pointer;
            list_ptr->list_ok.errn = LIST_ERR_NEXT_HOLE;
            return LIST_ERR_NEXT_HOLE; //TODO: сделать запоминание pointera где ошибка
        }

        pointer = list_ptr->next[pointer];

        counter++;
    }

    if (pointer != 0) {


        list_ptr->list_ok.next_hole_pointer = pointer;
        list_ptr->list_ok.errn = LIST_ERR_NULLPTR;
        return LIST_ERR_NEXT_HOLE;
    }


    counter = 0;
    pointer = 0;

    while (counter < list_ptr->size) {

        if (list_ptr->prev[pointer] == -1 || list_ptr->prev[pointer] == 0) {

            list_ptr->list_ok.prev_hole_pointer = pointer;
            list_ptr->list_ok.errn = LIST_ERR_NULLPTR;
            return LIST_ERR_PREV_HOLE; //TODO: сделать запоминание pointera где ошибка
        }

        pointer = list_ptr->prev[pointer];

        counter++;
    }

    if (pointer != 0) {

        list_ptr->list_ok.prev_hole_pointer = pointer;
        list_ptr->list_ok.errn = LIST_ERR_NULLPTR;
        return LIST_ERR_PREV_HOLE;
    }

    list_ptr->list_ok.errn = LIST_ERR_OK;
    #else
    void(0);
    #endif

    return LIST_ERR_OK;
}

//-----------------------------------------------------------------------------------------------------------------------------

void err_print(list_t* list_ptr, const char* _file, const char* _func, int _nline) {

    #ifdef LIST_SANITIZE
    fprintf(stderr, "On %s:%d in function %s Error: %d\n", _file, _nline, _func, list_ptr->list_ok.errn);
    #else
    void(0);
    #endif
}

//-----------------------------------------------------------------------------------------------------------------------------

#define LOG(FORMAT, ...) fprintf(stream, FORMAT, ##__VA_ARGS__)
#define LOG_NLINE        fprintf(stream, "\n")
#define LOG_FORMAT       fprintf(stream, "===================================================================================\n")

void list_dump(list_t* list_ptr, FILE* stream) {

    $;

    if (list_ptr == NULL) {

        $err("ZZZ");
    }
    LIST_OK();
    $;
    LOG_FORMAT;
    LOG_NLINE;
    LOG(FAT "%29sLIST DUMP\n" DEF, "");
    LOG_NLINE;

    LOG("%5stail = %zu %5shead = %zu %5ssize = %zu %5scapacity = %zu\n", \
        "", get_tail(list_ptr), "", get_head(list_ptr), "", list_ptr->size, "", list_ptr->capacity);

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

//-----------------------------------------------------------------------------------------------------------------------------

int html_dump(list_t* list_ptr, FILE* html_file) {

    if (html_file == NULL) {

        fprintf(stderr, RED FAT "HTML FILE NULLPTR\n" DEF);
        return 1;
    }

    fprintf(html_file, "<!DOCTYPE html>\n");
    fprintf(html_file, "<html>\n");
    fprintf(html_file, "<head>\n");
    fprintf(html_file, "    <meta charset=\"US-ASCII\">\n");
    fprintf(html_file, "    <title>LIST DUMP</title>\n");
    fprintf(html_file, "</head>\n");
    fprintf(html_file, "<body>\n");
    fprintf(html_file, "    <p style=\"font-family: monospace;\">\n        ");

    png_dump(list_ptr, "dump4html.png");

    fprintf(html_file, " DED_LOH\n");
    fprintf(html_file, "    < -- Image insert -->\n");
    fprintf(html_file, "    <img src=\"dump4html.png\" alt=\"graph.png\" style=\"max-width: 100%%; height: auto;\"><br>\n");

    fprintf(html_file, "\n    </p>\n");
    fprintf(html_file, "</body>\n");
    fprintf(html_file, "</html>\n");

    printf("HTML dump was writed succesfully.\n");

    return 0;
}

//-----------------------------------------------------------------------------------------------------------------------------

int png_dump(list_t* list_ptr, const char* png_name) {

    FILE* png_f = fopen(png_name, "w");

    dot_file_generate(list_ptr, "yashapidor.dot");

    char system_command[MAX_FILENAME_LEN * 2] = "dot -Tpng yashapidor.dot -o ";
    strncat(system_command, png_name, MAX_FILENAME_LEN);
    strcat(system_command, " ; rm yashapidor.dot");

    int errn = system(system_command);
    fclose(png_f);

    if (errn == -1) {

        fprintf(stderr, FAT "ERROR: running dot script fault.\n" DEF);
        return 1;
    }

    printf("PNG dump was created successfully.\n");

    return 0;
}

//-----------------------------------------------------------------------------------------------------------------------------

#define WRITE_DOT(FORMAT, ...) fprintf(dot_file, FORMAT, ##__VA_ARGS__)

int dot_file_generate(list_t* list_ptr, const char* dot_file_name) {

    FILE* dot_file = fopen(dot_file_name, "w");

    WRITE_DOT("digraph G { \n\n\trankdir = LR;\n\tsplines = true;\n\n\tsubgraph cluster_occupied {\n\n\t\tstyle=invis;\n\n");

    WRITE_DOT("\t\tnode0 [shape=record, style=filled, fillcolor=\"cyan\", height=.1, label=\""  \
        "{ { <prev> • | prev = %zu} | {system | index = 0} | { <next> • | next = %zu} }\"];\n",
                       get_head(list_ptr),                               get_tail(list_ptr));

    for (unsigned i = 1; i < list_ptr->capacity; i++) {

        if (list_ptr->next[i] == -1) {

            continue;
        }

        WRITE_DOT("\t\tnode%u [shape=record, height=.1, label=\""                                                                  \
            "{ { <prev> • | prev = %i} | {val = %lg | index = %u} | { <next> • | next = %i} }\"];\n",                              \
                      i,  get_current_indexed_elem_from_prev(list_ptr, i),                                                         \
                                        get_current_indexed_elem(list_ptr, i),                                                     \
                                                    i,                         get_current_indexed_elem_from_next(list_ptr, i));   \
    }

    WRITE_DOT("\n");

    int pointer = 0;
    for (unsigned i = 0; i < list_ptr->size; i++) {

        int next_pointer = list_ptr->next[pointer];
        WRITE_DOT("\t\tnode%d -> node%d [style=invis, weight=100];\n", pointer, list_ptr->next[pointer]);

        pointer = next_pointer;
    }

    WRITE_DOT("\n");

    for (unsigned i = 0; i <= list_ptr->size; i++) {

        int next_pointer = list_ptr->next[pointer];
        WRITE_DOT("\t\tnode%d:next -> node%d:prev [dir=both];\n", pointer, list_ptr->next[pointer]);

        pointer = next_pointer;
    }

    WRITE_DOT("\n\t\tHEAD [shape=record, style = filled, fillcolor=\"yellow\"];\n\t\tTAIL [shape=record, style = filled, fillcolor=\"yellow\"];\n\n");
    WRITE_DOT("\t\t{rank=same; node%zu; TAIL;}\n\t\t{rank=same; node%zu; HEAD;}\n\t}\n\n", \
                               get_tail(list_ptr),              get_head(list_ptr));

    WRITE_DOT("\tsubgraph cluster_free {\n\n\t\tstyle=invis;\n\n");

    for (unsigned i = 1; i < list_ptr->capacity; i++) {

        if (list_ptr->next[i] != -1) {

            continue;
        }

        WRITE_DOT("\t\tnode%u [shape=record, style=filled, fillcolor=\"lightgray\", height=.1, label=\""                         \
          "{ { <prev> • | prev = %d} | {FREE | index = %u} | { <next> • | next = %d} }\"];\n",                                   \
                            i,   get_current_indexed_elem_from_prev(list_ptr, i),                                                \
                                               i,                         get_current_indexed_elem_from_next(list_ptr, i));
    }

    WRITE_DOT("\n");

    for (pointer = 0; (unsigned) pointer < list_ptr->capacity; pointer++) {

        if (list_ptr->next[pointer] != -1) {

            continue;
        }

        int next_pointer = find_next_free(list_ptr, pointer + 1);

        if (next_pointer == -1) {

            break;
        }

        WRITE_DOT("\t\tnode%d -> node%d [style=invis, weight=100];\n", \
                       pointer,  next_pointer);
    }

    pointer = find_next_free(list_ptr, 0);
    WRITE_DOT("\t}\n\n\tnode0 -> node%d [style=invis];\n}", pointer);

    fclose(dot_file);

    printf("DOT file was created successfully.\n");
    return 0;
}

#undef WRITE_DOT

//-----------------------------------------------------------------------------------------------------------------------------


int find_next_free(list_t* list_ptr, int ptr) {

    while ((size_t) ptr < list_ptr->capacity) {

        if (list_ptr->next[ptr] == -1) {

            return ptr;
        }

        ptr++;
    }

    return -1;
}
