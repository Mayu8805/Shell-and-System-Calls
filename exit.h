/*
Team Name: Team 8 - (SysForge)

 Member Name: Mayuresh Keshav Kamble

 Course: CSCE 3600.002

 Description: This is builtin_exit.h - Header file for the exit built-in command.
              Provides function declarations for implementing the exit command
              functionality in the shell.

 */

#ifndef BUILTIN_EXIT_H
#define BUILTIN_EXIT_H

/* Global flag to signal shell should exit */
extern int should_exit_flag;

/**
 * executeExit - Execute the exit built-in command
 *
 * Sets a global flag to signal the shell to exit after all commands
 * on the current line have finished executing.
 *
 * Parameters:
 *   command_arguments - Array of command arguments (command_arguments[0] should be "exit")
 *
 * Returns: 0 to signal shell should exit, 1 otherwise
 *
 * Side Effects:
 *   - Sets the global variable should_exit_flag to 1
 *   - May print warning to stderr if extra arguments provided
 */
int executeExit(char **command_arguments);

/**
 * isExitCommand - Check if a command is the exit command
 *
 * Helper function to determine if the given command arguments
 * represent the exit built-in command.
 *
 * Parameters:
 *   command_arguments - Array of command arguments
 *
 * Returns:
 *   1 if command_arguments[0] is "exit"
 *   0 otherwise
 */
int isExitCommand(char **command_arguments);

#endif /* BUILTIN_EXIT_H */
