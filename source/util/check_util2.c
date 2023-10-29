#include "../main.h"

/**
 * equal_check - checks for the equal character
 * @str: the string to be checked
 * Return: (1) if found, (0) if not
 */
int equal_check(char *str)
{
	int i = 0;

	while (str[i] != 0)
	{
		if (str[i] == 61)
			return (1);
		i++;
	}
	return (0);
}