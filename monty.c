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
	int i;
	int line_number;
	int fd;
	char *buf[256] = NULL;
	int read_return;

	if (argc == 1 || argc > 2) /* 0 or 1 for no arguments? */
		return (EXIT_SUCCESS);
	fd = open(argv[1], O_RDONLY);

	if (fd == -1)
		return (EXIT_FAILURE);
	read_return = read(fd, buf, sizeof(buf));

}

/**
 * open filename
 * read code in line by line
 * parse line
 * if there's a command
 * execute command
 * handle errors
 */