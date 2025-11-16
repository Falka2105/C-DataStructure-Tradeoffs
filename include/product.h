#ifndef PRODUCT_H_INCLUDED
#define PRODUCT_H_INCLUDED

/*STRUCTURE DEFINITION*/

typedef struct{
    long int id;
    char name[100];
    float price;
    float cost;
    long int stock;
}Product;

//FUNCTION PROTOTYPES

int product_compare_by_id(void* productA, void* productB);
void product_print(void* data);
Product* product_create(long int id, const char* name, float price, float cost, long int stock);
void product_free(void* data);

#endif // PRODUCT_H_INCLUDED
