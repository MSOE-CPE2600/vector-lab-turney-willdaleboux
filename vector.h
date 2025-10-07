/*
banner
*/

typedef struct vector
{
    char name[10];
    double x;
    double y;
    double z;
} vector;

vector addvect(vector new);
vector findvect(char *name);
void clear(); //void??
