/*
 * Exercise 5-10 - K&R 2nd ED
 * -- ANK-dev
 *
 * RPN Calculator from the command line (argc & **argv support)
 */

#include <stdio.h>
#include <stdlib.h>   /* for atof() */
#include <ctype.h>
#include <math.h>
#include <string.h>   /* for strcmp() */

#define MAXOP   100   /* max size of operand or operator */
#define MAXVAL  100   /* maximum depth of val stack */
#define BUFSIZE 100   /* max size of buffer for ungetch */

#define NUMBER '0'   /* signal that a number was found   */
#define ERROR  '&'   /* signal that a command is invalid */

int getop(char *argv[]);
void printres(double f);

void push(double f);
double pop(void);

void sum(void);
void subtract(void);
void multiply(void);
void divide(void);
void modulo(void);

void mathSin(void);
void mathCos(void);
void mathTan(void);
void mathExp(void);
void mathPow(void);

int sp = 0;               /* next free stack position */
double val[MAXVAL];       /* value stack */

/* reverse Polish calculator */
int main(int argc, char *argv[])
{
	char **lastarg = argv + argc;    /* final argv index */
	int type;

	while (++argv < lastarg){
		type = getop(argv);
		switch (type) {
			case NUMBER:
				push(atof(*argv));
				break;
			case '+':
				sum();
				break;
			case '*':
				multiply();
				break;
			case '-':
				subtract();
				break;
			case '/':
				divide();
				break;
			case '%':   /* modulo (remainder) */
				modulo();
				break;
			case 'S':   /* 'S'ine */
				mathSin();
				break;
			case 'C':   /* 'C'osine */
				mathCos();
				break;
			case 'T':   /* 'T'angent */
				mathTan();
				break;
			case 'E':   /* 'E'xponetial */
				mathExp();
				break;
			case 'P':   /* 'P'ower */
				mathPow();
				break;
			case ERROR:   /* invalid command */
				printf("\terror: invalid command\n");
				break;
			default:
				printf("\terror: unknown command %s\n", *argv);
				break;
		}
	}
	printres(pop());
	return 0;
}


/* push:  push f onto value stack */
void push(double f)
{
	if (sp < MAXVAL)
		val[sp++] = f;
	else
		printf("\terror: stack full, can't push %g\n", f);
}

/* pop:  pop and return top value from stack */
double pop(void)
{
	if (sp > 0)
		return val[--sp];
	else {
		printf("\terror: stack empty\n");
		return 0.0;
	}
}

/* sum:  sums the top two elements of the stack */
void sum(void)
{
	push(pop() + pop());
}

/* subtract:  subtracts the top two elements of the stack */
void subtract(void)
{
	double op2;

	op2 = pop();
	push(pop() - op2);
}

/* multiply:  multiplies the top two elements of the stack */
void multiply(void)
{
	push(pop() * pop());
}

/* divide:  divides the top two elements of the stack */
void divide(void)
{
	double op2;

	op2 = pop();
	if (op2 != 0.0)
		push(pop() / op2);
	else
		printf("\terror: zero divisor\n");
}

/* modulo:  division remainder of the top two elements of the stack */
void modulo(void)
{
	double op1, op2;

	op2 = pop();
	op1 = pop();
	if (op2 != 0.0)
		push(op1 - op2 * (int)(op1/op2));
	else
		printf("\terror: zero divisor\n");

}

void mathSin(void)
{
	push(sin(pop()));
}

void mathCos(void)
{
	push(cos(pop()));
}

void mathTan(void)
{
	push(tan(pop()));
}

void mathExp(void)
{
	push(exp(pop()));
}

void mathPow(void)
{
	double op2;

	op2 = pop();
	push(pow(pop(), op2));
}

int getop(char *argv[])
{
	unsigned int j;
	char *math_op[] = {"sin", "cos", "tan", "exp", "pow"};

	/* check for math operators */
	for (j = 0; j < sizeof(math_op)/sizeof(math_op[0]); j++)
		if (strcmp(*argv, math_op[j]) == 0) {
			return toupper(math_op[j][0]);
		}

	/* binary operators */
	if (strcmp(*argv, "+") == 0 || strcmp(*argv, "-") == 0)
		return **argv;

	/* unary operators */
	if (**argv == '+' || **argv == '-') {
		return NUMBER;
	}

	/* other operators */
	if (!isdigit(**argv) && **argv != '.')
		return **argv;    /* not a number */

	/* collect integer and fraction parts */
	return NUMBER;
}

/* printres:  prints the formatted result of the calculation */
void printres(double f)
{
	printf("\t%.8g\n", f);
}