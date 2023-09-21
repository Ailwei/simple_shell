#include "shell.h"

/**
 * token_length - Calculates the length of a token.
 * @str: The string to be searched.
 * @delim: The delimiter character.
 *
 * Return: The length of the token.
 */
int token_length(char *str, char *delim)
{
    int len = 0;

    while (*str && *str != *delim)
    {
        len++;
        str++;
    }

    return (len);
}

/**
 * count_tokens - Counts the number of delimited words within a string.
 * @str: The string to be searched.
 * @delim: The delimiter character.
 *
 * Return: The number of tokens contained within str.
 */
int count_tokens(char *str, char *delim)
{
    int tokens = 0;

    while (*str)
    {
        while (*str == *delim)
            str++;
        if (*str)
        {
            tokens++;
            str += token_length(str, delim);
        }
    }

    return (tokens);
}

/**
 * _strtok - Tokenizes a string.
 * @line: The string.
 * @delim: The delimiter character to tokenize the string by.
 *
 * Return: A pointer to an array containing the tokenized words.
 */
char **_strtok(char *line, char *delim)
{
    char **tokens;
    int index = 0, t, letters, l, tokens_count;

    tokens_count = count_tokens(line, delim);
    if (tokens_count == 0)
        return (NULL);

    tokens = malloc(sizeof(char *) * (tokens_count + 1));
    if (!tokens)
        return (NULL);

    for (t = 0; t < tokens_count; t++)
    {
        while (*line == *delim)
            line++;

        letters = token_length(line, delim);

        tokens[t] = malloc(sizeof(char) * (letters + 1));
        if (!tokens[t])
        {
            for (index = 0; index < t; index++)
                free(tokens[index]);
            free(tokens);
            return (NULL);
        }

        for (l = 0; l < letters; l++)
        {
            tokens[t][l] = *line;
            line++;
        }

        tokens[t][l] = '\0';
    }

    tokens[tokens_count] = NULL;

    return (tokens);
}

