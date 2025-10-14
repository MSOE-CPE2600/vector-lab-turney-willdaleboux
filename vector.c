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

static vector storage[MAX_VECTORS];

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
    //check if vector already exists
    for(int i=0; i< MAX_VECTORS; i++)
    {
        if(!is_empty_slot(i) && strcmp(storage[i].name, v.name) == 0)
        {
            //overwrite vector if it already exists in the array
            storage[i] = v;
            return 0;
        }
    }
    //if vector doesn't already exist, add to first empty slot
    for(int i=0; i<MAX_VECTORS; i++)
    {
        if(is_empty_slot(i))
        {
            storage[i] = v;
            return 0;
        }
    }


    printf("Error, Vector array is full. cannot hold more than %d\n", MAX_VECTORS);
    return -1;
}

int is_empty_slot(int index)
{
    if(storage[index].name[0] == '\0')
    {
        return 1; // return 1 for empty slot
    } 
    else 
    {
        return 0; // return 0 for non-empty slot
    }
}

vector* findvect(const char *name)
{
    // itterate through vector array
    for(int i=0; i<MAX_VECTORS; i++)
    {
        //return matching vector if found
        if(!is_empty_slot(i) && strcmp(storage[i].name, name) == 0)
        {
            return &storage[i];
        }
    }
    return NULL;
}

void list()
{
    // itterate through vector array   
    for(int i=0; i<MAX_VECTORS; i++)
    {
        //print non-empty slots
        if(!is_empty_slot(i))
        {
            printvect(&storage[i]);
        }
    }
}

void clear()
{
    for(int i=0; i< MAX_VECTORS; i++)
    {
        storage[i].name[0] = '\0'; // mark as empty for each element of array
    }
    printf("vectors cleared.\n");
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