#include "../main.h"

/**
 * error_handler - handles errors print statement
 * @argv: the name of the shell program
 * @command: the name of the command
 * @counter: line count
 * @option: error case hint
 * Return: (void)
 */
void error_handler(char *argv, char *command, int counter, int option)
{
	char buffer[256] = "\0";

	print_string(argv, buffer);
	print_string(": ", buffer);
	print_decimal(counter, buffer);
	print_string(": ", buffer);
	print_string(command, buffer);
	if (option == -1)
	{
		write(2, buffer, __strlen(buffer));
		write(2, ": not found\n", 12);
	}
	else
		perror(buffer);
}
/**
 * arg_err - handles errors in argument mode using options
 * check for possible errors at different options
 * @argv: the argument vector
 * @option: the error code
 * @command: the command if needed
 * @line: the line where the error happened
 * Return: void
 */
void arg_err(char **argv, int option, char **command, int line)
{
	char err[256] = "";

	if (option == -2)
	{
		print_string(argv[0], err);
		print_string(": Usage: ", err);
		print_string(argv[0], err);
		print_string(" FILENAME\n", err);
		write(2, err, __strlen(err));
	}
	else if (option == -1 || option == 0 || option == -5)
	{
		if (option != -5)
			print_string(argv[1], err);
		else
			print_string(argv[0], err);
		print_string(": ", err);
		if (option != -5)
			print_decimal(line + 1, err);
		else
			print_decimal(line, err);
		print_string(": ", err);
		print_string(command[0], err);
		print_string(": ", err);
		print_string("not found\n", err);
		write(2, err, __strlen(err));
	}
	else if (option == 10)
	{
		print_string(argv[0], err);
		print_string(": ", err);
		print_string("0: ", err);
		print_string("cannot open ", err);
		print_string(argv[1], err);
		print_string(": No such file\n", err);
		write(2, err, __strlen(err));
	}
}
/**
 * exit_arg_err - handles the exit argument error
 * exit error is handled
 * @argv: the name of the shell
 * @command: the exit command
 * @option: the error code
 * Return: (void)
 */
void exit_arg_err(char *argv, char **command, int option)
{
	char err[256] = "";

	if (option == 0)
	{
		print_string(argv, err);
		print_string(": 1: ", err);
		print_string(command[0], err);
		print_string(": Illegal number: ", err);
		print_string(command[1], err);
		print_string("\n", err);
		write(2, err, __strlen(err));
	}
	if (option == 1)
	{
		print_string(argv, err);
		print_string(": 1: ", err);
		print_string(command[0], err);
		print_string(": usage: exit [status]\n", err);
		write(2, err, __strlen(err));
	}
}
/**
 * cd_err - handles cd errors
 * @command: user command
 * @argv: name of the shell
 * @wordc: word count
 * Return: (void)
 */
void cd_err(char **command, char *argv, int wordc)
{
	char err[256] = "";

	print_string(argv, err);
	print_string(": 1: ", err);
	print_string(command[0], err);
	print_string(": can't cd to ", err);
	print_string(command[1], err);
	print_string("\n", err);
	write(2, err, __strlen(err));
	free_memory(command, wordc);
}
