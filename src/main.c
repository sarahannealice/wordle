#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>//used to check if file exists 'access'

#include "..\inc\wordle.h"

/*
 * NOTE: Follow this example to use ANSI colours at the terminal:
 * https://www.theurbanpenguin.com/4184-2/
 *
 * In order to get ANSI colors showing in the CLion Run Console,
 * we need to do the following routine:
 *
 * 1. Choose Help -> Edit Custom Properties from CLion menu
 * 2. Add the following line to the idea.properties file:
 *      run.processes.with.pty=false
 * 3. Restart CLion.
 *
 * Reference:
 * https://youtrack.jetbrains.com/issue/CPP-8395/Registry-setting-runprocesseswithpty-not-saved#focus=Comments-27-2499735.0-0
 *
 */

int main(int argc, char *argv[]) {

    setbuf(stdout, 0);

    char readFileName[40];
    char writeFileName[40];

    const char alpha[] = {'A','B','C','D','E','F','G','H','I',
                          'J','K','L','M','N','O','P','Q','R',
                          'S','T','U','V','W','X','Y','Z'};


     if (argc != 5) {
         fprintf(stderr, "Invalid number of command line arguments.");
         return 1;
     } else if ((strcmp(argv[1],"-i") != 0 && strcmp(argv[3],"-i") != 0) || (strcmp(argv[1],"-o") != 0 && strcmp(argv[3],"-o") != 0)) {
         fprintf(stderr, "Invalid command line argument usage.");
         return 1;
     } else if (strcmp(argv[1],"-i") == 0 && strcmp(argv[3],"-o") == 0) {
         if (access(argv[2],F_OK) != 0) {
             fprintf(stderr, "Cannot open %s for reading.", argv[2]);
             return 1;
         } else if (access(argv[4],F_OK) != 0) {
             fprintf(stderr, "Cannot open %s for writing.", argv[4]);
             return 1;
         } else {
             strcpy(readFileName,argv[2]);
             strcpy(writeFileName, argv[4]);

             printf("Welcome to C-Wordle!!\n");
             currGameState(readFileName, writeFileName, alpha);
         }
     } else if (strcmp(argv[1],"-o") == 0 && strcmp(argv[3],"-i") == 0) {
         if (access(argv[2],F_OK) != 0) {
             fprintf(stderr, "Cannot open %s for writing.", argv[2]);
             return 1;
         } else if (access(argv[4],F_OK) != 0) {
             fprintf(stderr, "Cannot open %s for reading.", argv[4]);
             return 1;
         } else {
             strcpy(writeFileName, argv[2]);
             strcpy(readFileName,argv[4]);

             printf("Welcome to C-Wordle!!\n");
             currGameState(readFileName, writeFileName, alpha);
         }
     }


    return 0;
}
