/*
 * MyShell Project for SOFE 3950U / CSCI 3020U: Operating Systems
 *
 * Copyright (C) 2015, Muhammad Ahmad, Timothy MacDougall, Devin Westbye
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
#define NUM_ENV 2

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

int main(int argc, char *argv[], char *env[]) {
    // Input buffer and and commands
    char buffer[BUFFER_LEN] = { 0 };
    char command[BUFFER_LEN] = { 0 };
    char arg[BUFFER_LEN] = { 0 };
    char delim[BUFFER_LEN];
    char* token = NULL;
    char* SHELL = NULL;

	setenv("SHELL", get_executable(SHELL), 1);
	free(SHELL);


    // Parse the commands provided using argc and argv
	FILE *in_stream;
	if(argc > 1){
		in_stream = fopen(argv[1], "r");
		if(in_stream == NULL){
			printf("Could not open file %s", argv[1]);
			return EXIT_FAILURE;
		}
		
	} else {
		in_stream = stdin;
		printf("%s> ", get_cwd());
	}

	
    // Perform an infinite loop getting command input from users
    while (fgets(buffer, BUFFER_LEN, in_stream) != NULL) {
        strcpy(arg, ""); // reset arg
        strcpy(command, ""); // reset command
        // Perform string tokenization to get 
		// the command and argument
        strcpy(delim, " ");
        token = strtok(buffer, delim); // get first word
		// remove newline character if at end of string
        if (token[strlen(token)-1] == '\n')
            token[strlen(token)-1] = '\0'; 
        strcpy(command, token); // copy token to command

        // loop to get second word in buffer
        while(token != NULL) {
            strcpy(delim, "\n");
            token = strtok(NULL, delim);

            if (token == NULL)
                break;
            strcpy(arg, token); // store second word in arg 
        }

        // Check command and execute operations for each command
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
            environ(env);
        } else if (strcmp(command, "echo") == 0) {
            echo(arg);
        } else if (strcmp(command, "help") == 0) {
			help();
        } else if (strcmp(command, "pause") == 0) {
            pauses();
        } else if (strcmp(command, "") == 0) {
            
        } 
        
        // quit command -- exit the shell
        else if (strcmp(command, "quit") == 0) {
            return EXIT_SUCCESS;
        }

        // Unsupported command
        else {
            char program[BUFFER_LEN];
            char location[BUFFER_LEN];
            int len = sizeof(command) / sizeof(command[0]);

            for (int i = len; i >= 0; i--) {
                if (command[i] == '/') {
                    for (int j = i+1; j < len; j++) {
                        program[j-i-1] = command[j]; // get program name
                    }
                    for (int j = 0; j <= i; j++) {
                        location[j] = command[j]; // get location name
                    }
                    break;
                }
            }

            DIR *directory;
            struct dirent *ep = NULL;
            directory = opendir(location);
            if (directory != NULL) {
                while ((ep = readdir(directory))) {
                    if (strcmp(ep->d_name, program) == 0) {
                        int pid;
                        pid = fork();
                        if (pid < 0) {
                            printf("Error\n");
                            exit(1);
                        } else if (pid == 0) {
                            if (execvpe(program, arg, argv) == -1) { // run the program in the child process
                                printf("Error: could not run program\n");
                                exit(1);
                            }
                        }
                        wait(); // wait for the process to terminate
                    }
                }
            } else {
                printf("Program or program location does not exist\n");
            }
            //fputs("Unsupported command, use help to display the manual\n", stderr);
            free(ep);
        }
		if(argc == 1)
			printf("%s> ", get_cwd());

    }
    free(token); // free the token pointer
    return EXIT_SUCCESS;
}
