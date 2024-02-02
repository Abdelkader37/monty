#ifndef MONTY_H
#define MONTY_H

#define _GNU_SOURCE
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <stdarg.h>

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
        void (*f)(stack_t **stack, unsigned int line_number);
} instruction_t;

extern stack_t *head;
typedef void (*op_func)(stack_t **, unsigned int);

/*file operations*/
void open_f(char *file_name);
int tokenizer(char *buffer, int line_number, int format);
void file_reader(FILE *);
int len_chars(FILE *);
void fun_search(char *, char *, int, int);

/*Stack operations*/
stack_t *create_n(int n);
void free_n(void);
void print_sta(stack_t **, unsigned int);
void stack_add(stack_t **, unsigned int);
void que_add(stack_t **, unsigned int);

void fun_caller(op_func, char *, char *, int, int);

void prnt_up(stack_t **, unsigned int);
void pop_up(stack_t **, unsigned int);
void nonp(stack_t **, unsigned int);
void swap_n(stack_t **, unsigned int);

/*Math operations with nodes*/
void add_n(stack_t **, unsigned int);
void sub_n(stack_t **, unsigned int);
void div_n(stack_t **, unsigned int);
void mul_n(stack_t **, unsigned int);
void mod_n(stack_t **, unsigned int);

/*String operations*/
void prnt_char(stack_t **, unsigned int);
void prnt_str(stack_t **, unsigned int);
void rotationt(stack_t **, unsigned int);

/*Error hanlding*/
void print_err(int error_code, ...);
void print_errors(int error_code, ...);
void str_errors(int error_code, ...);
void rotationr(stack_t **, unsigned int);

#endif