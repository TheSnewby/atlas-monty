#include "monty.h"

/**
 * main - starts the monty interpreter
 * @argc: number of arguments
 * @argv: string array of arguments
 *
 * Return: EXIT_SUCCESS on success, EXIT_FAILURE otherwise
 */
char **tokens = NULL;

int main(int argc, char *argv[])
{
	int i, parse_return, call_return;
	unsigned int line_number = 1;
	FILE *file;
	char buf[256];
	stack_t *temp = NULL;
	stack_t **head = &temp;

	if (argc != 2) /* 0 or 1 for no arguments? */
		exitAll(head, NULL, line_number, 0);
	file = fopen(argv[1], "r");

	if (file == NULL)
	{
		fprintf(stderr, "Error: Can't open file %s\n", argv[1]);
		exitAll(head, file, line_number, 1);
	}

	while (fgets(buf, 256, file)) /* reads lines up to \n or 256 chars */
	{
		tokens = malloc(5 * sizeof(char *)); /* command, int, \n */
		if (tokens == NULL)
			exitAll(head, file, line_number, 2);
		for (i = 0; i < 5; i++) /* prepopulate with NULL*/
			tokens[i] = NULL;

		parse_return = parse(buf);
		if (parse_return != 0) /* if not empty line */
		{
			call_return = call_op_func(tokens[0], head, line_number);
			if (call_return != 1) /* if didn't return successfully */
			{
				exitAll(head, file, line_number, call_return);
			}
		}
		line_number++;
		freeAll(head);
	}
	fclose(file);
	return (0);
}

/**
 * parse - parses buffer for commands
 * @buf: buffer up the least of \n or 256 chars
 *
 * Return: 1 if successful, 0 if empty, -1 if too many
 */
int parse(char *buf)
{
	char *token;
	int token_count = 0;

	token = strtok(buf, " \r\t\n");
	if (token == NULL)
		return (0); /* no commands - add error message? */

	while (token != NULL) /* store tokens in memory */
	{
		if (token_count > 3)
			return (-1); /* add error for too many instructions ? */

		/* printf("token: %s\n", token); debug */
		tokens[token_count] = token;
		token = strtok(NULL, " \r\t\n");
		token_count++;
	}

	return (1); /* success */
}

/**
 * freeAll - frees all dynamically allocated memory
 * @head: head of list
 */
void freeAll(stack_t **head)
{
	stack_t *temp = NULL;
	/* int i; */

	if (tokens != NULL)
	{
		/* for (i = 0; tokens[i] != NULL; i++) */
		/*	free(tokens[i]); */
		free(tokens);
	}
	while (head != NULL && *head != NULL)
	{
		temp = *head;
		*head = (*head)->next;
		free(temp);
	}
	/* free(head); */
}

/**
 * exitAll - handles all exit calls
 * @head: head of list
 * @file: file pointer
 * @line_number: line number of error
 * @err_no: internal error number
 */
void exitAll(stack_t **head, FILE *file, unsigned int line_number, int err_no)
{
	if (file != NULL)
		fclose(file);
	switch (err_no)
	{
		case 0:
				fprintf(stderr, "USAGE: monty file\n");
				freeAll(head);
				exit(EXIT_FAILURE);
		case 1: /* fprintf in main.c to reduce arguments sent to exitAll */
				freeAll(head);
				exit(EXIT_FAILURE);
		case 2:
				fprintf(stderr, "Error: malloc failed\n");
				freeAll(head);
				exit(EXIT_FAILURE);
		case 3:
				fprintf(stderr, "L%u: unknown instruction %s\n", line_number,
					tokens[0]);
				freeAll(head);
				exit(EXIT_FAILURE);
		case 4:
				fprintf(stderr, "L%u: usage: push integer\n", line_number);
				freeAll(head);
				exit(EXIT_FAILURE);
	}
}
