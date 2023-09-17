#include "shell.h"

int main(void)
{
	 char *shell_name = "hsh";
char *line;	
	 size_t command_length;
	char command[MAX_COMMAND_LENGTH];
	/*get path env */

	char *path_env = getenv("PATH");
    if (path_env == NULL)
    {
        perror("Unable to get PATH");
        return 1;
    }

	while (1)
	{
		/*Display the prompt */
		printf("%s> ", shell_name);
		fflush(stdout);

		/*read the command line using custom_getline */
		line = custom_getline();



		/*read Read a command line */

		if (fgets(command, sizeof(command), stdin) == NULL)
		{
			/* Handl Ctrl + D */
			printf("\nExiting %s.\n", shell_name);
			break;
		}
		/*Remove the trailing newline character */
		command_length = strlen(command);
		if (command_length > 0 && command[command_length-1] == '\n')
		{
			command[command_length -1] ='\0';
		}
		/*Execute the command */

		if (command_length > 0)
		{
			if (strcmp(command, "exit") == 0)
			{
				/* handle the "exit" builtin command */
				exit_shell(shell_name);
				
			}
			else if (strncmp(command, "exit", 5) == 0)
			{
				/*handle exit with status*/
				const char *status = command + 5;
				handle_exit(status);
			}
			else
			{
				exit_shell(shell_name);
			}

			}
			else if (strcmp(command, "env") == 0)
			{
				/*handle the env builtin cmd*/
				env_builtin(environ);
			}
			else
			{
				
			if (strstr(command, " ") != NULL)
			{
				/*command has path ariguments use execute_command_arguments*/
				
				                       execute_command_with_path(command, path_env, shell_name);
				execute_command_with_args(command);
			}
			else
			{
				/*command has  arguments */
				execute_command_with_args(command);
			} 
			if(command_length > 0)
			{
				char *space_position = strchr(command, ' ');
				const char *arguments = space_position + 1;
				execute_cmd_args(command,arguments);
			}
			
			/*handle no arguments*/
			execute_command(command);

			}
			/*handle_cmd_with args */

			/*exit shell*/
		exit_shell(shell_name);
		}
		free(line);
		
	}
}
}
}

return (0);
}
