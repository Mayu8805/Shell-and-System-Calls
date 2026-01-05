#ifndef REDIRECTION_H
#define REDIRECTION_H

int find_and_replace_fd(char **command_arguments);
int find_less_than(char **input);
int find_greater_than(char **input);
int set_stdin_fd(char *file_name);
int set_stdout_fd(char *file_name);

#endif
