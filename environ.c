#include "shell.h"


/**
 * custom_print_environment - Prints the current environment
 * @info: Structure containing potential arguments. Used to maintain
 *          constant function prototype.
 * Return: Always 0
 */
int custom_print_environment(info_t *info)
{
	custom_print_list_strings(info->environment);
	return (0);
}

/**
 * custom_get_environment_variable - Gets the value of an environment variable
 * @info: Structure containing potential arguments. Used to maintain
 * @name: Environment variable name
 *
 * Return: The value of the environment variable
 */
char *custom_get_environment_variable(info_t *info, const char *name)
{
	list_t *node = info->environment;
	char *p;

	while (node)
	{
		p = custom_starts_with(node->str, name);
		if (p && *p)
			return (p);
		node = node->next;
	}
	return (NULL);
}

/**
 * custom_set_environment_variable - Initializes a new environment variable
 *                                  or modifies an existing one
 * @info: Structure containing potential arguments. Used to maintain
 *        constant function prototype.
 * Return: Always 0
 */
int custom_set_environment_variable(info_t *info)
{
	if (info->argc != 3)
	{
		custom_puts_error("Incorrect number of arguments\n");
		return (1);
	}
	if (custom_setenv(info, info->argv[1], info->argv[2]))
		return (0);
	return (1);
}

/**
 * custom_unset_environment_variable - Removes an environment variable
 * @info: Structure containing potential arguments. Used to maintain
 *        constant function prototype.
 * Return: Always 0
 */
int custom_unset_environment_variable(info_t *info)
{
	int i;

	if (info->argc == 1)
	{
		custom_puts_error("Too few arguments.\n");
		return (1);
	}
	for (i = 1; i <= info->argc; i++)
		custom_unsetenv(info, info->argv[i]);

	return (0);
}

/**
 * custom_populate_environment_list - Populates the environment linked list
 * @info: Structure containing potential arguments. Used to maintain
 *          constant function prototype.
 * Return: Always 0
 */
int custom_populate_environment_list(info_t *info)
{
	list_t *node = NULL;
	size_t i;

	for (i = 0; environ[i]; i++)
		custom_add_node_end(&node, environ[i], 0);
	info->environment = node;
	return (0);
}

