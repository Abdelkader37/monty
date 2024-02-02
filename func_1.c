#include "monty.h"

#include "monty.h"

/**
 * open_f - opens a file
 * @file_name: the file namepath
 * Return: void
 */

void open_f(char *file_name)
{
	FILE *fd = fopen(file_name, "r");

	if (file_name == NULL || fd == NULL)
		print_err(2, file_name);

	    file_reader(fd);
	fclose(fd);
}


/**
 * file_reader - reads a file
 * @fd: pointer to file descriptor
 * Return: void
 */

void file_reader(FILE *fd)
{
	int n, frmat = 0;
	char *bufer = NULL;
	size_t len = 0;

	for (n = 1; getline(&bufer, &len, fd) != -1; n++)
	{
		frmat = tokenizer(bufer, n, frmat);
	}
	free(bufer);
}


/**
 * tokenizer - Separates each line into tokens to determine
 * which function to call
 * @buffer: line from the file
 * @n: line number
 * @format:  storage format. If 0 Nodes will be entered as a stack.
 * if 1 nodes will be entered as a queue.
 * Return: Returns 0 if the opcode is stack. 1 if queue.
 */

int tokenizer(char *buffer, int n, int format)
{
	char *opcode, *v;
	const char *delim = "\n ";

	if (buffer == NULL)
		print_err(4);

	opcode = strtok(buffer, delim);
	if (opcode == NULL)
		return (format);
	v = strtok(NULL, delim);

	if (strcmp(opcode, "stack") == 0)
		return (0);
	if (strcmp(opcode, "queue") == 0)
		return (1);

	fun_search(opcode, v, n, format);
	return (format);
}

/**
 * fun_search - find the appropriate function for the opcode
 * @opcode: opcode
 * @value: argument of opcode
 * @format:  storage format. If 0 Nodes will be entered as a stack.
 * @ln: line number
 * if 1 nodes will be entered as a queue.
 * Return: void
 */
void fun_search(char *opcode, char *value, int ln, int format)
{
	int i;
	int f;

	instruction_t func_list[] = {
		{"push", stack_add},
		{"pall", print_sta},
		{"pint", prnt_up},
		{"pop", pop_up},
		{"nop", nonp},
		{"swap", swap_n},
		{"add", add_n},
		{"sub", sub_n},
		{"div", div_n},
		{"mul", mul_n},
		{"mod", mod_n},
		{"pchar", prnt_char},
		{"pstr", prnt_str},
		{"rotl", rotationt},
		{"rotr", rotationr},
		{NULL, NULL}
	};

	if (opcode[0] == '#')
		return;

	for (f = 1, i = 0; func_list[i].opcode != NULL; i++)
	{
		if (strcmp(opcode, func_list[i].opcode) == 0)
		{
			fun_caller(func_list[i].f, opcode, value, ln, format);
			f = 0;
		}
	}
	if (f == 1)
		print_err(3, ln, opcode);
}


/**
 * fun_caller - Calls the required function.
 * @func: Pointer to the function that is about to be called.
 * @op: string representing the opcode.
 * @val: string representing a numeric value.
 * @ln: line numeber for the instruction.
 * @format: Format specifier. If 0 Nodes will be entered as a stack.
 * if 1 nodes will be entered as a queue.
 */
void fun_caller(op_func func, char *op, char *val, int ln, int format)
{
	stack_t *node;
	int f;
	int x;

	f = 1;
	if (strcmp(op, "push") == 0)
	{
		if (val != NULL && val[0] == '-')
		{
			val = val + 1;
			f = -1;
		}
		if (val == NULL)
			print_err(5, ln);
		for (x = 0; val[x] != '\0'; x++)
		{
			if (isdigit(val[x]) == 0)
				print_err(5, ln);
		}
		node = create_n(atoi(val) * f);
		if (format == 0)
			func(&node, ln);
		if (format == 1)
			que_add(&node, ln);
	}
	else
		func(&head, ln);
}