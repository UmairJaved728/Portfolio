#ifndef ENTITY
#define ENTITY

#include<stdio.h>
#include<stdbool.h>
#include<string.h>

typedef struct Entity{
    char name[30];
    char id[30];
    char password[30];
}Entity;

void initializeEntity(Entity *e, const char* name, const char* id, const char* password)
{
    strcpy(e->name, name);
    strcpy(e->id, id);
    strcpy(e->password, password);
}

bool authLogin(Entity *e, const char* id, const char* password)
{
    return (!strcmp(e->id, id) && !strcmp(e->password, password));
}

#endif