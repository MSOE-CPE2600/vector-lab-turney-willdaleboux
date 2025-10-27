/***************************************************
* filename: vector.c
* description: vector storage and manipulation functions
* author: Will Dalebroux
* date: 10/7/2025
* compile with: $ make
***************************************************/

#include "vector.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

// static vector storage[MAX_VECTORS];
typedef struct Node 
{
    struct Node *next; 
    struct Node *prev;
    vector data; // storing by value
} Node;
static Node *g_head = NULL;
static Node *g_tail = NULL;


// //--------linked list functions--------
// list ll_init(void)
// {
//     list return_list = {NULL,NULL};
//     return return_list;
// }

// int ll_size(list *myList)
// {
//     int size = 0;
//     node *iterator = myList->head;
//     while(iterator)
//     {
//         size++;
//         iterator = iterator->next;
//     }
//     return size;
// }

// int ll_pushfront(list *myList, char *to_store)
// {
//     node *new_node = make_node(to_store);
//     if(to_store)
//     {
//         //is first node in list?
//         if(myList->head == NULL)
//         {
//             myList->head = myList->tail = new_node;
//         }
//         else //not first node in list
//         {
//             new_node->next = myList->head;
//             myList->head->prev = new_node;
//             myList->head = new_node;
//         }
//         return 0; // successful
//     }
//     return -1; //fail
// }

// int ll_pushback(list *myList, char *to_store)
// {
//     //TODO
//     if(to_store)
//     {
//         node *new_node = make_node(to_store);
//         //is first node in list?
//         if(myList->tail == NULL)
//         {
//             myList->tail = myList->head = new_node;
//         }
//         else //not first node
//         {
//             new_node->next = NULL;
//             myList->tail->next = new_node;
//             new_node->prev = myList->tail;
//             myList->tail = new_node;
//         }
//         return 0; //success
//     }
//     return -1; //fail
// }

// int ll_insert_after(list *myList, node *ins_node, char *to_store)
// {
//     //TODO
//     int to_return = 0;

//     if(to_store && ins_node)
//     {
//         if(ins_node == myList->tail)
//         {
//             to_return = ll_pushback(myList, to_store);
//         }
//         else 
//         {
//             node *new_node = make_node(to_store);

//             ins_node->next->prev = new_node;
//             new_node->next = ins_node->next;
//             new_node->prev = ins_node;
//             ins_node->next = new_node;

//             //update tail pointer if necessary
//             if(ins_node == myList->tail)
//             {
//                 myList->tail = new_node;
//             }

//         }
//         return to_return; // success
//     }
//     return -1; //fail
// }

// int ll_remove(list *myList, node *rmv_node)
// {
//     //TODO
// }

// void dump(list *myList)
// {
//     //TODO
// }

// void ll_clear(list *myList)
// {
//     //TODO
// }

//--------linked list static helpers----------
static Node *make_node(const vector *v)
{
    Node *new_node = (Node*)malloc(sizeof(Node));
    if(!new_node)
    {
        return NULL;
    }
    new_node->next = new_node->prev = NULL;
    new_node->data = *v;
    return new_node;
}

static void kill_node(Node *to_kill)
{
    free(to_kill);
}

static Node *find_node_by_name(const char *name)
{
    // iterate through linked list to find a node matching specified name
    for(Node *p = g_head; p; p = p->next) 
    {
        if(strcmp(p->data.name, name) == 0)
        {
            return p;
        }
    }
    return NULL;
}

//--------math layer------------ 
vector addvect(vector a, vector b)
{
    vector returnval;
    returnval.x = a.x + b.x;
    returnval.y = a.y + b.y;
    returnval.z = a.z + b.z;

    return returnval;
}

vector subvect(vector a, vector b)
{
    vector returnval;
    returnval.x = a.x - b.x;
    returnval.y = a.y - b.y;
    returnval.z = a.z - b.z;

    return returnval;

}

vector scalar_mult_vect(vector v, double scalar)
{
    vector returnval;
    returnval.x = v.x * scalar;
    returnval.y = v.y * scalar;
    returnval.z = v.z * scalar;

    return returnval;

}

//-----------storage layer-------------
int store_vector(vector v)
{
    // //check if vector already exists
    // for(int i=0; i< MAX_VECTORS; i++)
    // {
    //     if(!is_empty_slot(i) && strcmp(storage[i].name, v.name) == 0)
    //     {
    //         //overwrite vector if it already exists in the array
    //         storage[i] = v;
    //         return 0;
    //     }
    // }
    // //if vector doesn't already exist, add to first empty slot
    // for(int i=0; i<MAX_VECTORS; i++)
    // {
    //     if(is_empty_slot(i))
    //     {
    //         storage[i] = v;
    //         return 0;
    //     }
    // }


    // printf("Error, Vector array is full. cannot hold more than %d\n", MAX_VECTORS);
    // return -1;
    
    if(v.name[0] == '\0')
    {
        fprintf(stderr, "Error: unnamed vector\n.");
        return -1;
    }
    Node *existing = find_node_by_name(v.name);
    if(existing)
    {
        existing->data = v;
        return 0;
    }

    Node *n = make_node(&v);
    //push back

    if(!g_tail)
    {
        g_head = g_tail = n;
    }
    else 
    {
        n->prev = g_tail;
        g_tail->next = n;
        g_tail = n;
    }
    return 0;
}

// int is_empty_slot(int index)
// {
//     if(storage[index].name[0] == '\0')
//     {
//         return 1; // return 1 for empty slot
//     } 
//     else 
//     {
//         return 0; // return 0 for non-empty slot
//     }
// }

vector *findvect(const char *name)
{
    // // itterate through vector array
    // for(int i=0; i<MAX_VECTORS; i++)
    // {
    //     //return matching vector if found
    //     if(!is_empty_slot(i) && strcmp(storage[i].name, name) == 0)
    //     {
    //         return &storage[i];
    //     }
    // }
    // return NULL;
    Node *n = find_node_by_name(name);
    //return pointer to vector inside node if found, otherwise NULL;
    return n ? &n->data : NULL; 


}

void list()
{
    // // itterate through vector array   
    // for(int i=0; i<MAX_VECTORS; i++)
    // {
    //     //print non-empty slots
    //     if(!is_empty_slot(i))
    //     {
    //         printvect(&storage[i]);
    //     }
    // }


    if(!g_head)
    {
        printf("no vectors stored.\n");
        return;
    }
    for(Node *p = g_head; p; p = p->next)
    {
        printvect(&p->data);
    }
}

void clear()
{
    // for(int i=0; i< MAX_VECTORS; i++)
    // {
    //     storage[i].name[0] = '\0'; // mark as empty for each element of array
    // }
    // printf("vectors cleared.\n");
    Node *p = g_head;
    while(p)
    {
        Node *next = p->next;
        kill_node(p);
        p = next;
    }
    g_head = g_tail = NULL;
    printf("Vectors cleared.\n");
}

void quit()
{
    printf("exiting....\n");
    exit(0);
}

void help()
{
    printf("List of commands:\n");
    printf("    varname = x y z         assign vector(x,y,z)\n"); 
    printf("    varname                 display vector\n");
    printf("    var1 + var2             add 2 vectors & display result\n");
    printf("    var1 - var2             subtract 2 vectors & display result\n");
    printf("    var * num OR num * var  scalar multiplication\n");
    printf("    result = var1 + var2    do operation and store into result\n");
    printf("    list                    list vectors\n");
    printf("    clear                   clear vector list\n");
    printf("    help                    display this help page\n");
    printf("    quit                    quit the program\n");
}

void printvect(const vector *v)
{
    printf("%s = %.6g    %.6g    %.6g\n", v->name, v->x, v->y, v->z);
}