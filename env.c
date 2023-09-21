#include "shell.h"

/**
 * _copyenv - Creates a copy of the environment.
 *
 * Return: If an error occurs - NULL.
 *         Otherwise - a double pointer to the new copy.
 */
char **_copyenv(void)
{
    char **new_env;
    size_t size;
    int index;

    for (size = 0; environ[size]; size++)
        ;

    new_env = malloc(sizeof(char *) * (size + 1));
    if (!new_env)
        return (NULL);

    for (index = 0; environ[index]; index++)
    {
        new_env[index] = malloc(_strlen(environ[index]) + 1);

        if (!new_env[index])
        {
            for (index--; index >= 0; index--)
                free(new_env[index]);
            free(new_env);
            return (NULL);
        }
        _strcpy(new_env[index], environ[index]);
    }
    new_env[index] = NULL;

    return (new_env);
}

/**
 * Release_env - Frees the copied environment.
 */
void release_env(void)
{
    int index;

    for (index = 0; environ[index]; index++)
        free(environ[index]);

    free(environ);
}

/**
 * getenv - Gets an environmental variable from the PATH.
 * @var: The name of the environmental variable to get.
 *
 * Return: If the environmental variable does not exist - NULL.
 *         Otherwise - a pointer to the environmental variable.
 */
char **get_env(const char *var)
{
    int index, len;

    len = _strlen(var);
    for (index = 0; environ[index]; index++)
    {
        if (_strncmp(var, environ[index], len) == 0)
            return (&environ[index]);
    }

    return (NULL);
}

