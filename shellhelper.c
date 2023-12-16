#include <stdio.h>
#include "main.h"
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <errno.h>

/**
 * shellHelper - runs shell commands with fork and exceve
 *
 *@argv: an array of arguments as strings
 *@env: the currrent enviroment
 *
 *Return: always 0
 */

int shellHelper(char **argv, char **env, memStruct *allocMem)
{
	int status;
	pid_t child_pid;

	child_pid = fork();
	if (child_pid == -1)
	{
		printerr("At forking ERROR:");
		return (-1);
	}

	if (child_pid == 0)
	{
		if (execve(argv[0], argv, env) == -1)
		{
			printerr("At execve ERROR: ");
			exit(errno);
		}
	}
	else
	{
		wait(&status);
		allocMem->myerrno = WEXITSTATUS(status);
	}

	return (0);
}

/**
 * interactiveMode - runs the shell in interactive mode
 *
 *@av: an array of arguments as strings
 *@currentPath: the current path
 *@allocMem: a struct keeping track of dynamically allocated memory
 *
 * Return: always 0
*/

int interactiveMode(char **av, char *currentPath, memStruct *allocMem)
{
	size_t bufferSize = 1024;
	struct stat st;
	char *file = av[1];
	char *lineptr = NULL;
	char delim[] = " ";
	char **command;
	int fd;
	char *fullPath = strcon(currentPath, file);

	if (stat(fullPath, &st) == 0)
	{
		fd = open(fullPath, O_RDONLY);
		while (getLine(&lineptr, &bufferSize, fd) != -1)
		{
			command = tokenize(lineptr, delim);
			testBuiltin(command, av[0], allocMem);
		}
	}
	else
	{
		printstr(av[0]);
		printstr(": 1: ");
		printstr(file);
		printstr(": not found");
		_putchar('\n');
	}

	return (0);
}

/**
 * shellloop - the main shell loop
 *
 *@av: arguments
 *@allocMem: a struct keeping track of dynamically allocated memory
 *
 * Return: none
 */

int shellloop(char **av, memStruct *allocMem)
{
	char *lineptr = NULL;
	size_t bufferSize = 1024;
	char delim[] = " ";
	char newline[] = "\n";
	char **command, **lines;
	int terminal, i;

	terminal = isatty(STDIN_FILENO);
	if (terminal != 1)
	{
		if(getPipe(&lineptr, &bufferSize, STDIN_FILENO) != -1)
		{
			lines = tokenize(lineptr, newline);
			
			if (isempty(lineptr) != 0)
			{	for (i = 0; lines[i] != NULL; i++)
				{
					command = tokenize(lines[i], delim);
					addAddress(lineptr, allocMem);
					addAddress(lines, allocMem);
					addAddress(command, allocMem);
					testBuiltin(command, av[0], allocMem);
				}
			}
			else
			{	
				free(lineptr);
				free(lines);
			}
		}
	}
	else
	{
		printstr("$ ");
		fflush(stdout);
		while (getLine(&lineptr, &bufferSize, STDIN_FILENO) != -1)
		{
			command = tokenize(lineptr, delim);
			testBuiltin(command, av[0], allocMem);
			printstr("$ ");
			fflush(stdout);
			free(command);
		}
		free(lineptr);
	}
	return (0);
}
