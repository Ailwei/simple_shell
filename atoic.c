#include "shell.h"

/**
 * is_interactive - Checks if the shell is in interactive mode
 * @info: Structure containing potential arguments.
 *
 * Return: 1 if interactive mode, 0 otherwise
 */
int is_interactive(info_t *info)
{
    return (isatty(STDIN_FILENO) && info->read_file_descriptor <= 2);
}

/**
 * is_delimiter - Checks if a character is a delimiter
 * @c: The character to check
 * @delimiter_str: The delimiter string
 *
 * Return: 1 if true, 0 if false
 */
int is_delimiter(char c, char *delimiter_str)
{
    while (*delimiter_str)
    {
        if (*delimiter_str++ == c)
        {
            return 1;
        }
    }
    return 0;
}

/**
 * custom_is_alpha - Checks if a character is alphabetic
 * @c: The character to check
 *
 * Return: 1 if c is alphabetic, 0 otherwise
 */
int custom_is_alpha(int c)
{
    if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'))
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

/**
 * custom_atoi - Converts a string to an integer
 * @s: The string to be converted
 *
 * Return: 0 if no numbers in string, converted number otherwise
 */
int custom_atoi(char *s)
{
    int i, sign = 1, flag = 0, output;
    unsigned int result = 0;

    for (i = 0; s[i] != '\0' && flag != 2; i++)
    {
        if (s[i] == '-')
        {
            sign *= -1;
        }

        if (s[i] >= '0' && s[i] <= '9')
        {
            flag = 1;
            result *= 10;
            result += (s[i] - '0');
        }
        else if (flag == 1)
        {
            flag = 2;
        }
    }

    if (sign == -1)
    {
        output = -result;
    }
    else
    {
        output = result;
    }

    return output;
}

