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
typedef struct{
	char name[8];
	char value[256];
} env_var;

env_var env_vars[2];

// Define functions declared in myshell.h here
// Returns the current working directory path
char *get_cwd(){
    return getcwd(NULL, BUFFER_LEN);
}

// Returns the path of the current executable
char *get_executable(char* SHELL){
	SHELL = (char *) calloc(BUFFER_LEN, sizeof(char));
	int n = readlink("/proc/self/exe", SHELL, BUFFER_LEN);
	if(n > 0){
		return SHELL;
	} else {
		return NULL;
	}
}

int main(int argc, char *argv[]) {
    // Input buffer and and commands
    char buffer[BUFFER_LEN] = { 0 };
    char command[BUFFER_LEN] = { 0 };
    char arg[BUFFER_LEN] = { 0 };
    char delim[BUFFER_LEN];
    char* token;
    char* SHELL;

	//Initiallize environment variables
    SHELL = "";
	strcpy(env_vars[0].name, "PWD");
	strcpy(env_vars[0].value, get_cwd());
	strcpy(env_vars[1].name, "SHELL");
	strcpy(env_vars[1].value, get_executable(SHELL));

    // Parse the commands provided using argc and argv

	printf("%s> ", get_cwd());
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
		printf("%s> ", get_cwd());
    }
    free(token), free(SHELL); // free the token pointer
    return EXIT_SUCCESS;
}
