#include "shell.h"

/**
 * _strlen - Returns the length of a string.
 * @s: A pointer to the character string.
 *
 * Return: The length of the character string.
 */
int _strlen(const char *s)
{
    int length = 0;

    if (!s)
        return (length);
    for (length = 0; s[length]; length++)
        ;
    return (length);
}

/**
 * _strcpy - Copies the string pointed to by src, including the
 *           terminating null byte, to the buffer pointed by dest.
 * @dest: Pointer to the destination of the copied string.
 * @src: Pointer to the source of the source string.
 *
 * Return: Pointer to dest.
 */
char *_strcpy(char *dest, const char *src)
{
    size_t i;

    for (i = 0; src[i] != '\0'; i++)
        dest[i] = src[i];
    dest[i] = '\0';
    return (dest);
}

/**
 * _strcat - Concatenates two strings.
 * @dest: Pointer to the destination string.
 * @src: Pointer to the source string.
 *
 * Return: Pointer to the destination string.
 */
char *_strcat(char *dest, const char *src)
{
    char *dest_temp;
    const char *src_temp;

    dest_temp = dest;
    src_temp = src;

    while (*dest_temp != '\0')
        dest_temp++;

    while (*src_temp != '\0')
        *dest_temp++ = *src_temp++;
    *dest_temp = '\0';
    return (dest);
}

/**
 * _strncat - Concatenates two strings where n number
 *            of bytes are copied from source.
 * @dest: Pointer to destination string.
 * @src: Pointer to source string.
 * @n: n bytes to copy from src.
 *
 * Return: Pointer to destination string.
 */
char *_strncat(char *dest, const char *src, size_t n)
{
    size_t dest_len = _strlen(dest);
    size_t i;

    for (i = 0; i < n && src[i] != '\0'; i++)
        dest[dest_len + i] = src[i];
    dest[dest_len + i] = '\0';

    return (dest);
}

