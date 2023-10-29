#include "../main.h"

/**
 * space_check - checks if the string contains only spaces
 * @buffer: the string we're checking
 * Return: (1) if the string is only spaces, (0) otherwise
 */
int space_check(char *buffer)
{
	int i = 0;

	while (buffer[i] != 0)
	{
		if (buffer[i] != 32 && buffer[i] != 10)
			return (0);
		i++;
	}
	return (1);
}
/**
 * logic_check - checks for logical operators
 * @str: the string to be checked
 * Return: (1) if found, (0) if not
 */
int logic_check(char *str)
{
	int i = 0;


	while (str[i] != 0)
	{
		if (str[i] == '&' || str[i] == '|')
			return (1);
		i++;
	}
	return (0);
}
/**
 * alpha_check - checks for alphabetical chars in a string
 * @str: the string
 * Return: (1) if alphabetical chars exist, (0) otherwise
 */
int alpha_check(char *str)
{
	int i = 0;

	while (str[i] != 0)
	{
		if (str[i] >= 97 && str[i] <= 122)
			return (1);
		if (str[i] >= 65 && str[i] <= 90)
			return (1);
		i++;
	}
	return (0);
}
/**
 * semicolon_check - checks for the semicolon character
 * check for semicolon in user entry
 * @str: the string to be checked
 * Return: (1) if found, (0) if not
 */
int semicolon_check(char *str)
{
	int i = 0;


	while (str[i] != 0)
	{
		if (str[i] == ';')
		{
			while (str[i] != 0)
			{
			if (str[i] == 10)
				return (1);
			if (str[i] == ';' && str[i + 1] == 0)
			{
				str[i] = 0;
				return (1);
			}
			if (str[i] == ';' && str[i + 1] == '\n')
			{
				str[i] = 10;
				str[i + 1] = 0;
				return (1);
			}
			i++;
			}
			return (1);
		}
		i++;
	}
	return (0);
}
/**
  * file_exist_exec - file exit & executable
  * @command: user command
  * Return: 1 for success -1 if faill
  */
int file_exist_exec(char *command)
{
	struct stat status;
	int check;

	check = stat(command, &status);
	if (check == 0)
	{
		if (S_ISDIR(status.st_mode))
			return (-1);
		if (access(command, X_OK) == 0)
			return (1);
		else
			return (0);
	}
	return (-1);
}