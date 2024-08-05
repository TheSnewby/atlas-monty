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

/**
 * swap - swaps the top two elements of the stack
 * @head: head of the list
 * @line_number: number of input line
 *
 * Return: 1 if successful, 7 if can't swap
 */
int swap(stack_t **head, unsigned int line_number)
{
	(void) line_number;
	int temp;

	if (*head != NULL && (*head)->next != NULL)
	{
		temp = (*head)->n;
		(*head)->n = (*head)->next->n;
		(*head)->next->n = temp;
	}
	else
		return (7);
	return (1);
}
