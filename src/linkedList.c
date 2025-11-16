#include <stdlib.h>
#include <stdio.h>
#include "linkedList.h"

/*
 * linkedList.c
 *
 * Implements a generic, dynamic ordered singly-linked list.
 *
 * TRADE-OFF ANALYSIS:
 * - SEARCH:   O(n)     - Must use linear search (list_find_linear).
 * - INSERT:   O(n)     - O(n) to find the position, but O(1) to insert.
 * - REMOVE:   O(n)     - O(n) to find the position, but O(1) to remove.
 * - MEMORY:   Dynamic. No capacity limit, but uses malloc per-node.
 */


/**
 * @brief Creates a new, empty LinkedList instance.
 *
 * Allocates memory for the LinkedList management struct.
 * The list is initialized as empty (head is NULL).
 *
 * @param compare_func A function pointer used to compare elements.
 * @return A pointer to the new LinkedList, or NULL if memory fails.
 */
LinkedList* list_create(CompareFunc compare_func){
    LinkedList* lkl = (LinkedList*)malloc(sizeof(LinkedList));
    if(lkl == NULL) return NULL;
    lkl->head = NULL;
    lkl->counter = 0;
    lkl->compare = compare_func;
    return lkl;
}

/**
 * @brief Frees all memory associated with the LinkedList.
 *
 * Iterates through the list, freeing each Node, and then frees
 * the LinkedList management struct itself.
 * Note: This does NOT free the actual data (e.g., Products)
 * pointed to by the nodes. That is the caller's responsibility.
 *
 * @param list The LinkedList to free.
 */
void list_free(LinkedList* list){
    if(list == NULL) return;
    Node* current_pointer = list->head;
    Node* temp_pointer;
    while(current_pointer != NULL){
        temp_pointer = current_pointer->next;
        free(current_pointer);
        current_pointer = temp_pointer;
    }
    free(list);
}

/**
 * @brief Finds an element in the list using linear search.
 *
 * Iterates from the head of the list, comparing each element.
 * This is an O(n) operation.
 *
 * @param list The list to search in.
 * @param data_to_find A "template" data object to search for.
 * @return A pointer to the data if found, or NULL otherwise.
 */
void* list_find_linear(LinkedList* list, void* data_to_find){
    if(list == NULL || list->head == NULL) return NULL;
    Node* current = list->head;
    while(current != NULL){
        int comparison = list->compare(data_to_find, current->data);
        if(comparison == 0) return current->data;
        current = current->next;
    }
    return NULL;
}

/**
 * @brief Inserts a data element into the list, maintaining sort order.
 *
 * Finds the correct insertion point by iterating (O(n)) and then
 * performs the "re-wiring" of pointers to insert the new Node (O(1)).
 * Handles insertion at the head, middle, and end of the list.
 *
 * @param list The list to insert into.
 * @param data The data (e.g., Product*) to insert.
 * @return 1 on success, 0 on failure (list is NULL or malloc fails).
 */
int list_insert_sorted(LinkedList* list, void* data){
    if(list == NULL) return 0;
    Node* newNode = (Node*)malloc(sizeof(Node));
    if(newNode == NULL) return 0;
    newNode->data = data;
    if(list->head == NULL){
            newNode->next = NULL;
            list->head = newNode;
    }
    else if(list->compare(data, list->head->data) < 0){
            newNode->next = list->head;
            list->head = newNode;
    }
        else{
            Node* previous = list->head;
            Node* current = list->head->next;
            while(current != NULL && list->compare(data, current->data) > 0){
                previous = current;
                current = current->next;
            }
            newNode->next = current;
            previous->next = newNode;
        }
    list->counter++;
    return 1;
}

/**
 * @brief Removes a data element from the list.
 *
 * Finds the element to remove by iterating (O(n)) and then
 * performs the "re-wiring" of pointers to "skip" the node (O(1)).
 * Handles removal of the head, middle, and end nodes.
 *
 * @param list The list to remove from.
 * @param data_to_remove A "template" data object to find and remove.
 * @return The pointer to the removed data (so the caller can free it),
 * or NULL if the element was not found.
 */
void* list_remove(LinkedList* list, void* data_to_remove){
    if(list == NULL || list->head == NULL) return NULL;
    void* removed_data = NULL;
    Node* node_to_free = NULL;
    if(list->compare(data_to_remove, list->head->data) == 0){
        removed_data = list->head->data;
        node_to_free = list->head;
        list->head = list->head->next;
    }
    else{
        Node* previous = list->head;
        Node* current = list->head->next;
        while(current != NULL && list->compare(data_to_remove, current->data) != 0){
            previous = current;
            current = current->next;
        }
        if (current != NULL) {
            removed_data = current->data;
            node_to_free = current;
            previous->next = current->next;
        }
    }
    if(node_to_free != NULL){
        free(node_to_free);
        list->counter--;
    }
    return removed_data;
}

/**
 * @brief Prints all elements in the list to the console.
 *
 * Iterates through the list (from head to tail) and uses the
 * provided 'print_func' to print each element.
 *
 * @param list The list to print.
 * @param print_func The function that knows how to print a single element.
 */
void list_print(LinkedList* list, PrintFunc print_func){
    if(list == NULL || print_func == NULL) return;
    Node* current = list->head;
    while(current != NULL){
        print_func(current->data);
        current = current->next;
    }
}
