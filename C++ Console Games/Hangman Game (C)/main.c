#include <stdio.h>
#include "utils.h"
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>

void toLower(char word[WORD_SIZE])
{
    int i;
    for(i=0; i<WORD_SIZE; i++)
        word[i] |= 32;
}

bool isInvalid(const char word[WORD_SIZE])
{
    int i;
    for(i=0; i<WORD_SIZE; i++)
        if(word[i] < 'a' || word[i] > 'z')
            return true;
    return false;
}

void printStatistics(int totalGames, int gamesWon, const int *histogram, int characterCounts[26])
{
    int i, j;
    printf("\n*** STATISTICS REPORT ***\n\n");
    printf("Total Games Played: %d\n", totalGames);
    printf("Games Won: %d\n\n", gamesWon);

    printf("Games Won Percentage: %.2f%%", (float)gamesWon/(float)totalGames * 100);

    printf("\n\nHistogram of Number of Guesses in each Game Won:\n\n");
    for(i = 0; i < gamesWon; i++)
    {
        printf("Game %2d: ", i+1);
        for(j=0; j<histogram[i]; j++)
            printf("*");
        printf("\n");
    }

    printf("\n\nAverage Percentage of Characters in the Alphabets.\n\n");
    for(i = 0; i < 26; i++)
    {
        printf("%c : %.2f%%\n", i+97, (float)characterCounts[i] / (float)totalGames * 100);
    }

    printf("\n");
}

bool hard_processGuess(char clue[WORD_SIZE+1], bool answerFlags[WORD_SIZE], char guessedLetters[26], const char* answer, const char* attempt){
    int guessesCorrectly = 0, i, j;

    // first check for exact matches
    for(i = 0; i < WORD_SIZE; i++){
        if(attempt[i] == answer[i]){
            clue[i] = attempt[i];
            answerFlags[i] = true;
            guessedLetters[answer[i]-97] = answer[i];
        }

        if(answerFlags[i] == true)
            guessesCorrectly++;
    }

	for( i =0; i<WORD_SIZE; i++){
		if(clue[i] == '-'){//not an exact match
			for ( j=0; j<WORD_SIZE; j++){
				if(attempt[i] == answer[j] && !answerFlags[j]){ //a match in a different position
					answerFlags[j] = true;
                    guessedLetters[answer[j]-97] = answer[j];
					break; //end of the j loop as we only need one clue per letter
				}
			}
		}
	}

	printf("%s\n\n", clue);
    printf("Correctly guessed letters: ");
    for (i = 0; i < 26; i++)
        if (guessedLetters[i] != '\0')
            printf("%c ", guessedLetters[i]);
    printf("\n\n");
	return guessesCorrectly == WORD_SIZE; //return 0 if not
}

bool processGuess(const char* answer, const char* attempt){
    int guessesCorrectly = 0, i, j;
    char clue[6] = {'-', '-', '-', '-', '-', '\0'};
    bool answerFlags[5] = {false, false, false, false, false};
    char guessedLetters[26];
    for(i=0; i<26; i++) {
        guessedLetters[i] = '\0';
    }
    // first check for exact matches
    for(i = 0; i < WORD_SIZE; i++){
        if(attempt[i] == answer[i]){
            clue[i] = attempt[i];
            answerFlags[i] = true;
            guessedLetters[answer[i]-97] = answer[i];
        }

        if(answerFlags[i] == true)
            guessesCorrectly++;
    }

    for( i =0; i<WORD_SIZE; i++){
        if(clue[i] == '-'){//not an exact match
            for ( j=0; j<WORD_SIZE; j++){
                if(attempt[i] == answer[j] && !answerFlags[j]){ //a match in a different position
                    answerFlags[j] = true;
                    guessedLetters[answer[j]-97] = answer[j];
                    break; //end of the j loop as we only need one clue per letter
                }
            }
        }
    }

    printf("%s\n\n", clue);
    printf("Correctly guessed letters: ");
    for (i = 0; i < 26; i++)
        if (guessedLetters[i] != '\0')
            printf("%c ", guessedLetters[i]);
    printf("\n\n");
    return guessesCorrectly == WORD_SIZE; //return 0 if not
}

bool validateGuess(char dictionary[DICT_SIZE][WORD_SIZE+1], char word[WORD_SIZE+1])
{
    int i, j;
    bool found;
    for(i = 0; i < DICT_SIZE; i++)
    {
        found = true;
        for(j=0; j<WORD_SIZE; j++)
        {
            if(word[i] != dictionary[DICT_SIZE][i])
            {
                found = false;
                break;
            }
        }
        if( found )
            return true;
    }

    return i != DICT_SIZE;
}

int main(){
    //pick a random word
    srand(time(NULL));
    int i;
    char words[DICT_SIZE][WORD_SIZE+1], choice;
    bool isHardMode;
    load_word_list(words);

    // variables for statistic report
    int totalGames = 0, gamesWon = 0, histSize = 16;
    int characterCounts[26];
    int *histogram = (int*) malloc (histSize * sizeof (int));

    for(i=0; i<26; i++)
        characterCounts[i] = 0;

    //game starts
    do {
        printf("\nDo you want to Enable Hard Mode (Y for YES): ");
        choice = getchar();
        getchar();
        isHardMode = (choice == 'Y' || choice == 'y');
        char answer[WORD_SIZE+1];
        char guessedLetters[26];
        char clue[6] = {'-', '-', '-', '-', '-', '\0'};
        bool answerFlags[5] = {false, false, false, false, false};
        int random = rand() % DICT_SIZE;
        for(i=0; i<WORD_SIZE; i++)
            answer[i] = words[random][i];
        //loop

        int num_of_guesses = 0;
        bool guessed_correctly = false;
        char attempt[WORD_SIZE+1];

        for(i=0; i<26; i++) {
            guessedLetters[i] = '\0';
        }

        while (num_of_guesses < 6) {
            printf("Enter a 5 letter word and press enter: ");
            for (i = 0; i < WORD_SIZE; i++)
                attempt[i] = getchar();
            getchar(); // to discard the '\n'

            toLower(attempt);
            printf("You guessed %s\n", attempt);

            if (isInvalid(attempt)) {
                printf("You have %d guesses remaining\n", 6 - num_of_guesses);
                printf("%s contains invalid characters, Try Again with letters only!\n\n", attempt);
                continue;
            }
            if (!validateGuess(words, attempt)) {
                printf("You have %d guesses remaining\n", 6 - num_of_guesses);
                printf("%s is not a valid word, Try Again!\n\n", attempt);
                continue;
            }
            printf("\n");
            num_of_guesses += 1;
            if(isHardMode)
                guessed_correctly = hard_processGuess(clue, answerFlags, guessedLetters, answer, attempt);
            else
                guessed_correctly = processGuess(answer, attempt);

            if (guessed_correctly)
                break;

            printf("You have %d guesses remaining\n\n", 6 - num_of_guesses);
        }

        //show the message displayed at the end of the game
        if (guessed_correctly) {
            printf("You guessed the word in %d guesses\n", num_of_guesses);
            if(gamesWon == histSize)
            {
                histogram = (int*) realloc(histogram, histSize*2 * sizeof (int));
                histSize *= 2;
            }
            histogram[gamesWon] = num_of_guesses;
            gamesWon++;
        } else {
            printf("You did not guess the word in 6 guesses. :( The word was %s\n", answer);
        }

        for(i=0; i<WORD_SIZE; i++) {
            characterCounts[answer[i] - 97]++;
        }

        totalGames++;
        printf("\nDo you want to Play Again (Y for YES): ");
        choice = getchar();
        getchar();
    }while(choice == 'y' || choice == 'Y');

    printStatistics(totalGames, gamesWon, histogram, characterCounts);
    free(histogram);
	return 0;
}