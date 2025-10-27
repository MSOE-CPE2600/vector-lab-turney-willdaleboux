/*********************************************************
* filename: main.c
* description: vector calculator capable of the following:
*              Add/subtract vectors
*              Scalar multiplication of vectors
*              Store vectors
* author: Will Dalebroux
* date: 10/7/2025
* compile with: make
**********************************************************/
#include "vector.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <signal.h>

int main(int argc, char *argv[])
{
    atexit(clear); // force free when quitting
    signal(SIGINT, signal_handler);
    char filename[256];
    char input[100];
    char name1[10];
    char name2[10];
    char name3[10];

    double x;
    double y;
    double z;
    double scalar;

    vector *v1;
    vector *v2;
    vector result;
    //handle command line argument
    if(argc > 1 && (strcmp(argv[1], "-h") == 0 || strcmp(argv[1], "--help") == 0))
    {
        help();
    }

    printf("=========================================================\n");
    printf("Vector Calculator\n");
    printf("Type 'help' for command list\n");
    printf("=========================================================\n");

    for(;;) //infinite loop, exits when user types "quit"
    {
        printf("vectorCalc>");
        if(!fgets(input, sizeof(input), stdin))
        {
            break;
        }
        input[strcspn(input, "\n")] = '\0'; //remove trailing newline


        //-----commands-------
        if(strcmp(input, "quit") == 0 || strcmp(input, "Quit") == 0)
        {
            quit();
        }
        else if(strcmp(input, "help") == 0 || strcmp(input, "Help") == 0)
        {
            help();
        }
        else if(strcmp(input, "list") == 0 || strcmp(input, "List") == 0)
        {
            list();
        }
        else if (strcmp(input, "clear") == 0 || strcmp(input, "Clear") == 0)
        {
            clear();
        }
        //------- create vectors ----------
        else if(sscanf(input, "%9s = %lf %lf %lf", name1, &x, &y, &z) == 4)
        {
            vector v;
            strcpy(v.name, name1);
            v.x = x;
            v.y = y;
            v.z = z;
            if(store_vector(v) == 0)
            {
            printf("Stored %s = %.2f %.2f %.2f\n", v.name, v.x, v.y, v.z);
            }
        }
        //------ add 2 vectors ----------
        else if(sscanf(input, "%9s + %9s", name1, name2) == 2)
        {
            v1 = findvect(name1);
            v2 = findvect(name2);
            if(v1 && v2)
            {
                result = addvect(*v1, *v2);
                printf("Result: (%.2f, %.2f, %.2f)\n", result.x, result.y, result.z);
            }
            else 
            {
                printf("Error: one or both vectors not found.\n");
            }
        }
        //-------- store the sum of 2 vectors --------
        else if(sscanf(input, "%9s = %9s + %9s", name1, name2, name3) == 3)
        {
            vector *v2 = findvect(name2);
            vector *v3 = findvect(name3);
            if(v2 && v3)
            {
                result = addvect(*v2, *v3);
                strcpy(result.name, name1);
                if(store_vector(result) == 0)
                {
                    printf("Stored %s = (%.2f, %.2f, %.2f)\n",  result.name, result.x, result.y, result.z);
                }
                else 
                {
                    printf("Error: one or both vectors not found\n");
                }
            }
        }
        //------- subtract 2 vectors ---------
        else if(sscanf(input, "%9s - %9s", name1, name2) == 2)
        {
            v1 = findvect(name1);
            v2 = findvect(name2);
            if(v1 && v2)
            {
                result = subvect(*v1, *v2);
                printf("Result: (%.2f, %.2f, %.2f)\n", result.x, result.y, result.z);
            }
            else
            {
                printf("Error: one or both vectors not found\n");
            }
        }
        //-------- store the difference of 2 vectors --------
        else if(sscanf(input, "%9s = %9s - %9s", name1, name2, name3) == 3)
        {
            vector *v2 = findvect(name2);
            vector *v3 = findvect(name3);
            if(v2 && v3)
            {
                result = subvect(*v2, *v3);
                strcpy(result.name, name1);
                if(store_vector(result) == 0)
                {
                    printf("Stored %s = (%.2f, %.2f, %.2f)\n",  result.name, result.x, result.y, result.z);
                }
            }
        }
        //------------scalar multiplication-------------
        else if(sscanf(input, "%9s * %lf", name1, &scalar) == 2)
        {
            v1 = findvect(name1);
            if(!v1)
            {
                printf("Error: vector not found.\n");
            }
            else
            {
                
                result = scalar_mult_vect(*v1, scalar);
                printf("Result: (%.2f, %.2f, %.2f)\n", result.x, result.y, result.z);
            }
        }
        else if(sscanf(input, "%lf * %9s", &scalar, name1) == 2)
        {
            v1 = findvect(name1);
            if(v1)
            {
                result = scalar_mult_vect(*v1, scalar);
                printf("Results: (%.2f, %.2f, %.2f)\n", result.x, result.y, result.z);
            }
            else
            {
                printf("Error: vector not found\n");
            }
        }
        //------- storing scalar muliplication in new vector
        else if(sscanf(input, "%9s = %9s * %lf", name1, name2, &scalar) == 3)
        {
            vector *v2 = findvect(name2);   
            if(!v2)
            {
                printf("Error: vector %s not found\n",name2);
            }
            else 
            {
                vector scalar_result = scalar_mult_vect(*v2, scalar);
                strcpy(scalar_result.name, name1);
                
                if(store_vector(scalar_result) == 0)
                {
                    printf("Stored %s = %.2f, %.2f, %.2f\n", scalar_result.name, scalar_result.x, scalar_result.y, scalar_result.z);
                }
            }
        }
        else if(sscanf(input, "%9s = %lf * %9s", name1, &scalar, name2) == 3) // handle reverse case
        {
            vector *v2 = findvect(name2);
            if(!v2)
            {
                printf("Error: vector %s not found\n", name2);
            }
            else 
            {
                vector scalar_result = scalar_mult_vect(*v2, scalar);
                strcpy(scalar_result.name, name1);
                if(store_vector(scalar_result) == 0)
                {
                    printf("Stored %s = %.2f, %.2f, %.2f\n", scalar_result.name, scalar_result.x, scalar_result.y, scalar_result.z);
                }
            }
        }
        //-------- save/load csv -------
        else if(sscanf(input, "save %255s", filename) == 1)
        {
            save_csv(filename);
        }
        else if(sscanf(input, "loadfresh %255s", filename) == 1)
        {
            load_csv(filename, 0);
        }
        else if(sscanf(input, "load %255s", filename) == 1)
        {
            load_csv(filename, 1);
        }

        //-------- display a single vector ----------- 
        else if(sscanf(input, "%9s", name1) == 1)
        {
            v1 = findvect(name1);
            if(v1)
            {
                printvect(v1);
            }
            else 
            {
                printf("Error: vector not found.\n");
            }
        }
        //------- invalid input -------------------
        else 
        {
            printf("Unrecognized command. Type 'help' for more details.\n");
        }
    }

    return 0;
}