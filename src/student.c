#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "student.h"

/**
 * @brief Creates a new Student instance on the heap.
 *
 * Allocates memory for a Student structure and initializes it
 * with the provided values.
 *
 * @param id The student's unique ID.
 * @param name The student's name.
 * @param gpa The student's Grade Point Average.
 * @return A pointer to the newly created Student, or NULL if
 * memory allocation fails.
 */
Student* student_create(long int id, const char* name, float gpa){
    Student* A = (Student *)malloc(sizeof(Student));
    if(A == NULL) return NULL;
    A->id = id;
    A->gpa = gpa;
    strcpy(A->name, name);
    return A;
}

/**
 * @brief Frees the memory allocated for a Student.
 *
 * This function is compatible with the 'void*' signature
 * required by the generic data structures.
 *
 * @param data A void pointer to the Student instance to be freed.
 */
void student_free(void* data){
    free(data);
}

/**
 * @brief Prints the details of a single Student to the console.
 *
 * This function is compatible with the 'PrintFunc' typedef
 * (void(*)(void*)) used by the generic data structures.
 *
 * @param data A void pointer to the Student instance to be printed.
 */
void student_print(void* data){
    Student* A = (Student*)data;
    printf("Student's data:\n");
    printf("    id: %ld\n", A->id);
    printf("    Name: %s\n", A->name);
    printf("    GPA: %.2f\n", A->gpa);
}

/**
 * @brief Compares two Student instances by their ID.
 *
 * This function is compatible with the 'CompareFunc' typedef
 * (int (*)(void*, void*)) used by the generic data structures.
 *
 * @param studentA A void pointer to the first Student.
 * @param studentB A void pointer to the second Student.
 * @return < 0 if A's ID < B's ID.
 * @return 0 if A's ID == B's ID.
 * @return > 0 if A's ID > B's ID.
 */
int student_compare_by_id(void* studentA, void* studentB){
    Student* A = (Student*)studentA;
    Student* B = (Student*)studentB;
    if(A->id < B->id){
        return -1;
    }
    else if(A->id == B->id){
        return 0;
    }
    else return 1;
}
