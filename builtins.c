#include "shell.h"


/**
 * custom_display_history - Displays the history list, one command per line,
 *                         preceded with line numbers, starting at 0.
 * @info: Structure containing potential arguments. Used to maintain
 *        constant function prototype.
 * Return: Always 0
 */
int custom_display_history(info_t *info)
{
	custom_print_list(info->command_history);
	return (0);
}

/**
 * custom_unset_alias - Unsets an alias string
 * @info: Parameter struct
 * @str: The string alias
 *
 * Return: Always 0 on success, 1 on error
 */
int custom_unset_alias(info_t *info, char *str)
{
	char *p, c;
	int ret;

	p = custom_strchr(str, '=');
	if (!p)
		return (1);
	c = *p;
	*p = 0;
	ret = custom_delete_node_at_index(&(info->aliases),
	                                   custom_get_node_index(info->aliases, custom_node_starts_with(info->aliases, str, -1)));
	*p = c;
	return (ret);
}

/**
 * custom_set_alias - Sets an alias string
 * @info: Parameter struct
 * @str: The string alias
 *
 * Return: Always 0 on success, 1 on error
 */
int custom_set_alias(info_t *info, char *str)
{
	char *p;

	p = custom_strchr(str, '=');
	if (!p)
		return (1);
	if (!*++p)
		return (custom_unset_alias(info, str));

	custom_unset_alias(info, str);
	return (custom_add_node_end(&(info->aliases), str, 0) == NULL);
}

/**
 * custom_print_alias - Prints an alias string
 * @node: The alias node
 *
 * Return: Always 0 on success, 1 on error
 */
int custom_print_alias(list_t *node)
{
	char *p = NULL, *a = NULL;

	if (node)
	{
		p = custom_strchr(node->str, '=');
		for (a = node->str; a <= p; a++)
			custom_putchar(*a);
		custom_putchar('\'');
		custom_puts(p + 1);
		custom_puts("'\n");
		return (0);
	}
	return (1);
}

/**
 * custom_alias - Mimics the alias builtin (man alias)
 * @info: Structure containing potential arguments. Used to maintain
 *          constant function prototype.
 * Return: Always 0
 */
int custom_alias(info_t *info)
{
	int i = 0;
	char *p = NULL;
	list_t *node = NULL;

	if (info->argc == 1)
	{
		node = info->aliases;
		while (node)
		{
			custom_print_alias(node);
			node = node->next;
		}
		return (0);
	}
	for (i = 1; info->argv[i]; i++)
	{
		p = custom_strchr(info->argv[i], '=');
		if (p)
			custom_set_alias(info, info->argv[i]);
		else
			custom_print_alias(custom_node_starts_with(info->aliases, info->argv[i], '='));
	}

	return (0);
}

