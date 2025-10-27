/*********************************************************
* filename: vector.h
* description: function prototypes for vector.c
* author: Will dalebroux
* date: 10/7/2025
* compile with: $ msake
*********************************************************/
#ifndef VECTOR_H
#define VECTOR_H

// #define MAX_VECTORS 10
typedef struct vector
{
    char name[10];
    double x;
    double y;
    double z;
} vector;


//-----linked list functions-------
// list ll_init(void);
// int ll_size(list *myList);
// int ll_pushfront(list *myList, char *to_store);
// int ll_pushback(list *myList, char *to_store);
// int ll_insert_after(list *myList, node *ins_node, char *to_store);
// int ll_remove(list *myList, node *rmv_node);
// void dump(list *myList);
// void ll_clear(list *myList);
//------linked list static helpers------
static Node *make_node(const vector *v);
static void kill_node(node *to_kill);



//------math layer---------
vector addvect(vector a, vector b); 
vector subvect(vector a, vector b);
vector scalar_mult_vect(vector v, double scalar);

//-----storage layer-------
int store_vector(vector v); // store vector in vector array
vector* findvect(const char *name); // find first empty location 
int is_empty_slot(int index); // if first element in array is '\0', slot is empty


//--------helper functions-------
void list(); // list all stored vectors
void clear(); // clear stored vectors
void help(); // print out commands
void quit(); 
void printvect(const vector *v);  



#endif