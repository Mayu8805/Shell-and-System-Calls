/*
Team Name: Team 8 - (SysForge)

 Member Name: Mayuresh Keshav Kamble

 Course: CSCE 3600.002

 Description: This is builtin_exit.c - Implementation of the exit built-in command.
              This command allows the user to exit the shell. If the exit command is
              on the same line with other commands (separated by semicolons), it ensures
              that the other commands execute and finish before exiting the shell.

 Valid examples:
   newshell> exit
   newshell> exit; cat file1
   newshell> cat file1; exit

 */

#include "exit.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* Global flag to signal that the shell should exit */
int should_exit_flag = 0;


/**
 * executeExit - Execute the exit built-in command
 *
 * This function is called when the user types "exit" at the shell prompt.
 * It sets a global flag that tells the main shell loop to exit after
 * completing execution of all commands on the current line.
 *
 * Parameters:
 *   command_arguments - Array of command arguments (command_arguments[0] is "exit")
 *
 * Returns: 0 to signal that shell should exit
 *
 * Implementation Notes:
 *   - Does not call exit() directly to allow other commands to complete
 *   - Sets the global should_exit_flag to 1
 *   - Main shell loop checks this flag after executing all commands
 */
int executeExit(char **command_arguments)
{
    /* Validate that we have at least the command name */
    if (command_arguments[0] == NULL)
    {
        return 1;
    }

    /* Check if extra arguments were provided (optional validation) */
    if (command_arguments[1] != NULL)
    {
        fprintf(stderr, "Warning: exit does not take arguments\n");
    }

    /* Set the global exit flag */
    should_exit_flag = 1;

    /* Return 0 to signal that shell should exit
     * The main loop will check should_exit_flag and terminate
     * after all commands on the current line have been processed.
     *
     * Example:
     *   newshell> ls; exit; pwd
     *   This will execute ls, set should_exit_flag=1, then execute pwd,
     *   and finally exit the shell.
     */
    return 0;
}


/**
 * isExitCommand - Check if the given command is "exit"
 *
 * This helper function determines whether the command being processed
 * is the exit built-in command.
 *
 * Parameters:
 *   command_arguments - Array of command arguments
 *
 * Returns: 1 if the command is "exit", 0 otherwise
 *
 * Usage:
 *   if (isExitCommand(command_arguments)) {
 *       return executeExit(command_arguments);
 *   }
 */
int isExitCommand(char **command_arguments)
{
    /* Check for NULL array */
    if (command_arguments == NULL || command_arguments[0] == NULL)
    {
        return 0;
    }

    /* Compare first argument with "exit" */
    return (strcmp(command_arguments[0], "exit") == 0);
}
