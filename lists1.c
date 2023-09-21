#include "shell.h"

/**
 * custom_list_length - determines the length of a custom linked list
 * @head: pointer to the first node
 *
 * Return: size of the list
 */
size_t custom_list_length(const CustomList *head)
{
    size_t count = 0;

    while (head)
    {
        head = head->next;
        count++;
    }
    return count;
}

/**
 * custom_list_to_strings - returns an array of strings from a custom linked list
 * @head: pointer to the first node
 *
 * Return: array of strings
 */
char **custom_list_to_strings(CustomList *head)
{
    CustomList *node = head;
    size_t size = custom_list_length(head);
    char **strings;
    char *string;

    if (!head || !size)
        return NULL;

    strings = malloc(sizeof(char *) * (size + 1));
    if (!strings)
        return NULL;

    for (size_t i = 0; node; node = node->next, i++)
    {
        string = malloc(_custom_strlen(node->data) + 1);
        if (!string)
        {
            for (size_t j = 0; j < i; j++)
                free(strings[j]);
            free(strings);
            return NULL;
        }

        string = _custom_strcpy(string, node->data);
        strings[i] = string;
    }
    strings[size] = NULL;
    return strings;
}

/**
 * custom_list_print - prints all elements of a custom linked list
 * @head: pointer to the first node
 *
 * Return: size of the list
 */
size_t custom_list_print(const CustomList *head)
{
    size_t count = 0;

    while (head)
    {
        _custom_puts(convert_number(head->number, 10, 0));
        _custom_putchar(':');
        _custom_putchar(' ');
        _custom_puts(head->data ? head->data : "(nil)");
        _custom_puts("\n");
        head = head->next;
        count++;
    }
    return count;
}

/**
 * custom_list_starts_with - returns the node whose string starts with a prefix
 * @node: pointer to the custom list head
 * @prefix: string to match
 * @c: the next character after the prefix to match
 *
 * Return: matching node or NULL
 */
CustomList *custom_list_starts_with(CustomList *node, char *prefix, char c)
{
    char *p = NULL;

    while (node)
    {
        p = custom_starts_with(node->data, prefix);
        if (p && ((c == -1) || (*p == c)))
            return node;
        node = node->next;
    }
    return NULL;
}

/**
 * custom_get_node_index - gets the index of a node in a custom list
 * @head: pointer to the custom list head
 * @node: pointer to the node
 *
 * Return: index of the node or -1
 */
ssize_t custom_get_node_index(CustomList *head, CustomList *node)
{
    size_t index = 0;

    while (head)
    {
        if (head == node)
            return index;
        head = head->next;
        index++;
    }
    return -1;
}

