#ifndef ORDEREDARRAY_H_INCLUDED
#define ORDEREDARRAY_H_INCLUDED

/*STRUCTURES DEFINITION*/

/*Pointer to function. HOW the array will compare two generic elements*/
typedef int (*CompareFunc)(void* a, void* b);
typedef void (*PrintFunc)(void* data);

typedef struct{
    void** data;
    int counter;
    int capacity;
    CompareFunc compare;
}OrderedArray;

/*FUNCTION PROTOTYPES*/

OrderedArray* oa_create(int capacity, CompareFunc compare_func);
void oa_free(OrderedArray* arr);
void* oa_find_binary(OrderedArray* arr, void* data_to_find);
int oa_insert_sorted(OrderedArray* arr, void* data);
void oa_print(OrderedArray* arr, PrintFunc print_func);
void* oa_remove(OrderedArray* arr, void* data_to_remove);


#endif // ORDEREDARRAY_H_INCLUDED
