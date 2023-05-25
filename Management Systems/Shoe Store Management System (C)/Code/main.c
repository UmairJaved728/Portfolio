#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

// Maximum capacity of the shoes array
#define MAX_CAPACITY 100

// Struct to store the instance of shoes
struct Shoes{
    int number;     // shoe number
    int size;     // shoe size
    int rentDay;    // day of renting shoe
    bool isRented;  // check if the shoes is rented
    bool isLost;    // check if the shoe is lost
};

typedef struct Shoes* Shoes;    // rename the datatype for convenience

enum ShoeSize{Small, Medium, Large};        // Enum for Sizes to increase readability

// Required Variables to manage the inventory data
Shoes* shoes;
int numberOfShoes;
int currentDay;

// Helper Functions
void readInventory();
int showMenuAndInput();
int inputSize();
void rentNewShoes();
void returnShoes();
void printRentedShoesInEachSize();
void printRentedShoesOverall();
void printNotRentedShoesInEachSize();
void printNotRentedShoesOverall();
int countLostShoes(int size);
void printAnalytics();
void updateLost();
void printAllLostShoes();
void releaseMemory();

int main()
{
    int option;

    readInventory();    // read the file containing all shoes data
    do{
        option = showMenuAndInput();    // print menu and get the input option

        switch (option)
        {
            case 1:
                rentNewShoes();
                break;
            case 2:
                returnShoes();
                break;
            case 3:
                printRentedShoesInEachSize();
                break;
            case 4:
                printRentedShoesOverall();
                break;
            case 5:
                printNotRentedShoesInEachSize();
                break;
            case 6:
                printNotRentedShoesOverall();
                break;
            case 7:
                printAnalytics();
                break;
            case 8:
                printAllLostShoes();
                break;
            case 9:
                currentDay++;
                updateLost();
                break;
            default:
                printf("\nTHANK YOU FOR USING APPLICATION> GOOD BYE :-) \n");
                break;
        }
    }while(option != 0);

    releaseMemory();
    return 0;
}

void readInventory()
{
    int number;
    Shoes shoe;

    shoes = (Shoes*) malloc (sizeof (Shoes) * MAX_CAPACITY);
    currentDay = 1;
    numberOfShoes = 0;

    for(number = 1001; number <= 1030; number++)
    {
        shoe = (Shoes) malloc (sizeof(struct Shoes));
        shoe->number = number;
        shoe->size = Small;
        shoe->isRented = false;
        shoe->isLost = false;
        shoes[numberOfShoes] = shoe;
        numberOfShoes++;
    }

    for(number = 2001; number <= 2020; number++)
    {
        shoe = (Shoes) malloc (sizeof(struct Shoes));
        shoe->number = number;
        shoe->size = Medium;
        shoe->isRented = false;
        shoe->isLost = false;
        shoes[numberOfShoes] = shoe;
        numberOfShoes++;
    }

    for(number = 3001; number <= 3025; number++)
    {
        shoe = (Shoes) malloc (sizeof(struct Shoes));
        shoe->number = number;
        shoe->size = Large;
        shoe->isRented = false;
        shoe->isLost = false;
        shoes[numberOfShoes] = shoe;
        numberOfShoes++;
    }

    printf("\nInventory Data has been Successfully read.\n");
    printf("Number of Shoes in inventory: %d\n\n", numberOfShoes);
}

int showMenuAndInput()
{
    int option;

    do{
        printf("\n                                 BBB MENU                          \n");
        printf("\n<<<<<<<<<<<<------------------------------------------------------------->>>>>>>>>>>>\n\n");
        printf("Enter - 1 - to Rent a pair of Shoes to Customer.\n");
        printf("Enter - 2 - to Return a pair of Shoes from Customer.\n");
        printf("Enter - 3 - to Check Number of Shoes Currently Rented in each size.\n");
        printf("Enter - 4 - to Check Number of Shoes Currently Rented Overall.\n");
        printf("Enter - 5 - to Check Number of Shoes Currently not Rented in each Size.\n");
        printf("Enter - 6 - to Check Number of Shoes Currently not Rented Overall.\n");
        printf("Enter - 7 - to Get indication of which shoe size is the most and least commonly lost.\n");
        printf("Enter - 8 - to Check which Specific Shoes are Lost.\n");
        printf("Enter - 9 - to End the Current Day.\n");
        printf("Enter - 0 - to Quit Application.\n");
        printf("\n<<<<<<<<<<<<------------------------------------------------------------->>>>>>>>>>>>\n\n");
        printf("Enter your choice: ");
        scanf("%d", &option);

        if(option < 0 || option > 9)
        {
            printf("\n --- INVALID SELECTION ---\n");
            option = -1;
        }
    } while (option < 0 || option > 9);

    return option;
}

int inputSize()
{
    bool valid;
    char inp;
    int size;

    do {
        valid = true;
        printf("\nEnter the Size of Shoes (S -> Small, M -> Medium, L -> Large): ");
        scanf(" %c", &inp);

        inp |= 32;     // Convert to small letter if required, A -> a, a -> a
        if(inp == 's')
            size = Small;
        else if(inp == 'm')
            size = Medium;
        else if(inp == 'l')
            size = Large;
        else {
            printf("\n--- INVALID INPUT ---\n Please Enter S for Small, M for Medium, L for Large.\n");
            valid = false;
        }
    } while( !valid );

    return size;
}

void rentNewShoes()
{
    int size, i;
    bool valid;

    printf("\n *** RENT A PAIR OF SHOES ***\n");

    size = inputSize();

    valid = false;
    for( i = 0; i < numberOfShoes; i++ )
    {
        if( !shoes[i]->isRented && shoes[i]->size == size )
        {
            printf("\nRenting Pair of Shoes with Number -> %d\n", shoes[i]->number);
            shoes[i]->isRented = true;
            shoes[i]->rentDay = currentDay;
            valid = true;
            break;
        }
    }

    if( !valid )
        printf("\nNo Shoes Found of the Given Size in Inventory. Please Try Again Later.\n\n");
}

void returnShoes()
{
    int size, i;
    bool valid;

    printf("\n *** RETURNING A PAIR OF SHOES ***\n");

    size = inputSize();

    valid = false;
    for( i = 0; i < numberOfShoes; i++ )
    {
        if( shoes[i]->isRented && shoes[i]->size == size && !shoes[i]->isLost )
        {
            printf("\nReturning Pair of Shoes with Number -> %d\n", shoes[i]->number);
            shoes[i]->isRented = false;
            shoes[i]->rentDay = -1;
            valid = true;
            break;
        }
    }

    if( !valid )
        printf("\nNo Shoes of the Given Size is Rented from the Inventory \"TODAY\". Please Try Again Later.\n\n");
}

void printRentedShoesInEachSize()
{
    int size, i, count;

    printf("\n *** TOTAL OF SHOES RENTED IN EACH SIZE ***\n");

    size = Small;
    count = 0;
    for( i = 0; i < numberOfShoes; i++)
        if( shoes[i]->isRented && shoes[i]->size == size )
            count++;

    if(count == 0)
        printf("\nNo Pair of Shoes of Small Size are currently Rented.\n");
    else
        printf("\nA Total of %d Pair of Shoes of Small Size are currently Rented.\n", count);

    size = Medium;
    count = 0;
    for( i = 0; i < numberOfShoes; i++)
        if( shoes[i]->isRented && shoes[i]->size == size )
            count++;

    if(count == 0)
        printf("\nNo Pair of Shoes of Medium Size are currently Rented.\n");
    else
        printf("\nA Total of %d Pair of Shoes of Medium Size are currently Rented.\n", count);

    size = Large;
    count = 0;
    for( i = 0; i < numberOfShoes; i++)
        if( shoes[i]->isRented && shoes[i]->size == size )
            count++;

    if(count == 0)
        printf("\nNo Pair of Shoes of Large Size are currently Rented.\n");
    else
        printf("\nA Total of %d Pair of Shoes of Large Size are currently Rented.\n", count);
}

void printRentedShoesOverall()
{
    printf("\n *** TOTAL OF SHOES RENTED OVERALL ***\n");
    int count = 0, i;
    for( i = 0; i < numberOfShoes; i++)
        if( shoes[i]->isRented )
            count++;

    if(count == 0)
        printf("\nNo Pair of Shoes of any size are currently Rented.\n");
    else
        printf("\nA Total of %d Pair of Shoes of All Sizes are currently Rented.\n", count);
}

void printNotRentedShoesInEachSize()
{
    int size, i, count;

    printf("\n *** TOTAL OF SHOES NOT RENTED IN EACH SIZE ***\n");

    size = Small;
    count = 0;
    for( i = 0; i < numberOfShoes; i++)
        if( !shoes[i]->isRented && shoes[i]->size == size )
            count++;

    printf("\nA Total of %d Pair of Shoes of Small Size are Not currently Rented.\n", count);

    size = Medium;
    count = 0;
    for( i = 0; i < numberOfShoes; i++)
        if( !shoes[i]->isRented && shoes[i]->size == size )
            count++;

    printf("\nA Total of %d Pair of Shoes of Medium Size are Not currently Rented.\n", count);

    size = Large;
    count = 0;
    for( i = 0; i < numberOfShoes; i++)
        if( !shoes[i]->isRented && shoes[i]->size == size )
            count++;

    printf("\nA Total of %d Pair of Shoes of Large Size are Not currently Rented.\n", count);
}

void printNotRentedShoesOverall()
{
    printf("\n *** TOTAL OF SHOES NOT RENTED OVERALL ***\n");
    int count = 0, i;
    for( i = 0; i < numberOfShoes; i++)
        if( !shoes[i]->isRented )
            count++;

    printf("\nA Total of %d Pair of Shoes of All Sizes are Not currently Rented.\n", count);
}

void updateLost()
{
    int i, count = 0;

    for( i = 0; i < numberOfShoes; i++)
        if( shoes[i]->isRented && shoes[i]->rentDay != currentDay ) {
            shoes[i]->isLost = true;
            count++;
        }

    printf("\n%d Shoes are marked as Lost Today.\n\n", count);
}

int countLostShoes(int size)
{
    int i, count = 0;

    for( i = 0; i < numberOfShoes; i++)
        if( shoes[i]->size == size && shoes[i]->isLost )
            count++;

    return count;
}

void printAnalytics()
{
    printf("\n*** INDICATION ABOUT THE LOST SHOES ***\n\n");
    int lostSmall, lostMedium, lostLarge;

    lostSmall = countLostShoes(Small);
    lostMedium = countLostShoes(Medium);
    lostLarge = countLostShoes(Large);

    if(lostMedium == 0 && lostSmall == 0 && lostLarge == 0)
        printf("HURRAH! No Shoes are Lost So far.\n");

    // All are equal
    if( lostLarge == lostSmall && lostSmall == lostMedium )
        printf("All Shoes are Equally Likely to be Lost.\n");

    // 2 are equal and the third is larger
    else if( lostLarge > lostMedium && lostSmall == lostMedium )
        printf("Large Shoes are to be Lost Most Commonly and Small and Medium Shoes are less but equally likely to be Lost.\n");
    else if( lostSmall > lostMedium && lostMedium == lostLarge )
        printf("Small Shoes are to be Lost Most Commonly and Medium and Large Shoes are less but equally likely to be Lost.\n");
    else if( lostMedium > lostSmall && lostSmall == lostLarge )
        printf("Medium Shoes are to be Lost Most Commonly and Small and Large Shoes are less but equally likely to be Lost.\n");

    // 2 are equal and the third is smaller
    else if( lostLarge < lostMedium && lostSmall == lostMedium )
        printf("Small and Medium Shoes are More and equally likely to be Lost and the Large Shoes are to be Lost Less Commonly.\n");
    else if( lostSmall < lostMedium && lostMedium == lostLarge )
        printf("Large and Medium Shoes are More and equally likely to be Lost and the Small Shoes are to be Lost Less Commonly.\n");
    else if( lostMedium < lostSmall && lostSmall == lostLarge )
        printf("Small and Large Shoes are More and equally likely to be Lost and the Medium Shoes are to be Lost Less Commonly.\n");

    // all are different -> Most likely : highest, less likely : lowest
    else if( lostLarge > lostMedium && lostMedium > lostSmall )
        printf("Large Shoes are Most likely to be Lost and the Small Shoes are least Likely to be Lost.\n");
    else if( lostLarge > lostMedium && lostMedium < lostSmall )
        printf("Large Shoes are Most likely to be Lost and the Medium Shoes are least Likely to be Lost.\n");
    else if( lostMedium > lostSmall && lostSmall > lostLarge )
        printf("Medium Shoes are More likely to be Lost and the Large Shoes are least Likely to be Lost.\n");
    else if( lostMedium > lostSmall && lostSmall < lostLarge )
        printf("Medium Shoes are More likely to be Lost and the Small Shoes are least Likely to be Lost.\n");
    else if( lostSmall > lostMedium && lostMedium > lostLarge )
        printf("Small Shoes are More likely to be Lost and the Large Shoes are least Likely to be Lost.\n");
    else if( lostSmall > lostMedium && lostMedium < lostLarge )
        printf("Small Shoes are More likely to be Lost and the Medium Shoes are least Likely to be Lost.\n");
}

void printAllLostShoes()
{
    int count, i;

    printf("\n*** COMPLETE DETAILS OF THE LOST SHOWS ***\n\n");

    count = countLostShoes(Small);
    if(count == 0)
        printf("No Pair of Shoes of Small Size are Lost So far.\n\n");
    else {
        printf("A Total of %d Pair of Shoes of Small Size are Lost.\n\nDetails:\n", count);
        for( i = 0; i < numberOfShoes; i++)
            if( shoes[i]->size == Small && shoes[i]->isLost )
                printf("Shoe Number: %d, Size: Small\n", shoes[i]->number);
        printf("\n");
    }

    count = countLostShoes(Medium);
    if(count == 0)
        printf("No Pair of Shoes of Medium Size are Lost So far.\n\n");
    else {
        printf("A Total of %d Pair of Shoes of Medium Size are Lost.\n\nDetails:\n", count);
        for( i = 0; i < numberOfShoes; i++)
            if( shoes[i]->size == Medium && shoes[i]->isLost )
                printf("Shoe Number: %d, Size: Medium\n", shoes[i]->number);
        printf("\n");
    }

    count = countLostShoes(Large);
    if(count == 0)
        printf("No Pair of Shoes of Large Size are Lost So far.\n\n");
    else {
        printf("A Total of %d Pair of Shoes of Large Size are Lost.\n\nDetails:\n", count);
        for( i = 0; i < numberOfShoes; i++)
            if( shoes[i]->size == Large && shoes[i]->isLost )
                printf("Shoe Number: %d, Size: Large\n", shoes[i]->number);
        printf("\n");
    }
}

void releaseMemory()
{
    int i;

    for(i=0; i<numberOfShoes; i++)
        free(shoes[i]);

    free(shoes);
}