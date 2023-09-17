#include "shell.h"

void execute_command_with_args(char *command)
{
	pid_t child_pid = fork();

	if (child_pid == -1)
	{
		perror("Fork failed");
		exit(1);
	}
	else if (child_pid == 0)
	{
		/*This is the child process */

		char *args[MAX_ARGS + 2];
		
		/*tokenise the cmd into args */

			int arg_count = 0;
			char *token =strtok(command, " ");

			while (token != NULL && arg_count< MAX_ARGS)
			{
				args[arg_count++] = token;
				token = strtok(NULL, " ");
			}
			args[arg_count++] = NULL;
			execvp(args[0], args);

			/*if execvp retuens there was an error */
			perror("Command execution failed");
			exit(1);
	}
	else
	{
		/* this the parent process */
		 int status;
		 waitpid(child_pid, &status, 0);

		 if (WIFEXITED(status))
		 {
			 int exit_status = WEXITSTATUS(status);

			 if (exit_status != 0)
			 {
				 printf("Error: Command exited with status %d\n", exit_status);
			 }
		 }
		 else
		 {
			 printf("Error: Command did not exit normally\n");
		 }
	}
}
