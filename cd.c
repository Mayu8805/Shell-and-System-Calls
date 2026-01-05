/*

 Team Name: Team 8 - (SysForge)

 Member Built-in Command Role "cd": Nathanlie Ortega

 Course: CSCE 3600.002

 Date: December 4, 2025

 Description: This is cd.c file that implements the change directory built-in command.

 */


 #include "shell.h"


int executeCD(char **command_arguments)
{
    char *targetPath;
    char *homeDir;

    //This will check if user wants to go to HOME directory
    if (command_arguments[1] == NULL || strcmp(command_arguments[1], "~") == 0)
    {

        homeDir = getenv("HOME");       //This will retrieve the home environment variable for system call.

        if (homeDir == NULL)
        {
            fprintf(stderr, "cd: HOME environment variable not set\n");
            return 0;
        }

        targetPath = homeDir;

    }

    else
    {
        //This gives user provided a specific path
        targetPath = command_arguments[1];
    }


    //This is to Use chdir() system call to change directory
    if (chdir(targetPath) != 0)
    {
        perror("cd");           //This means that if chdir returns -1 on error, error message will display.
        return 0;
    }


    return 1;                   //Return 1 when successfully changed directory.
}
