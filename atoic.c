
#include "shell.h"

/**
 * is_interactive - return true if shell is interactive mode
 * @info: struct addresses
 *
 * Return: 1 if interactive mode, 0 otherwise
 */
int is_interactive(info_t *info)
{
	return (isatty(STDIN_FILENO) && info->readfd <= 2);
}

/**
 * check_delimiters - checks if character is a delimeter
 * @character: the char to check
 * @delim: the delimeter string
 * Return: 1 if true, 0 if false
 */
int check_delimiters(char character, char *delim)
{
	while (*delim)
		if (*delim++ == character)
			return (1);
	return (0);
}

/**
 * check_alpha - check for alphaetic char
 * @character: The char to input
 * Return: 1 if c is alphabetic, 0 otherwise
 */

int check_alpha(int character)
{
	if ((character >= 'a' && character <= 'z') || (character >= 'A' && character <= 'Z'))
		return (1);
	else
		return (0);
}

/**
 * convert_str_int - convert a string to an integer
 * @str: the string to be converted
 * Return: 0 if no numbers in string, converted number otherwise
 */

int convert_str_int(char *str)
{
	int j, sign = 1, flag = 0, output;
	unsigned int result = 0;

	for (j = 0; str[j] != '\0' && flag != 2; j++)
	{
		if (str[j] == '-')
			sign *= -1;

		if (str[j] >= '0' && str[j] <= '9')
		{
			flag = 1;
			result *= 10;
			result += (str[j] - '0');
		}
		else if (flag == 1)
			flag = 2;
	}

	if (sign == -1)
		output = -result;
	else
		output = result;

	return (output);
}

