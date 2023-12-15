#include "main.h"
#include <sys/stat.h>

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
			commands[i].func(argv);
			return;
		}
	}
	if (stat(argv[0], &st) == 0)
		shellHelper(argv, environ);
	else
	{
		temp = searchFile(argv[0], allocMem);
		if (temp != NULL)
		{
			argv[0] = temp;
			shellHelper(argv, environ);
		}
		else
			printf("%s: 1: %s: not found\n", av, argv[0]);
	}
}

/**
 * myexit - exits the shell
 *
 * @argv: an array of arguments as strings
 *
 * Return: returns 1 if the exit argument is not an int
 */

int myexit(char **argv)
{
	char *valueStr;
	int value;

	if (argv[1] == NULL)
	{
		exit(0);
	}
	else
	{
		valueStr = argv[1];
		value = _atoi(valueStr);
		if (value == -1)
			return (1);
	}
	exit(value);
}

/**
 * printEnv - prints the current enviroment
 *
 * @argv: an array of arguments as strings
 *
 * Return: always 0
 */

int printEnv(char **argv)
{
	size_t i;

	if (!argv)
		exit(EXIT_FAILURE);

	for (i = 0; environ[i] != NULL; i++)
		printf("%s\n", environ[i]);

	return (0);
}
