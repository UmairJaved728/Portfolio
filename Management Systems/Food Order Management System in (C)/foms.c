#ifndef FOODSYSTEM
#define FOODSYSTEM

#include<stdio.h>
#include<string.h>
#include "foms.h"
#include "utilities.h"
#include "DisjointList.c"
#include "User.c"
#include "Meal.c"
#include "Restaurant.c"

// The main program starts from here as main menu
void mainMenu(FOMS *f)
{
    int option = 0;
    char header[2000];
    do {
        char s[][100] = {"Restaurant Panel", "Users Panel", "Exit"};    // options to print
        int count = 3;
        getMainMenuHeader(header);  
        option = optionsScreen(s, count, header);   // get input
        switch (option) {
            case 1:
                RestaurantPanel(f);
                break;
            case 2:
                UsersPanel(f);
                break;
            case 3:
                return;
            default:
                printf("Unexpected Error From Main Menu\n\n");
        }
    }while(option != 3);    // loop until exit
}

void RestaurantPanel(FOMS *f)
{
    int option = 0;
    char s1[][100] = {"Login as Existing Restaurant", "Register a New Restaurant", "Go Back"};
    int count = 3;
    char name[100];
    char header[2000];
    f->loggedInRestaurant = NULL;
    getRestaurantHeader(header);
    option = optionsScreen(s1, count, header);
    switch (option)
    {
        case 1:
            f->loggedInRestaurant = restaurantLogin(f);
            break;
        case 2:
            f->loggedInRestaurant = restaurantSignUp(f);
            break;
        case 3:
            return;
        default:
            printf("Unexpected Error From Restaurant Panel\n\n");
    }

    // if the user cancelled to login
    if(f->loggedInRestaurant == NULL)
        return;

    strcat(header, "\n\n\n");
    sprintf(name, "\t\t\t\t\t\t\t\t|----->    Welcome %s    <-----|\n", f->loggedInRestaurant->e.name);
    strcat(header, name);

    char s2[][100] = {"Check List of Available Meals", "Add a New Meal", "Delete a Existing Meal", "Update a meal", "Logout"};
    count = 5;

    do {
        option = optionsScreen(s2, count, header);
        switch(option)
        {
            case 1:
                printMealsList(f->meals, f->loggedInRestaurant->e.id, f->loggedInRestaurant->e.name, header, false);
                suspend();
                break;
            case 2:
                addNewMeal(f, header);
                break;
            case 3:
                removeMeal(f, header);
                break;
            case 4:
                updateMeal(f, header);
                break;
            case 5:
                f->loggedInRestaurant = NULL;   // logout
                return;
            default:
                printf("Unexpected Error From Restaurant Panel\n\n");
        }
    }while(option != 5);
}

Restaurant* restaurantLogin(FOMS* f)
{
    char id[30], password[30];
    Restaurant* res = NULL;
    int i;
    bool loggedIn = true;
    char header[2000];
    getRestaurantHeader(header);
    char confirmHeader[2000];
    getConfirmHeader(confirmHeader);
    char confirmH[2000];
    confirmH[0] = '\0';

    do {
        system("cls");
        printf("%s", header);
        printf("\n\n\t\t\t\t");
        for( i = 0; i < 50; i++)
            printf("<>");
        printf("\n\n\n");
        printf("\t\t\t\t\t\t\t\t\t----------------------\n");
        printf("\t\t\t\t\t\t\t\t\t|  Restaurant Login  |\n");
        printf("\t\t\t\t\t\t\t\t\t----------------------\n\n");
        printf("\n\t\t\t\t");
        for( i = 0; i < 50; i++)
            printf("<>");
        printf("\n\n\n\t\t\t\t\t\t\t\t");
        printf("Enter Restaurant ID: ");
        scanf("%s", id);
        toIDCase(id);
        printf("\n\t\t\t\t\t\t\t\t");
        printf("Enter Password: ");
        scanf("%s", password);

        res = NULL;
        for(i=0; i<f->restaurantsCount; i++) {
            if (authLogin(&f->restaurants[i].e, id, password)) {
                res = &f->restaurants[i];
            }
        }
        if (res == NULL) {
            loggedIn = confirmationScreen("\tIncorrect ID or Password! Do you want to Login Again?", confirmH);
        } else
            return res;
    }while(loggedIn);
    return NULL;
}

Restaurant* restaurantSignUp(FOMS* f)
{
    char name[30], id[30], password1[30], password2[30];
    bool flag = true;
    int i;
    char header[2000];
    getRestaurantHeader(header);
    char confirmHeader[2000];
    getConfirmHeader(confirmHeader);

    do {
        system("cls");
        printf("%s", header);
        printf("\n\n\t\t\t\t");
        for( i = 0; i < 50; i++)
            printf("<>");
        printf("\n\n\n");
        printf("\t\t\t\t\t\t\t\t\t-----------------------\n");
        printf("\t\t\t\t\t\t\t\t\t|  Restaurant SignUp  |\n");
        printf("\t\t\t\t\t\t\t\t\t-----------------------\n\n");
        printf("\n\t\t\t\t");
        for( i = 0; i < 50; i++)
            printf("<>");
        printf("\n\n\n\t\t\t\t\t\t\t\t");
        printf("Enter Restaurant Name: ");
        scanf("%[^\n]s", name);     // input till \n
        toNameCase(name);
        printf("\n\t\t\t\t\t\t\t\t");
        printf("Enter Restaurant ID: ");
        scanf("%s", id);
        toIDCase(id);
        printf("\n\t\t\t\t\t\t\t\t");
        printf("Enter Password: ");
        scanf("%s", password1);
        printf("\n\t\t\t\t\t\t\t\t");
        printf("Confirmation! Enter Password Again: ");
        scanf("%s", password2);
        if ( strcmp(password1, password2) != 0 ) {
            printf("\n\t\t\t\t\t\t\t\t");
            printf("OOPS! Password Does not Match.\n\n");
            for(i=3; i>=1; i--) {
                printf("\r\t\t\t\t\t\t\t\tTry Again in %d seconds.", i);
                Sleep(1000);
            }
        }
        bool isValidLogin = true;
        for(i=0; i<f->restaurantsCount; i++)
        {
            if(!strcmp(password1, password2) && !strcmp(f->restaurants[i].e.id, id)) {
                flag = confirmationScreen("Restaurant with this ID Already exists. Do you want to try Signing up Again?", confirmHeader);
                isValidLogin = false;
            }

        }
        if (isValidLogin && !strcmp(password1, password2))
        {
            initializeRestaurant(&(f->restaurants[f->restaurantsCount]), name, id, password1 );
            f->restaurantsCount++;
            return &(f->restaurants[f->restaurantsCount-1]);
        }
        clearInputBuffer();
    }while(flag);
    return NULL;
}

void addNewMeal(FOMS* f, char* header)
{
    char type[20], name[30], description[100], price[10];
    char id[30];
    strcpy(id, f->loggedInRestaurant->e.id);
    int i;
    system("cls");
    printf("%s", header);
    printf("\n\n\t\t\t\t");
    for( i = 0; i < 50; i++)
        printf("<>");
    printf("\n\n\n\t\t\t\t\t\t\t\t\t|---->   ADD NEW MEAL   <----|");
    printf("\n\n\n\t\t\t\t");
    for( i = 0; i < 50; i++)
        printf("<>");
    printf("\n\n\t\t\t\t\t\t\t\t");
    printf("Enter the type of Meal (e.g Pizza, Burger): ");
    scanf("%s", type);
    toIDCase(type);
    clearInputBuffer();
    printf("\n\t\t\t\t\t\t\t\t");
    printf("Enter the Name of Meal: ");
    scanf("%[^\n]s", name);
    toNameCase(name);
    printf("\n\t\t\t\t\t\t\t\t");
    clearInputBuffer();
    printf("Enter the brief Description of the meal: ");
    scanf("%[^\n]s", description);
    printf("\n\t\t\t\t\t\t\t\t");
    clearInputBuffer();
    printf("Enter the price of the meal: ");
    scanf("%s", price);
    Meal *newMeal = (Meal*)malloc(sizeof(Meal));
    initializeMeal(newMeal, id, type, name, description, atoi(price));
    addMeal(f->meals ,id, newMeal);
    f->mealsCount++;
    printf("\n\n\t\t\t\t\t\t\t\t");
    printf("<-----------------Meal Added Successfully------------------->\n\n");
    for(i = 3; i >= 1; i--)
    {
        printf("\r\t\t\t\t\t\t\t\tReturning to previous screen in %d seconds.", i);
        Sleep(1000);
    }
}

void removeMeal(FOMS* f, char* header)
{
    char name[30];
    char id[30];
    strcpy(id, f->loggedInRestaurant->e.id);
    int i;
    system("cls");
    printf("%s", header);
    printf("\n\n\t\t\t\t");
    for( i = 0; i < 50; i++)
        printf("<>");
    printf("\n\n\n\t\t\t\t\t\t\t\t\t|---->   DELETE A MEAL   <----|");
    printf("\n\n\n\t\t\t\t");
    for( i = 0; i < 50; i++)
        printf("<>");
    printf("\n\t\t\t\t\t\t\t\t");
    printMealsList(f->meals, id, f->loggedInRestaurant->e.name, header, false);
    printf("\n\n\t\t\t\t\t\t\t\t");
    printf("Enter the name of the meal you want to delete: ");
    scanf("%[^\n]s", name);
    toNameCase(name);
    if(deleteMeal(f->meals, id, name)) {
        f->mealsCount--;
        printf("\n\n\t\t\t\t\t\t\t\t");
        printf("<-----------------Meal Deleted Successfully------------------->\n\n");
        for(i = 3; i >= 1; i--)
        {
            printf("\r\t\t\t\t\t\t\t\tReturning to previous screen in %d seconds.", i);
            Sleep(1000);
        }
    }
    else
        system("pause");
}

void updateMeal(FOMS *f, char* header)
{
    char name[30];
    int i;
    char id[30];
    strcpy(id, f->loggedInRestaurant->e.id);
    system("cls");
    printf("%s", header);
    printf("\n\n\t\t\t\t");
    for( i = 0; i < 50; i++)
        printf("<>");
    printf("\n\n\n\t\t\t\t\t\t\t\t\t|---->   UPDATE A MEAL   <----|");
    printf("\n\n\n\t\t\t\t");
    for( i = 0; i < 50; i++)
        printf("<>");
    printf("\n\t\t\t\t\t\t\t\t");
    printMealsList(f->meals, id, f->loggedInRestaurant->e.name, header, false);
    printf("\n\n\t\t\t\t\t\t\t\t");
    printf("Enter the name of the Meal you want to update: ");
    scanf("%[^\n]s", name);
    toNameCase(name);
    Meal *meal = NULL;
    meal = getMealbyNameAndKey(f->meals, id, name);
    if(meal == NULL) {
        system("pause");
        return;
    }
    char tempHeader[2000], temp[2000];
    strcpy(tempHeader, header);
    sprintf(temp, "\n\n\t\t\t\t\t\t\t\t|----->    Selected Meal: %s    <-----|\n\n\n\t\t\t\t\t\t\t\tWhat do you want to Update?\n\n", name);
    char updated[100];
    bool flag = true;
    do {
        strcpy(header, tempHeader);
        strcat(header, temp);
        char s[][100] = {"Type", "Name", "Description", "Price", "Go Back"};
        int option = optionsScreen(s, 5, header);
        switch (option) {
            case 1:
                printf("\n\n\t\t\t\t\t\t\t\t");
                printf("Enter the new type of the meal: ");
                scanf("%[^\n]s", updated);
                toIDCase(updated);
                strcpy(meal->typeOfMeal, updated);
                break;
            case 2:
                printf("\n\n\t\t\t\t\t\t\t\t");
                printf("Enter the new Name of the meal: ");
                scanf("%[^\n]s", updated);
                toNameCase(updated);
                strcpy(meal->mealName, updated);
                break;
            case 3:
                printf("\n\n\t\t\t\t\t\t\t\t");
                printf("Enter the new Description of the meal: ");
                scanf("%[^\n]s", updated);
                strcpy(meal->description, updated);
                break;
            case 4:
                printf("\n\n\t\t\t\t\t\t\t\t");
                printf("\nEnter the new Price of the meal: ");
                scanf("%s", updated);
                meal->price = atoi(updated);
                break;
            case 5:
                return;
            default:
                printf("Unexpected Error From update meal\n\n");
        }
        flag = confirmationScreen("Do You want to update anything else in this meal?", tempHeader);
    }while(flag);
}

void UsersPanel(FOMS* f)
{
    int option = 0;
    char s1[][100] = {"Login as Existing User", "Register as a New User", "Go Back"};
    int count = 3;
    char header[2000];
    getUserHeader(header);
    option = optionsScreen(s1, count, header);
    switch (option)
    {
        case 1:
            f->loggedInUser = UserLogin(f);
            break;
        case 2:
            f->loggedInUser = UserSignUp(f);
            break;
        case 3:
            return;
        default:
            printf("Unexpected Error From Users Panel\n\n");
    }

    if(f->loggedInUser == NULL)
        return;

    strcat(header, "\n\n\n");
    char temp[200];
    sprintf(temp, "\t\t\t\t\t\t\t\t|----->    Welcome %s    <-----|\n", f->loggedInUser->e.name);
    strcat(header, temp);

    char s2[][100] = {"Order Food", "View Cart", "Manage Wallet", "Change Address", "Logout"};
    count = 5;

    do {
        option = optionsScreen(s2, count, header);
        switch(option)
        {
            case 1:
                orderFood(f, header);
                break;
            case 2:
                viewCart(f, header);
                break;
            case 3:
                manageWallet(f, header);
                break;
            case 4:
                changeAddress(f, header);
                break;
            case 5:
                f->loggedInUser = NULL;
                return;
            default:
                printf("Unexpected Error From Users Panel\n\n");
        }
    }while(option != 5);
}

User* UserLogin(FOMS *f)
{
    char id[30], password[30];
    int i;
    User* user = NULL;
    bool loggedIn = true;
    char header[2000];
    char confirmHeader[2000];
    confirmHeader[0] = '\0';
    getUserHeader(header);

    do {
        system("cls");
        printf("%s", header);
        printf("\n\n\t\t\t\t");
        for( i = 0; i < 50; i++)
            printf("<>");
        printf("\n\n\n");
        printf("\t\t\t\t\t\t\t\t\t----------------------\n");
        printf("\t\t\t\t\t\t\t\t\t|     USER LOGIN     |\n");
        printf("\t\t\t\t\t\t\t\t\t----------------------\n\n");
        printf("\n\t\t\t\t");
        for( i = 0; i < 50; i++)
            printf("<>");
        printf("\n\n\n\t\t\t\t\t\t\t\t");
        printf("Enter User ID: ");
        scanf("%s", id);
        toIDCase(id);
        printf("\n\t\t\t\t\t\t\t\t");
        printf("Enter Password: ");
        scanf("%s", password);

        for(i=0; i<f->usersCount; i++)
            if(authLogin(&f->users[i].e, id, password))
            {
                user = &f->users[i];
            }
        if (user == NULL) {
            loggedIn = confirmationScreen("Incorrect ID or Password. Do you want to Login Again?", confirmHeader);
        } else
            return user;
    }while(loggedIn);
    return NULL;
}

User* UserSignUp(FOMS *f)
{
    char name[30], id[30], password1[30], password2[30], address[100];
    char confirmHeader[2000];
    confirmHeader[0] = '\0';
    bool flag = true;
    int i;
    char header[2000];
    getUserHeader(header);
    do {
        system("cls");
        printf("%s", header);
        printf("\n\n\t\t\t\t");
        for( i = 0; i < 50; i++)
            printf("<>");
        printf("\n\n\n");
        printf("\t\t\t\t\t\t\t\t\t----------------\n");
        printf("\t\t\t\t\t\t\t\t\t|  USER SignUp  |\n");
        printf("\t\t\t\t\t\t\t\t\t----------------\n\n");
        printf("\n\t\t\t\t");
        for( i = 0; i < 50; i++)
            printf("<>");
        printf("\n\n\n\t\t\t\t\t\t\t\t");
        printf("Enter Your Name: ");
        scanf("%[^\n]s", name);
        toNameCase(name);
        printf("\n\t\t\t\t\t\t\t\t");
        clearInputBuffer();
        printf("Enter Your Address: ");
        scanf("%[^\n]s", address);
        printf("\n\t\t\t\t\t\t\t\t");
        clearInputBuffer();
        printf("Enter your ID: ");
        scanf("%s", id);
        toIDCase(id);
        printf("\n\t\t\t\t\t\t\t\t");
        clearInputBuffer();
        printf("Enter Password: ");
        scanf("%s", password1);
        printf("\n\t\t\t\t\t\t\t\t");
        clearInputBuffer();
        printf("Confirmation! Enter Password Again: ");
        scanf("%s", password2);
        if (strcmp(password1, password2)) {
            printf("\n\t\t\t\t\t\t\t\t");
            printf("OOPS! Password Does not Match.\n\n");
            for(i=3; i>=1; i--) {
                printf("\r\t\t\t\t\t\t\t\tTry Again in %d seconds.", i);
                Sleep(1000);
            }
            clearInputBuffer();
        }
        bool isValidLogin = true;
        for(i=0; i<f->usersCount; i++)
        {
            if(!strcmp( password1, password2) && !strcmp(f->users[i].e.id, id)) {
                flag = confirmationScreen("User with this ID Already exists. Do you want to try Signing up Again?", confirmHeader);
                isValidLogin = false;
            }

        }
        if (isValidLogin && !strcmp(password1,password2))
        {
            initializeUser(&(f->users[f->usersCount]), name, id, password1, address, 0);
            f->usersCount++;
            return &(f->users[f->usersCount-1]);
        }
    }while(flag);
    return NULL;
}

void orderFood(FOMS *f, char* header)
{
    int option = 3;
    char s[][100] = {"Search Meals by Restaurant", "Search Meals by Name", "Go Back"};
    getOrderHeader(header);
    char temp[2000];
    strcpy(temp, header);
    strcat(temp, "\n\n\t\t\t\t\t\t\t\tHow do you want to search for your favourite Meals?");
    option = optionsScreen(s, 3, temp);
    switch(option)
    {
        case 1:
            orderByResturant(f, header);
            break;
        case 2:
            orderBySearch(f, header);
            break;
        case 3:
            return;
        default:
            printf("Unexpected Error From Order Food\n\n");
    }
}

Restaurant* getRestaurantbyName(FOMS* f, char *name)
{
    int i;
    for(i = 0; i < f->restaurantsCount; i++)
        if(!strcmp(name, f->restaurants[i].e.name))
            return &f->restaurants[i];
    return NULL;
}

void orderByResturant(FOMS* f, char* header)
{
    char name[30];
    Meal* meal = NULL;
    int i;
    do{
        system("cls");
        printf("%s", header);
        printf("\n\n\t\t\t\t\t\t\t\t|---->   Available Restaurants   <----|\n");
        for(i = 0; i < f->restaurantsCount; i++)
            printf("\n\n\t\t\t\t\t\t\t\t\t-->   %s\n", f->restaurants[i].e.name);
        printf("\n\n\t\t\t\t\t\t\t\tEnter the Restaurant Name --> ");
        scanf("%[^\n]s", name);
        f->loggedInRestaurant = getRestaurantbyName(f, name);
        if(f->loggedInRestaurant == NULL)
        {
            printf("\n\n\t\t\t\t\t\t\t\t");
            printf("<----------------- Restaurant Does not Exist ------------------->\n\n");
            for(i = 3; i >= 1; i--)
            {
                printf("\r\t\t\t\t\t\t\t\tReturning to previous screen in %d seconds.", i);
                Sleep(1000);
            }
            clearInputBuffer();
        }
    }while(f->loggedInRestaurant == NULL);

    do{
        printMealsList(f->meals, f->loggedInRestaurant->e.id, f->loggedInRestaurant->e.name, header, true);
        clearInputBuffer();
        printf("\n\n\t\t\t\t\t\t\t\t");
        printf("Enter the Meal Name: ");
        scanf("%[^\n]s", name);
        toNameCase(name);
        meal = getMealbyName(f->meals, name);
        if(meal == NULL)
        {
            printf("\n\n\t\t\t\t\t\t\t\t");
            printf("<----------------- Meal Does not Exist ------------------->\n\n");
            for(i = 3; i >= 1; i--)
            {
                printf("\r\t\t\t\t\t\t\t\tReturning to previous screen in %d seconds.", i);
                Sleep(1000);
            }
        }
    }while(meal == NULL);
    f->loggedInRestaurant = NULL;
    addToCart(f, meal, header);
}

void orderBySearch(FOMS* f, char* header)
{
    char type[20], name[30];
    Meal *meal = NULL;
    int i;

    do {
        system("cls");
        printf("%s", header);
        printf("\n\n\t\t\t\t\t\t\t\t|---->   Search for your Favourite Meals.   <----|\n");
        printf("\n\n\t\t\t\t\t\t\t\t");
        printf("Enter your keywords (e.g pizza, burger) --> ");
        scanf("%[^\n]s", type);
        toIDCase(type);
        printf("\n");
        showMealsBySearch(f->meals, type);
        printf("\n\n\t\t\t\t\t\t\t\t");
        clearInputBuffer();
        printf("Enter the Meal Name (Case Sensitive): ");
        scanf("%[^\n]s", name);
        toNameCase(name);
        meal = getMealbyName(f->meals, name);
        printf("\n%s\n", name);
        if(meal == NULL)
        {
            printf("\n\n\t\t\t\t\t\t\t\t");
            printf("<----------------- Meal Does not Exist ------------------->\n\n");
            for(i = 3; i >= 1; i--)
            {
                printf("\r\t\t\t\t\t\t\t\tReturning to previous screen in %d seconds.", i);
                Sleep(1000);
            }
            clearInputBuffer();
        }
    }while(meal == NULL);
    addToCart(f, meal, header);
}

void addToCart(FOMS *f, Meal* meal, char* header)
{
    char confirmHeader[2000];
    confirmHeader[0] = '\0';
    system("cls");
    int i;
    printf("%s", header);
    printf("\n\n\t\t\t\t\t\t\t\t|---->   Selected Meal   <----|\n\n\n");
    displayList(meal);
    printf("\n\n\t\t\t\t\t\t\t\t\t");
    printf("-->   Processing...");
    Sleep(3000);
    char confirmMeal[2000];
     strcpy(confirmMeal, "\tAre You sure you want to add ");
    strcat(confirmMeal, meal->mealName);
    strcat(confirmMeal, " to your cart.");
    bool isConfirmed = confirmationScreen(confirmMeal, confirmHeader);
    system("cls");
    printf("%s", header);
    printf("\n\n\t\t\t\t\t\t\t\t|---->   Selected Meal   <----|\n\n\n");
    displayList(meal);
    printf("\n\n\t\t\t\t\t\t");
    if(isConfirmed){
        addToUserCart(f->loggedInUser, meal);
        printf("<-----------------Meal Successfully Added to cart------------------->\n\n");
    }
    else{
        printf("<-----------------Cancelled Adding to Cart------------------->\n\n");
    }
    for(i = 3; i >= 1; i--)
    {
        printf("\r\t\t\t\t\t\t\tReturning to previous screen in %d seconds.", i);
        Sleep(1000);
    }
}

void viewCart(FOMS *f, char* header)
{
    system("cls");
    int i;
    getCartHeader(header);
    printf("%s", header);
    char tempCart[2000];
    strcpy(tempCart, header);
    printf("\n\n\t\t\t\t\t\t\t\t|---->   VIEW CART   <----|\n\n\n");
    showCart(f->loggedInUser);
    printf("\n\n\n\n\t\t\t\t\t\t\t\t Grand Total --> $ %d.\n\n\n", calculatePriceOfCart(f->loggedInUser));
    system("pause");
    char s[][100] = {"Checkout", "Empty Cart", "Go Back"};
    int option = optionsScreen(s, 3, tempCart);
    switch(option)
    {
        case 1:
            checkoutMeal(f, header);
            break;
        case 2:
            emptyCart(f->loggedInUser);
            printf("\n\n\t\t\t\t\t\t\t<-----------------Cart Emptied Successfully------------------->\n\n");
            for(i = 3; i >= 1; i--)
            {
                printf("\r\t\t\t\t\t\t\t\tReturning to previous screen in %d seconds.", i);
                Sleep(1000);
            }
            return;
        case 3:
            return;
        default:
            printf("Unexpected Error From view cart\n\n");
    }
}

void checkoutMeal(FOMS *f, char* header)
{
    char confirmHeader[2000];
    confirmHeader[0] = '\0';
    int price = calculatePriceOfCart(f->loggedInUser);
    system("cls");
    getCartHeader(header);
    printf("%s", header);
    strcat(header, "\n\n\t\t\t\t\t\t\t\t|---->   CHECKOUT   <----|\n");
    strcat(header, "\n\n\t\t\t\t\t\t\t\t");
    char confirm[500];
    sprintf(confirm, "Are You sure you want to checkout all the Meals from your Cart?\n\t\t\t\t\t\t\tAn amount of $. %d will be deducted from your wallet.\n\n\t\t\t\t\t\t\tDelivery Address: %s\n", price, f->loggedInUser->address);
    bool isConfirmed = confirmationScreen(confirm, confirmHeader);

    system("cls");
    printf("%s", header);
    if(isConfirmed)
    {
        int wallet = f->loggedInUser->wallet;
        if(price < wallet)
        {
            f->loggedInUser->wallet -= price;
            printf("\n\n\t\t\t\t\t\t\t\t");
            printf("--> Order Placed Successfully!!\n");
            printf("\n\n\t\t\t\t\t\t\t\t");
            printf("--> Your Meals are on their way. Please be patient. ");
            printf("\n\n\t\t\t\t\t\t\t\t");
            printf("--> Deducted %d $ from your wallet. New Balance is %d.\n", price, f->loggedInUser->wallet);
            printf("\n\n\t\t\t\t\t\t\t\t");
            printf("<---------------------Thanks For Ordering!!!---------------------->\n\n");
            emptyCart(f->loggedInUser);
        }
        else{
            printf("\n\n\t\t\t\t\t\t");
            printf("You don't have enough balance in your wallet. Please Deposit funds and try ordering Again!!\n\n");
        }
    }
    else {
        printf("<-----------------Checkout Cancelled Successfully------------------->\n\n");
    }
    system("pause");
}

void manageWallet(FOMS* f, char* header)
{
    system("cls");
    getWalletHeader(header);
    strcat(header,  "\n\n\t\t\t\t\t\t\t\t|---->   MANAGE WALLET   <----|\n");
    strcat(header, "\n\n\t\t\t\t\t\t\t\t");
    char temp[100];
    sprintf(temp, "-->  Current Balance: %d\n\n", f->loggedInUser->wallet);
    strcat(header, temp);
    printf("%s", header);
    char s[][100] = {"Deposit Amount", "Go Back"};
    int option = optionsScreen(s, 2, header);
    switch(option)
    {
        case 1:
            depositInWallet(f, header);
            break;
        case 2:
            return;
        default:
            printf("Unexpected Error From Manage Wallet\n\n");
    }
}

void changeAddress(FOMS* f, char* header)
{
    system("cls");
    int i;
    char confirm[400];
    printf("%s", header);
    strcpy(confirm, "\n\n\t\t\t\t\t\t\t\t|---->   Change Address   <----|\n\n\t\t\t\t\t\t--> Current Address: ");
    sprintf(confirm, "%s\n\n\t\t\t\t\t\t-->   Are you sure you want to change this address?\n", f->loggedInUser->address);
    bool isConfirmed = confirmationScreen(confirm, header);
    if(isConfirmed)
    {
        char address[100];
        printf("\n\n\t\t\t\t\t\t\t\t");
        printf("-->   Enter the New Address: ");
        scanf("%[^\n]s", address);
        strcpy(f->loggedInUser->address, address);
        printf("\n\n\t\t\t\t\t\t\t");
        printf("<-----------------Address Changed Successfully------------------->\n\n");
    }
    else
        printf("\n\n\t\t\t\t\t\t\t<-----------------Cancelled Request------------------->\n\n");
    for(i = 3; i >= 1; i--)
    {
        printf("\r\t\t\t\t\t\t\tReturning to previous screen in %d seconds.", i);
        Sleep(1000);
    }
}

void depositInWallet(FOMS *f, char* header)
{
    char accountNo[20], pin[10];
    int i;
    int amount;
    do {
        system("cls");
        printf("%s", header);
        printf("\n\n\t\t\t\t\t\t\t\t|---->   DEPOSIT AMOUNT   <----|\n");
        printf("\n\n\t\t\t\t\t\t\t\t");
        printf("-->   Enter 12 digit Credit Card Number: ");
        scanf("%s", accountNo);
        printf("\n\n\t\t\t\t\t\t\t\t");
        printf("-->   Enter 4 digit pin: ");
        scanf("%s", pin);
        if(strlen(accountNo) != 12)
            printf("\n\n\t\t\t\t\t\t\t\tInvalid Credit card number!! Length must be 12\n");
        if(strlen(pin) != 4)
            printf("\n\t\t\t\t\t\t\t\tInvalid pin!! Length must be 4\n\n\n");
        if(strlen(accountNo) != 12 || strlen(pin) != 4)
            for(i = 3; i >= 1; i--)
            {
                printf("\r\t\t\t\t\t\t\t\tReturning to previous screen in %d seconds.", i);
                Sleep(1000);
            }
    }while(strlen(accountNo) != 12 || strlen(pin) != 4);

    do{
        printf("\n\n\t\t\t\t\t\t\t\t");
        printf("-->   Enter the amount you want to deposit (Max Amount = 50,000): ");
        scanf("%d", &amount);
    }while(amount <= 0 || amount > 50000);
    clearInputBuffer();
    f->loggedInUser->wallet += amount;
    printf("\n\n\t\t\t\t\t\t\t");
    printf("<--------------%d $ added to your wallet successfully. Your new balance is %d.------------>\n\n\n", amount, f->loggedInUser->wallet);
    for(i = 3; i >= 1; i--)
    {
        printf("\r\t\t\t\t\t\t\tReturning to previous screen in %d seconds.", i);
        Sleep(1000);
    }
}

void initializeFOMS(FOMS *f)
{
    //string name, id, password,wallet, typeOfMeal, description, price, address;
    int i;
    FILE* file;
    Meal *m;
    initializeDisjointList(&f->meals);
    f->loggedInRestaurant = NULL;
    f->loggedInUser = NULL;

    file = fopen("Users.bin", "rb");
    if(file == NULL)
    {
        printf("\nOOPS!! Users.bin File does not Exist\n\n");
    }
    fread(&f->usersCount, sizeof(int), 1, file);
    for(i=0; i<f->usersCount; i++)
    {
        fread(&f->users[i], sizeof(User), 1, file);
    }
    fclose(file);

    file = fopen("Restaurants.bin", "rb");
    if(file == NULL)
        printf("\nOOPS!! Restaurants.bin File does not Exist\n\n");
    fread(&f->restaurantsCount, sizeof(int), 1, file);
    for(i=0; i<f->restaurantsCount; i++) {
        fread(&f->restaurants[i], sizeof(Restaurant), 1, file);
    }
    fclose(file);

    file = fopen("Meals.bin", "rb");
    if(file == NULL)
        printf("OOPS!! Meals.bin File does not Exist\n\n");

    fread(&f->mealsCount, sizeof(int), 1, file);
    for(i=0; i<f->mealsCount; i++)
    {
        m = (Meal*)malloc(sizeof(Meal));
        fread(m, sizeof(Meal), 1, file);
        addMeal(f->meals, m->resID, m);
    }
    fclose(file);
}

void saveFOMS(FOMS* f)
{
    FILE* file;
    int i;

    file = fopen("Users.bin", "wb");
    fwrite(&f->usersCount, sizeof(int), 1, file);
    for(i=0; i<f->usersCount; i++)
        fwrite(&f->users[i], sizeof(User), 1, file);
    fclose(file);

    file = fopen("Restaurants.bin", "wb");
    fwrite(&f->restaurantsCount, sizeof(int), 1, file);
    for(i=0; i<f->restaurantsCount; i++)
        fwrite(&f->restaurants[i], sizeof(Restaurant), 1, file);
    fclose(file);

    file = fopen("Meals.bin", "wb");
    fwrite(&f->mealsCount, sizeof(int), 1, file);
    DisjointSetStdOut(f->meals, file);
    fclose(file);
}

void freeMemory(FOMS **f)
{
    freeMemoryList(&(*f)->meals);
    free((*f));
    (*f) = NULL;
}

void start(FOMS *f)
{
    f = (FOMS*)malloc(sizeof(FOMS));
    initializeFOMS(f);
    startIntro();
    mainMenu(f);
    saveFOMS(f);
    freeMemory(&f);
}

#endif
