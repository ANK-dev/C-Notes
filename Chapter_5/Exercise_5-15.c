/*
 * Exercise 5-15 - K&R 2nd ED
 * -- ANK-dev
 *
 * qcksort:  fold '-f' flag support
 *
 * The example presented in the book needed some modifications to work on modern
 * compilers.
 *
 * The casting of a function pointer to another type and its subsequent calling
 * is undefined behavior (UB) according to more modern C standards (C11). For
 * compliance, the function (strcmp/numcmp) passed as argument should be cast
 * back to their original type before it's called.
 *
 * The only reason this example works without uncasting is because, according to
 * the C standard (§6.2.5):
 *
 *     "A pointer to void shall have the same representation and alignment
 *      requirements as a pointer to a character type."
 *
 * Relying on this behavior is dangerous, as the casting & calling of other
 * function types WILL result in UB.
 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

#define MAXLINES 5000            /* max #lines to be sorted      */
#define MAXLEN   1000            /* max length of anu input line */

enum flags_e {                   /* flag states */
	NUMERIC = 1 << 0,
	REVERSE = 1 << 1,
	FOLD    = 1 << 2
};

char *lineptr[MAXLINES];         /* pointers to text lines */

void writelines(char *lineptr[], int nlines);
int readlines(char *lineptr[], int nlines, int fold);
int getline(char s[], int lim, int fold);
int argchk(int argc, char *argv[], enum flags_e *flags, char *valid_flags[]);

void qcksort(void *lineptr[], int left, int right, int reverse,
             int (*comp)(void *, void *));
void swap(void *v[], int, int);
int numcmp(const char *, const char *);

/* sort input lines */
int main(int argc, char *argv[])
{
	int nlines;                                 /* number of input lines read */
	enum flags_e flags = 0;                     /* initial flags              */

	char *valid_flags[] = {                     /* argument flags             */
		"-n", "-r", "-f", "\0"
	};

	if (!argchk(argc, argv, &flags, valid_flags)) {
		printf("Invalid flags\n");
		return 1;
	}
	if ((nlines = readlines(lineptr, MAXLINES, flags & FOLD)) >= 0) {
		qcksort((void **) lineptr, 0, nlines-1, flags & REVERSE,
		        (int (*)(void *, void *))(flags & NUMERIC ? numcmp : strcmp));
		writelines(lineptr, nlines);
		return 0;
	} else {
		printf("input too big to sort\n");
		return 2;
	}
}

/* qcksort:  sort v[left]...v[right] into increasing order */
void qcksort(void *v[], int left, int right, int reverse,
             int (*comp)(void *, void *))
{
	int i, last;

	if (left >= right)           /* do nothing if array contains */
		return;                  /* fewer than two elements      */
	swap(v, left, (left + right)/2);
	last = left;
	for (i = left + 1; i <= right; i++)
		if (reverse ? (*comp)(v[i], v[left]) > 0 : (*comp)(v[i], v[left]) < 0)
			swap(v, ++last, i);
	swap(v, left, last);
	qcksort(v, left, last-1, reverse, comp);
	qcksort(v, last + 1, right, reverse, comp);
}

/* numcmp:  compare s1 and s2 numerically */
int numcmp(const char *s1, const char *s2)
{
	double v1, v2;

	v1 = atof(s1);
	v2 = atof(s2);
	if (v1 < v2)
		return -1;
	else if (v1 > v2)
		return 1;
	else
		return 0;
}

void swap(void *v[], int i, int j)
{
	void *temp;

	temp = v[i];
	v[i] = v[j];
	v[j] = temp;
}

/* writelines:  write output lines */
void writelines(char *lineptr[], int nlines)
{
	while (nlines-- > 0)
		printf("%s\n", *lineptr++);
}

/* readlines:  read input lines */
int readlines(char *lineptr[], int maxlines, int fold)
{
	int len, nlines;
	char line[MAXLEN];
	char *p;

	nlines = 0;
	while ((len = getline(line, MAXLEN, fold)) > 0)
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

int getline(char s[], int lim, int fold)
{
	int c, i;

	for (i = 0; i < lim - 1 && (c = getchar()) != EOF && c != '\n'; i++)
		if (fold)
			s[i] = tolower(c);
		else
			s[i] = c;
	if (c == '\n') {
		s[i++] = c;
	}
	s[i] = '\0';
	return i;
}

int argchk(int argc, char *argv[], enum flags_e *flags, char *valid_flags[])
{
	/* enter loop first */
	int chk = 1;

	/* no args */
	if (argc == 1)
		return 1;

	/* check for optional arguments */
	if (argc > 1) {
		int i, j;
		for (i = 1; i < argc && chk; i++) {
			chk = 0;
			for (j = 0; *valid_flags[j] != '\0'; j++) {
				/* check for already used flags */
				if (chk || (*flags & (1 << j)))
					continue;

				/* check if argument is a valid flag */
				chk = strcmp(argv[i], valid_flags[j]) == 0;

				/* if flag is valid, mark it as used */
				if (chk) {
					/* enable each flag in order (2^j):
					   1 = NUMERIC, 2 = REVERSE */
					*flags |= 1 << j;
				}
			}
		}
		/* all flags are valid */
		if (chk)
			return 1;
	}

	/* invalid flags */
	return 0;
}