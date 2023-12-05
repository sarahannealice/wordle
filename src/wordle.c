//
// Created by sarah on 12/15/2022.
//
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <ctype.h>

#include "..\inc\wordle.h"

//If time allows, come back and implement this
//char** getGameInfo(char readFileName[], char line1[], char line2[], char wordToGuess[], int wordLength, int maxGuess) {}

void currGameState (char readFileName[], char writeFileName[], const char alpha[]) {
    //declaring variables
    bool result;
    bool valid;

    int wordLength = 0;
    int maxGuess = 0;
    int guessCount = 0;

    char line1[LINE_LENGTH];
    char line2[LINE_LENGTH];
    char wordToGuess[LINE_LENGTH];
    char guess[LINE_LENGTH];
    char guessColour[LINE_LENGTH];


    //reading inputted file for game parameters and the word to guess
    FILE *readFile = fopen(readFileName, "r");

    fscanf(readFile,"%s", line1);
    wordLength = atoi(line1);
    fscanf(readFile,"%s", line2);
    maxGuess = atoi(line2);
    fscanf(readFile,"%s", wordToGuess);

    fclose(readFile);


    //allocating memory for the board
    char** gameBoard = (char**) calloc(maxGuess+1, sizeof(char*));
    for(int i=0; i<=maxGuess; i++) {
        gameBoard[i] = (char*) calloc(wordLength+1, sizeof(char));
    }

    //printing current game state to console for first round
    for (int i = 0; i < maxGuess; i++) {
        for (int j = 0; j < wordLength; j++) {
            gameBoard[i][j] = '_';
        }
    }


    //---------do while loop to go through each guess---------//
    do {
        //print current game state of the following guesses
        printf("\nCurrent game state:\n");

        for (int i = 0; i < maxGuess; i++) {
            for (int j = 0; j < wordLength; j++) {
                printf("%c ", gameBoard[i][j]);
            }
            printf("\n");
        }

        //if statements to check if the game has been won, lost, or ongoing
        if (strcmp(guess, wordToGuess) == 0) {
            printf("\nYou WIN!!!\nThe game result was written to the %s file.", writeFileName);
            result = true;
            writeToFile(gameBoard, maxGuess, wordLength, writeFileName, result);
            exit(0);
        } else if (strcmp(guess, wordToGuess) != 0 && guessCount == maxGuess) {
            printf("\nYou LOSE!!!\nThe game result was written to the %s file.", writeFileName);
            result = false;
            writeToFile(gameBoard, maxGuess, wordLength, writeFileName, result);
            //implement writeToFile method
            exit(0);
        }


        //do while loop to check validity of word
        do {
            //ask for user guess
            printf("\nPlease enter a %i-letter word: ", wordLength);
            scanf("%s", guess);

            //converts to all uppercase
            for (int i = 0; i < wordLength; i++) {
                guess[i] = toupper(guess[i]);
            }

            valid = wordValidation(guess, wordLength,alpha);
        } while (!valid);


        //comparing guess to word
        for (int i = 0; i < wordLength; i++) {
            for (int j = 0; j < wordLength; j++) {
                if ((const char *) guess[i] == (const char *) wordToGuess[i] && (const char *) guess[i] != (const char *) wordToGuess[j]) {
                    //change to green
                    green();
                    printf("%c ", (const char *)guess[i]);
                    reset();
                    guessColour[i] = guess[i];
                    gameBoard[guessCount][i] = guessColour[i];
                    break;
                } else if ((const char *) guess[i] == (const char *) wordToGuess[j] && (const char *) guess[i] != (const char *) wordToGuess[i]) {
                    //change color to yellow
                    yellow();
                    printf("%c ", (const char *)guess[i]);
                    reset();
                    guessColour[i] = guess[i];
                    gameBoard[guessCount][i] = guessColour[i];
                } else {
                    //no changes made
//                    printf("%c ", (const char *)guess[i]);
                    guessColour[i] = guess[i];
                    gameBoard[guessCount][i] = guessColour[i];
                }
            }
        }
        guessCount++;
    } while (guessCount < maxGuess + 1);



    //frees previously allocated memory
    free(*gameBoard);
    free(gameBoard);

}


//---------write to file---------//
void writeToFile(char** gameBoard, int maxGuess, int wordLength, char writeFileName[], bool result) {
    FILE *writeFile;
    writeFile = fopen(writeFileName, "w");

    //if statement to check if user won or lost
    if (result == true) {
        //print statements and for loop to write to output file
        fprintf(writeFile,"The solution was found.\n");

        for (int i = 0; i < maxGuess; i++) {
            for (int j = 0; j < wordLength; j++) {
                fprintf(writeFile,"%c ", gameBoard[i][j]);
            }
            fprintf(writeFile,"\n");
        }
    } else if (result == false) {
        //print statements and for loop to write to output file
        fprintf(writeFile,"The solution was not found.\n");

        for (int i = 0; i < maxGuess; i++) {
            for (int j = 0; j < wordLength; j++) {
                fprintf(writeFile,"%c ", gameBoard[i][j]);
            }
            fprintf(writeFile,"\n");
        }
    }

    fclose(writeFile);
}


//---------colour methods---------//
void green() {
    printf("\033[0;32m");
}

void yellow() {
    printf("\033[0;33m");
}

void reset() {
    printf("\033[0m");
}


//---------word validation---------//
bool wordValidation(char guess[], int wordLength, char alpha[]) {
    if (strlen(guess) == wordLength) {
        return true;
    } else if (strlen(guess) != wordLength) {
        return false;
    } else {
        //for loop to check each character
        for (int i = 0; i < wordLength; i++) {
            for (int j = 0; j < strlen(alpha); j++) {
                if (guess[i] != alpha[j]) {
                    return false;
                }
            }
        }
        return true;
    }
}

