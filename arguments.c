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
			if (arg_count >= MAX_ARGS)
			{
				fprintf(stderr, "Too many arguments\n");
				exit(EXIT_FAILURE);
			}
			args[arg_count++] = NULL;
			if (execvp(args[0], args) == -1)
			{
				 /*if execvp retuens there was an error */
                        perror("Command execution failed");
                        exit(EXIT_FAILURE);

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
				 fprintf(stderr, " Command exited with status %d\n", exit_status);
			 }
			 else if (WIFSIGNALED(status))
			 {
				 int term_signal = WTERMSIG(status);
            fprintf(stderr, "Command terminated by signal %d\n", term_signal);
			 }
			 else
		 {
			fprintf(stderr, "Command did not exit normally\n");
		 }
	}
}
}
