#include "../main.h"

/**
  * free_memory - free memory
  * @pointer: point to memory to free
  * @n: count of character
  */
void free_memory(char **pointer, int n)
{
	int i = 0;

	while (i < n)
	{
		free(*(pointer + i));
		i++;
	}
	free(pointer);
}
/**
 * _realloc - reallocates a new space in heap memory
 * where the size == new_size
 * @new_size: the size in bytes to allocate
 * @old_size: the size in bytes of the previously allocated memory
 * @ptr: a void pointer to the previously allocated memory
 * Return: (ptr) if new_size == old_size,
 * if (new_size == 0) and (ptr) is not NULL, then free(ptr),
 * if (ptr) is NULL, then the call is equivalent to malloc(new_size)
 */
void *_realloc(void *ptr, unsigned int old_size, unsigned int new_size)
{
	void *new_pointer;
	char *old_stuff, *new_stuff;
	unsigned int i;

	if (new_size == old_size)
		return (ptr);
	if (new_size == 0 && ptr != NULL)
	{
		free(ptr);
		return (NULL);
	}
	if (ptr == NULL)
	{
		ptr = malloc(new_size);
		if (ptr == NULL)
			return (NULL);
		return (ptr);
	}
	if (new_size > old_size)
	{
		new_pointer = malloc(new_size);
		if (new_pointer == NULL)
			return (NULL);
		old_stuff = ptr;
		new_stuff = new_pointer;
		for (i = 0; i < old_size; i++)
			new_stuff[i] = old_stuff[i];
	}
	return (new_pointer);
}
/**
 * free_env - frees environment memory
 * @environ: the environment to free
 * @n: the number of variables in the environment
 * Return: (void)
 */
void free_env(char **environ, int n)
{
	int i = 0;

	while (i < n)
	{
		free(environ[i]);
		i++;
	}
	free(environ);
}
/**
 * free_everything - frees the memory allocated
 * @head: the head of the list
 * Return: (void)
 */
void free_everything(alloclist_t **head)
{
	alloclist_t *ptr = *head, *placeholder;

	if (ptr == NULL)
		return;
	while (ptr != NULL)
	{
		placeholder = ptr;
		ptr = ptr->next;
		free(placeholder->address);
		free(placeholder);
	}
	*head = NULL;
}
/**
 * ultimate_free - frees literally everything
 * @path: the pathlist
 * @head: the alloclist
 * @buffer: the getline buffer
 * Return: (void);
 */
void ultimate_free(path_t **path, alloclist_t **head, char *buffer)
{
	if (path != NULL)
		free_pathlist(path);
	free_everything(head);
	free(buffer);
}
