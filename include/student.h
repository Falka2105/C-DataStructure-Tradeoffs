#ifndef STUDENT_H_INCLUDED
#define STUDENT_H_INCLUDED

/*STRUCTURE DEFINITION*/

typedef struct{
    long int id;
    char name[100];
    float gpa; //"Grade Point Average"
}Student;

//FUNCTION PROTOTYPES

int student_compare_by_id(void* studentA, void* studentB);
void student_print(void* data);
Student* student_create(long int id, const char* name, float gpa);
void student_free(void* data);

#endif // STUDENT_H_INCLUDED
