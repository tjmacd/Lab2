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

// Define your utility functions here, these will most likely be functions that you call
// in your myshell.c source file

//cd <directory> - Change the current default directory to <directory>
void cd(char *name) {
    if (chdir(name) == -1) {
        puts("Error: directory not found");
    } else {
        setenv("PWD", name, 1);
    }
}

//clr - Clear the screen
void clr(){
	system("clear");
}

//dir <directory> - List the contents of directory <directory>
void dir(char *name){
	if(strcmp(name, "") == 0){
		name = ".";
	}

    DIR *directory;
    struct dirent *ep = NULL;

    directory = opendir(name);
    if(directory != NULL){
        while((ep = readdir(directory))){
            puts(ep->d_name);
        }
        (void) closedir(directory);
    }
    else{
        perror("Couldn't open the directory");
    }
    free(ep);
}

//environ - List all the environment strings
void environ(char* env[]){
	int i;
	for( i = 0; env[i] != NULL; i++) {
		printf("%s\n",env[i]);
	}	
}

//echo <comment> - Display <comment> on the display followed by a
//new line (multiple spaces/tabs may be reduced to a single space)
void echo(char *text){
    puts(text);
}

//help - Display the user manual using the more filter
void help(){
    system("more readme");
}

//pause - Pause operation of the shell until 'Enter' is pressed
void pauses(){
	char c;
	puts("Press Enter to continue...");
	do{
		c = fgetc(stdin);
	} while (c != 10);
}

