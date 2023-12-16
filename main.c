#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include "main.h"
#include <errno.h>

/**
 * main - simple shell that runs commands without any argument and
 * with their full path
 *
 *@ac: the number of arguments passed
 *@av: an array of arguments as strings
 *
 * Return: always returns 0
 */

int main(int ac, char **av)
{
	size_t dirLen = 1024;
	char *dir;
	memStruct *allocMem;

	allocMem = malloc(sizeof(memStruct));

	if (!allocMem)
	{
		printerr("Memory allocation failed");
		exit(errno);
	}

	allocMem->size = 0;
	allocMem->allocatedSize = 0;
	allocMem->myerrno = 0;
	allocMem->memPtr = NULL;
	allocMem->name = av[0];

	dir = malloc(dirLen * sizeof(char));

	if (!dir)
	{
		printerr("Memory allocation failed");
		exit(errno);
	}
	addAddress(dir, allocMem);
	if (ac < 2)
	{
		while (getcwd(dir, dirLen) == NULL)
		{
			dir = _realloc(dir, dirLen, dirLen * 1.5, sizeof(char *));
			dirLen *= 1.5;
		}
		shellloop(av, allocMem);
	}
	else
	{
		interactiveMode(av, dir, allocMem);
	}

	_myexit(allocMem->myerrno, allocMem);
	return (0);
}
