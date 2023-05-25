#ifndef FOMS_FOMS_H
#define FOMS_FOMS_H

#include<stdio.h>
#include<string.h>
#include "DisjointList.c"
#include "User.c"
#include "Meal.c"
#include "Restaurant.c"

// macros to set the limits
#define MAX_USERS 100
#define MAX_RESTAURANTS 30

// Main program structure
typedef struct FOMS{
    User users[MAX_USERS];
    Restaurant restaurants[MAX_RESTAURANTS];
    disjointList *meals;
    Restaurant* loggedInRestaurant;
    User* loggedInUser;
    int usersCount;
    int restaurantsCount;
    int mealsCount;
}FOMS;

// required functions
int optionsScreen(char s[][100], int count, char* header);
bool confirmationScreen(char* s, char header[2000]);
void mainMenu(FOMS *f);
void RestaurantPanel(FOMS *f);
Restaurant* restaurantLogin(FOMS* f);
Restaurant* restaurantSignUp(FOMS* f);
void addNewMeal(FOMS* f, char* header);
void removeMeal(FOMS* f, char* header);
void updateMeal(FOMS *f, char* header);
void UsersPanel(FOMS* f);
User* UserLogin(FOMS *f);
User* UserSignUp(FOMS *f);
void orderFood(FOMS *f, char* header);
Restaurant* getRestaurantbyName(FOMS* f, char *name);
void orderByResturant(FOMS* f, char* header);
void orderBySearch(FOMS* f, char* header);
void addToCart(FOMS *f, Meal* meal, char* header);
void viewCart(FOMS *f, char* header);
void checkoutMeal(FOMS *f, char* header);
void manageWallet(FOMS* f, char* header);
void changeAddress(FOMS* f, char* header);
void depositInWallet(FOMS *f, char* header);
void initializeFOMS(FOMS *f);
void saveFOMS(FOMS* f);
void start(FOMS *f);

#endif //FOMS_FOMS_H
