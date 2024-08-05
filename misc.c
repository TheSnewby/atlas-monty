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
 * Return: 1 if successful, 2 if malloc error, 7 if can't swap
 */
int swap(stack_t **head, unsigned int line_number)
{
	(void) line_number;
	stack_t *temp = NULL, *swap = NULL;

	if (*head != NULL && (*head)->next != NULL)
	{ /* old head stored in swap, free head, then place swap after new head */
		temp = *head;
		swap = (stack_t *)malloc(sizeof(stack_t *));
		if (swap == NULL)
			return (2);
		swap->n = (*head)->n;
		swap->prev = (*head)->next;
		swap->prev = (*head)->next->next;

		*head = (*head)->next;
		free(temp);
		temp = NULL;
		(*head)->prev = NULL;
		(*head)->next = swap;
	}
	else
		return (7);
	return (1);
}
