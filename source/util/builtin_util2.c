#include "../main.h"

/**
 * setenv_handler - handles the setenv builtin
 * @buffer: the command and its arguments
 * @head: head of the alloc list
 * @path: head of the pathlist
 * Return: (1);
 */
int setenv_handler(char *buffer, alloclist_t **head, path_t **path)
{
	char **command, err[128] = "\0";
	int option, wordc;

	wordc = word_count(buffer);
	command = tokenizer(buffer);
	path = (path_t **) path;
	if (command[1] == NULL || command[2] == NULL)
	{
		print_string(command[0], err);
		print_string(": Usage: setenv VARNAME VALUE\n", err);
		write(2, err, __strlen(err));
		free_memory(command, wordc);
		return (-1);
	}
	option = _setenv(command[1], command[2], head);
	if (option == 0)
	{
		print_string(command[0], err);
		print_string(": Memory allocation failed\n", err);
		write(2, err, __strlen(err));
		free_memory(command, wordc);
		return (-1);
	}
	if (option == -1)
	{
		print_string(command[0], err);
		print_string(": bad variable name\n", err);
		write(2, err, __strlen(err));
		free_memory(command, wordc);
		return (-1);
	}
	free_memory(command, wordc);
	return (-1);
}
/**
 * unsetenv_handler - handles the unset builtin
 * @buffer: the user command
 * @head: the head of the alloclist
 * @path: the head of the pathlist
 * Return: always (1)
 */
int unsetenv_handler(char *buffer, alloclist_t **head, path_t **path)
{
	int option = 0, wordc = word_count(buffer);
	char err[256] = "", **command;

	command = tokenizer(buffer);
	path = (path_t **) path;
	if (wordc != 2)
	{
		print_string(command[0], err);
		print_string(": Usage: unsetenv VARNAME\n", err);
		write(2, err, __strlen(err));
		free_memory(command, wordc);
		return (-1);
	}
	option = _unsetenv(command[1], head);
	if (option == -1)
	{
		print_string(command[0], err);
		print_string(": bad variable name\n", err);
		write(2, err, __strlen(err));
		free_memory(command, wordc);
		return (-1);
	}
	if (option == 0)
	{
		print_string(command[0], err);
		print_string(": Memory allocation failed\n", err);
		write(2, err, __strlen(err));
		free_memory(command, wordc);
		return (-1);
	}
	free_memory(command, wordc);
	return (-1);
}
/**
 * _setenv - sets a new environment variable or modifies an
 * existing one
 * @name: name of the variable to set
 * @value: the value of the said variable
 * @head: head of the alloc list
 * Return: (-1) on failure, (1) on success
 */
int _setenv(char *name, char *value, alloclist_t **head)
{
	unsigned int i = 0, size = 0;
	char **mod_env, *newvar, buff[256];
	char **ptr = environ;

	if (name == 0 || *name == 0)
		return (-1);
	if (equal_check(name))
		return (-1);
	while (*(environ + i) != NULL)
	{
		_strncpy(buff, ptr[i], _strlentok(ptr[i]));
		if (str_cmp(buff, name))
		{
		size = (unsigned int) (__strlen(name) + __strlen(value) + 2);
		newvar = malloc(size);
		*newvar = '\0';
		if (newvar == NULL)
			return (0);
		set_entry(newvar, name, value);
		*(ptr + i) = newvar;
		add_node_end(head, (void *) newvar);
		return (1);
		}
		i++;
	}
	i = string_count(ptr);
	mod_env = _realloc(ptr, i * sizeof(char *), (i + 2) * sizeof(char *));
	if (mod_env == NULL)
		return (0);
	add_node_end(head, (void *) mod_env);
	size = (unsigned int) (__strlen(name) + __strlen(value) + 2);
	mod_env[i] = malloc(size * sizeof(char));
	if (mod_env[i] == NULL)
		return (0);
	mod_env[i][0] = '\0';
	set_entry(mod_env[i], name, value);
	mod_env[i + 1] = NULL;
	environ = mod_env;
	add_node_end(head, (void *) mod_env[i]);
	return (1);
}
/**
 * _unsetenv - unsets an environment variable
 * @name: name of the variable to set
 * @head: head of the alloc list
 * Return: (-1) on failure, (1) on success
 */
int _unsetenv(char *name, alloclist_t **head)
{
	unsigned int i = 0, size = 0, check = 0, j = 0;
	char **mod_env, buff[256];
	char **ptr = environ;

	if (name == 0 || *name == 0)
		return (-1);
	if (equal_check(name))
		return (-1);
	while (*(environ + i) != NULL)
	{
		_strncpy(buff, ptr[i], _strlentok(ptr[i]));
		if (str_cmp(buff, name))
		{
			check = i;
			break;
		}
		i++;
	}
	i = 0;
	if (check)
	{
		size = string_count(environ);
		mod_env = malloc(size * sizeof(char *));
		if (mod_env == NULL)
			return (0);
		for (i = 0; j < size - 1; j++, i++)
		{
		if (j != check)
			mod_env[j] = environ[i];
		else
		{
			i++;
			mod_env[j] = environ[i];
		}
		}
		mod_env[size - 1] = NULL;
		add_node_end(head, mod_env);
		environ = mod_env;
	}
	return (1);
}
/**
 * _getenv - gets the value of an environment variable
 * values of env inputed
 * @name: the variable name
 * Return: (NULL) if not found, the value otherwise
 */
char *_getenv(const char *name)
{
	int i = 0, j = 0;

	while (environ[i] != NULL)
	{
		if (str_cmp((char *) name, environ[i]))
		{
		while (environ[i][j] != '=')
			j++;
		j++;
		return (environ[i] + j);
		}
		i++;
	}
	return (NULL);
}