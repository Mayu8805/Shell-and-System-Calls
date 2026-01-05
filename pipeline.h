/**
 * pipeline.h
 *
 * Author: Mayuresh Kamble
 * Course: CSCE 3600 - Systems Programming
 *
 * Description: Header file for pipeline functionality.
 * Provides function declarations for implementing command pipelining
 * in the shell (supporting up to 3 commands with 2 pipes).
 */

#ifndef PIPELINE_H
#define PIPELINE_H

/**
 * execute_pipeline - Execute a series of commands connected by pipes
 *
 * Creates child processes and pipes to execute multiple commands where
 * the output of one command becomes the input of the next command.
 *
 * Parameters:
 *   commands     - Array of command strings to execute
 *   num_commands - Number of commands in the pipeline (max 3)
 *
 * Returns: void
 *
 * Example Usage:
 *   char *cmds[] = {"ls -l", "grep txt", "wc -l"};
 *   execute_pipeline(cmds, 3);
 *
 * System Calls:
 *   - Uses pipe() to create pipes
 *   - Uses fork() to create child processes
 *   - Uses dup2() to redirect stdin/stdout
 *   - Uses execvp() to execute commands
 *   - Uses waitpid() to wait for completion
 */
void execute_pipeline(char *commands[], int num_commands);

/**
 * has_pipe - Check if a command contains a pipe operator
 *
 * Determines whether a command string contains the pipe character '|'.
 *
 * Parameters:
 *   command - Command string to check
 *
 * Returns:
 *   1 if pipe operator '|' is found
 *   0 if no pipe operator found or command is NULL
 *
 * Example:
 *   has_pipe("ls | grep txt")  -> returns 1
 *   has_pipe("ls -l")          -> returns 0
 */
int has_pipe(const char *command);

/**
 * split_pipeline - Split a command string by pipe operators
 *
 * Parses a command string containing pipes and separates it into
 * individual command strings. Trims whitespace from each command.
 *
 * Parameters:
 *   command       - Command string to split (e.g., "ls | grep txt | wc")
 *   pipe_commands - Array to store pointers to split command strings
 *   max_commands  - Maximum number of commands to split into
 *
 * Returns:
 *   Number of commands found (0 to max_commands)
 *
 * Memory Management:
 *   - Allocates memory for each command string using strdup()
 *   - CALLER IS RESPONSIBLE for freeing each allocated string
 *
 * Example Usage:
 *   char *cmds[4];
 *   char input[] = "ls -l | grep txt | wc";
 *   int n = split_pipeline(input, cmds, 4);
 *   // n = 3, cmds[0]="ls -l", cmds[1]="grep txt", cmds[2]="wc"
 *
 *   // Free allocated memory
 *   for (int i = 0; i < n; i++) {
 *       free(cmds[i]);
 *   }
 */
int split_pipeline(char *command, char *pipe_commands[], int max_commands);

#endif /* PIPELINE_H */
