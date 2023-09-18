#include "shell.h"

/*define aliases list variable here */

struct Alias* alias_list = NULL;


#define MAX_ALIAS_NAME 100
#define MAX_ALIAS_VALUE 100

void add_alias(const char* name, const char* value)
{

	struct Alias* alias = (struct Ailas*)malloc(sizeof(struct Alias));
	if (alias == NULL)
	{
		perror("Failed to allocate memory for alias");
		return;
	}
	strncpy(alias->name, name, MAX_ALIAS_NAME);
	strncpy(alias->value, value, MAX_ALIAS_VALUE);
	alias->next = alias_list;
	alias_list = alias;
}
/*funct to print aliases*/

void print_aliases(const char* alias_name)
{
	 struct Alias* current = alias_list;

	 while (current != NULL)
	 {
		 if (alias_name == NULL || strcmp(current->name, alias_name) == 0)
		 {
			 printf("%s='%s'\n", current->name, current->value);
		 }
		 current = current->next;
	 }
}
/*funct to handle the aliases builtin command */

void alias_builtin(char** args)
{
	int i;

	if (args == NULL)
	{
		return;
	}
	/* if no arguments are provided, print all aliases */
	if (args[1] == NULL)
	{
		print_aliases(NULL);
		return;
	}
	/*iterate through the arguments to handle the aliases */
	for (i = 1; args[i] != NULL; i++)
	{
		char* token = strtok(args[i], "=");
		if (token == NULL)
		{
			/* invalid argument */
			continue;
		}
		char* name = token;
        char* value = strtok(NULL, "=");

	if (value == NULL)
	{
		/*No value provided treated it ias printing an alias */
		print_aliases(name);
	}
	else
	{
		/*define or redefine an alias*/
		add_alias(name, value);
	}
	}
}
