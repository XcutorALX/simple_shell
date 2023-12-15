#include "main.h"
#include <unistd.h>

/**
 * _putchar - writes the character c to stdout
 * @c: The character to print
 *
 * Return: On success 1.
 * On error, -1 is returned, and errno is set appropriately.
 */

int _putchar(char c)
{
	return (write(1, &c, 1));
}

/**
 * printstr - prints a string
 *
 *@str: the string to be printed
 *
 *Return: void
 */

 void printstr(char *str)
{
	size_t i;

	for (i = 0; str[i] != '\0'; i++)
		_putchar(str[i]);
}

/**
 * puterr - writes a character to the standard error stream
 *
 * @c: the character to write
 *
 * Return: -1 on failure
 */

int puterr(char c)
{
	return (write(2, &c, 1));
}

/**
 * printerr - writes a string to the standard error stream
 *
 *@str: the string to write
 *
 *Return: void
 */

void printerr(char *str)
{
	size_t i;

	for (i = 0; str[i] != '\0'; i++)
		puterr(str[i]);
}
