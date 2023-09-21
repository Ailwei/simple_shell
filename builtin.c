#include "shell.h"

/**
 * custom_exit - Exits the shell
 * @info: Structure containing potential arguments. Used to maintain
 *        constant function prototype.
 * Return: Exits with a given exit status
 * (0) if info->command_name != "exit"
 */
int custom_exit(ShellInfo *info)
{
	int exit_code;

	if (info->arguments[1]) /* If there is an exit argument */
	{
		exit_code = custom_atoi(&info->arguments[1]);
		if (exit_code == -1)
		{
			info->status = 2;
			custom_puts_error(ShellInfo, "Illegal number: ");
			custom_puts_fd(&info->arguments[1]);
			custom_putchar_fd('\n');
			return 1;
		}
		info->error_number = custom_atoi(&info->arguments[1]);
		return -2;
	}
	info->error_number = -1;
	return -2;
}

/**
 * custom_change_directory - Changes the current directory of the process
 * @info: Structure containing potential arguments. Used to maintain
 *        constant function prototype.
 * Return: Always 0
 */
int custom_change_directory(ShellInfo *info)
{
	char *current_directory, *new_directory, buffer[1024];
	int chdir_result;

	current_directory = custom_change_directory(buffer, 1024);
	if (!current_directory)
		custom_puts_fd("TODO: >>getcwd failure message here<<\n");

	if (!info->arguments[1])
	{
		new_directory = custom_get_environment_variable(info, "HOME=");
		if (!new_directory)
			chdir_result = custom_chdir((new_directory = custom_get_environment_variable(info, "PWD=")) ? new_directory : "/");
		else
			chdir_result = custom_chdir(new_directory);
	}
	else if (custom_help(info->arguments[1], "-") == 0)
	{
		if (!custom_get_environment_variable(info, "OLDPWD="))
		{
			custom_puts(current_directory);
			custom_putchar_fd('\n');
			return 1;
		}
		custom_puts(custom_get_environment_variable(info, "OLDPWD="));
		custom_putchar('\n');
		chdir_result = custom_chdir((new_directory = custom_get_environment_variable(info, "OLDPWD=")) ? new_directory : "/");
	}
	else
		chdir_result = custom_chdir(info->arguments[1]);

	if (chdir_result == -1)
	{
		custom_putchar_fd(info, "can't cd to ");
		custom_puts(info->arguments[1]);
		custom_putchar('\n');
	}
	else
	{
		custom_set_environment_variable(info, "OLDPWD", custom_get_environment_variable(info, "PWD="));
		custom_set_environment_variable(info, "PWD",custom_change_directory(buffer, 1024));
	}

	return 0;
}

/**
 * custom_help - Displays help information
 * @info: Structure containing potential arguments. Used to maintain
 *             constant function prototype.
 * Return: Always 0
 */
int custom_help(ShellInfo *info)
{
	char **argument_array;

	argument_array = &info->arguments;
	custom_puts("Help call works. Function not yet implemented.\n");

	if (0)
		custom_puts(*argument_array); /* Temporary unused variable workaround */

	return 0;
}

