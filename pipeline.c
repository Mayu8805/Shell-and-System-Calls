/**
 * pipeline.c
 * Team 8 - SysForge
 * Author: Mayuresh Kamble
 */
#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>
#include "pipeline.h"

#define MAX_ARGS 100
#define MAX_PIPELINE_COMMANDS 3

static void parse_command(char *command, char *args[]) {
    int i = 0;
    char *token = strtok(command, " \t\n");

    while (token != NULL && i < MAX_ARGS - 1) {
        args[i++] = token;
        token = strtok(NULL, " \t\n");
    }
    args[i] = NULL;
}

void execute_pipeline(char *commands[], int num_commands) {
    int i, j;
    int pipes[2][2];
    pid_t pids[MAX_PIPELINE_COMMANDS];
    char *args[MAX_ARGS];
    int status;

    if (num_commands < 1) return;

    if (num_commands > MAX_PIPELINE_COMMANDS) {
        fprintf(stderr, "Error: maximum of %d commands supported in pipeline\n",
                MAX_PIPELINE_COMMANDS);
        return;
    }

    for (i = 0; i < num_commands - 1; i++) {
        if (pipe(pipes[i]) < 0) {
            perror("pipe");
            return;
        }
    }

    for (i = 0; i < num_commands; i++) {
        char *cmd_copy = strdup(commands[i]);
        if (cmd_copy == NULL) {
            perror("strdup");
            continue;
        }

        parse_command(cmd_copy, args);

        if (args[0] == NULL) {
            free(cmd_copy);
            continue;
        }

        pids[i] = fork();

        if (pids[i] < 0) {
            perror("fork");
            free(cmd_copy);
            return;
        }
        else if (pids[i] == 0) {


	    //Igor added this to help handle signals
	    signal(SIGINT, SIG_DFL);
	    signal(SIGTSTP, SIG_DFL);
	    signal(SIGQUIT, SIG_DFL);
	    //tell me to change this, if this causes problems


            if (i > 0) {
                if (dup2(pipes[i-1][0], STDIN_FILENO) < 0) {
                    perror("dup2 stdin");
                    exit(1);
                }
            }

            if (i < num_commands - 1) {
                if (dup2(pipes[i][1], STDOUT_FILENO) < 0) {
                    perror("dup2 stdout");
                    exit(1);
                }
            }

            for (j = 0; j < num_commands - 1; j++) {
                close(pipes[j][0]);
                close(pipes[j][1]);
            }

            execvp(args[0], args);
            fprintf(stderr, "Error: command '%s' not found\n", args[0]);
            exit(1);
        }

        free(cmd_copy);
    }

    for (i = 0; i < num_commands - 1; i++) {
        close(pipes[i][0]);
        close(pipes[i][1]);
    }

    for (i = 0; i < num_commands; i++) {
        if (waitpid(pids[i], &status, 0) < 0) {
            perror("waitpid");
        }
    }
}

int has_pipe(const char *command) {
    if (command == NULL) return 0;
    return (strchr(command, '|') != NULL);
}

int split_pipeline(char *command, char *pipe_commands[], int max_commands) {
    int count = 0;
    char *token;
    char *saveptr;

    token = strtok_r(command, "|", &saveptr);

    while (token != NULL && count < max_commands) {
        while (*token == ' ' || *token == '\t') {
            token++;
        }

        if (strlen(token) > 0) {
            char *end = token + strlen(token) - 1;
            while (end > token && (*end == ' ' || *end == '\t' || *end == '\n')) {
                *end = '\0';
                end--;
            }

            pipe_commands[count] = strdup(token);
            if (pipe_commands[count] == NULL) {
                perror("strdup");
                return count;
            }
            count++;
        }

        token = strtok_r(NULL, "|", &saveptr);
    }

    return count;
}
