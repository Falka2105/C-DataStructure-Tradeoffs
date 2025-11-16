#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "orderedArray.h"
#include "linkedList.h"
#include "student.h"
#include "product.h"

/* --- FUNCTION PROTOTYPES --- */
void load_students(OrderedArray* db, const char* filename);
void load_products(LinkedList* db, const char* filename);
void cleanup_students(OrderedArray* db);
void cleanup_products(LinkedList* db);

int main() {
    printf("Initializing trade-offs test...\n\n");

    /* --- CREATION --- */
    OrderedArray* student_db = oa_create(100, student_compare_by_id);
    LinkedList* product_db = list_create(product_compare_by_id);

    if (student_db == NULL || product_db == NULL) {
        printf("Fatal ERROR: Couldn't create the database\n");
        return 1;
    }

    /* --- FILE LOADING --- */
    load_students(student_db, "data/students.csv");
    load_products(product_db, "data/products.csv");

    printf("\n--- INITIAL LOADING COMPLETE ---\n");

    /* --- PRINT --- */
    oa_print(student_db, student_print);
    list_print(product_db, product_print);

    /* --- STRESS TEST --- */
    printf("\n--- INITIALIZING STRESS TEST ---\n");

    printf("Inserting 'Zoe (ID 50)' (at beginning)...\n");
    oa_insert_sorted(student_db, student_create(50, "Zoe (First)", 9.9));

    printf("Inserting 'Alex (ID 500)' (at final)...\n");
    oa_insert_sorted(student_db, student_create(500, "Alex (Final)", 6.0));

    printf("Inserting 'Pedro (ID 103)' (at the middle)...\n");
    oa_insert_sorted(student_db, student_create(103, "Pedro (Middle)", 7.5));

    printf("Eliminating 'Juan (ID 101)' (From the middle)...\n");

    Student* plantilla_juan = student_create(101, "", 0.0);
    if (plantilla_juan != NULL) {

        Student* data_borrada = oa_remove(student_db, plantilla_juan);

        if (data_borrada != NULL) {
            printf("  -> Success at eliminating %s\n", data_borrada->name);
            student_free(data_borrada);
        }
        student_free(plantilla_juan);
    }

    printf("Eliminating 'Teclado (ID 5)' (head)...\n");
    Product* plantilla_teclado = product_create(5, "", 0, 0, 0);
    if (plantilla_teclado != NULL) {

        Product* data_borrada_lista = list_remove(product_db, plantilla_teclado);

        if (data_borrada_lista != NULL) {
            printf("  -> Success at eliminating: %s\n", data_borrada_lista->name);
            product_free(data_borrada_lista);
        }
        product_free(plantilla_teclado);
    }

    printf("\n--- 'Stress Test' complete. Showing final results: ---\n");

    oa_print(student_db, student_print);
    list_print(product_db, product_print);

    /* --- CLEAN ALL --- */
    printf("\nInitializing memory cleanse...\n");
    cleanup_students(student_db);
    cleanup_products(product_db);

    printf("Cleanse complete.\n");
    return 0;
}

void load_students(OrderedArray* db, const char* filename) {
    FILE* file = fopen(filename, "r");
    if (file == NULL) {
        printf("Error: Couldn't open the file %s\n", filename);
        return;
    }
    printf("Loading students from %s...\n", filename);

    char line_buffer[256];
    while (fgets(line_buffer, sizeof(line_buffer), file) != NULL) {
        long id;
        char name[100];
        float gpa;

        int items_matched = sscanf(line_buffer, " %ld ,%[^,] ,%f ", &id, name, &gpa);

        if (items_matched == 3) {
            Student* newStudent = student_create(id, name, gpa);
            if (newStudent != NULL) {
                int result = oa_insert_sorted(db, newStudent);
                if (result == 0) {
                    printf("Array's full. Couldn't insert %s\n", name);
                    free(newStudent);
                }
            }
        }
    }
    fclose(file);
    printf("Students loading complete.\n");
}

void load_products(LinkedList* db, const char* filename) {
    FILE* file = fopen(filename, "r");
    if (file == NULL) {
        printf("Error: Couldn't open the file %s\n", filename);
        return;
    }
    printf("Loading products from %s...\n", filename);

    char line_buffer[256];
    while (fgets(line_buffer, sizeof(line_buffer), file) != NULL) {
        long id;
        char name[100];
        float price, cost;
        long int stock;

        int items_matched = sscanf(line_buffer, " %ld ,%[^,] ,%f ,%f ,%ld ",
                                   &id, name, &price, &cost, &stock);

        if (items_matched == 5) {
            Product* newProduct = product_create(id, name, price, cost, stock);
            if (newProduct != NULL) {
                int result = list_insert_sorted(db, newProduct);
                if (result == 0) {
                    printf("Memory error %s\n", name);
                    free(newProduct);
                }
            }
        }
    }
    fclose(file);
    printf("Products loading complete.\n");
}

void cleanup_students(OrderedArray* db) {
    if (db == NULL) return;
    for (int i = 0; i < db->counter; i++) {
        if (db->data[i] != NULL) {
            student_free(db->data[i]);
        }
    }
    oa_free(db);
    printf("Students database freed.\n");
}

void cleanup_products(LinkedList* db) {
    if (db == NULL) return;

    Node* current = db->head;
    while (current != NULL) {
        if (current->data != NULL) {
            product_free(current->data);
        }
        current = current->next;
    }
    list_free(db);
    printf("Products database freed.\n");
}
