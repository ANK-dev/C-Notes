/*
 * Exercise 5-13 - K&R 2nd ED
 * -- ANK-dev
 *
 * tail:  print the last n lines of its input
 */

#include <ctype.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define MAXLINES 100
#define MAXLEN   100

int readlines(char *lineptr[], int maxlines);
int argcheck(int argc, char **argv);
int getline(char s[], int lim);
void tail(char *lines[], int nlines, int n);

int main(int argc, char **argv)
{
	char *lines[MAXLINES];
	int check, nlines;

	check = argcheck(argc, argv);
	if (check == 0 && (nlines = readlines(lines, MAXLINES)) >= 0)
		tail(lines, nlines, 10);
	else if (check == 1 && (nlines = readlines(lines, MAXLINES)) >= 0)
		tail(lines, nlines, atoi(&(argv[1][1])));
	else {
		printf("Error or invalid argument\n");
		printf("tail - usage: [-n]\n"
		       "-n: [optional] print last 'n' lines of input (default = 10)\n");
		return -1;
	}

	return 0;
}

int argcheck(int argc, char **argv)
{
	int i, ncheck;

	if (argc == 1)
		/* no args */
		return 0;
	if (argc == 2) {
		/* check for optional argument */
		if (**++argv == '-') {
			i = 1;
			do {
				ncheck = isdigit((*argv)[i]);
			} while (ncheck && (*argv)[++i] != '\0');

			if (ncheck)
				/* 1 arg */
				return 1;
		}
	}

	/* error */
	return -1;

}

void tail(char *lines[], int nlines, int n)
{
	n = nlines < n ? nlines : n;
	while (n > 0) {
		printf("%s\n", lines[nlines - n--]);
	}
}

int readlines(char *lineptr[], int maxlines)
{
	int len, nlines;
	char line[MAXLEN];
	char *p;

	nlines = 0;
	while ((len = getline(line, MAXLEN)) > 0)
		if (nlines >= maxlines || (p = malloc(len)) == NULL) {
			printf("Buffer FULL\n");
			return -1;
		} else {
			line[len - 1] = '\0';  /* delete newline */
			strcpy(p, line);
			lineptr[nlines++] = p;
		}
	return nlines;
}

int getline(char s[], int lim)
{
  int c, i;

  for (i = 0; i < lim - 1 && (c = getchar()) != EOF && c != '\n'; i++)
    s[i] = c;
  if (c == '\n') {
    s[i++] = c;
  }
  s[i] = '\0';
  return i;
}