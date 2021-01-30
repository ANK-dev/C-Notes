/*
 * Exercise 5-02 - K&R 2nd ED
 * -- ANK-dev
 *
 * getfloat:  get next float from input into *pn
 */

#include <stdio.h>
#include <ctype.h>

#define BUFSIZE 10

int  getfloat(float *pn);
int  getch(void);
void ungetch(int);

char buf[BUFSIZE];  /* buffer for ungetch */
int  bufp = 0;      /* next free position in buf */

int main()
{
	int i, gi, n;
	float array[BUFSIZE];

	/* collect digits until EOF or invalid symbol */
	for (n = 0; n < BUFSIZE && (gi = getfloat(&array[n])) != EOF && gi != 0; n++)
		;

	printf("a[%d] = {", n);
	for (i = 0; i < n - 1; i++)
		printf("%f, ", array[i]);
	printf("%f}\n", array[i]);
	return 0;
}

/* getfloat:  get next float from input into *pn */
int getfloat(float *pn)
{
	int c, sign, temp;
	float power;

	while (isspace(c = getch()))  /* skip white space */
		;
	if (!isdigit(c) && c != EOF && c != '+' && c != '-' && c != '.') {
		ungetch(c);               /* it's not a number */
		return 0;
	}
	sign = (c == '-') ? -1 : 1;
	if (c == '+' || c == '-') {
		temp = c;                 /* remember sign char */
		if (!isdigit(c = getch())) {
			if (c != EOF)
				ungetch(c);      /* push back non-digit */
			ungetch(temp);       /* push back sign char */
			return 0;            /* return 'not a number' signal */
		}
	}
	for (*pn = 0.0; isdigit(c); c = getch())
		*pn = 10.0 * *pn + (c - '0');  /* integer part */
	if (c == '.')
		c = getch();
	for (power = 1.0; isdigit(c); c = getch()) {
		*pn = 10.0 * *pn + (c - '0');  /* fractional part */
		power *= 10.0;
	}
	*pn *= sign / power;
	if (c != EOF)
		ungetch(c);
	return c;
}

int getch(void) /* get a (possibly pushed back) character */
{
	return (bufp > 0) ? buf[--bufp] : getchar();
}

void ungetch(int c) /* push character back on input */
{
	if (bufp >= BUFSIZE)
		printf("ungetch: too many characters\n");
	else
		buf[bufp++] = c;
}