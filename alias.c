#include "shell.h"

/* Define aliases list variable here */
struct Alias* alias_list = NULL;



void add_alias(const char* name, const char* value)
{
    struct Alias* alias = (struct Alias*)malloc(sizeof(struct Alias));
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

void alias_builtin(char** args)
{
	char* name;
	char* value;
	 char* token;
    int i;

    if (args == NULL)
    {
        return;
    }
    /* If no arguments are provided, print all aliases */
    if (args[1] == NULL)
    {
        print_aliases(NULL);
        return;
    }

    /* Iterate through the arguments to handle the aliases */
    for (i = 1; args[i] != NULL; i++)
    {
        token = strtok(args[i], "=");
        if (token == NULL)
        {
            /* Invalid argument */
            continue;
        }
        name = token;
        value = strtok(NULL, "=");

        if (value == NULL)
        {
            /* No value provided; treat it as printing an alias */
            print_aliases(name);
        }
        else
        {
            /* Define or redefine an alias */
            add_alias(name, value);
        }
    }
}

