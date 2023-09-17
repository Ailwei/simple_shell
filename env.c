#include "shell.h"

/**
 * set_environment_variable - Set an environment variable.
 * @variable: The name of the variable to set.
 * @value: The value to assign to the variable.
 *
 * This function sets or modifies an environment variable.
 *
 * Return: 0 on success, 1 on failure.
 */
int set_env(const char *variable, const char *value)
{
    if (setenv(variable, value, 1) != 0)
    {
        perror("setenv");

        /* Return 1 to indicate failure*/

	return (1);
    }
    /*Return 0 to indicate success*/

    return (0);
}

/**
 * unset_environment_variable - Unset an environment variable.
 * @variable: The name of the variable to unset.
 *
 * This function unsets an environment variable.
 *
 * Return: 0 on success, 1 on failure.
 */
int unset_env(const char *variable)
{
    if (unsetenv(variable) != 0)
    {
        perror("unsetenv");
        return (1); /* Return 1 to indicate failure*/
    }
    return (0); /* Return 0 to indicate success*/
}

