#include "shell.h"

/**
 * initializeShellInfo - initializes ShellInfo struct
 * @info: pointer to ShellInfo struct
 */
void initializeShellInfo(ShellInfo *info)
{
    info->arguments = NULL;
    info->argumentVector = NULL;
    info->executablePath = NULL;
    info->argumentCount = 0;
}

/**
 * setShellInfo - sets values in ShellInfo struct
 * @info: pointer to ShellInfo struct
 * @av: argument vector
 */
void setShellInfo(ShellInfo *info, char **av)
{
    int i = 0;

    info->programName = av[0];
    if (info->arguments)
    {
        info->argumentVector = stringToWords(info->arguments, " \t");
        if (!info->argumentVector)
        {
            info->argumentVector = malloc(sizeof(char *) * 2);
            if (info->argumentVector)
            {
                info->argumentVector[0] =  replaceString(info->arguments);
                info->argumentVector[1] = NULL;
            }
        }
        for (i = 0; info->argumentVector && info->argumentVector[i]; i++)
            ;
        info->argumentCount = i;

        replaceAliases(info);
        replaceVariables(info);
    }
}

/**
 * freeShellInfo - frees fields in ShellInfo struct
 * @info: pointer to ShellInfo struct
 * @all: true if freeing all fields
 */
void freeShellInfo(ShellInfo *info, int all)
{
    freeStringArray(info->argumentVector);
    info->argumentVector = NULL;
    info->executablePath = NULL;
    if (all)
    {
        if (!info->commandBuffer)
            free(info->arguments);
        if (info->environmentVariables)
            freeStringList(&(info->environmentVariables));
        if (info->commandHistory)
            freeStringList(&(info->commandHistory));
        if (info->aliases)
            freeStringList(&(info->aliases));
        freeStringArray(info->environ);
        info->environ = NULL;
        free(info->commandBuffer);
        if (info->readFileDescriptor > 2)
            close(info->readFileDescriptor);
        flushStandardOutputBuffer();
    }
}

