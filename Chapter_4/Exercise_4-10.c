/**
 * Exercise 4-10 - K&R 2nd ED
 * ==========================
 * > by ANK-dev
 *
 * RPN calculator (getline support)
 * --------------------------------
 */

#include <stdio.h>
#include <stdlib.h>   /* for atof() */
#include <ctype.h>
#include <math.h>
#include <string.h>   /* for strcmp() */

#define MAXLINE 1000
#define MAXOP    100   /* max size of operand or operator */
#define MAXVAL   100   /* maximum depth of val stack */
#define BUFSIZE  100   /* max size of buffer for ungetch */

#define NUMBER         '0'   /* signal that a number was found   */
#define VARIABLE_READ  'a'   /* signal that a variable was found */
#define VARIABLE_WRITE '<'   /* signal to write a value into a variable */
#define ERROR          '&'   /* signal that a command is invalid */

int getop(char s[]);
int getline(char s[], int lim);
void printres(double f);

void push(double f);
double pop(void);
double top(void);

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

void var_read(char var);
void var_write(char var);

void duplicate(void);
void swap(void);
void clear(void);

int getch(void);
void ungetch(int c);

char line[MAXLINE];
int  line_i;

double val[MAXVAL];       /* value stack */
double last_val = 0.0;

char buf[BUFSIZE];        /* buffer for ungetch */
int  sp   = 0;            /* next free stack position */
int  bufp = 0;            /* next free position in buf */

char var_arr[26] = {0};   /* variables array (a-z) */

/* reverse Polish calculator */
int main()
{
	int type;
	int pop_res = 1;    /* controls popping for the current input line */
	char s[MAXOP];      /* input line */

	while (getline(line, MAXLINE) != 0) {
		line_i = 0;
		while ((type = getop(s)) != '\0') {
			switch (type) {
				case NUMBER:
					push(atof(s));
					break;
				case VARIABLE_READ:
					var_read(s[0]);
					break;
				case VARIABLE_WRITE:
					var_write(s[0]);
					pop_res = 0;
					break;
				case '_':   /* print the most recently printed value */
					printres(last_val);
					pop_res = 0;
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
				case '#':   /* print top element of stack w/o popping it */
					printres(top());
					pop_res = 0;
					break;
				case '@':   /* duplicate top element of stack */
					duplicate();
					pop_res = 0;
					break;
				case '$':   /* swap the top two elements of stack */
					swap();
					pop_res = 0;
					break;
				case '!':   /* clear the stack */
					clear();
					pop_res = 0;
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
				case '\n':  /* print top of the stack if at newline */
					if (pop_res) printres(pop());
					pop_res = 1;
					break;
				case ERROR:   /* invalid command */
					printf("\terror: invalid command\n");
					break;
				default:
					printf("\terror: unknown command %s\n", s);
					break;
			}
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

/* write:  writes values to variables */
void var_write(char var)
{
	var_arr[var - 'a'] = pop();
	printf("\tstack value written into %c\n", var);
}

void var_read(char var)
{
	push(var_arr[var - 'a']);
	var_arr[var - 'a'] = 0;
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
	int i, j, c;
	char math_buf[5], math_op[5][4] = {"sin", "cos", "tan", "exp", "pow"};

	i = 0, j = 0;

	/* skips all whitespace */
	while ((s[i] = c = line[line_i++]) == ' ' || c == '\t')
		;

	/* terminates string in case there's no other characters */
	s[i + 1] = '\0';

	/* if it's a lower case char (a-z) it's either a variable or a math
	   operation */
	if (isalpha(c) && islower(c)) {
		math_buf[j] = c;
		/* count and store sequence of chars */
		while ((c = line[line_i++])) {
			if (!isalpha(c)) {
				line_i--;
				break;
			}
			math_buf[++j] = c;
			/* if 'j' index is larger than 2 (3 chars) then it's not a valid
			   math operation */
			if (j > 2)
				break;
		}
		math_buf[++j] = '\0';

		/* 1 char = variable */
		if (j == 1) {
			/* if var is at end of line, pop stack and store into var */
			if ((c = line[line_i++]) == '\n' && sp != 0) {
				line_i--;
				return VARIABLE_WRITE;
			}
			/* else read value stored into var */
			line_i--;
			return VARIABLE_READ;
		}
		/* 3 chars = math operation */
		if (j == 3) {
			for (j = 0; j < 5; j++) {
				/* checks if buffer corresponds to valid math operation */
				/* NOTE: 'strcmp' returns 0 when strings are equal */
				if (strcmp(math_buf, math_op[j]) == 0) {
					/*
					 * returns the first letter (in uppercase) of the
					 * corresponding math operation (sin = 'S', cos = 'C', etc.)
					 */
					return toupper(math_op[j][0]);
				}
			}
		}

		/* unknown/invalid operation */
		return ERROR;

	}

	/* check if operators are binary or unary (for negative number support) */
	if (c == '+' || c == '-') {
		if (isdigit(c = line[line_i++])) {    /* if a digit follows, then it's unary */
			line_i--;
		} else {                       /* else, it's an binary operator */
			line_i--;
			c = s[i];
			return c;
		}
	}

	/* other operators */
	if (!isdigit(c) && c != '.')
		return c;        /* not a number */

	/* collect integer part */
	if (isdigit(c))
		while (isdigit(s[++i] = c = line[line_i++]))
			;

	/* collect fraction part */
	if (c == '.')
		while (isdigit(s[++i] = c = line[line_i++]))
			;

	/* terminate string */
	s[i] = '\0';

	if (c != EOF)
		line_i--;

	return NUMBER;
}

/* getline:  get line into s, return length */
int getline(char s[], int lim)
{
    int c, i;

    i = 0;
    while (--lim > 0 && (c = getchar()) != EOF && c != '\n')
        s[i++] = c;
    if (c == '\n')
        s[i++] = c;
    s[i] = '\0';

    return i;
}

/* printres:  prints the formatted result of the calculation */
void printres(double f)
{
	printf("\t%.8g\n", f);
	last_val = f;
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