#include "../main.h"

/**
 * logictok - tokenizes the user's input
 * @ch: string
 * @del: delimiter
 * Return: pointer to commandlist
 */
char **logictok(char *ch, char *del)
{
	int cmdc = 0, i = 1, char_count = 0;
	char *command = NULL;
	char **commandlist = NULL;

	if (ch == NULL)
		return (NULL);
	cmdc = logic_counter(ch);
	commandlist = _calloc(sizeof(char *), (cmdc + 1));
	if (commandlist == NULL)
		return (NULL);
	command = _strtok(ch, del);
	if (command != NULL)
	{
	char_count = __strlen(command);
	*commandlist = _calloc(char_count + 2, sizeof(char));
	if (*commandlist == NULL)
	{
		free(commandlist);
		return (NULL);
	}
	fill_row_logic(commandlist, 0, command);
	}
	while (i < cmdc)
	{
		command = _strtok(NULL, del);
		if (command != NULL)
		{
		char_count = __strlen(command);
		*(commandlist + i) = _calloc(char_count + 2, sizeof(char));
		if (*(commandlist + i) == NULL)
		{
			free_memory(commandlist, i);
			return (NULL);
		}
		fill_row_logic(commandlist, i, command);
		}
		i++;
	}
	commandlist[i] = NULL;
	return (commandlist);
}
/**
 * multicmd_hand - handles multiple commands
 * @buffer: user input
 * @argv: name of the shell
 * @p: pathlist
 * @head: head of the alloclist
 * Return: (void)
 */
void multicmd_hand(char *buffer, char *argv, path_t **p, alloclist_t **head)
{
	int cmdc, check, i, wordc;
	char **commandlist, **command;
	int (*f)(char *buffer, alloclist_t **head, path_t **path);

	cmdc = cmd_counter(buffer);
	commandlist = cmdtok(buffer);
	for (i = 0; i < cmdc; i++)
	{
		f = bltn_chck(commandlist[i]);
		if (f != NULL)
			if (f(commandlist[i], head, p) == 1)
				continue;
		var_set(commandlist[i], &wordc, &command);
		check = file_exist_exec(command[0]);
		if (exec_handl(check, command, argv, p, wordc, i))
			continue;
		free_memory(command, wordc);
	}
	free_memory(commandlist, cmdc);
}
/**
 * logic_hand - handles multiple commands
 * @buffer: user input
 * @argv: name of the shell
 * @p: pathlist
 * @head: head of the alloclist
 * Return: (void)
 */
void logic_hand(char *buffer, char *argv, path_t **p, alloclist_t **head)
{
	int cmdc = 0, check, check2, i, wordc;
	char **commandlist, **command, del[22] = "";
	int (*f)(char *buffer, alloclist_t **head, path_t **path);

	initializer(buffer, &cmdc, &check, del);
	commandlist = logictok(buffer, del);
	for (i = 0; i < cmdc && commandlist[i] != NULL; i++)
	{
		f = bltn_chck(commandlist[i]);
		if (f != NULL)
		{
			if (f(commandlist[i], head, p) == -1)
				break;
			continue;
		}
		var_set(commandlist[i], &wordc, &command);
		check2 = file_exist_exec(command[0]);
		if (check == 1)
		{
		if (lexec_handl(check2, command, argv, p, wordc, i) == 1)
			break;
		}
		else
		{
		if (lexec_handl(check2, command, argv, p, wordc, i) == 1)
			continue;
		else
		{
			free_memory(command, wordc);
			break;
		}
		}
		free_memory(command, wordc);
	}
	free_memory(commandlist, cmdc);
}