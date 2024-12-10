#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include "checkPassword.h"

// This code cracks a given password, 3 characters at a time
// if run with "-f" then it uses forking, if not, then it run through each section of 3 individualy
//
// Author: Colin Hill
//
// Citations:
// Used course content code to understand how to use forking
// Referred to the GeeksForGeeks page on how to use forking and other realted topics
// NOTE: These no direct code was used from these sources, these were use purly for understanding forking 



// Brute forces through the password 3 characters at a time
void bruteForce(int start) {
    // Checks every combo starting from char 33.
    for (char a = 33; a <= 126; a++) {
        for (char b = 33; b <= 126; b++) {
            for (char c = 33; c <= 126; c++) {
                char input[4] = {a, b, c, '\0'}; //create the password guess
                int check = checkPassword(input, start); // check if the password is correct with the checkPassword() method

                if (check == 0) { // if it is found, print the results
                    printf("Process %d with parent %d finds %d-%d: %s\n", getpid(), getppid(), start, start + 2, input);
                    return;
                }
            }
        }
    }
}

//Main method, checks arguments and calls bruteForce(). If -f then use forking
int main(int argc, char *argv[]) {

    int forkArg = 0;

    // Compares the line arg to see if it is -f
    if (argc > 1 && strcmp(argv[1], "-f") == 0) {
        forkArg = 1;
    }

    // If forking is called (-f)
    if (forkArg == 1) {
        pid_t pidList[4];
        int splitPass[4] = {0, 3, 6, 9}; //makes the segemts of 3 for the password
	 printf("Process %d with parent %d cracking the password...\n", getpid(), getppid());

        for (int i = 0; i < 4; i++) {
            // Creates children
            if ((pidList[i] = fork()) == 0) {
                bruteForce(splitPass[i]);
                exit(0);
            }
	    //If the forking fails
	    else if (pidList[i] < 0) {
                perror("Fork Failed");
                return 1;
            }
        }

        // Wait for all child processes to finish
        for (int i = 0; i < 4; i++) {
            waitpid(pidList[i], NULL, 0);
        }
    } 
    
    //If forking is not called, default state / run
    else {
        int splitPass[4] = {0, 3, 6, 9};
        printf("Process %d with parent %d cracking the password...\n", getpid(), getppid());

        for (int i = 0; i < 4; i++) {
            bruteForce(splitPass[i]);
        }
    }

    return 0;
}

