#include "monty.h"

/**
 * isNum - checks if a string is an integer
 * @c: string to be compared
 *
 * Return: 1 if integer, 0 if not
 */
int isNum(char *c)
{
	int i;

	if (c == NULL)
		return (1);

	for (i = 0; c[i] != '\0'; i++)
	{
		if (i == 0 && c[i] == '-')
			;
		else if (c[i] >= 48 && c[i] <= 57)
			;
		else
			return (0);
	}
	return (1);
}
