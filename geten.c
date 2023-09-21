#include "shell.h"

/**
 * getEnvironment - returns the string array copy of our environment
 * @info: Pointer to ShellInfo struct
 *
 * Return: String array containing environment variables
 */
char **getEnvironment(ShellInfo *info)
{
    if (!info->environment || info->environmentChanged)
    {
        info->environment = listToStrings(info->environmentVariables);
        info->environmentChanged = 0;
    }

    return (info->environment);
}

/**
 * unsetEnvironmentVariable - Remove an environment variable
 * @info: Pointer to ShellInfo struct
 * @variable: The string representing the environment variable
 *
 * Return: 1 on success, 0 otherwise
 */
int unsetEnvironmentVariable(ShellInfo *info, char *variable)
{
    list_t *node = info->environmentVariables;
    size_t index = 0;
    char *p;

    if (!node || !variable)
        return (0);

    while (node)
    {
        p = startsWith(node->str, variable);
        if (p && *p == '=')
        {
            info->environmentChanged = deleteNodeAtIndex(&(info->environmentVariables), index);
            index = 0;
            node = info->environmentVariables;
            continue;
        }
        node = node->next;
        index++;
    }
    return (info->environmentChanged);
}

/**
 * setEnvironmentVariable - Initialize a new environment variable
 *                         or modify an existing one
 * @info: Pointer to ShellInfo struct
 * @variable: The string representing the environment variable
 * @value: The string representing the environment variable's value
 *
 * Return: 0 on success, 1 on failure
 */
int setEnvironmentVariable(ShellInfo *info, char *variable, char *value)
{
    char *buffer = NULL;
    list_t *node;
    char *p;

    if (!variable || !value)
        return (1);

    buffer = malloc(_strlen(variable) + _strlen(value) + 2);
    if (!buffer)
        return (1);
    _strcpy(buffer, variable);
    _strcat(buffer, "=");
    _strcat(buffer, value);
    node = info->environmentVariables;
    while (node)
    {
        p = startsWith(node->str, variable);
        if (p && *p == '=')
        {
            free(node->str);
            node->str = buffer;
            info->environmentChanged = 1;
            return (0);
        }
        node = node->next;
    }
    addNodeEnd(&(info->environmentVariables), buffer, 0);
    free(buffer);
    info->environmentChanged = 1;
    return (0);
}

