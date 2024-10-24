#ifndef _DYNARRAY_H
#define _DYNARRAY_H

/*
    dynarray.h by cdm ©August 2024

    A simple header-only macro-based implementation of a dynamic array of any specific type.
*/

#include <stdio.h>
#include <stdlib.h>

#define DEFINE_DYNAMIC_ARRAY(name, type)\
    typedef void* (*p_func) (type); /*value printing function*/ \
    typedef void* (*f_func) (type); /*value freeing function*/ \
    typedef struct{\
        type* items;\
        size_t size;\
        size_t capacity;\
    } name;\
    name* name##_create(size_t capacity){\
        name* d_array = (name*) malloc(sizeof(name));\
        if (d_array){\
            type* items = (type*) calloc(capacity, sizeof(type));\
            if (!items){\
                free(d_array);\
                return NULL;\
            }\
            d_array->items = items;\
            d_array->capacity = capacity;\
            d_array->size = 0;\
        }\
        return d_array;\
    }\
    int name##_push(name* d_array, type value){\
        if (!d_array || !d_array->items) return 1;\
        if (d_array->size >= d_array->capacity){\
            size_t new_capacity = d_array->capacity*2;\
            type* new_items = (type*) realloc(d_array->items, sizeof(type*)*new_capacity);\
            if (!new_items) return 1;\
            d_array->items = new_items;\
            d_array->capacity = new_capacity;\
        }\
        d_array->items[d_array->size++] = value;\
        return 0;\
    }\
    void name##_print(name* d_array, p_func func){\
        puts("[");\
        for (int i=0; i<d_array->size; ++i){\
            printf("    Index: % 3d : ", i);\
            if (func != NULL){\
                func(d_array->items[i]);\
                putchar('\n');\
            }\
            else{\
                printf("Value of type "#type"\n");\
            }\
        }\
        puts("]\n");\
    }\
    void name##_free(name* d_array, f_func func){\
        if (d_array){\
            if (d_array->items){\
                if (func != NULL){\
                    for (int i=0; i<d_array->size; ++i){\
                        func(d_array->items[i]);\
                    }\
                }\
                free(d_array->items);\
            }\
            free(d_array);\
        }\
    }

#endif // _DYNARRAY_H
