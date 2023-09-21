#include "shell.h"
#include <unistd.h>
/**
 * checkInteractiveMode - returns true if shell is in interactive mode
 * @shellInfo: struct containing shell information
 *
 * Return: 1 if in interactive mode, 0 otherwise
 */
int checkInteractiveMode(ShellInfo *shellInfo)
{
    return (isatty(STDIN_FILENO) && shellInfo->readfd <= 2);
}

/**
 * isDelimiter - checks if a character is a delimiter
 * @character: the character to check
 * @delimiters: the delimiter string
 * Return: 1 if true, 0 if false
 */
int isDelimiter(char character, char *delimiters)
{
    while (*delimiters)
    {
        if (*delimiters++ == character)
        {
            return 1;
        }
    }
    return 0;
}

/**
 * isAlphabetic - checks if a character is alphabetic
 * @character: The character to check
 * Return: 1 if character is alphabetic, 0 otherwise
 */
int isAlphabetic(int character)
{
    if ((character >= 'a' && character <= 'z') || (character >= 'A' && character <= 'Z'))
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

/**
 * stringToInteger - converts a string to an integer
 * @str: the string to be converted
 * Return: 0 if no numbers in string, converted number otherwise
 */
int stringToInteger(char *str)
{
    int index, sign = 1, flag = 0, result = 0;
    unsigned int number = 0;

    for (index = 0; str[index] != '\0' && flag != 2; index++)
    {
        if (str[index] == '-')
        {
            sign *= -1;
        }

        if (str[index] >= '0' && str[index] <= '9')
        {
            flag = 1;
            number *= 10;
            number += (str[index] - '0');
        }
        else if (flag == 1)
        {
            flag = 2;
        }
    }

    if (sign == -1)
    {
        result = -number;
    }
    else
    {
        result = number;
    }

    return result;
}


