#include "shell.h"


int handle_cd(const char *directory)
{
	char *prev_directory;
	char *current_directory;

	if (directory == NULL || directory[0] == '\0')
	{
		/*If no argument is given, change to the home directory */
		directory = getenv("HOME");
		if (directory == NULL)
		{
			fprintf(stderr, "cd: HOME not set\n");
			return (1);

		}
	}
	else if (strcmp(directory, "_") == 0)
	{
		/* Handle "cd -" by changing to the previous directory */
		directory = getenv("OLDPWD");

		if (directory == NULL)
		{
			fprintf(stderr, "cd: OLDPWD not set\n");
			return (1);
		}
	}
	/*save the current working directory */
	prev_directory = getcwd(NULL, 0);

	if (prev_directory == NULL)
	{
		perror("getcwd");
		return (1);
	}
	/*change the directory */
	 if (chdir(directory) != 0)
	 {
		 perror("chdir");
		 free(prev_directory);
		 return (1);
	 }
	 else
	 {
		 /*update the PWD nad OLDPWD env variables */

		 if (setenv("OLDPWD", prev_directory, 1) != 0)
		 {
			 perror("setenv");
		 }
		 current_directory = getcwd(NULL, 0);

		 if (current_directory == NULL)
		 {
			 perror("getcwd");
		 }
		 else if (setenv("PWD", current_directory, 1) != 0)
		 {
			 perror("setenv");
		 }
		   free(prev_directory);
        return 0;
	 }
}
