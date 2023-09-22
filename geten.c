#include "shell.h"

/**
 * fetch_environ - return the string array copy of the environ
 * @info: Structure containing potential argument. Used to maintain
 *          constant function prototype.
 * Return: Always 0
 */
char **fetch_environ(info_t *info)
{
	if (!info->environ || info->env_changed)
	{
		info->environ = list_to_str(info->env);
		info->env_changed = 0;
	}

	return (info->environ);
}

/**
 * unset_env - Remove an environ variable
 * @info: Structure that  contains potential arguments. Used to maintain
 *        constant function prototype.
 *  Return: 1 on delete, 0 otherwise
 * @vars: the string env vars property
 */
int unset_env(info_t *info, char *vars)
{
	list_t *node = info->env;
	size_t i = 0;
	char *p;

	if (!node || !vars)
		return (0);

	while (node)
	{
		p = begin_with(node->str, vars);
		if (p && *p == '=')
		{
			info->env_changed = remove_node_at_index(&(info->env), i);
			i = 0;
			node = info->env;
			continue;
		}
		node = node->next;
		i++;
	}
	return (info->env_changed);
}

/**
 * set_env - Initialise a new environment vars,
 *             or modify an existing one
 * @info: Structure containing potential argument. Used to maintain
 *        constant function prototype.
 * @vars: the string env var property
 * @value: the string env var value
 *  Return: Always 0
 */
int set_env(info_t *info, char *vars, char *value)
{
	char *buf = NULL;
	list_t *node;
	char *p;

	if (!vars || !value)
		return (0);

	buf = malloc(string_length(vars) + string_length(value) + 2);
	if (!buf)
		return (1);
	string_copy(buf, vars);
	string_concatenate(buf, "=");
	string_concatenate(buf, value);
	node = info->env;
	while (node)
	{
		p = begin_with(node->str, vars);
		if (p && *p == '=')
		{
			free(node->str);
			node->str = buf;
			info->env_changed = 1;
			return (0);
		}
		node = node->next;
	}
	add_node_end(&(info->env), buf, 0);
	free(buf);
	info->env_changed = 1;
	return (0);
}

