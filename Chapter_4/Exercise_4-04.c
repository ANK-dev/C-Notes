/**
 * Exercise 4-4 - K&R 2nd ED
 * =========================
 * > by ANK-dev
 *
 * RPN calculator (top, duplicate, swap)
 * -------------------------------------
 */

#include <stdio.h>
#include <stdlib.h>   /* for atof() */
#include <ctype.h>

#define MAXOP   100   /* max size of operand or operator */
#define NUMBER  '0'   /* signal that a number was found */
#define MAXVAL  100   /* maximum depth of val stack */
#define BUFSIZE 100

int getop(char s[]);
void printres(double f);

void push(double f);
double pop(void);
double top(void);

void sum(void);
void subtract(void);
void multiply(void);
void divide(void);
void modulo(void);

void duplicate(void);
void swap(void);
void clear(void);

int getch(void);
void ungetch(int c);

int sp = 0;           /* next free stack position */
double val[MAXVAL];   /* value stack */
char buf[BUFSIZE];    /* buffer for ungetch */
int  bufp = 0;        /* next free position in buf */

/* reverse Polish calculator */
int main()
{
	int type, pop_res = 1;
	char s[MAXOP];

	while ((type = getop(s)) != EOF) {
		switch (type) {
			case NUMBER:
				push(atof(s));
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
			case '%':
			/* modulo (remainder) */
				modulo();
				break;
			case '#':
			/* Print top element of stack w/o popping it */
				printres(top());
				pop_res = 0;    /* disables popping for current input line */
				break;
			case '@':
			/* Duplicate top element of stack */
				duplicate();
				pop_res = 0;
				break;
			case '$':
			/* Swap the top two elements of stack */
				swap();
				pop_res = 0;
				break;
			case '!':
			/* Clear the stack */
				clear();
				pop_res = 0;
				break;
			case '\n':
			/* print top of the stack if at newline */
				if (pop_res) printres(pop());
				pop_res = 1;    /* reenables popping for next line */
				break;
			default:
				printf("\terror: unknown command %s\n", s);
				break;
		}
	}
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

/* top:  print top element of the stack w/o popping it */
double top(void)
{
	if (sp > 0)
		return val[sp - 1];
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
/* duplicate:  duplicate the top element of the stack */
void duplicate(void)
{
	printf("\tstack top duplicated\n");
	push(top());
}

/* swap:  swap the top two elements of the stack */
void swap(void)
{
	int i;
	double aux;

	if (sp < 2)
		printf("\terror: not enough elements to swap (< 2)");
	else {
		i = sp - 1;    /* top element index */
		aux = val[i];
		val[i] = val[i-1];
		val[i-1] = aux;
		printf("\ttop two elements swaped\n");
	}
}

void clear(void)
{
	/* sets stack position back to the beggining */
	sp = 0;
	printf("\tstack cleared\n");
}

/* getop:  get next operator or numeric operand */
int getop(char s[])
{
	int i, c;

	while ((s[0] = c = getch()) == ' ' || c == '\t')
		;

	s[1] = '\0';
	i = 0;

	if (!isdigit(c) && c != '.') {
		if (c == '+' || c == '-') {     /* check if unary */
			if (isdigit(c = getch())) { /* if a digit follows then it's unary */
				ungetch(c);
			} else {   	                /* else, it's an operator */
				ungetch(c);
				c = s[0];
				return c;   /* not a number */
			}
		} else {
			return c;       /* not a number */
		}
	}

	if (isdigit(c))   /* collect integer part */
		while (isdigit(s[++i] = c = getch()))
			;

	if (c == '.')     /* collect fraction part */
		while (isdigit(s[++i] = c = getch()))
			;

	s[i] = '\0';

	if (c != EOF)
		ungetch(c);

	return NUMBER;
}

/* printres:  prints the formatted result of the calculation */
void printres(double f)
{
	printf("\t%.8g\n", f);
}

/* getch:  get a (possibly pushed back) character */
int getch(void)
{
	return (bufp > 0) ? buf[--bufp] : getchar();
}

/* ungetch:  push character back on input */
void ungetch(int c)
{
	if (bufp >= BUFSIZE)
		printf("\tungetch: too many characters\n");
	else
		buf[bufp++] = c;
}