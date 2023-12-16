#include <stdio.h>
#include "main.h"

/**
 * _atoi - converts string to integers
 *
 * @str: the string to convert
 *
 * Return: returns the number converted
 */

int _atoi(char *str)
{
	int value = 0;
	int len, sign;
	size_t i;

	sign = 1;
	for (len = 0; str[len] != '\0'; len++)
		;

	if (str[0] == '-')
	{
		str[0] = '0';
		sign = -1;
	}

	len--;
	for (i = 0; str[i] != '\0'; i++, len--)
	{
		if (str[i] >= '0' && str[i] <= '9')
			value += (str[i] - '0') * (_pow(10, len));
		else
			return (-1);
	}

	if (sign == -1)
		str[0] = '-';

	return (value * sign);
}

/**
 * _pow - finds the exponent of a number
 *
 * @x: the base
 * @y: the exponent
 *
 * Return: the answer
 */

int _pow(long int x, long int y)
{
	int result = 1;
	int i;

	for (i = 0; i < y; i++)
		result *= x;

	return (result);
}
