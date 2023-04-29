#include "shell.h"

/**
 * *append_node - appends a node to the end of the list
 * @head: pointer to head node
 * @str: string of node
 * @index: node index
 * Return: size of list
 *
 */

list_t *append_node(list_t **head, const char *str, int index)
{
	list_t *brand_node;
	list_t *node;

	if (head == NULL)
		return (NULL);

	node = *head;
	brand_node = malloc(sizeof(list_t));
	if (!brand_node)
		return (NULL);
	_memset((void *)brand_node, 0, sizeof(list_t));
	brand_node->index = index;
	if (str)
	{
		brand_node->str = _strdup(str);
		if (!brand_node->str)
		{
			free(brand_node);
			return (NULL);
		}
	}
	if (node)
	{
		while (node->next)
			node = node->next;
		node->next = brand_node;
	}
	else
		*head = brand_node;
	return (new_node);
}

/**
 * *add_node - adds a new node atthe beginning of a list
 * @head:pointer to head node
 * @str: string of node
 * @index: node index
 * Return: size of list
 *
 */

list_t *add_node(list_t **head, const char *str, int index)
{
	list_t *new_node = malloc(sizeof(list_t));

	if (new_node == NULL)
	{
		return (NULL);		/* Unable to allocate memory */
	}

	/* Allocate memory for string */

	new_node->str = (char *)malloc(strlen(str) + 1);
	if (new_node->str == NULL)
	{
		free(new_node);
		return (NULL);
	}

	_strcpy(new_node->str, str);
	new_node->index = index;

	/* Set new node as head of linked list */

	new_node->next = *head;
	*head = new_node;

	/* Return pointer to linked list */

	return (*head);
}

/**
 * display_list_str - prints only the string of a linked list
 * @q: pointer to first node
 *
 * Return: size of list
 */
size_t display_list_str(const list_t *q)
{
	size_t poi = 0;

	while (q != NULL)
	{
		_puts(q->str : "(nil)");
		_puts("\n");
		q = q->next;
		poi++;
	}
	return (poi);
}

/**
 * free_list - frees a linked list
 * @head_add: pointer to head node
 *i
 * Return: void
 */
void free_list(list_t **head_add)
{
	list_t *node, *next_node, *head;

	if (!head_add || !*head_add)
		return (0);
	head = *head_add;
	node = head;
	while (node)
	{
		next_node = node->next;
		free(node->str);
		free(node);
		node = next_node;
	}
	*head_add = NULL;
}

/**
 * remove_node_at_index - deletes node at given index
 * @head: address of pointer to first node
 * @index: index of node to delete
 *
 * Return: 1 on success, 0 on failure
 */
int remove_node_at_index(list_t **head, unsigned int index)
{
	list_t *node, *del_node;
	unsigned int i = 0;

	if (!head || !*head)
		return (0);

	if (!index)
	{
		node = *head;
		*head = (*head)->next;
		free(node->str);
		free(node);
		return (1);
	}
	node = *head;
	while (node)
	{
		if (i == index)
		{
			del_node->next = node->next;
			free(node->str);
			free(node);
			return (1);
		}
		i++;
		del_node = node;
		node = node->next;
	}
	return (0);
}
