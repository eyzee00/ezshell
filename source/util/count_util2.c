#include "../main.h"
/**
 * cmd_counter - count the number of commands
 * count user command entry
 * @str: the string to operate with
 * Return: the line count if successful
 */
int cmd_counter(char *str)
{
	int i = 0, counter = 0;

	while (*(str + i) != 0)
	{
		if (*(str + i) == ';')
			counter++;
		i++;
	}
	return (counter + 1);
}
/**
 * logic_counter - countes the number of commands
 * @str: the string to operate on
 * Return: the line count
 */
int logic_counter(char *str)
{
	int i = 0, counter = 0;

	while (*(str + i) != 0)
	{
		if (*(str + i) == '&' && *(str + i + 1) == '&')
		{
			counter++;
			i++;
		}
		if (*(str + i) == '|' && *(str + i + 1) == '|')
		{
			counter++;
			i++;
		}
		i++;
	}
	return (counter + 1);
}
/**
 * string_count - counts how many strings in the env list
 * @env: environment array
 * Return: the count
 */
int string_count(char **env)
{
	int i = 0;

	if (env == NULL)
		return (0);
	while (*(env + i) != NULL)
		i++;
	return (i);
}