#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "product.h"

/**
 * @brief Creates a new Product instance on the heap.
 *
 * Allocates memory for a Product structure and initializes it
 * with the provided values.
 *
 * @param id The product's unique ID
 * @param name The product's name.
 * @param price The product's selling price.
 * @param cost The product's cost
 * @param stock The product's available stock quantity.
 * @return A pointer to the newly created Product, or NULL if
 * memory allocation fails.
 */
Product* product_create(long int id, const char* name, float price, float cost, long int stock){
    Product* A = (Product *)malloc(sizeof(Product));
    if(A == NULL) return NULL;

    A->id = id;
    A->price = price;
    A->cost = cost;
    A->stock = stock;
    strcpy(A->name, name);
    return A;
}

/**
 * @brief Frees the memory allocated for a Product.
 *
 * This function is compatible with the 'void*' signature
 * required by the generic data structures.
 *
 * @param data A void pointer to the Product instance to be freed.
 */
void product_free(void* data){
    free(data);
}

/**
 * @brief Prints the details of a single Product to the console.
 *
 * This function is compatible with the 'PrintFunc' typedef
 * (void (*)(void*)) used by the generic data structures.
 *
 * @param data A void pointer to the Product instance to be printed.
 */
void product_print(void* data){
    Product* A = (Product*)data;
    printf("Product's data: \n");
    printf("    id: %ld\n", A->id);
    printf("    Name: %s\n", A->name);
    printf("    Price: %.2f\n", A->price);
    printf("    Cost: %.2f\n", A->cost);
    printf("    Available stock: %ld\n", A->stock);
}

/**
 * @brief Compares two Product instances by their ID.
 *
 * This function is compatible with the 'CompareFunc' typedef
 * (int (*)(void*, void*)) used by the generic data structures.
 *
 * @param productA A void pointer to the first Product.
 * @param productB A void pointer to the second Product.
 * @return < 0 if A's ID < B's ID
 * @return 0 if A's ID == B's ID
 * @return > 0 A's ID > B's ID
 */
int product_compare_by_id(void* productA, void* productB){
    Product* A = (Product*)productA;
    Product* B = (Product*)productB;
    if(A->id < B->id){
        return -1;
    }
    else if(A->id == B->id){
        return 0;
    }
    else return 1;
}
