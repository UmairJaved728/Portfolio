#ifndef USER
#define USER

#include<stdio.h>
#include<string.h>
#include "Meal.c"
#include "Entity.c"

#define MAX_CART_ITEMS 30

typedef struct User{
    Entity e;
    char address[100];
    int wallet;
    Meal* cart[MAX_CART_ITEMS];
    int numOfMeals;
}User;

void initializeUser(User* u, const char* name, const char* id, const char* password, const char* address, int wallet)
{
    initializeEntity(&u->e, name, id, password);
    strcpy(u->address, address);
    u->wallet = wallet;
    u->numOfMeals = 0;
}

void addToUserCart(User* u, Meal* meal)
{
    if(u->numOfMeals < MAX_CART_ITEMS)
        u->cart[u->numOfMeals++] = meal;
    else 
        printf("\n\n\t\t\t\t\t\t\t<-----------------Cart is Full----------------->\n\n");
}

void showCart(User* u)
{
    int i;
    if(u->numOfMeals == 0)
        printf("\n\n\t\t\t\t\t\t\t<-----------------Cart is Empty----------------->\n\n");
    else
    {
        for(i=0; i < u->numOfMeals; i++)
            displayList(u->cart[i]);
    }
}

void emptyCart(User *u)
{
    u->numOfMeals = 0;
}

int calculatePriceOfCart(User* u)
{
    int price = 0, i;
    for(i=0; i < u->numOfMeals; i++)
        price += u->cart[i]->price;

    return price;
}

void userStdOut(User* u, FILE* file)
{

    if(file == NULL)
    {
        printf("%s\t", u->e.id);
        printf("%s\t", u->e.name);
        printf("%s\t", u->e.password);
        printf("%s\t", u->address);
        printf("%d\t", u->wallet);
        printf("\n");
    }
    else
    {
        fprintf(file, "%s,", u->e.id);
        fprintf(file, "%s,", u->e.name);
        fprintf(file, "%s,", u->e.password);
        fprintf(file, "%s,", u->address);
        fprintf(file, "%d,", u->wallet);
        fprintf(file, "\n");
    }
}

#endif