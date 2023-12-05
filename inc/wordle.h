//
// Created by sarah on 12/15/2022.
//
#include <stdbool.h>

#define LINE_LENGTH 10

#ifndef ASSIGN5_WORDLE_H
#define ASSIGN5_WORDLE_H

//main methods
void currGameState (char readFileName[], char writeFileName[], const char alpha[]);
void writeToFile(char** gameBoard, int maxGuess, int wordLength, char writeFileName[], bool result);

//smaller functions
void green();
void yellow();
void reset();
bool wordValidation(char guess[], int wordLength, char alpha[]);

//will revisit if time permits
char** getGameInfo(char readFileName[], char line1[], char line2[], char wordToGuess[], int wordLength, int maxGuess);

#endif //ASSIGN5_WORDLE_H
