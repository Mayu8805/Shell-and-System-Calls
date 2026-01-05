
#include <fcntl.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

int find_less_than(char **input)
{
    int i = 0;
    while(input[i] != NULL)
    {
        if(strcmp(input[i], "<") == 0 )
        {
            return i;
        }
        i++;
    }
    return -1;
}

int find_greater_than(char **input)
{
    int i = 0;
    while(input[i] != NULL)
    {
        if(strcmp(input[i], ">") == 0 )
        {
            return i;
        }
        i++;
    }
    return -1;
}

int set_stdin_fd(char *file_name)
{
    int temp_fd = open(file_name, O_RDONLY);
    if (temp_fd < 0) return 1;
    dup2(temp_fd, STDIN_FILENO);
    // close(STDIN_FILENO);
    return 0;
}

int set_stdout_fd(char *file_name)
{
    int temp_fd = open(file_name, O_WRONLY | O_CREAT, 0644);
    if (temp_fd < 0) return 1;
    dup2(temp_fd, STDOUT_FILENO);
    // close(STDOUT_FILENO);
    return 0;
}


int find_and_replace_fd(char **command_arguments)
{
    // look for < or > and change the file descriptor table as needed, command_args end in NULL
    int in_index = find_less_than(command_arguments);
    int out_index = find_greater_than(command_arguments);

    // check if our indecies are -1 (no redirection found)
    if(in_index != -1)
    {
        //call our set function
        if(set_stdin_fd(command_arguments[in_index + 1]) == 1)
        {
            printf("error when attempting to set input file");
        }
    }
    if(out_index != -1)
    {
        // call our set  function
        if(set_stdout_fd(command_arguments[out_index + 1]) == 1)
        {
            printf("error when attempting to set output file");
        }
    }
    return 1;
}
