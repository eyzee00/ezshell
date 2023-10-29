#include "../main.h"

/**
 * get_del - gets the logical operator
 * @buffer: the user input
 * Return: (1) if AND, (0) if OR
 */
int get_del(char *buffer)
{
	int i = 0;

	while (buffer[i] != 0)
	{
		if (buffer[i] == '&')
			return (1);
		if (buffer[i] == '|')
			return (0);
		i++;
	}
	return (0);
}
