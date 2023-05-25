#include<stdio.h>
#include<string.h>
#include "DisjointList.c"
#include "User.c"
#include "Meal.c"
#include "Restaurant.c"

int main()
{
    FILE* file;
    int num;
    
    file = fopen("Restaurants.bin", "wb");
    Restaurant *res;
    num = 4;
    fwrite(&num, sizeof(int), 1, file);
    res = (Restaurant*)malloc(sizeof(Restaurant));
    initializeRestaurant(res, "McDonald's", "mcdonalds", "2339");
    fwrite(res, sizeof(Restaurant), 1, file);
    res = (Restaurant*)malloc(sizeof(Restaurant));
    initializeRestaurant(res, "KFC", "kfc", "2339");
    fwrite(res, sizeof(Restaurant), 1, file);
    res = (Restaurant*)malloc(sizeof(Restaurant));
    initializeRestaurant(res, "Dominos", "dominos", "2339");
    fwrite(res, sizeof(Restaurant), 1, file);
    res = (Restaurant*)malloc(sizeof(Restaurant));
    initializeRestaurant(res, "Howdy", "howdy", "2339");
    fwrite(res, sizeof(Restaurant), 1, file);
    fclose(file);
    
    /*
    file = fopen("Restaurants.bin", "rb");
    Restaurant *res = (Restaurant*)malloc(sizeof(Restaurant));
    fread(&num, sizeof(int), 1, file);
    for(int i=0; i<num; i++)
    {
        fread(res, sizeof(Restaurant), 1, file);
        restaurantStdOut(res, NULL);
    }
    fclose(file);
    */
    
    
    file = fopen("Users.bin", "wb");
    User *user;
    num = 2;
    fwrite(&num, sizeof(int), 1, file);
    user = (User*)malloc(sizeof(User));
    initializeUser(user, "Jones Smith", "Jones", "39", "Chings pokli bander, Daryagali.", 1000);
    fwrite(user, sizeof(User), 1, file);
    user = (User*)malloc(sizeof(User));
    initializeUser(user, "Harry Brook", "Harry", "23", "flat 200, King road, Capital.", 3000);
    fwrite(user, sizeof(User), 1, file);
    fclose(file);
    
    /*
    file = fopen("Users.bin", "rb");
    User *user = (User*)malloc(sizeof(User));
    fread(&num, sizeof(int), 1, file);
    for(int i=0; i<num; i++)
    {
        fread(user, sizeof(User), 1, file);
        userStdOut(user, NULL);
    }
    fclose(file);
    */
    
    file = fopen("Meals.bin", "wb");
    num = 30;
    fwrite(&num, sizeof(int), 1, file);

    Meal *meal[30];
    meal[0] = (Meal*)malloc(sizeof(Meal));
    initializeMeal(meal[0], "mcdonalds", "burger", "Mc Double Cheesy", "Sear-sizzled 100%% Beef with Double layer of Melted cheese.", 565);
    meal[1] = (Meal*)malloc(sizeof(Meal));
    initializeMeal(meal[1], "mcdonalds", "burger", "Mc Royale Burger", "Made with Beef patty Cheese slice Lettuce Tomato and Pickles.", 735 );
    meal[2] = (Meal*)malloc(sizeof(Meal));
    initializeMeal(meal[2], "mcdonalds", "burger", "Big Mac", "Double layer of sear-sizzled Beef Cheese diced onions icebergs and crunch of Pickles", 675);
    meal[3] = (Meal*)malloc(sizeof(Meal));
    initializeMeal(meal[3], "mcdonalds", "burger", "Mega Mac","Made with 4-Layers of sear-sizzled Beef patty with sauces and Meltd Cheese and crunch of Pickles.", 1025);
    meal[4] = (Meal*)malloc(sizeof(Meal));
    initializeMeal(meal[4], "mcdonalds", "wrap", "Mc Wrap", "BBQ Wrap with perfectly cooked Tortilla Chipotle and Cheesy Mayo.", 405);
    meal[5] = (Meal*)malloc(sizeof(Meal));
    initializeMeal(meal[5], "mcdonalds", "wrap", "Mc Arabia", "Two grilled Chicken Patties Arabic bread lettuce with a unique and unforgettable taste.", 785);
    meal[6] = (Meal*)malloc(sizeof(Meal));
    initializeMeal(meal[6], "mcdonalds", "nuggets", "6 pcs Mc Nuggets", "Whichever way you enjoy your favourite McNuggets. Made with juicy white meat.", 585);
    meal[7] = (Meal*)malloc(sizeof(Meal));
    initializeMeal(meal[7], "mcdonalds", "nuggets", "20 pcs Mc Nuggets", "Made with juicy white meat that makes them hard to resist more quantity.", 1235);
    meal[8] = (Meal*)malloc(sizeof(Meal));
    initializeMeal(meal[8], "kfc", "chicken", "Chicken Meal 1","Kentucky fried Chicken providess the best the most crispy fried Chicken." , 370);
    meal[9] = (Meal*)malloc(sizeof(Meal));
    initializeMeal(meal[9], "kfc", "chicken", "Hot Shots 9pcs","Hot and Crispy fried chicken ready to beat th hunger." , 450);
    meal[10] = (Meal*)malloc(sizeof(Meal));
    initializeMeal(meal[10], "kfc", "wings", "Hot Wings 10pcs","Hungry? 10 pcs of crispy fried Wing with a regular drink and sauces." , 440);
    meal[11] = (Meal*)malloc(sizeof(Meal));
    initializeMeal(meal[11], "kfc", "wings", "Saucy Wings","10pcs of Crispy fried wings dipped in 5 sauces ready to beat the appitite." , 670);
    meal[12] = (Meal*)malloc(sizeof(Meal));
    initializeMeal(meal[12], "kfc", "burger", "Krunch Burger","Crunchy Chicken fillet spicy mayo lettuce between a sesame seed bun." , 560);
    meal[13] = (Meal*)malloc(sizeof(Meal));
    initializeMeal(meal[13], "kfc", "burger", "Mighty Zinger","Signature Zinger but bigger! Diuble zinger fillet with a combination of spicy and plain mayo and cheese." , 850);
    meal[14] = (Meal*)malloc(sizeof(Meal));
    initializeMeal(meal[14], "kfc", "deal", "Xtreme Duo Box","The irresistible of 2 signature Zinger Burgers + 2 hot wings and a Large bucket of fries." , 1370);
    meal[15] = (Meal*)malloc(sizeof(Meal));
    initializeMeal(meal[15], "kfc", "Meal", "Wow Box","1 Zinger and 1 hot and crispy fried Chicken + 1 regular fries + 1 drink." , 925);
    meal[16] = (Meal*)malloc(sizeof(Meal));
    initializeMeal(meal[16], "dominos", "pizza", "One & Only","Small hand tossed Pizza with 345ml Drink." , 399);
    meal[17] = (Meal*)malloc(sizeof(Meal));
    initializeMeal(meal[17], "dominos", "pizza", "The Hungry One","8 inch Pizza with 345ml Drink.", 599);
    meal[18] = (Meal*)malloc(sizeof(Meal));
    initializeMeal(meal[18], "dominos", "pizza", "Too Good for Two","Medium Pizza with 2 x 345ml Drinks.", 1199);
    meal[19] = (Meal*)malloc(sizeof(Meal));
    initializeMeal(meal[19], "dominos", "pizza", "The Show Stopper", "Large Pizza with 1.5 liter Drink.", 1499);
    meal[20] = (Meal*)malloc(sizeof(Meal));
    initializeMeal(meal[20], "dominos", "pizza", "Fix for Four", "2 Medium Pizzas with 1.5 liter Drink.", 2199);
    meal[21] = (Meal*)malloc(sizeof(Meal));
    initializeMeal(meal[21], "dominos", "pizza", "Fix for Six", "2 Large Pizzas with 1.5 liter Drink.", 2599);
    meal[22] = (Meal*)malloc(sizeof(Meal));
    initializeMeal(meal[22], "dominos", "deal", "The Game Changer", "Nothing like anything before. Large Premium Pizza with 1.5 liter Drink.", 2199);
    meal[23] = (Meal*)malloc(sizeof(Meal));
    initializeMeal(meal[23], "howdy", "steak", "Despirado", "Jalapeno Sauce Chicken Steak", 1099);
    meal[24] = (Meal*)malloc(sizeof(Meal));
    initializeMeal(meal[24], "howdy", "steak", "Texan", "Mushroom Creamy White steak", 1099);
    meal[25] = (Meal*)malloc(sizeof(Meal));
    initializeMeal(meal[25], "howdy", "wings", "Kick of Chick (Grilled)", "Grilled Buffalo Wings.", 559);
    meal[26] = (Meal*)malloc(sizeof(Meal));
    initializeMeal(meal[26], "howdy", "wings", "Kick of Chick (Fried)", "Fried Buffalo Wings.", 559);
    meal[27] = (Meal*)malloc(sizeof(Meal));
    initializeMeal(meal[27], "howdy", "desert", "Chocaine", "Choclate Nautella Cake,", 1299);
    meal[28] = (Meal*)malloc(sizeof(Meal));
    initializeMeal(meal[28], "howdy", "desert", "Tres Amigos Lotus", "3 Milk Cake Louts.", 1699);
    meal[29] = (Meal*)malloc(sizeof(Meal));
    initializeMeal(meal[29], "howdy", "desert", "Oreo Shake", "Sweet cold and delicious Oreo shake. ", 399);

    for(int i=0; i<num; i++)
        fwrite(meal[i], sizeof(Meal), 1, file);

    fclose(file);
    printf("Writing Completed\n");
    
    /*
    file = fopen("Meals.bin", "rb");
    Meal *meal = (Meal*)malloc(sizeof(Meal));
    fread(&num, sizeof(int), 1, file);
    for(int i=0; i<num; i++)
    {
        fread(meal, sizeof(Meal), 1, file);
        mealStdOut(meal, NULL);
    }
    fclose(file);
    */
    return 0;
}
