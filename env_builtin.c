#include "shell.h"

/**
 * env_builtin - Implements the env built-in command
 * @envp: The environment variables
 */

void env_builtin(char **envp)
{
	int i;

	/*Iterate through and print the environment variables */

	for (i = 0; envp[i] != NULL; i++)
	{
		printf("%s\n", envp[i]);
	}


}
