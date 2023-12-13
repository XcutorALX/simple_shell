#include <stdio.h>
#include "main.h"
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

/**
 * shellHelper - runs shell commands with fork and exceve
 *
 *@argv: an array of arguments as strings
 *@env: the currrent enviroment
 *
 *Return: always 0
 */

int shellHelper(char **argv, char **env)
{
	int status;
	pid_t child_pid;

	child_pid = fork();
	if (child_pid == -1)
	{
		perror("At forking ERROR:");
		return (-1);
	}

	if (child_pid == 0)
	{
		if (execve(argv[0], argv, env) == -1)
		{
			perror("At execve ERROR:");
		}
	}
	else
	{
		wait(&status);
	}

	return (0);
}

/**
 * interactiveMode - runs the shell in interactive mode
 *
 * @av: an array of arguments as strings
 *
 * Return: always 0
 */

int interactiveMode(char **av, char *currentPath)
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
		while(getLine(&lineptr, &bufferSize, fd) != -1)
		{
			command = tokenize(lineptr, delim);
			testBuiltin(command, av[0]);
		}	
	}
	else
		printf("%s: 1: %s: not found\n", av[0], file);

	exit(0);
}

/**
 * shellloop - the main shell loop
 *
 * @av: arguments
 *
 * Return: none
 */

int shellloop(char **av)
{
	char *lineptr = NULL;
	size_t bufferSize = 1024;
	char delim[] = " ";
	char **command;
	int terminal;

	terminal = isatty(STDIN_FILENO);
	if (terminal == 1)
	{
		printf("$ ");
		fflush(stdout);
	}
	while (getLine(&lineptr, &bufferSize, STDIN_FILENO) != -1)
	{
		command = tokenize(lineptr, delim);
		testBuiltin(command, av[0]);

		if (terminal == 1)
		{
			printf("$ ");
			fflush(stdout);
		}
	}
	if (terminal == 1)
		printf("\n");
}
