#ifndef RESTAURANT
#define RESTAURANT

#include<stdio.h>
#include<string.h>
#include "Entity.c"

typedef struct Restaurant{
    Entity e;
}Restaurant;

void initializeRestaurant(Restaurant* r, const char* name, const char* id, const char* password)
{
    initializeEntity(&r->e, name, id, password);
}

void restaurantStdOut(Restaurant* r, FILE* file)
{

    if(file == NULL)
    {
        printf("%s\t", r->e.id);
        printf("%s\t", r->e.name);
        printf("%s\t", r->e.password);
        printf("\n");
    }
    else
    {
        fprintf(file, "%s,", r->e.id);
        fprintf(file, "%s,", r->e.name);
        fprintf(file, "%s,", r->e.password);
        fprintf(file, "\n");
    }
}

#endif