#include "shell.h"

/**
 * custom_atoi - Converts a string to an integer
 * @str: The string to be converted
 *
 * Return: The converted number if successful, or -1 on error
 */
int custom_atoi(char *str)
{
	int i = 0;
	unsigned long int result = 0;

	if (*str == '+')
		str++;  /* TODO: why does this make main return 255? */
	for (i = 0;  str[i] != '\0'; i++)
	{
		if (str[i] >= '0' && str[i] <= '9')
		{
			result *= 10;
			result += (str[i] - '0');
			if (result > INT_MAX)
				return (-1);
		}
		else
			return (-1);
	}
	return (result);
}

/**
 * print_custom_error - Prints an error message
 * @info: The parameter & return info struct
 * @error_type: String containing the specified error type
 */
void print_custom_error(info_t *info, char *error_type)
{
	_eputs(info->fname);
	_eputs(": ");
	print_custom_d(info->line_count, STDERR_FILENO);
	_eputs(": ");
	_eputs(info->argv[0]);
	_eputs(": ");
	_eputs(error_type);
}

/**
 * print_custom_d - Prints a decimal (integer) number (base 10)
 * @input: The input number
 * @fd: The file descriptor to write to
 *
 * Return: The number of characters printed
 */
int print_custom_d(int input, int fd)
{
	int (*custom_putchar)(char) = _putchar;
	int i, count = 0;
	unsigned int abs_value, current;

	if (fd == STDERR_FILENO)
		custom_putchar = _eputchar;
	if (input < 0)
	{
		abs_value = -input;
		custom_putchar('-');
		count++;
	}
	else
		abs_value = input;
	current = abs_value;
	for (i = 1000000000; i > 1; i /= 10)
	{
		if (abs_value / i)
		{
			custom_putchar('0' + current / i);
			count++;
		}
		current %= i;
	}
	custom_putchar('0' + current);
	count++;

	return (count);
}

/**
 * custom_convert_number - Converter function, a clone of itoa
 * @num: The number to convert
 * @base: The base for conversion
 * @flags: Argument flags
 *
 * Return: A string representing the converted number
 */
char *custom_convert_number(long int num, int base, int flags)
{
	static char *array;
	static char buffer[50];
	char sign = 0;
	char *ptr;
	unsigned long n = num;

	if (!(flags & CONVERT_UNSIGNED) && num < 0)
	{
		n = -num;
		sign = '-';
	}
	array = flags & CONVERT_LOWERCASE ? "0123456789abcdef" : "0123456789ABCDEF";
	ptr = &buffer[49];
	*ptr = '\0';

	do	{
		*--ptr = array[n % base];
		n /= base;
	} while (n != 0);

	if (sign)
		*--ptr = sign;
	return (ptr);
}

/**
 * remove_custom_comments - Replaces the first instance of '#' with '\0'
 * @buf: Address of the string to modify
 */
void remove_custom_comments(char *buf)
{
	int i;

	for (i = 0; buf[i] != '\0'; i++)
		if (buf[i] == '#' && (!i || buf[i - 1] == ' '))
		{
			buf[i] = '\0';
			break;
		}
}

