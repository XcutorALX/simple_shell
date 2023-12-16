#include "main.h"
#include <sys/stat.h>
#include <errno.h>

/**
 * testBuiltin - handles builtin functions if any
 * else runs the command
 *
 *@argv: the commnand line input
 *@av: the name of the file being run
 *@allocMem: a struct keeping track of dynamically allocated memory
 *
 *Return: none
 */

void testBuiltin(char **argv, char *av, memStruct *allocMem)
{
	size_t i;
	struct stat st;
	char *temp;
	builtins commands[] = {
		{"exit", &myexit},
		{"env", &printEnv},
		{NULL}
	};

	for (i = 0; commands[i].cmd != NULL; i++)
	{
		if (_strcmp(argv[0], commands[i].cmd) == 0)
		{
			commands[i].func(argv, allocMem);
			return;
		}
	}
	if (stat(argv[0], &st) == 0 &&
		(argv[0][0] == '/' || argv[0][0] == '.'))
		shellHelper(argv, environ, allocMem);
	else
	{
		temp = searchFile(argv[0], allocMem);
		fflush(stdout);
		if (temp != NULL)
		{
			argv[0] = temp;
			shellHelper(argv, environ, allocMem);
			free(temp);
		}
		else
		{
			printerr(av);
			printerr(": 1: ");
			printerr(argv[0]);
			printerr(": not found");
			puterr('\n');
			allocMem->myerrno = 127;
			free(temp);
		}
	}
}

/**
 * myexit - exits the shell
 *
 *@argv: an array of arguments as strings
 *@allocMem: a struct containing details about allocated memory
 *
 * Return: returns 1 if the exit argument is not an int
 */

int myexit(char **argv, memStruct *allocMem)
{
	char *valueStr;
	int value = allocMem->myerrno;

	if (argv[1] == NULL)
	{
		if (allocMem->memPtr)
			freeMem(allocMem);

		free(allocMem);
		exit(value);
	}
	else
	{
		valueStr = argv[1];
		value = _atoi(valueStr);
		if (value < 0)
		{
			printerr(allocMem->name);
			printerr(": 1: exit: Illegal number: ");
			printerr(valueStr);
			puterr('\n');
			value = 2;
		}
	}

	if (allocMem->memPtr)
		freeMem(allocMem);

	free(allocMem);
	exit(value);
}

/**
 * printEnv - prints the current enviroment
 *
 * @argv: an array of arguments as strings
 *
 * Return: always 0
 */

int printEnv(char **argv, memStruct *allocMem)
{
	size_t i;
	int count;

	for(count = 0; count < allocMem->size; count++)
		;

	if (!argv)
	{
		allocMem->myerrno = 1;
		return (-1);
	}

	for (i = 0; environ[i] != NULL; i++)
	{
		printstr(environ[i]);
		_putchar('\n');
	}
	return (0);
}

/**
 * _myexit - unlike myexit, this function takes in an int
 *
 *@exitcode: the exit code to use
 *@allocMem: a list that keeps track of allocated memory
 *
 *Return: void
 */

void _myexit(int exitcode, memStruct *allocMem)
{
	if (allocMem->memPtr)
		freeMem(allocMem);
	
	free(allocMem);
	exit(exitcode);
}
