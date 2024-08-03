#include "monty.h"

/**
 * stack - adds node at beginning
 * @head: pointer to head
 * @val: value of integer
 *
 * Return: pointer to head
 */
void push(stack_t **head, unsigned int line_number)
{
	stack_t *temp = NULL;
	stack_t *new_node = NULL;

	/* check if tokens is correctly shaped */

	if (head == NULL) /* uninitiated */
	{
		head = (stack_t **)malloc(sizeof(stack_t));
		if (head == NULL)
		{
			printf("Error: malloc failed\n");
			exit(EXIT_FAILURE);
		}
		(*head)->n = atoi(tokens[1]); /* consider atoi check */
		(*head)->next = NULL;
		(*head)->prev = NULL;
	}
	else
	{
		temp = *head;
		new_node = (stack_t *)malloc(sizeof(stack_t));
		if (new_node == NULL)
		{
			printf("Error: malloc failed\n");
			freeAll(head);
			exit(EXIT_FAILURE);
		}
		new_node->n = atoi(tokens[1]);
		new_node->next = *head;
		new_node->prev = NULL;
		(*head)->prev = new_node;
		*head = new_node;
	}
}
/**
 * pall - prints all items in stack
 * @head: head of stack
 * @line_number: line number from input
 */
void pall(stack_t **head, unsigned int line_number)
{
	(void) line_number;
	stack_t *temp = *head;

	/* check if pall is correctly shaped */

	while (temp != NULL)
	{
		printf("%d\n", temp->n);
		*temp = *temp->next;
	}
}

/**
 * get_op_func - function pointer to a set of functions
 * @s: command
 * @head: head of stack
 * @line_number: input line number - used for errors
 *
 * Return: 1 if successful, 0 otherwise 
 */
int call_op_func(char *s, stack_t **head, unsigned int line_number)
{
	instruction_t ops[] = {
		{"push", push},
		{"pall", pall},
		{NULL, NULL}
		};

	int i = -1;

	while (i++ < 3)
	{
		if (strcmp(s,ops[i].opcode) == 0)
			ops[i].f(head, line_number);
	}
	if (i == 4)
	{
		return (0);
	}
	return (1);
}
/**
 * freeAll - frees all dynamically allocated memory
 */
void freeAll(stack_t **head)
{
	stack_t *temp = NULL;
	int i;

	if (tokens != NULL)
	{
		(void) temp;
		for (i = 0; tokens[i] != NULL; i++)
			free(tokens[i]);
	}
	while (*head != NULL)
	{
		temp = *head;
		*head = (*head)->next;
		free(temp);
	}
	free(head);
}
