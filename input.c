#include <stdio.h>
#include <unistd.h>

/**
 * my_fgetc - a function that reads a character from a file
 *
 * @fd: the file descriptor to read from
 *
 * Return: returms EOF if theres nothing to read
 */

int my_fgetc(int fd)
{
	char c;
	ssize_t bytesRead = read(fd, &c, 1);

	if (fd == -1)
		return (EOF);

	if (bytesRead == -1 || bytesRead == 0)
		return (EOF);

	return ((int)c);
}
