#include "../main.h"

/**
 * alloclist_init - initializes a alloclist
 * Return: (NULL)
 */
alloclist_t *alloclist_init(void)
{
	return (NULL);
}
/**
 * add_node_end - Adds a node to the end of the list
 * @head: the address of the list
 * @address: the data contained in the node
 * Return: the address of the new node added, (NULL)
 * if allocation fails
 */
alloclist_t *add_node_end(alloclist_t **head, void *address)
{
	alloclist_t *node = malloc(sizeof(alloclist_t));
	alloclist_t *iter = *head;

	if (node == NULL)
		return (NULL);
	node->address = (void *) address;
	node->next = NULL;
	if (iter == NULL)
	{
		*head = node;
		return (node);
	}
	while (iter->next != NULL)
		iter = iter->next;
	iter->next = node;
	return (node);
}