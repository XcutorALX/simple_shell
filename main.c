#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include "main.h"

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
	size_t bufferSize = 1024;
	size_t dirLen = 1024;
	char delim[] = " ";
	char **command, *dir, *temp;
	void **allocMem;
	int allocated = 0;
	int sizeAllocMem = 0;
	char buffer[1024];

	allocMem = malloc(sizeAllocMem * sizeof(void));
	allocMem[0] = NULL;
	dir = malloc(dirLen * sizeof(char));

	if (ac < 2)
	{
		while (getcwd(dir, dirLen) == NULL)
		{
			dir = _realloc(dir, dirLen, dirLen * 1.5, sizeof(char *));
			dirLen *= 1.5;
		}
		shellloop(av);
	}
	else
	{
		interactiveMode(av, dir);
	}

/**	freeMem();**/
	return (0);
}
