#include "../main.h"

/**
 * set_entry - sets an entry with the given name and value
 * @name: the name of the variable
 * @value: the value of the given variable
 * @buffer: where to put the entry in
 * Return: (void)
 */
void set_entry(char *buffer, char *name, char *value)
{
	print_string(name, buffer);
	addto_buff(buffer, 61);
	print_string(value, buffer);
}
/**
 * var_set - sets some variables
 * @buffer: buffer
 * @check: wordc
 * @command: the command to set
 * Return: (void)
 */
void var_set(char *buffer, int *check, char ***command)
{
	*check = word_count(buffer);
	*command = tokenizer(buffer);
}
/**
 * replacer - functions for place holder
 * @head: head of the alloclist
 * @buff3: buffer
 * @command: user command
 * @wordc: word count
 * Return: (void)
 */
void replacer(alloclist_t **head, char *buff3, char **command, int wordc)
{
	_setenv("OLDPWD", getenv("PWD"), head);
	buff3 = getcwd(buff3, 256);
	_setenv("PWD", buff3, head);
	free_memory(command, wordc);
}
/**
 * initializer - initializes some necessary variables
 * @buffer: user input
 * @cmdc: command count
 * @check: case
 * @del: delimiter
 * Return: (void)
 */
void initializer(char *buffer, int *cmdc, int *check, char *del)
{
	*cmdc = logic_counter(buffer);
	*check = get_del(buffer);
	set_delimiter(*check, del);
}
/**
 * set_delimiter - sets the delimiter
 * @check: the case
 * @del: the char to be sets
 * Return: (void)
 */
void set_delimiter(int check, char *del)
{
	if (check == 1)
		print_string("&", del);
	else
		print_string("|", del);
}
