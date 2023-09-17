#include "shell.h"

void execute_command_with_path(char *command, char *path, char *shell_name )
{	
	char full_command[MAX_PATH_LENGTH];
	int found = 0;

	/*Tokenise the input to seperate command and arguments */

	char *args[MAX_ARGS + 2];

	/*Token the command line arguments */

	int arg_count = 0;
	char *token = strtok(command, " ");

	while (token != NULL && arg_count < MAX_ARGS)
	{
		args[arg_count++] = token;
		token = strtok(NULL, " ");
	}
	args[arg_count++] = NULL;

	/*check if command contans a '/' */

	if (strchr(args[0], '/') != NULL)
	{
		/* command contains a '/' it is already a full path */
		strcpy(full_command, args[0]);
	}
	else if (path != NULL)
	{
		/* use the provided path */
		char *path_token = strtok(path, ":");

		while (path_token != NULL)
		{
			snprintf(full_command, sizeof(full_command), "%s/%s", path_token, args[0]);

			if (access(full_command, X_OK) == 0)
			{
				found = 1;
				break;
			}
			path_token = strtok(NULL, ":");
		}
	}
	else
	{
		/*command does not cont a '/' so search for its PATH*/
		char *path_env = getenv("PATH");
		if (path_env != NULL)
		{
			char *path_token = strtok(path_env, ":");

			while (path_token != NULL)
			{
				snprintf(full_command, sizeof(full_command), "%s/%s", path_token, args[0]);

				if (access(full_command, X_OK) == 0)
				{
					found = 1;
					break;
				}
				 path_token = strtok(NULL, ":");
			}

		}
	}

	/*if the command exists, execute it */

	if (found)
	{
		pid_t child_pid = fork();

		if (child_pid == -1)
		{
			perror("Fork failed");
			exit(1);
		}
		else if (child_pid == 0)
		{
			/* This is the child process */
			 
			execv(full_command, args);
			 
			 /*if execv returns there is error*/

			perror("Command execution failed");
			exit(1);
		}
		else
		{
			/*This is the parent process */

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
			else if (WIFSIGNALED(status))
			{
				int signal_num = WTERMSIG(status);
				fprintf(stderr, "%s: %s: Terminated by signal %d\n", shell_name, args[0], signal_num);

			}
			else
			{
				 fprintf(stderr,"%s: %s: Command did not exit normally\n", shell_name, args[0]);
			}
		}
	}
	else
	{
		/*print error message to stedrr */

		fprintf(stderr, "%s: %s: Command not found\n", shell_name, args[0]);
	}
}

