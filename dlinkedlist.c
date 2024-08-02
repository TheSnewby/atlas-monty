#include "monty.h"

/**
 * stack - adds node at beginning
 * @head: pointer to head
 * @val: value of integer
 *
 * Return: pointer to head
 */
stack_t push(stack_t *head, unsigned int line_number)
{
	stack_t *temp = NULL;
	stack_t *new_node = NULL;

	if (head == NULL) /* uninitiated */
	{
		head = (stack_t *)malloc(sizeof(stack_t));
		if (head == NULL)
		{
			/* and malloc error */
			exit(EXIT_FAILURE);
		}
		head->n = tokens[1];
		head->next = NULL;
		head->prev = NULL;
		return (*head);
	}
	else
	{
		temp = head;
		new_node = (stack_t *)malloc(sizeof(stack_t));
		if (new_node == NULL)
		{
			/* insert malloc error */
			exit(EXIT_FAILURE);
		}
		new_node->n = tokens[1];
		new_node->next = head;
		new_node->prev = NULL;
		head->prev = new_node;
		head = new_node;
		return (*head);
	}
}
/**
 * pall - prints all items in stack
 * @head: head of stack
 * @line_number: line number from input
 */
void pall(stack_t *head, unsigned int line_number)
{
	(void) line_number;
	stack_t *temp = head;

	while (temp != NULL)
	{
		printf("%d\n", temp->n);
		temp = temp->next;
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
int (*get_op_func(char *s))(stack_t *head, unsigned int line_number)
{
	instruction_t ops[] = {
		{"push", push},
		{"pall", pall},
		{NULL, NULL}
		};

	int i = -1;

	while (i++ < 3)
	{
		if (*s == ops[i].opcode[0])
			return (ops[i].f); /* or ops[i].opcode[1] */
	}
	if (i == 4)
		return (0);
	return (1);
}
