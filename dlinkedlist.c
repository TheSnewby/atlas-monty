#include "monty.h"

/**
 * push - adds node at beginning
 * @head: pointer to head
 * @line_number: value of integer
 *
 * Return: 1 on success, 2 on malloc issue, 4 on bad push usage
 */
int push(stack_t **head, unsigned int line_number)
{
	stack_t *temp = NULL;
	stack_t *new_node = NULL;
	int tokens_size = 0;

	while (tokens[tokens_size] != NULL)
		tokens_size++;
	(void) line_number;
	if (tokens_size != 2)
		return (4);
	if (strlen(tokens[1]) == 1 && tokens[1][0] == '0')
		;
	else if (atoi(tokens[1]) == 0)
		return (4);

	if (*head == NULL)
	{
		(void) temp;
		*head = (stack_t *)malloc(sizeof(stack_t));
		(*head)->n = atoi(tokens[1]);
		(*head)->next = NULL;
		(*head)->prev = NULL;
	}
	else
	{
		temp = *head;
		new_node = (stack_t *)malloc(sizeof(stack_t));
		if (new_node == NULL)
			return (2);
		new_node->n = atoi(tokens[1]);
		new_node->next = *head;
		new_node->prev = NULL;
		(*head)->prev = new_node;
		*head = new_node;
	}
	return (1);
}
/**
 * pall - prints all items in stack
 * @head: head of stack
 * @line_number: line number from input
 *
 * Return: 1 on success
 */
int pall(stack_t **head, unsigned int line_number)
{
	(void) line_number;
	stack_t *temp = *head;

	/* check if pall is correctly shaped */

	while (temp != NULL)
	{
		printf("%d\n", temp->n);
		temp = temp->next;
	}
	return (1);
}

/**
 * call_op_func - function pointer to a set of functions
 * @s: command
 * @head: head of stack
 * @line_number: input line number - used for errors
 *
 * Return: 1 if successful, 3 if unknown instruction
 */
int call_op_func(char *s, stack_t **head, unsigned int line_number)
{
	instruction_t ops[] = {
		{"push", push},
		{"pall", pall},
		{NULL, NULL}
		};

	int i = 0;

	while (ops[i].opcode != NULL)
	{
		if (strcmp(s, ops[i].opcode) == 0)
			return (ops[i].f(head, line_number));
		i++;
	}
	return (3);
}