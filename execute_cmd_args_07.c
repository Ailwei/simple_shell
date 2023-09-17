#include "shell.h"

/**
 * Execute a command with arguments.
 * @param command The command to execute.
 * @param arguments The arguments for the command.
 */

void execute_cmd_args(const char *command, const char *arguments)
{
	 pid_t child_pid = fork();

	 if (child_pid == -1)
	 {
		 perror("fork");
		 exit(1);
	 }
	 if (child_pid == 0)
	 {
		 /*this child is executed by the child process*/

		  execlp(command, command, arguments, NULL);

		 /*if excelp returns, error */

		 perror("execlp");
		 exit(1);

	 }
	 else
	 {
		 /* this code is executed by the the parents */
		  int status;
		  waitpid(child_pid, &status, 0);
		  if (WIFEXITED(status))
		  {
			  printf("Child exited with status %d\n", WEXITSTATUS(status));

		  }
	 }
}
