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
