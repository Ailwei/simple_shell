#include "shell.h"

/**
 * add_custom_node - adds a custom node to the start of the list
 * @head: address of pointer to head node
 * @data: data field of the node
 * @number: node index used by history
 *
 * Return: pointer to the new node
 */
CustomList *add_custom_node(CustomList **head, const char *data, int number)
{
	CustomList *new_head;

	if (!head)
		return (NULL);
	new_head = malloc(sizeof(CustomList));
	if (!new_head)
		return (NULL);
	_custom_memset((void *)new_head, 0, sizeof(CustomList));
	new_head->number = number;
	if (data)
	{
		new_head->data = _custom_strdup(data);
		if (!new_head->data)
		{
			free(new_head);
			return (NULL);
		}
	}
	new_head->next = *head;
	*head = new_head;
	return (new_head);
}

/**
 * add_custom_node_end - adds a custom node to the end of the list
 * @head: address of pointer to head node
 * @data: data field of the node
 * @number: node index used by history
 *
 * Return: pointer to the new node
 */
CustomList *add_custom_node_end(CustomList **head, const char *data, int number)
{
	CustomList *new_node, *node;

	if (!head)
		return (NULL);

	node = *head;
	new_node = malloc(sizeof(CustomList));
	if (!new_node)
		return (NULL);
	_custom_memset((void *)new_node, 0, sizeof(CustomList));
	new_node->number = number;
	if (data)
	{
		new_node->data = _custom_strdup(data);
		if (!new_node->data)
		{
			free(new_node);
			return (NULL);
		}
	}
	if (node)
	{
		while (node->next)
			node = node->next;
		node->next = new_node;
	}
	else
		*head = new_node;
	return (new_node);
}

/**
 * custom_print_list_data - prints only the data element of a custom list
 * @h: pointer to first node
 *
 * Return: size of list
 */
size_t custom_print_list_data(const CustomList *h)
{
	size_t i = 0;

	while (h)
	{
		_custom_puts(h->data ? h->data : "(nil)");
		_custom_puts("\n");
		h = h->next;
		i++;
	}
	return (i);
}

/**
 * custom_delete_node_at_index - deletes a custom node at a given index
 * @head: address of pointer to first node
 * @index: index of node to delete
 *
 * Return: 1 on success, 0 on failure
 */
int custom_delete_node_at_index(CustomList **head, unsigned int index)
{
	CustomList *node, *prev_node;
	unsigned int i = 0;

	if (!head || !*head)
		return (0);

	if (!index)
	{
		node = *head;
		*head = (*head)->next;
		free(node->data);
		free(node);
		return (1);
	}
	node = *head;
	while (node)
	{
		if (i == index)
		{
			prev_node->next = node->next;
			free(node->data);
			free(node);
			return (1);
		}
		i++;
		prev_node = node;
		node = node->next;
	}
	return (0);
}

/**
 * custom_free_list - frees all nodes of a custom list
 * @head_ptr: address of pointer to head node
 *
 * Return: void
 */
void custom_free_list(CustomList **head_ptr)
{
	CustomList *node, *next_node, *head;

	if (!head_ptr || !*head_ptr)
		return;
	head = *head_ptr;
	node = head;
	while (node)
	{
		next_node = node->next;
		free(node->data);
		free(node);
		node = next_node;
	}
	*head_ptr = NULL;
}

