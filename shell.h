/*

 Team Name: Team 8 - (SysForge)

 Members Names: Colten Mikulastik, Mayuresh Keshav Kamble, Nathanlie Ortega, and Igor Leeck

 Course: CSCE 3600.002

 Date: December 4, 2025

 Description: This is shell.h, a Header FIle.

 */

#ifndef SHELL_H
#define SHELL_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <errno.h>
#include <signal.h>


//The global constants
#define MAXIMUM_INPUT_LENGTH 512
#define MAXIMUM_ARGUMENT_COUNT 64



//Cd Command and Alias Support (Nathanlie Ortega):

//Alias Support configuration
#define TOTAL_ALIAS_CAPACITY 50
#define ALIAS_NAME_MAXIMUM_LENGTH 50
#define ALIAS_COMMAND_MAXIMUM_LENGTH 256


typedef struct
{
    char shortName[ALIAS_NAME_MAXIMUM_LENGTH];

    char fullCommand[ALIAS_COMMAND_MAXIMUM_LENGTH];

    int isActive;                //This means that 1 if is in use, 0 if is removed
}

AliasEntry;

//This is global alias storage
extern AliasEntry aliasStorage[TOTAL_ALIAS_CAPACITY];
extern int alias_count;



//Command execution implementation for "cd"
int executeCD(char **command_arguments);

//Implementation Functions for "Alias Support"
int executeAlias(char **command_arguments);
void initializeAlias(void);
int storeAlias(const char *shortName, const char *command_string);
int deleteAlias(const char *shortName);
void removeAllAliases(void);
void printAliases(void);
char* findAlias(const char *user_input);



//TODO: Colten's functions (path command and I/O redirection)
#include "path.h"
#include "redirection.h"


//TODO: Mayuresh's functions (exit command and pipelining)
#include "exit.h"
#include "pipeline.h"


//TODO: Igor's functions (myhistory command and signal handling)
#include "myhistory.h"
#include "signalhandler.h"



//These are the shell helper function prototypes for main.c file.
char** inputParse(char *input_line);

int procExecuteCommand(char **command_arguments, char **shell_path);

void deallocateArgument(char **command_arguments);

#endif

/* SHELL_H */
