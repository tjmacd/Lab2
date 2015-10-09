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

// Define your utility functions here, these will most likely be functions that you call
// in your myshell.c source file

//cd <directory> - Change the current default directory to <directory>
extern void cd(const char *name){

}

//clr - Clear the screen
void clr(){
	system("clear");
}

//dir <directory> - List the contents of directory <directory>
void dir(const char *name){
    DIR *directory;
    struct dirent *ep;

    directory = opendir(name);
    if(directory != NULL){
        while(ep = readdir(directory)){
            puts(ep->d_name);
        }
        (void) closedir(directory);
    }
    else{
        perror("Couldn't open the directory");
    }
}

//environ - List all the environment strings
extern void environ(){

}

//echo <comment> - Display <comment> on the display followed by a
//new line (multiple spaces/tabs may be reduced to a single space)
extern void echo(const char *text){

}

//help - Display the user manual using the more filter
extern void help(){

}

//pause - Pause operation of the shell until 'Enter' is pressed
extern void pause(){

}

