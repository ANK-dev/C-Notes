/**
 * Exercise 4-2 - K&R 2nd ED
 * =========================
 * > by ANK-dev
 *
 * atof (scientific notation support)
 * ----------------------------------
 */

#include <stdio.h>
#include <ctype.h>

#define MAXLINE 100		/* maximum input line length */

double atof(char s[]);
int getline(char line[], int max);

int main()
{
	char line[MAXLINE];

	printf("atof (scientific notation support)\n"
		   "==================================\n");
	printf("> converts string into double\n\n");

	printf("Numeric String: ");
	while (getline(line, MAXLINE) > 0) {
		printf("Double: %g\n\n", atof(line));
		printf("Numeric String: ");
	}
	return 0;
}

/* atof:  convert string s to double */
double atof(char s[])
{
	double val, dec_pow, pow;
	int i, sign, exp, expsign;

	/* skip white space */
	for (i = 0; isspace(s[i]); i++)
		;

	/* checks if sign exists */
	sign = (s[i] == '-') ? -1 : 1;
	if (s[i] == '+' || s[i] == '-')
		i++;

	/* sums each digit in base 10 */
	for (val = 0.0; isdigit(s[i]); i++)
		val = 10.0 * val + (s[i] - '0');

	/* checks if decimal part exists */
	if (s[i] == '.')
		i++;

	/* sum all decimal digits while calculating their corresponding power */
	for (dec_pow = 1.0; isdigit(s[i]); i++) {
		val = 10.0 * val + (s[i] - '0');
		dec_pow *= 10.0;
	}

	/* checks if E notation exists */
	if (s[i] == 'e' || s[i] == 'E')
		i++;

	/* cheks if exponent sign exists */
	expsign = (s[i] == '-') ? -1 : 1;
	if (s[i] == '-' || s[i] == '+')
		i++;

	/* sums each digit of the exponent in base 10 */
	for (exp = 0; isdigit(s[i]); i++)
		exp = 10 * exp + (s[i] - '0');

	/* calculates the power of 10 to the exponent */
	for (pow = 1.0; exp > 0; exp--)
		pow *= 10.0;

	/* returns the number divided by its power */
	return expsign == -1
		? (sign * val / dec_pow) / pow
		: (sign * val / dec_pow) * pow;
}


/* getline:  get line into s, return length */
int getline(char s[], int lim)
{
	int c, i;

	i = 0;
	while (--lim > 0 && (c=getchar()) != EOF && c != '\n')
		s[i++] = c;
	s[i] = '\0';
	return i;
}
