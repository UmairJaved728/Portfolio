#include<stdio.h>
#include<string.h>
#include<windows.h>

void getInvalidString(char* s);
void getConfirmHeader(char* s);

// Clear the standard input buffer
void clearInputBuffer(void)
{
    // Discard all remaining char's from the standard input buffer:
    while (getchar() != '\n')
    {
        ; // do nothing!
    }
}

// Wait for user to input the "enter" key to continue
void suspend(void)
{
    printf("<ENTER> to continue...");
    clearInputBuffer();
    putchar('\n');
}

// This is a generic called in almost every function, to print the menu to the screen
// It takes strings as parameters to print as optons
int optionsScreen(char s[][100], int count, char* header)
{
    int index, option, i, t;
    char invalid[2000];
    invalid[0] = '\0';
    do {
        system("cls");
        printf("%s%s", header, invalid);
        printf("\n\n\t\t\t\t");
        for( i = 0; i < 50; i++)
            printf("<>");
        printf("\n\n\n");
        for (index = 0; index < count; index++) {
            printf("\t\t\t\t\t\t\t\tEnter   < %d >   |-->   %s\n\n", index + 1, s[index]);
        }
        printf("\n\t\t\t\t");
        for( i = 0; i < 50; i++)
            printf("<>");
        printf("\n\n\t\t\t\t\t\t\t\tEnter your Choice --> __\b\b ");
        t = scanf("%d", &option);

        if(t == 0 || option <= 0 || option > count) {
            clearInputBuffer();
            getInvalidString(invalid);
            option = -1;
        }
    }while(option <= 0 || option > count);
    clearInputBuffer();
    return option;
}

// This function is also a core function of this program
// It takes a confirmation msg and verifies from user Yes or No
bool confirmationScreen(char* s, char header[2000])
{
    int option;
    int i, t;
    char invalid[2000];
    if(header[0] == '\0')
        getConfirmHeader(header);
    do {
        system("cls");
        printf("%s%s", header, invalid);
        printf("\n\n\n\n\t\t\t\t\t\t");
        for(i = 0; i<80; i++)
            printf("#");
        printf("\n\n\n\n\t\t\t\t\t\t");
        printf("%s\n\n", s);
        printf("\t\t\t\t\t\t\t\t Enter < 0 >  |-->   NO\n\n");
        printf("\t\t\t\t\t\t\t\t Enter < 1 >  |-->   YES\n\n");
        printf("\n\t\t\t\t\t\t");
        for(i = 0; i<80; i++)
            printf("#");
        printf("\n\n\n\n\t\t\t\t\t\t\t\tEnter your Choice --> _\b");
        t = scanf("%d", &option);
        if(t == 0 || !(option == 0 || option == 1) ){
            clearInputBuffer();
            getInvalidString(invalid);
            option = -1;
        }
    }while(!(option == 0 || option == 1));
    clearInputBuffer();
    return option;
}


void toIDCase(char* s)
{
    int i, len = strlen(s);
    for(i=0; i<len; i++)
        if(s[i] >= 'A' && s[i] <= 'Z')
            s[i] += 32;
}

void toNameCase(char* s)
{
    int i, len = strlen(s);
    if(s[0] >= 'a' && s[0] <= 'z' )
        s[0] -= 32;
    for(i=1; i<len; i++)
        if(s[i-1] == ' ' && s[i] >= 'a' && s[i] <= 'z')
            s[i] -= 32;
}

void getInvalidString(char* s)
{
    strcpy(s, "\n\n\t\t\t\t\t\t<----------------------INVALID INPUT!!!---------------------->\n");
}

void getMainMenuHeader(char* s)
{
    strcpy(s, "\n\n\n");

    strcat(s, "\t |M||M|      |M||M|           |A|           |I||I||I||I||I|  |N||N|        |N|      |M||M|      |M||M|  |E||E||E||E|  |N||N|        |N|  |U|         |U|\n");
    strcat(s, "\t |M| |M|    |M| |M|         |A| |A|               |I|        |N| |N|       |N|      |M| |M|    |M| |M|  |E|           |N| |N|       |N|  |U|         |U|\n");
    strcat(s, "\t |M|  |M|  |M|  |M|        |A|   |A|              |I|        |N|  |N|      |N|      |M|  |M|  |M|  |M|  |E|           |N|  |N|      |N|  |U|         |U|\n");
    strcat(s, "\t |M|   |M||M|   |M|       |A|     |A|             |I|        |N|   |N|     |N|      |M|   |M||M|   |M|  |E|           |N|   |N|     |N|  |U|         |U|\n");
    strcat(s, "\t |M|    |M|     |M|      |A|       |A|            |I|        |N|    |N|    |N|      |M|    |M|     |M|  |E||E||E|     |N|    |N|    |N|  |U|         |U|\n");
    strcat(s, "\t |M|            |M|     |A||A||A||A||A|           |I|        |N|     |N|   |N|      |M|            |M|  |E|           |N|     |N|   |N|  |U|         |U|\n");
    strcat(s, "\t |M|            |M|    |A|           |A|          |I|        |N|      |N|  |N|      |M|            |M|  |E|           |N|      |N|  |N|  |U|         |U|\n");
    strcat(s, "\t |M|            |M|   |A|             |A|         |I|        |N|       |N| |N|      |M|            |M|  |E|           |N|       |N| |N|  |U|         |U|\n");
    strcat(s, "\t |M|            |M|  |A|               |A|  |I||I||I||I||I|  |N|        |N||N|      |M|            |M|  |E||E||E||E|  |N|        |N||N|  |U||U||U||U||U|\n");
    strcat(s, "\n");
    strcat(s, "\t    ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
}

void getRestaurantHeader(char* s)
{
    strcpy(s, "\n\n\n");

    strcat(s, "\t\t\t   |S||S||S||S|  |E||E||E||E|  |L|           |L|               |N||N|        |N|  |O||O||O||O||O|  |W|             |W|  \n");
    strcat(s, "\t\t\t   |S|           |E|           |L|           |L|               |N| |N|       |N|  |O|         |O|  |W|             |W|  \n");
    strcat(s, "\t\t\t   |S|           |E|           |L|           |L|               |N|  |N|      |N|  |O|         |O|  |W|             |W|  \n");
    strcat(s, "\t\t\t   |S|           |E|           |L|           |L|               |N|   |N|     |N|  |O|         |O|  |W|             |W|  \n");
    strcat(s, "\t\t\t   |S||S||S||S|  |E||E||E|     |L|           |L|               |N|    |N|    |N|  |O|   |O|   |O|  |W|     |W|     |W|  \n");
    strcat(s, "\t\t\t            |S|  |E|           |L|           |L|               |N|     |N|   |N|  |O|         |O|  |W|   |W| |W|   |W|  \n");
    strcat(s, "\t\t\t            |S|  |E|           |L|           |L|               |N|      |N|  |N|  |O|         |O|  |W|  |W|   |W|  |W|  \n");
    strcat(s, "\t\t\t            |S|  |E|           |L|           |L|               |N|       |N| |N|  |O|         |O|  |W| |W|     |W| |W|  \n");
    strcat(s, "\t\t\t   |S||S||S||S|  |E||E||E||E|  |L||L||L||L|  |L||L||L||L|      |N|        |N||N|  |O||O||O||O||O|  |W||W|       |W||W|  \n");
    strcat(s, "\n");
    strcat(s, "\t\t\t   ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~   \n");
}

void getUserHeader(char* s)
{
    strcpy(s, "\n\n\n");

    strcat(s, "\t\t\t|H|         |H|  |U|         |U|  |N||N|        |N|      |G||G||G|       |R||R||R|    |Y|            |Y|     |?||?||?|     \n");
    strcat(s, "\t\t\t|H|         |H|  |U|         |U|  |N| |N|       |N|    |G|       |G|   |R|       |R|    |Y|        |Y|      |?|     |?|    \n");
    strcat(s, "\t\t\t|H|         |H|  |U|         |U|  |N|  |N|      |N|  |G|         |G|  |R|        |R|      |Y|    |Y|       |?|       |?|   \n");
    strcat(s, "\t\t\t|H|         |H|  |U|         |U|  |N|   |N|     |N|  |G|              |R|      |R|          |Y||Y|          |?|     |?|    \n");
    strcat(s, "\t\t\t|H||H||H||H||H|  |U|         |U|  |N|    |N|    |N|  |G|              |R|    |R|              |Y|                  |?|     \n");
    strcat(s, "\t\t\t|H|         |H|  |U|         |U|  |N|     |N|   |N|  |G|   |G||G||G|  |R|  |R|                |Y|                 |?|      \n");
    strcat(s, "\t\t\t|H|         |H|  |U|         |U|  |N|      |N|  |N|  |G|   |G|   |G|  |R|    |R|              |Y|                |?|       \n");
    strcat(s, "\t\t\t|H|         |H|  |U|         |U|  |N|       |N| |N|    |G|       |G|  |R|      |R|            |Y|                          \n");
    strcat(s, "\t\t\t|H|         |H|  |U||U||U||U||U|  |N|        |N||N|      |G||G||G|    |R|        |R|          |Y|                |?|       \n");
    strcat(s, "\n");
    strcat(s, "\t\t\t~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~   \n");

}


void getOrderHeader(char* s)
{
    strcpy(s, "\n\n\n");

    strcat(s, "\t\t  |O||O||O||O||O|     |R||R||R|    |D||D||D||D||D|  |E||E||E||E|     |R||R||R|        |N||N|        |N|  |O||O||O||O||O|  |W|             |W| \n");
    strcat(s, "\t\t  |O|         |O|   |R|       |R|     |D|      |D|  |E|            |R|       |R|      |N| |N|       |N|  |O|         |O|  |W|             |W| \n");
    strcat(s, "\t\t  |O|         |O|  |R|        |R|     |D|      |D|  |E|           |R|        |R|      |N|  |N|      |N|  |O|         |O|  |W|             |W| \n");
    strcat(s, "\t\t  |O|         |O|  |R|      |R|       |D|      |D|  |E|           |R|      |R|        |N|   |N|     |N|  |O|         |O|  |W|             |W| \n");
    strcat(s, "\t\t  |O|   |O|   |O|  |R|    |R|         |D|      |D|  |E||E||E|     |R|    |R|          |N|    |N|    |N|  |O|   |O|   |O|  |W|     |W|     |W| \n");
    strcat(s, "\t\t  |O|         |O|  |R|  |R|           |D|      |D|  |E|           |R|  |R|            |N|     |N|   |N|  |O|         |O|  |W|   |W| |W|   |W| \n");
    strcat(s, "\t\t  |O|         |O|  |R|    |R|         |D|      |D|  |E|           |R|    |R|          |N|      |N|  |N|  |O|         |O|  |W|  |W|   |W|  |W| \n");
    strcat(s, "\t\t  |O|         |O|  |R|      |R|       |D|      |D|  |E|           |R|      |R|        |N|       |N| |N|  |O|         |O|  |W| |W|     |W| |W| \n");
    strcat(s, "\t\t  |O||O||O||O||O|  |R|        |R|  |D||D||D||D||D|  |E||E||E||E|  |R|        |R|      |N|        |N||N|  |O||O||O||O||O|  |W||W|       |W||W| \n");
    strcat(s, "\n");
    strcat(s, "\t\t  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ \n");
}

void getCartHeader(char* s)
{
    strcpy(s, "\n\n\n");

    strcat(s, "\t\t\t\t\t\t   |C||C||C||C|           |A|              |R||R||R|    |T||T||T||T||T| \n");
    strcat(s, "\t\t\t\t\t\t   |C|                  |A| |A|          |R|       |R|        |T|       \n");
    strcat(s, "\t\t\t\t\t\t   |C|                 |A|   |A|        |R|        |R|        |T|       \n");
    strcat(s, "\t\t\t\t\t\t   |C|                |A|     |A|       |R|      |R|          |T|       \n");
    strcat(s, "\t\t\t\t\t\t   |C|               |A|       |A|      |R|    |R|            |T|       \n");
    strcat(s, "\t\t\t\t\t\t   |C|              |A||A||A||A||A|     |R|  |R|              |T|       \n");
    strcat(s, "\t\t\t\t\t\t   |C|             |A|           |A|    |R|    |R|            |T|       \n");
    strcat(s, "\t\t\t\t\t\t   |C|            |A|             |A|   |R|      |R|          |T|       \n");
    strcat(s, "\t\t\t\t\t\t   |C||C||C||C|  |A|               |A|  |R|        |R|        |T|       \n");
    strcat(s, "\n");
    strcat(s, "\t\t\t\t\t\t   ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ \n");
}

void getWalletHeader(char* s)
{
    strcpy(s, "\n\n\n");

    strcat(s, "\t\t\t\t     |W|             |W|           |A|           |L|           |L|             |E||E||E||E|  |T||T||T||T||T| \n");
    strcat(s, "\t\t\t\t     |W|             |W|         |A| |A|         |L|           |L|             |E|                 |T|       \n");
    strcat(s, "\t\t\t\t     |W|             |W|        |A|   |A|        |L|           |L|             |E|                 |T|       \n");
    strcat(s, "\t\t\t\t     |W|             |W|       |A|     |A|       |L|           |L|             |E|                 |T|       \n");
    strcat(s, "\t\t\t\t     |W|     |W|     |W|      |A|       |A|      |L|           |L|             |E||E||E|           |T|       \n");
    strcat(s, "\t\t\t\t     |W|   |W| |W|   |W|     |A||A||A||A||A|     |L|           |L|             |E|                 |T|       \n");
    strcat(s, "\t\t\t\t     |W|  |W|   |W|  |W|    |A|           |A|    |L|           |L|             |E|                 |T|       \n");
    strcat(s, "\t\t\t\t     |W| |W|     |W| |W|   |A|             |A|   |L|           |L|             |E|                 |T|       \n");
    strcat(s, "\t\t\t\t     |W||W|       |W||W|  |A|               |A|  |L||L||L||L|  |L||L||L||L|    |E||E||E||E|        |T|       \n");
    strcat(s, "\n");
    strcat(s, "\t\t\t\t     ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ \n");
}

void getConfirmHeader(char* s)
{
    strcpy(s, "\n\n\n");

    strcat(s, "\t\t   |C||C||C||C|  |O||O||O||O||O|  |N||N|        |N|  |F||F||F||F|  |I||I||I||I||I|     |R||R||R|    |M||M|      |M||M|     |?||?||?|   \n");
    strcat(s, "\t\t   |C|           |O|         |O|  |N| |N|       |N|  |F|                 |I|         |R|       |R|  |M| |M|    |M| |M|    |?|     |?|  \n");
    strcat(s, "\t\t   |C|           |O|         |O|  |N|  |N|      |N|  |F|                 |I|        |R|        |R|  |M|  |M|  |M|  |M|   |?|       |?| \n");
    strcat(s, "\t\t   |C|           |O|         |O|  |N|   |N|     |N|  |F|                 |I|        |R|      |R|    |M|   |M||M|   |M|    |?|     |?|  \n");
    strcat(s, "\t\t   |C|           |O|   |O|   |O|  |N|    |N|    |N|  |F||F||F|           |I|        |R|    |R|      |M|    |M|     |M|           |?|   \n");
    strcat(s, "\t\t   |C|           |O|         |O|  |N|     |N|   |N|  |F|                 |I|        |R|  |R|        |M|            |M|          |?|    \n");
    strcat(s, "\t\t   |C|           |O|         |O|  |N|      |N|  |N|  |F|                 |I|        |R|    |R|      |M|            |M|         |?|     \n");
    strcat(s, "\t\t   |C|           |O|         |O|  |N|       |N| |N|  |F|                 |I|        |R|      |R|    |M|            |M|                 \n");
    strcat(s, "\t\t   |C||C||C||C|  |O||O||O||O||O|  |N|        |N||N|  |F|           |I||I||I||I||I|  |R|        |R|  |M|            |M|         |?|     \n");
    strcat(s, "\n");
    strcat(s, "\t\t   ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ \n");
}

void startIntro()
{
    printf( "\n\n\n\n\n\n\n\n\n\t\t\t  Please Enter Full Screen mode and Press any key to Start...\n\n");
    system("pause");
    system("cls");
    Sleep(500);
    printf( "\n\n");

    printf("\t\t\t\t\t  $$      $$      \n");
    printf("\t\t\t\t\t  $$      $$      \n");
    printf("\t\t\t\t\t  $$      $$  $$$$$$  $$       $$$$$$   $$$$$$  $$$$  $$$$  $$$$$$     \n");
    printf("\t\t\t\t\t  $$  $$  $$  $$      $$       $$       $$  $$  $$  $$  $$  $$          \n");
    printf("\t\t\t\t\t  $$  $$  $$  $$$$    $$       $$       $$  $$  $$  $$  $$  $$$$       \n");
    printf("\t\t\t\t\t  $$  $$  $$  $$      $$       $$       $$  $$  $$      $$  $$          \n");
    printf("\t\t\t\t\t  $$$$$$$$$$  $$$$$$  $$$$$$   $$$$$$   $$$$$$  $$      $$  $$$$$$     \n");

    Sleep(1000);
    printf( "\n\n");

    printf("\t\t\t\t\t\t\t\t\t   $$$$$$$$$$  $$$$$$$$   \n");
    printf("\t\t\t\t\t\t\t\t\t       $$      $$    $$   \n");
    printf("\t\t\t\t\t\t\t\t\t       $$      $$ $$ $$   \n");
    printf("\t\t\t\t\t\t\t\t\t       $$      $$    $$   \n");
    printf("\t\t\t\t\t\t\t\t\t       $$      $$$$$$$$   \n");

    Sleep(1000);
    printf( "\n\n");

    printf( "\t\t\t\t\t\t\t\t\t\t\t   $$$$$$$$  $$$$$$$$$$  $$$$$$$$$$  $$$$$$$$$$$$  \n");
    printf( "\t\t\t\t\t\t\t\t\t\t\t   $$        $$      $$  $$      $$    $$      $$  \n");
    printf( "\t\t\t\t\t\t\t\t\t\t\t   $$        $$      $$  $$      $$    $$      $$  \n");
    printf( "\t\t\t\t\t\t\t\t\t\t\t   $$$$$$    $$  $$  $$  $$  $$  $$    $$      $$  \n");
    printf( "\t\t\t\t\t\t\t\t\t\t\t   $$        $$      $$  $$      $$    $$      $$  \n");
    printf( "\t\t\t\t\t\t\t\t\t\t\t   $$        $$      $$  $$      $$    $$      $$  \n");
    printf( "\t\t\t\t\t\t\t\t\t\t\t   $$        $$$$$$$$$$  $$$$$$$$$$  $$$$$$$$$$$$  \n");


    Sleep(1000);
    printf( "\n\n");

    printf( "\t\t\t\t\t $$$$$$$$$$  $$$$$$  $$$$$$$$$$ $$$$$$  $$$$$$  $$$$$$$$$  $$$$      $$    $$$$$$$$  \n");
    printf( "\t\t\t\t\t $$      $$  $$   $$ $$     $$  $$      $$   $$     $$     $$ $$     $$    $$        \n");
    printf( "\t\t\t\t\t $$      $$  $$   $$ $$     $$  $$      $$   $$     $$     $$  $$    $$    $$        \n");
    printf( "\t\t\t\t\t $$  $$  $$  $$$$$$  $$     $$  $$$$    $$$$$$      $$     $$   $$   $$    $$ $$$$  \n");
    printf( "\t\t\t\t\t $$      $$  $$$$    $$     $$  $$      $$$$        $$     $$    $$  $$    $$ $$ $$  \n");
    printf( "\t\t\t\t\t $$      $$  $$ $    $$     $$  $$      $$ $$       $$     $$     $$ $$    $$    $$  \n");
    printf( "\t\t\t\t\t $$$$$$$$$$  $$  $$  $$$$$$$$$$ $$$$$$  $$  $$   $$$$$$$$  $$      $$$$    $$$$$$$$  \n");

    Sleep(1000);
    printf( "\n\n");

    printf( "\t\t\t\t\t\t\t\t\t $$$$$$  $$      $$  $$$$$$$  $$$$$$$$$$  $$$$$$$  $$$$     $$$$          \n");
    printf( "\t\t\t\t\t\t\t\t\t $$       $$    $$   $$           $$      $$       $$ $$   $$ $$          \n");
    printf( "\t\t\t\t\t\t\t\t\t $$        $$  $$    $$           $$      $$       $$  $$ $$  $$          \n");
    printf( "\t\t\t\t\t\t\t\t\t $$$$$$     $$$$     $$$$$$       $$      $$$$     $$   $$$   $$          \n");
    printf( "\t\t\t\t\t\t\t\t\t      $$     $$           $$      $$      $$       $$         $$          \n");
    printf( "\t\t\t\t\t\t\t\t\t      $$     $$           $$      $$      $$       $$         $$          \n");
    printf( "\t\t\t\t\t\t\t\t\t $$$$$$      $$      $$$$$$       $$      $$$$$$$  $$         $$          \n");

    Sleep(1000);
    printf( "\n\n\n");

    int i; 
    for(i=5; i>=1; i--)
    {
        printf( "\r\t\t\t\t\t\t\t\t\t  Starting in %d seconds", i);
        Sleep(1000);  
    }
}
