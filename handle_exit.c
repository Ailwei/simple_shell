#include "shell.h"

/**
 * Handle the exit command with status.
 * @param status The exit status to use.
 */

void handle_exit(const char *status)
{
	int exit_status = atoi(status);
	exit(exit_status);
}
