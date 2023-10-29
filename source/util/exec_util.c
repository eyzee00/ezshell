#include "../main.h"
/**
 * exec_handl - handles command execution
 * @check: the file status
 * @cmd: the command entered by the user
 * @argv: name of the shell
 * @wdc: how many words in the command
 * @p: pathlist
 * @c: line count
 * Return: (1) to continue, (0) to resume
 */
int exec_handl(int check, char **cmd, char *argv, path_t **p, int wdc, int c)
{
	int check2 = 0;

	if (check == 0)
	{
		error_handler(argv, cmd[0], c, -1);
		free_memory(cmd, wdc);
		return (1);
	}
	if (check == 1 || check == -1)
	{
		if (check == -1)
		{
			check2 = executable_locator(p, cmd);
			if (check2 == -1)
			{
				error_handler(argv, cmd[0], c, check);
				free_memory(cmd, wdc);
				return (1);
			}
		}
		executor(cmd);
	}
	return (0);
}
/**
 * executor - executes a command in a child process
 * @command: the command array
 * Return: (void)
 */
void executor(char **command)
{
	pid_t child_id;
	int status = 0, exec;

	child_id = fork();
	if (child_id == 0)
	{
		exec = execve(command[0], command, environ);
		if (exec == -1)
		{
			perror("execve");
			exit(99);
		}
	}
	else
		wait(&status);
}
/**
 * logicexecutor - executes a command in a child process
 * @command: the command array
 * Return: (void)
 */
int logicexecutor(char **command)
{
	pid_t child_id;
	int status = 0, exec;

	child_id = fork();
	if (child_id == 0)
	{
		exec = execve(command[0], command, environ);
		if (exec == -1)
		{
			perror("execve");
			exit(99);
		}
	}
	else
		wait(&status);
	if (status != 0)
		return (-1);
	return (0);
}
/**
 * lexec_handl - handles command execution
 * @check: the file status
 * @cmd: the command entered by the user
 * @argv: name of the shell
 * @wdc: how many words in the command
 * @p: pathlist
 * @c: line count
 * Return: (1) to continue, (0) to resume
 */
int lexec_handl(int check, char **cmd, char *argv, path_t **p, int wdc, int c)
{
	int check2 = 0;

	if (check == 0)
	{
		error_handler(argv, cmd[0], c, -1);
		free_memory(cmd, wdc);
		return (1);
	}
	if (check == 1 || check == -1)
	{
		if (check == -1)
		{
			check2 = executable_locator(p, cmd);
			if (check2 == -1 || check2 == 0)
			{
				error_handler(argv, cmd[0], c, check);
				free_memory(cmd, wdc);
				return (1);
			}
		}
		if (logicexecutor(cmd) != 0)
		{
			free_memory(cmd, wdc);
			return (1);
		}
	}
	return (0);
}
