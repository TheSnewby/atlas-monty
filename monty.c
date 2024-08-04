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
	stack_t **head = NULL;

	if (argc == 1 || argc > 2) /* 0 or 1 for no arguments? */
		exitAll(head, file, line_number, 0);
	file = fopen(argv[1], "r");

	if (file == NULL)
	{
		fprintf(stderr, "Error: Can't open file %s", argv[1]);
		exitAll(head, file, line_number, 1);
	}

	while (fgets(buf, 256, file)) /* reads lines up to \n or 256 chars */
	{
		tokens = malloc(3 * sizeof(char *)); /* command, int, \n */
		if (tokens == NULL)
			exitAll(head, file, line_number, 2);
		for (i = 0; i < 3; i++) /* prepopulate with NULL*/
			tokens[i] = NULL;

		parse_return = parse(buf);
		if (!parse_return) /* consider return errors */
			printf("didn't parse right, do stuff\n");
		call_return = call_op_func(tokens[0], head, line_number);
		if (!call_return)
			exitAll(head, file, line_number, call_return);
		line_number++;
	}
	fclose(file);
	freeAll(head);
	return (0);
}

/**
 * parse - parses buffer for commands
 * @buf: buffer up the least of \n or 256 chars
 *
 * Return: 1 if successful, 0 if otherwise
 */
int parse(char *buf)
{
	char *token;
	int token_count = 0;

	token = strtok(buf, " ");
	if (token == NULL)
		return (0); /* no commands - add error message? */

	while (token != NULL) /* store tokens in memory */
	{
		if (token_count > 3)
			return (0); /* add error for too many instructions ? */
		tokens[token_count] = token;
		token = strtok(NULL, " ");
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
	int i;

	if (tokens != NULL)
	{
		(void) temp;
		free(tokens);
		/* for (i = 0; tokens[i] != NULL; i++) */
		/*	free(tokens[i]); */
	}
	while (*head != NULL)
	{
		temp = *head;
		*head = (*head)->next;
		free(temp);
	}
	free(head);
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
	fclose(file);
	switch (err_no)
	{
		case 0:
				fprintf(stderr, "USAGE: monty file\n");
				freeAll(head);
				exit(EXIT_FAILURE);
				break;
		case 1:
				exit(EXIT_FAILURE);
				freeAll(head);
				break;
		case 2:
				fprintf(stderr, "Error: malloc failed\n");
				freeAll(head);
				exit(EXIT_FAILURE);
		case 3:
				fprintf(stderr, "L%u: unknown instruction %s", line_number,
					tokens[0]);
				freeAll(head);
				exit(EXIT_FAILURE);
	}
}
