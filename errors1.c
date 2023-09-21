#include "shell.h"

/**
 * custom_puts_error - Prints an error string to stderr
 * @error_string: The error string to be printed
 *
 * Return: Nothing
 */
void custom_puts_error(char *error_string)
{
	int i = 0;

	if (!error_string)
		return;
	while (error_string[i] != '\0')
	{
		custom_putchar_error(error_string[i]);
		i++;
	}
}

/**
 * custom_putchar_error - Writes the character c to stderr
 * @c: The character to print
 *
 * Return: On success 1.
 * On error, -1 is returned, and errno is set appropriately.
 */
int custom_putchar_error(char c)
{
	static int i;
	static char buf[WRITE_BUF_SIZE];

	if (c == CUSTOM_BUF_FLUSH || i >= CUSTOM_WRITE_BUF_SIZE)
	{
		write(STDERR_FILENO, buf, i);
		i = 0;
	}
	if (c != CUSTOM_BUF_FLUSH)
		buf[i++] = c;
	return (1);
}

/**
 * custom_putchar_fd - Writes the character c to the given file descriptor
 * @c: The character to print
 * @fd: The file descriptor to write to
 *
 * Return: On success 1.
 * On error, -1 is returned, and errno is set appropriately.
 */
int custom_putchar_fd(char c, int fd)
{
	static int i;
	static char buf[WRITE_BUF_SIZE];

	if (c == CUSTOM_BUF_FLUSH || i >= CUSTOM_WRITE_BUF_SIZE)
	{
		write(fd, buf, i);
		i = 0;
	}
	if (c != CUSTOM_BUF_FLUSH)
		buf[i++] = c;
	return (1);
}

/**
 * custom_puts_fd - Prints an input string to the given file descriptor
 * @str: The string to be printed
 * @fd: The file descriptor to write to
 *
 * Return: The number of characters written
 */
int custom_puts_fd(char *str, int fd)
{
	int i = 0;

	if (!str)
		return (0);
	while (*str)
	{
		i += custom_putchar_fd(*str++, fd);
	}
	return (i);
}

