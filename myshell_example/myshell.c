/*
 * MyShell Project for SOFE 3950U / CSCI 3020U: Operating Systems
 *
 * Copyright (C) 2015, <GROUP MEMBERS>
 * All rights reserved.
 * 
 */
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <dirent.h>
#include <sys/types.h>
#include <string.h>
#include "utility.h"
#include "myshell.h"

// Put macros or constants here using #define
#define BUFFER_LEN 256

// Put global environment variables here

// Define functions declared in myshell.h here

int main(int argc, char *argv[]) {
    // Input buffer and and commands
    char buffer[BUFFER_LEN] = { 0 };
    char command[BUFFER_LEN] = { 0 };
    char arg[BUFFER_LEN] = { 0 };
    char delim[BUFFER_LEN];
    char* token;
    //int inputLen;

    // Parse the commands provided using argc and argv

    // Perform an infinite loop getting command input from users
    while (fgets(buffer, BUFFER_LEN, stdin) != NULL) {
        //inputLen = strlen(buffer); // get length of line typed in shell
        strcpy(arg, ""); // reset arg
        strcpy(command, ""); // reset command

        // Perform string tokenization to get the command and argument
        strcpy(delim, " ");
        token = strtok(buffer, delim); // get first word
        if (token[strlen(token)-1] == '\n')
            token[strlen(token)-1] = '\0'; // remove newline character if at end of string
        strcpy(command, token); // copy token to command

        // loop to get second word in buffer
        while(token != NULL) {
            strcpy(delim, "\n");
            token = strtok(NULL, delim);
            if (token == NULL)
                break;
            strcpy(arg, token); // store second word in arg 
        }

        // Check the command and execute the operations for each command
        // cd command -- change the current directory
        if (strcmp(command, "cd") == 0) {
            if (strcmp(arg, " ") == 0 || strcmp(arg, "") == 0)
                printf("Error: cd: argument required\n");
            cd(arg);
        } else if (strcmp(command, "clr") == 0) {
            clr();
        } else if (strcmp(command, "dir") == 0) {
            dir(arg);
        } else if (strcmp(command, "environ") == 0) {
            //environ();
        } else if (strcmp(command, "echo") == 0) {
            echo(arg);
        } else if (strcmp(command, "help") == 0) {
            help();
        } else if (strcmp(command, "pause") == 0) {
            pauses();
        }
        
        // quit command -- exit the shell
        else if (strcmp(command, "quit") == 0) {
            return EXIT_SUCCESS;
        }

        // Unsupported command
        else {
            fputs("Unsupported command, use help to display the manual\n", stderr);
        }
    }
    free(token); // free the token pointer
    return EXIT_SUCCESS;
}
