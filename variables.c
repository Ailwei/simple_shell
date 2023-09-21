#include "shell.h"

/**
 * isChainDelimiter - test if the current char in buffer is a chain delimiter
 * @shellInfo: the parameter struct
 * @buf: the char buffer
 * @p: address of the current position in buf
 *
 * Return: 1 if chain delimiter, 0 otherwise
 */
int isChainDelimiter(ShellInfo *info, char *buf, size_t *p)
{
    size_t j = *p;

    if (buf[j] == '|' && buf[j + 1] == '|')
    {
        buf[j] = 0;
        j++;
        ShellInfo->cmd_buf_type = CMD_OR;
    }
    else if (buf[j] == '&' && buf[j + 1] == '&')
    {
        buf[j] = 0;
        j++;
        shellInfo->cmd_buf_type = CMD_AND;
    }
    else if (buf[j] == ';') /* found the end of this command */
    {
        buf[j] = 0; /* replace semicolon with null */
        shellInfo->cmd_buf_type = CMD_CHAIN;
    }
    else
        return (0);
    *p = j;
    return (1);
}

/**
 * checkChain - checks if we should continue chaining based on the last status
 * @shellInfo: the parameter struct
 * @buf: the char buffer
 * @p: address of the current position in buf
 * @i: starting position in buf
 * @len: length of buf
 *
 * Return: Void
 */
void checkChain(ShellInfo *info, char *buf, size_t *p, size_t i, size_t len)
{
    size_t j = *p;

    if (shellInfo->cmd_buf_type == CMD_AND)
    {
        if (shellInfo->status)
        {
            buf[i] = 0;
            j = len;
        }
    }
    if (shellInfo->cmd_buf_type == CMD_OR)
    {
        if (!shellInfo->status)
        {
            buf[i] = 0;
            j = len;
        }
    }

    *p = j;
}

/**
 * replaceAliases - replaces aliases in the tokenized string
 * @shellInfo: the parameter struct
 *
 * Return: 1 if replaced, 0 otherwise
 */
int replaceAliases(ShellInfo *info)
{
    int i;
    list_t *node;
    char *p;

    for (i = 0; i < 10; i++)
    {
        node = nodeStartsWith(shellInfo->alias, shellInfo->argv[0], '=');
        if (!node)
            return (0);
        free(shellInfo->argv[0]);
        p = _strchr(node->str, '=');
        if (!p)
            return (0);
        p = _strdup(p + 1);
        if (!p)
            return (0);
        shellInfo->argv[0] = p;
    }
    return (1);
}

/**
 * replaceVariables - replaces variables in the tokenized string
 * @shellInfo: the parameter struct
 *
 * Return: 1 if replaced, 0 otherwise
 */
int replaceVariables(ShellInfo *info)
{
    int i = 0;
    list_t *node;

    for (i = 0; shellInfo->argv[i]; i++)
    {
        if (shellInfo->argv[i][0] != '$' || !shellInfo->argv[i][1])
            continue;

        if (!_strcmp(shellInfo->argv[i], "$?"))
        {
            replaceString(&(shellInfo->argv[i]), _strdup(convertNumber(shellInfo->status, 10, 0)));
            continue;
        }
        if (!_strcmp(shellInfo->argv[i], "$$"))
        {
            replaceString(&(shellInfo->argv[i]), _strdup(convertNumber(getpid(), 10, 0)));
            continue;
        }
        node = nodeStartsWith(shellInfo->env, &shellInfo->argv[i][1], '=');
        if (node)
        {
            replaceString(&(shellInfo->argv[i]), _strdup(_strchr(node->str, '=') + 1));
            continue;
        }
        replaceString(&shellInfo->argv[i], _strdup(""));
    }
    return (0);
}

/**
 * replaceString - replaces a string
 * @old: address of the old string
 * @new: new string
 *
 * Return: 1 if replaced, 0 otherwise
 */
int replaceString(char **old, char *new)
{
    free(*old);
    *old = new;
    return (1);
}

