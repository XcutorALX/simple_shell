#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>

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
