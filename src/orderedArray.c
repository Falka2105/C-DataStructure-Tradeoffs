#include <stdlib.h>
#include <stdio.h>
#include "orderedArray.h"

/*
 * orderedArray.c
 *
 * Implements a generic, fixed-capacity ordered array
 *
 * TRADE-OFF ANALYSIS:
 * - SEARCH: O(log n) - Uses binary search (_oa_find_index).
 * - INSERT: O(n) - Must perform a linear shift to make space.
 * - REMOVE: O(n) - Must perform a linear shift to close gaps.
 * - MEMORY: Static (Fixed-capacity). Simple, but limited.
 */


/**
 * @brief (Private) Finds an element or its insertion point using binary search.
 *
 * This static helper function is the core of the module. It performs a
 * binary search for a 'data_to_find'. It reports whether the item was
 * found via the 'pFound' output parameter and returns the index.
 *
 * @param arr The array to search in.
 * @param data_to_find A "template" data object to search for (e.g., a
 * Student struct with just the ID set).
 * @param pFound [out] An output pointer. Will be set to 1 if found, 0 otherwise.
 * @return The index of the element (if *pFound = 1)
 * @return The index where the element *should be inserted* (if *pFound = 0)
 */
static int _oa_find_index(OrderedArray* arr, void* data_to_find, int* pFound){
    if(arr->counter == 0){
        *pFound = 0;
        return 0;
    }
    int low = 0;
    int high = arr->counter-1;
    int mid;
    while (low <= high){
        mid = (low + high) / 2;
        int comparison = arr->compare(data_to_find, arr->data[mid]);
        if (comparison == 0) {
            *pFound = 1;
            return mid;
        }
        else if (comparison > 0) {
            low = mid + 1;
        }
        else {
            high = mid - 1;
        }
    }
    *pFound = 0;
    return low;
}

/**
 * @brief Creates a new OrderedArray instance.
 *
 * Allocates memory for both the OrderedArray management struct
 * and the internal 'data' array (of void pointers).
 *
 * @param capacity The maximum number of elements the array can hold.
 * @param compare_func A function pointer used to compare elements.
 * @return A pointer to the new OrderedArray, or NULL if memory fails.
*/
OrderedArray* oa_create(int capacity, CompareFunc compare_func){
    OrderedArray* arr = (OrderedArray*)malloc(sizeof(OrderedArray));
    if(arr == NULL) return NULL;
    arr->data = (void**)malloc(capacity * sizeof(void*));
    if (arr->data == NULL){
        free(arr);
        return NULL;
    }
    arr->capacity = capacity;
    arr->counter = 0;
    arr->compare = compare_func;
    return arr;
}

/**
 * @brief Frees all memory associated with the OrderedArray
 *
 * Frees the internal 'data' array and the management struct itself.
 * Note: This does NOT free the actual data (e.g., Students)
 * pointed to by the array. That is the caller's responsibility.
 *
 * @param arr The orderedArray to free.
 */
void oa_free(OrderedArray* arr){
    if(arr == NULL) return;
    free(arr->data);
    free(arr);
}

/**
 * @brief Finds an element in the array using binary search.
 *
 * This is a public wrapper for the _oa_find_index helper function.
 *
 * @param arr The array to search in.
 * @param data_to_find A "template" data object to search for.
 * @return A pointer to the data if found, or NULL otherwise.
 */
void* oa_find_binary(OrderedArray* arr, void* data_to_find){
    int found_status = 0;
    int index = _oa_find_index(arr, data_to_find, &found_status);
    if(found_status == 1){
        return arr->data[index];
    }
    else return NULL;
}

/**
 * @brief Inserts a data element into the array, maintaining sort order.
 *
 * Finds the correct insertion point using binary search (O(log n))
 * and then shifts all subsequent elements to make space (O(n)).
 *
 * @param arr The array to insert into.
 * @param data The data to insert.
 * @return 1 on success, 0 on failure (array is full or data exists).
*/
int oa_insert_sorted(OrderedArray* arr, void* data){
    if(arr == NULL || arr->counter == arr->capacity) return 0;
    int found_status = 0;
    int index_to_insert = _oa_find_index(arr, data, &found_status);
    if(found_status == 1) return 0;
    for(int j = arr->counter; j > index_to_insert; j--) arr->data[j] = arr->data[j-1];
    arr->data[index_to_insert] = data;
    arr->counter++;
    return 1;
}

/**
 * @brief Removes a data element from the array, maintaining sort order.
 *
 * Finds the element using binary search (O(log n)) and then
 * shifts all subsequent elements to close the gap (O(n)).
 *
 * @param arr The array to remove from.
 * @param data_to_remove A "template" data object to find and remove.
 * @return The pointer to the removed data (so the caller can free it),
 * or NULL if the element was not found.
 */
void* oa_remove(OrderedArray* arr, void* data_to_remove) {
    if (arr == NULL || arr->counter == 0) return NULL;
    int found_status = 0;
    int index_to_remove = _oa_find_index(arr, data_to_remove, &found_status);
    if (found_status == 0) {
        return NULL;
    }
    void* removed_data = arr->data[index_to_remove];
    for (int j = index_to_remove; j < arr->counter - 1; j++) {
        arr->data[j] = arr->data[j+1];
    }
    arr->counter--;
    return removed_data;
}

/**
 * @brief Prints all elements in the array to the console.
 *
 * Iterates through the array and uses the provided 'print_func'
 * to print each element.
 *
 * @param arr The array to print.
 * @param print_func The function that knows how to print a single element.
 */
void oa_print(OrderedArray* arr, PrintFunc print_func) {
    if (arr == NULL || print_func == NULL) return;

    printf("\n-----Array----- (Cap: %d, Count: %d)\n", arr->capacity, arr->counter);

    if (arr->counter == 0) {
        printf("Empty array.\n");
    }

    for (int i = 0; i < arr->counter; i++) {
        print_func(arr->data[i]);
    }

    printf("-----End of Array-----\n");
}


