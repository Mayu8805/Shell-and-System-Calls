
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

char *init_path()
{
    char * path = getenv("PATH");
    // return 0 if there was a failure to initialize path...
    if (path == NULL)
    {
        return 0;
    }
    else
    {
        return path;
    }
}

char *my_strdup(const char *in)
{
    int len = strlen(in) + 1;
    char *dup = malloc(len);
    if (dup != NULL)
    {
        strcpy(dup, in);
    }
    return dup;
}


int path_cmd(char **command_arguments, char **path)
{
    // we are going to be adjusting the path variable in the program
    // because I don't want to be messing with UNIX $PATH var...
    // check if there is any other arguments
    if(command_arguments[1] == NULL)
    {
        printf("current path is: %s\n", *path);
    }
    else
    {
        if(strcmp(command_arguments[1], "+") == 0)
        {
            // command attempt to add pathname to path.
            // get the length of current path
            int path_len = strlen(*path);
            int add_len = strlen(command_arguments[2]);
            int sum = path_len + add_len + 2; // + 1 for colon delemiter, + 1 for null term
            char *new_path = (char *)malloc(sum * sizeof(char)); // create new str storage

            // copy and concat to get our new path
            memcpy(new_path, *path, strlen(*path) + 1);
            strcat(new_path, ":");
            strcat(new_path, command_arguments[2]);

            // free old path (dereferenc path hidden string)
            free(*path);
            // set to new_path
            *path = new_path;
            //return a 0 for no problems
            return 0;
        }
        else if(strcmp(command_arguments[1], "-") == 0)
        {
            // command attempt to remove pathname from path
            int difference = (strlen(*path) - strlen(command_arguments[2])); // get difference + 1 for nullterm

            // create mutable copy of path.
            char *path_copy = my_strdup(*path);
            if(!path_copy) return 1;

            char *possible_new_path = (char *)malloc(sizeof(char) * (difference + 1)); // generate heap str w/o that removed path

            // some flags
            int found_flag = 0, first = 1;

            // split into list, over each ':', loop through them
            char *paths = strtok(path_copy,":");
            printf("%s", paths);
            while(paths != NULL)
            {
                // test to see if not same str
                if(strcmp(paths, command_arguments[2]) != 0)
                {
                    // add colon only if not the first path
                    if(!first)
                    {
                        strcat(possible_new_path,":");
                    }
                    // add paths that dont match to new path
                    strcat(possible_new_path, paths);
                    first = 0;
                }
                else
                {
                    // if same we don't add but set a flag so we know that it appeared
                    found_flag += 1;
                }
                paths = strtok(NULL, ":");
            }
            // check our flag
            if (found_flag == 0)
            {
                // if the str was not found, just leave path the same
                free(possible_new_path);
                free(path_copy);
                // let them know it wasn't successful
                return 1;
            }
            else
            {
                // if we removed the path, set our path
                free(*path);
                free(path_copy);
                *path = possible_new_path;
                return 0;
            }
        }
        else
        {
            // some input error occured
            printf("usage: path (+|-) <file path to add or remove>\n");
            // there was an error, not major tho
            return 1;
        }
    }
    //return a success to caller 0 == good :^)
    return 0;
}
