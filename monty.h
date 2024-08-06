#ifndef MONTY_H
#define MONTY_H
#include <stdlib.h>
#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>

/**
 * struct stack_s - doubly linked list representation of a stack (or queue)
 * @n: integer
 * @prev: points to the previous element of the stack (or queue)
 * @next: points to the next element of the stack (or queue)
 *
 * Description: doubly linked list node structure
 * for stack, queues, LIFO, FIFO
 */
typedef struct stack_s
{
	int n;
	struct stack_s *prev;
	struct stack_s *next;
} stack_t;
/**
 * struct instruction_s - opcode and its function
 * @opcode: the opcode
 * @f: function to handle the opcode
 *
 * Description: opcode and its function
 * for stack, queues, LIFO, FIFO
 */
typedef struct instruction_s
{
	char *opcode;
	int (*f)(stack_t **stack, unsigned int line_number);
} instruction_t;

extern char tokens;

int push(stack_t **, unsigned int);
int pall(stack_t **, unsigned int);
int call_op_func(char *, stack_t **, unsigned int);
int parse(char *);
void freeAll(stack_t **);
void exitAll(stack_t **, FILE *, unsigned int, int);
int isNum(char *);
int pint(stack_t **, unsigned int);
int pop(stack_t **, unsigned int);
int swap(stack_t **, unsigned int);
int add(stack_t **, unsigned int);
int nop(stack_t **, unsigned int);

#endif
