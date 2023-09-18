#include "shell.h"

int execute_command(const char *command)
{
	 int exit_status;

	/*fork a child process to execute the coomand */

	pid_t child_pid= fork();

	if (child_pid == -1)
	{
		perror("Fork failed");
		exit(1);
	}
	else if (child_pid == 0)
	{
		/* this is the child process */
		
		execlp(command, command, NULL);

		/*if execp returns, there was an error */

		perror("Command execution failed");
		exit(1);

	}
	else
	{
		/*( This is the arent process */

		int status;
		waitpid(child_pid, &status, 0);

		if (WIFEXITED(status))
		{
			exit_status = WEXITSTATUS(status);

			if (exit_status != 0)
			{
				printf("Error: Command exited with status %d\n", exit_status);
			}
		}
		else
		{
			printf("Error: Command did not exit normally\n");
			
		}
		return (exit_status);

	}
}
