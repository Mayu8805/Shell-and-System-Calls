/* Add a new built-in myhistory command that lists the shell history of previous
commands run in your shell (not the bash shell). Note that this does not have
to work with the up-arrow key as in bash, but only with a new myhistory
command run inside your shell. You may not make use of the history builtin
command, but instead keep track of your history of commands in some sort of
data structure. Your myhistory built-in command should support a history of
20 most recent commands (i.e., this means that the 21st command will overwrite
the 1st command, for example). Your myhistory command should support a
couple flags: -c to clear your myhistory list by deleting all entries, and -e
<myhistory_number> to execute one of your twenty myhistory
commands in your list. */

/*
* Team 8
* shell functionality: myhistory
* author: Igor Leeck
*
*/

#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>

#include "myhistory.h"
#include "pipeline.h"

#define MAX_HIST_SIZE 20

char *history[MAX_HIST_SIZE];
int current_history = 0; //next index to insert at
int history_size = 0; //how many commands are being stored

//there already was another one I wanted to make a new one
char *history_strdup(char *s) {
    size_t length = strlen(s) + 1;
    char *copy = malloc(length);
    if(!copy) {
	return NULL;
    }

    for(size_t i=0; i<length; i++) {
	copy[i] = s[i];
    }
    return copy;
}

void initHistory() {
    for (int i=0; i < MAX_HIST_SIZE; i++) {
	history[i] = NULL;
    }
    current_history = 0;
    history_size = 0;
}

void executeMyHistory(char **command_arguments) {
    size_t size = 0;
    while(command_arguments[size] != NULL) {
	// printf("%s\n", command_arguments[size]);
	size++;
    }
    if(size == 1) {
	print_history();
    } else if(size == 2) {
	if(strcmp(command_arguments[1], "-c") == 0) {
	    if(current_history == 0) {
		printf("No history to clear\n");
	    } else {
		printf("Clearing history\n");
		clear_history();
	    }
	}
    } else if (size == 3) {

	if(strcmp(command_arguments[1], "-e") == 0){
	    if(command_arguments[2] == NULL) {
		printf("Invalid set of arguments\n");
		return;
	    }
	    int num = atoi(command_arguments[2]);

	    if(num < 1 || num > 20) {
		printf("Out of range of history\n");
		return;
	    }
	    char *old_cmd = return_old_command(history[num - 1]);
	    execute_old_command(old_cmd);
	    free(old_cmd);
	} else {
	    printf("Invalid set of arguments\n");
	}
    } else {
	printf("Invalid number of arguments\n");
	return;
    }
}


void write_history(char *cmd) {
    //this is to overwrite previous history
    if (history[current_history] != NULL) {
	free(history[current_history]);
    }

    history[current_history] = history_strdup(cmd);

    current_history = (current_history + 1) % MAX_HIST_SIZE;

    //once it becomes 20 it doesn't grow any further
    if (history_size < MAX_HIST_SIZE) {
	history_size++;
    }
}

void print_history() {
    if(history_size == 0) {
	printf("No history to display\n");
	return;
    }

    //want to start at the beginning whether that is wrapped around or not
    int starting_index = (current_history - history_size + MAX_HIST_SIZE) % MAX_HIST_SIZE;

    //iterate through history to print it out
    for(int i=0; i<history_size; i++) {
	int index = (starting_index + i) % MAX_HIST_SIZE;
	printf("%d: %s", i+1, history[index]);
    }
}

void clear_history() {
    for(int i=0; i<MAX_HIST_SIZE; i++) {
	if(history[i]) {
	    free(history[i]);
	    history[i] = NULL;
	}
    }
    current_history = 0;
    history_size = 0;
}

//returning back the old command as a group of arguments
char **parse_command(char *cmd) {
    int count = 0;
    char *tmp = history_strdup(cmd);
    char *token = strtok(tmp, " \t\n");
    while (token != NULL) {
	count++;
	token = strtok(NULL, " \t\n");
    }
    free(tmp);

    char **args = malloc((count+1) * sizeof(char*));
    int i = 0;
    token = strtok(cmd, " \t\n");
    while(token != NULL) {
	args[i] = token;
	i++;
	token = strtok(NULL, " \t\n");
    }
    args[i] = NULL;
    return args;
}

char *return_old_command(char *old_cmd) {
    if(old_cmd == NULL) {
	printf("Invalid option\n");
	return NULL;
    }

    //must copy to not alter history
    char *cmd = history_strdup(old_cmd);
    return cmd;
}

void execute_old_command(char *old_cmd) {
    //cause you free the original one later
    char *cmd_copy = history_strdup(old_cmd);

    if(has_pipe(cmd_copy)) {
	char *pipeCommands[4];
	int pipeCount = split_pipeline(cmd_copy, pipeCommands, 4);

	if (pipeCount > 0) {
	    execute_pipeline(pipeCommands, pipeCount);
	    for(int i=0;i<pipeCount;i++) {
		free(pipeCommands[i]);
	    }
	}

	free(cmd_copy);
    } else {

    char **args = parse_command(cmd_copy);

    if(args[0] == NULL) {
	free(args);
	free(cmd_copy);
	return;
    }

    if (strcmp(args[0], "myhistory") == 0) {
	executeMyHistory(args);
    } else {

	printf("Executing command %s \n", cmd_copy);
	fflush(stdout);

	pid_t pid = fork();
	if (pid == 0) {
	    execvp(args[0], args);
	    perror("Invalid command");
	    //exit child process
	    exit(1);
	} else if (pid > 0) {
	    waitpid(pid, NULL, 0);
	} else {
	    perror("Fork didn't work\n");
	}

    }
    free(args);
    free(cmd_copy);

    }
    /* char **args = parse_command(cmd_copy);

    if(args[0] == NULL) {
	free(args);
	free(cmd_copy);
	return;
    }

    if (strcmp(args[0], "myhistory") == 0) {
	executeMyHistory(args);
    } else {

	printf("Executing command %s \n", cmd_copy);
	fflush(stdout);

	pid_t pid = fork();
	if (pid == 0) {
	    execvp(args[0], args);
	    perror("Invalid command");
	    //exit child process
	    exit(1);
	} else if (pid > 0) {
	    waitpid(pid, NULL, 0);
	} else {
	    perror("Fork didn't work\n");
	}

    }
    free(args);
    free(cmd_copy); */
}
