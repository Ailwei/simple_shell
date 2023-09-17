#include "shell.h"

/* Implement the exit builtin command */

void exit_shell(char *shell_name)
{
	/* Exit the shell with a status code of 0*/
	printf("Exiting %s.\n", shell_name);
	exit(0);
}
