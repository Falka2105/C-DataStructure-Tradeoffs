#ifndef LINKEDLIST_H_INCLUDED
#define LINKEDLIST_H_INCLUDED
#include <stdio.h>
#include <stdlib.h>


/*Pointer to function. HOW the list will compare two generic elements*/
typedef int (*CompareFunc)(void* a, void* b);
typedef void (*PrintFunc)(void* data);

typedef struct Node{
    void* data;
    struct Node* next;
}Node;

typedef struct{
    Node* head;
    int counter;
    CompareFunc compare;
}LinkedList;

/*PUBLIC INTERFACE (FUNCTION PROTOTYPES LinkedList.c will provide)*/

LinkedList* list_create(CompareFunc compare_func);
void list_free(LinkedList* list);
int list_insert_sorted(LinkedList* list, void* data);
void* list_remove(LinkedList* list, void* data_to_remove);
void* list_find_linear(LinkedList* list, void* data_to_find);
void list_print(LinkedList* list, PrintFunc print_func);


#endif // LINKEDLIST_H_INCLUDED
