#include "shell.h"

/*function to replace variables like$?$$ in a command line*/
void replace_variables(char *command, int last_exit_status)
{
	char *variable;

	/*replace $?, if found */

	while ((variable  = strstr(command, "$?")) != NULL)
	{
		char replacement[32];
		snprintf(replacement, sizeof(replacement),  "%d", last_exit_status);
		replace_in_string(variable, 2, replacement);
	}
	/* replace $$, if found */

	while ((variable = strstr(command, "$$")) != NULL)
	{
		char replacement[32];
		snprintf(replacement, sizeof(replacement), "%d", getpid());
		replace_in_string(variable,2, replacement);
	}

}
/* helper function to replace a substring withing a string */

void replace_in_string(char *str, int offset, const char *replacement)
{ 
	int length = strlen(replacement);
    memmove(str + length, str + offset, strlen(str + offset) + 1);
    memcpy(str, replacement, length);
	
}
