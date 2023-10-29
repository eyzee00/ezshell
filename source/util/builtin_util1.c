#include "../main.h"
/**
 * bltn_chck - checks for supported builtin
 * @buff: user's command entry
 * Return: the builtin function to execute if found
 */
int (*bltn_chck(char *buff))(char *buffer, alloclist_t **head, path_t **path)
{
	builtin_t builtin_list[] = {
		{"cd", cd_handler},
		{"unsetenv", unsetenv_handler},
		{"setenv", setenv_handler},
		{"exit", exit_handler},
		{"env", env_handler},
		{NULL, NULL}
	};
	int i = 0;

	if (space_check(buff))
		return (emptycmd_handler);
	while (i < 5)
	{
		if (str_cmp(buff, builtin_list[i].cmdname))
			return (builtin_list[i].func);
		i++;
	}
	return (NULL);
}
/**
 * exit_handler - handles exit
 * with argument and without argument
 * @head: head of the alloclist
 * @buffer: the user input
 * @path: the head of the pathlist
 * Return: return (void)
 */
int exit_handler(char *buffer, alloclist_t **head, path_t **path)
{
	char **command, *err;
	int status = 0, check = 0, wordc;

	wordc = word_count(buffer);
	command = tokenizer(buffer);
	if (command[1] == NULL)
	{
		free_memory(command, wordc);
		ultimate_free(path, head, buffer);
		exit(status);
	}
	else
	{

		check = alpha_check(command[1]);
		if (check)
		{
			err = _getenv("_");
			exit_arg_err(err, command, 0);
			free_memory(command, wordc);
		}
		else
		{
		status = _atoi(command[1]);
		free_memory(command, wordc);
		ultimate_free(path, head, buffer);
		exit(status);
		}
	}
	return (-1);
}
/**
 * env_handler - handles printing the environment
 * @buffer: buffer
 * @head: head of the allocation list
 * @path: the head of the pathlist
 * Return: (1)
 */
int env_handler(char *buffer, alloclist_t **head, path_t **path)
{
	int i = 0;

	head = (alloclist_t **) head;
	buffer = (char *) buffer;
	path = (path_t **) path;
	while (*(environ + i) != NULL)
	{
		write(1, environ[i], __strlen(environ[i]));
		write(1, "\n", 1);
		i++;
	}
	return (-1);
}
/**
 * emptycmd_handler - handles the newline character
 * @buffer: the buffer
 * @head: head of the allocation list
 * @path: head of the pathlist
 * Return: (1)
 */
int emptycmd_handler(char *buffer, alloclist_t **head, path_t **path)
{
	head = (alloclist_t **) head;
	buffer = (char *) buffer;
	path = (path_t **) path;
	return (-1);
}
/**
 * cd_handler - changes directory
 * @buffer: the user commmand
 * @head: head of the alloclist
 * @path: head of the pathlist
 * Return: (1)
 */
int cd_handler(char *buffer, alloclist_t **head, path_t **path)
{
	char **command, *buff1, buff2[256], *buff3;
	int wordc, check;

	buff3 = buff2;
	wordc = word_count(buffer);
	command = tokenizer(buffer);
	path = (path_t **) path;
	if (wordc == 1)
	{
		buff1 = getenv("HOME");
		check = chdir(buff1);
		if (check == -1)
		{
			cd_err(command, getenv("_"), wordc);
			return (-1);
		}
		replacer(head, buff3, command, wordc);
	}
	else if (command[1][0] == '-' && command[1][1] == 0)
	{
		buff1 = getenv("OLDPWD");
		check = chdir(buff1);
		if (check == -1)
		{
			cd_err(command, _getenv("_"), wordc);
			return (-1);
		}
		replacer(head, buff3, command, wordc);
	}
	else
	{
		check = chdir(command[1]);
		if (check == -1)
		{
			cd_err(command, _getenv("_"), wordc);
			return (-1);
		}
		replacer(head, buff3, command, wordc);
	}
	return (-1);
}