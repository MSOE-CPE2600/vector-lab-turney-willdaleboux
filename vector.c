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
#include <ctype.h>

typedef struct Node 
{
    struct Node *next; 
    struct Node *prev;
    vector data; // storing by value
} Node;
static Node *g_head = NULL;
static Node *g_tail = NULL;


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
    // traverse through linked list to find a node matching specified name
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


vector *findvect(const char *name)
{
    Node *n = find_node_by_name(name);
    //return pointer to vector inside node if found, otherwise NULL;
    return n ? &n->data : NULL; 


}

void list()
{
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
    printf("    save <file.csv>         save vectors to CSV\n");
    printf("    load <file.csv>         load vectors(merge mode)\n");
    printf("    loadfresh <file.csv>    clears vectors first, then load vectors\n");
    printf("    help                    display this help page\n");
    printf("    quit                    quit the program\n");
}

void printvect(const vector *v)
{
    printf("%s = %.6g    %.6g    %.6g\n", v->name, v->x, v->y, v->z);
}

//-------CSV helper-------
static int parse_csv_line(const char *line, vector *out)
{
    char name[10];
    double x;
    double y;
    double z;
    int n = 0;
    
    int matched = sscanf(line, " %9[^,] , %lf , %lf , %lf %n",
                        name, &x, &y, &z, &n);

    if(matched != 4)
    {
        return -1;
    }

    //make sure no trailing non-space chars after parsed text
    for(const char *p = line + n; *p; ++p)
    {
        if(!isspace((unsigned char)*p))
        {
            return -1;
        }
    }

    //fill result
    strncpy(out->name, name, sizeof(out->name) - 1);
    out->name[sizeof(out->name) - 1] = '\0';
    out->x = x;
    out->y = y;
    out->z = z;
    return 0;
}

//-------CSV file I/O-------
int load_csv(const char *filename, int merge)
{
    if(!filename || !*filename)
    {
        fprintf(stderr, "load_csv: invalid filename\n");
        return -1;
    }

    FILE *fp = fopen(filename, "r");
    if(!fp)
    {
        perror("load_csv: fopen");
        return -1;
    }
    
    if(!merge)
    {
        clear(); // clear stored vector if merge = 0
    }

    char line[256];
    int line_num = 0;
    int loaded = 0;

    while(fgets(line, sizeof(line),fp))
    {
        line_num++;

        //skip blank lines/comments
        char *p = line;
        while(isspace((unsigned char)*p))
        {
            p++;
        }
        if(*p == '\0' || *p == '#')
        {
            continue;
        }
        //skip header line
        if(strncasecmp(p, "name", 4) == 0)
        {
            continue;
        }

        vector v;
        if(parse_csv_line(p, &v) == 0)
        {
            if(store_vector(v) == 0)
            {
                loaded++;
            }
            else
            {
                fprintf(stderr, "load_csv: failed to store %s\n", v.name);
            }
        }
        else
        {
            fprintf(stderr, "load_csv: error in line %d: %s", line_num, line);
        }
    }
    fclose(fp);
    printf("Loaded %d vector(s) from %s\n", loaded, filename);
    return 0;
}

int save_csv(const char *filename)
{
    if(!filename || !*filename)
    {
        fprintf(stderr, "save_csv: invalid filename.\n");
        return -1;
    }

    FILE *fp = fopen(filename, "w");
    if(!fp)
    {
        perror("save_csv: fopen");
        return -1;
    }

    //header line
    fprintf(fp, "name,x,y,z\n");

    for(Node *p = g_head; p; p = p->next)
    {
        fprintf(fp, "%s,%.17g,%.17g,%.17g\n",
                p->data.name, p->data.x, p->data.y, p->data.z);
    }
    fclose(fp);
    printf("Saved %s\n", filename);
    return 0;
}