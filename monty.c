#include "monty.h"

/**
 * main - starts the monty interpreter
 * @argc: number of arguments
 * @argv: string array of arguments
 *
 * Return: EXIT_SUCCESS on success, EXIT_FAILURE otherwise
 */

int main(int argc, char *argv[])
{
	int i, read_return, parse_return;
	unsigned int line_number = 0;
	FILE *file;
	char *buf[256], **tokens = NULL;
	stack_t *list = NULL;

	if (argc == 1 || argc > 2) /* 0 or 1 for no arguments? */
	{
		printf("USAGE: monty file\n");
		/* freeAll */
		exit (EXIT_FAILURE);
	}
	file = fopen(argv[1], "r");

	if (file == NULL)
	{
		printf("Error: Can't open file %s", argv[1]);
		exit (EXIT_FAILURE);
	}

	while (fgets(buf, 256, file)) /* reads lines up to \n or 256 chars */
	{
		tokens = malloc (3 * sizeof(char *)); /* command, int, \n */
		if (tokens == NULL)
		{
			/* freeAll */
			printf("Error: malloc failed\n");
			exit(EXIT_FAILURE);
		}
		for (i = 0; i < 3; i++) /* prepopulate with NULL*/
			tokens[i] = NULL;

		parse_return = parse(buf);
		if (parse_return != 1)
			printf("didn't parse right, do stuff");
		get_op_func(tokens[0])(tokens[1], line_number);
		line_number++;
	}
	fclose(argv[1]);

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
	int buf_len = 0, token_count = 0;

	if (buf != NULL)
		buf_len = strlen(buf_len);

	token = strtok(buf, " ");
	if (token == NULL)
		return (0); /* no commands - add error message? */

	while (token != NULL) /* store tokens in memory */
	{
		if (token_count > 3)
			return (0); /* add error for too many instructions ? */
		(*tokens)[token_count] = token;
		token = strtok(NULL, " ");
		token_count++;
	}

	return (1); /* success */
}
