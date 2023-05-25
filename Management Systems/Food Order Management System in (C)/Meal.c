#ifndef MEAL
#define MEAL

#include<stdio.h>
#include<string.h>

typedef struct Meal{
    char resID[30];
    char mealName[30];
    char description[100];
    char typeOfMeal[20];
    int price;
}Meal;

void initializeMeal(Meal *m, const char* resID, const char* typeOfMeal, const char* mealName, const char* description, int price)
{
    strcpy(m->resID, resID);
    strcpy(m->typeOfMeal, typeOfMeal);
    strcpy(m->mealName, mealName);
    strcpy(m->description, description);
    m->price = price;
}

void mealStdOut(Meal *m, FILE* file)
{
    if(file == NULL)
    {
        printf("%s\t", m->resID);
        printf("%s\t", m->typeOfMeal);
        printf("%s\t", m->mealName);
        printf("%s\t", m->description);
        printf("%d\t", m->price);
        printf("\n");
    }
    else 
    {
        fprintf(file, "%s,", m->resID);
        fprintf(file, "%s,", m->typeOfMeal);
        fprintf(file, "%s,", m->mealName);
        fprintf(file, "%s,", m->description);
        fprintf(file, "%d,", m->price);
        fprintf(file, "\n");
    }
}

void displayList(Meal *m)
{
    printf("\t\t\t\t\t\tMeal Name --> %s", m->mealName);
    printf("\t\tPrice --> $ %d\n", m->price);
    printf("\t\t\t\t\t\t---------");
    printf("\n\t\t\t\t\t\tDescription --> %s\n", m->description);
    printf("\t\t\t\t\t\t<------------------------------------->\n\n");
}

#endif