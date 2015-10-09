/*
 * MyShell Project for SOFE 3950U / CSCI 3020U: Operating Systems
 *
 * Copyright (C) 2015, <GROUP MEMBERS>
 * All rights reserved.
 * 
 */
#ifndef UTILITY_H_
#define UTILITY_H_

// Include your relevant functions declarations here they must start with the 
// extern keyword such as in the following example:
// extern void display_help(void);
extern void cd(const char *name);
extern void clr();
extern void dir(const char *name);
extern void environ(char* env[]);
extern void echo(const char *text);
extern void help();
extern void pauses();

#endif /* UTILITY_H_ */
