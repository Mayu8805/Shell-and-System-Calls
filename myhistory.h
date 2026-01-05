#ifndef MY_HISTORY_H
#define MY_HISTORY_H

char *history_strdup(char *s);
void initHistory(void);
void executeMyHistory(char **command_arguments);
void print_history(void);
void write_history(char *cmd);
void clear_history(void);
char *get_history_command(int n);
char *return_old_command(char *old_cmd);
void execute_old_command(char *old_cmd);
char **parse_command(char *cmd);

#endif
