/*

 Team Name: Team 8 - (SysForge)

 Member Advanced Feature Role "Alias Support": Nathanlie Ortega

 Course: CSCE 3600.002

 Date: December 4, 2025

 Description: This is alias.c file that implements the Alias Support.

 */


 #include "shell.h"

//Global alias storage
AliasEntry aliasStorage[TOTAL_ALIAS_CAPACITY];
int alias_count = 0;


void initializeAlias(void)
{
    int arrIdx;

    //This will clear all alias slots.
    for (arrIdx = 0; arrIdx < TOTAL_ALIAS_CAPACITY; arrIdx++)
    {
        aliasStorage[arrIdx].isActive = 0;
        aliasStorage[arrIdx].shortName[0] = '\0';
        aliasStorage[arrIdx].fullCommand[0] = '\0';
    }

    alias_count = 0;
}


int storeAlias(const char *shortName, const char *command_string)
{
    int searchIdx;

    //This will check if this alias name already exists.
    for (searchIdx = 0; searchIdx < TOTAL_ALIAS_CAPACITY; searchIdx++)
    {
        if (aliasStorage[searchIdx].isActive && strcmp(aliasStorage[searchIdx].shortName, shortName) == 0)
        {
            //Therefore, if the alias does exists, it will update the command.
            strncpy(aliasStorage[searchIdx].fullCommand, command_string, ALIAS_COMMAND_MAXIMUM_LENGTH - 1);

            aliasStorage[searchIdx].fullCommand[ALIAS_COMMAND_MAXIMUM_LENGTH - 1] = '\0';

            return 1;
        }
    }

    //If Alias doesn't exist, it will find an empty slot.
    for (searchIdx = 0; searchIdx < TOTAL_ALIAS_CAPACITY; searchIdx++)
    {
        if (!aliasStorage[searchIdx].isActive)
        {
            //When found empty slot, this will store new alias.
            strncpy(aliasStorage[searchIdx].shortName, shortName, ALIAS_NAME_MAXIMUM_LENGTH - 1);

            aliasStorage[searchIdx].shortName[ALIAS_NAME_MAXIMUM_LENGTH - 1] = '\0';

            strncpy(aliasStorage[searchIdx].fullCommand, command_string, ALIAS_COMMAND_MAXIMUM_LENGTH - 1);

            aliasStorage[searchIdx].fullCommand[ALIAS_COMMAND_MAXIMUM_LENGTH - 1] = '\0';

            aliasStorage[searchIdx].isActive = 1;

            alias_count++;

            return 1;
        }
    }

    //This statement means that there is no empty slots available.
    fprintf(stderr, "alias: maximum number of aliases reached\n");
    return 0;
}


int deleteAlias(const char *shortName)
{
    int searchIdx;

    for (searchIdx = 0; searchIdx < TOTAL_ALIAS_CAPACITY; searchIdx++)
    {
        if (aliasStorage[searchIdx].isActive && strcmp(aliasStorage[searchIdx].shortName, shortName) == 0)
        {
            //This means that if the alias found, it will mark as inactive.
            aliasStorage[searchIdx].isActive = 0;
            alias_count--;
            return 1;
        }
    }

    //This means that the Alias is not found.
    fprintf(stderr, "alias: %s: not found\n", shortName);

    return 0;

}



//This indicates the removal of the entire alias system.
void removeAllAliases(void)
{
    int clearIdx;

    for (clearIdx = 0; clearIdx < TOTAL_ALIAS_CAPACITY; clearIdx++)
    {
        aliasStorage[clearIdx].isActive = 0;
    }

    alias_count = 0;
}


//This will display all currently defined aliases.
void printAliases(void)
{
    int displayIdx;
    int foundAny = 0;

    for (displayIdx = 0; displayIdx < TOTAL_ALIAS_CAPACITY; displayIdx++)
    {
        if (aliasStorage[displayIdx].isActive)
        {
            printf("alias %s='%s'\n", aliasStorage[displayIdx].shortName, aliasStorage[displayIdx].fullCommand);
            foundAny = 1;

        }
    }

    if (!foundAny)
    {
        printf("No aliases defined\n");
    }
}



char* findAlias(const char *user_input)
{
    int lookupIdx;
    char *subCmd;

    for (lookupIdx = 0; lookupIdx < TOTAL_ALIAS_CAPACITY; lookupIdx++)
     {
        if (aliasStorage[lookupIdx].isActive && strcmp(aliasStorage[lookupIdx].shortName, user_input) == 0)
        {
            //This means that if matching alias is found, it will allocate memory for return value.
            subCmd = malloc(strlen(aliasStorage[lookupIdx].fullCommand) + 1);

            if (subCmd == NULL)
            {
                perror("malloc");
                return NULL;
            }

            strcpy(subCmd, aliasStorage[lookupIdx].fullCommand);

            return subCmd;

        }
    }

    //This means that the matching alias not found.
    return NULL;
}

//This is Alias execution
int executeAlias(char **command_arguments)
{
    char *equalsPos;
    char *aliasName;
    char *aliasCmd;
    char reconBuffer[512];
    int argIdx;

    //This will display all aliases
    if (command_arguments[1] == NULL)
    {
        printAliases();
        return 1;
    }

    //This will clear all aliases flag
    if (strcmp(command_arguments[1], "-c") == 0)
    {
        removeAllAliases();
        return 1;
    }

    //This will remove single alias flag
    if (strcmp(command_arguments[1], "-r") == 0)
    {
        if (command_arguments[2] == NULL)
        {
            fprintf(stderr, "alias: -r requires an argument\n");
            return 1;

        }

        deleteAlias(command_arguments[2]);

        return 1;

    }


    //This will reconstruct full argument since parsing may have split it.
    strcpy(reconBuffer, command_arguments[1]);

    argIdx = 2;


    while (command_arguments[argIdx] != NULL)
    {
        strcat(reconBuffer, " ");
        strcat(reconBuffer, command_arguments[argIdx]);
        argIdx++;
    }

    //This will locate the equals sign.
    equalsPos = strchr(reconBuffer, '=');

    if (equalsPos == NULL)
    {
        fprintf(stderr, "alias: invalid syntax. Use: alias name='command'\n");
        return 1;
    }

    //This will split into name and command parts.
    *equalsPos = '\0';

    aliasName = reconBuffer;

    aliasCmd = equalsPos + 1;

    //Implemented so that quotes are removed if present
    if (aliasCmd[0] == '\'' || aliasCmd[0] == '"')
    {
        aliasCmd++;                     //This will skip opening quote.
        int cmdLen = strlen(aliasCmd);


        if (cmdLen > 0 && (aliasCmd[cmdLen-1] == '\'' || aliasCmd[cmdLen-1] == '"'))
        {
            aliasCmd[cmdLen-1] = '\0';
        }
    }


    //This procedure stores the new alias
    if (storeAlias(aliasName, aliasCmd))
    {
        printf("Alias added: %s='%s'\n", aliasName, aliasCmd);
    }

    return 1;

}
