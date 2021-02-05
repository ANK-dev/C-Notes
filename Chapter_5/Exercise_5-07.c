/*
 * Exercise 5-07 - K&R 2nd ED
 * -- ANK-dev
 *
 * readlines:  fixed array storage
 */

#include <stdio.h>
#include <string.h>

#define MAXLINES  5000  /* max #lines to be sorted */
#define MAXLEN    1000  /* max length of any input line */
#define MAXSTORE 10000  /* max combined storage for all input lines */

int readlines(char *lineprt[], char *lnstore, int maxlines);
void writelines(char *lineptr[], int nlines);

int getline(char *, int);
void qsort(char *v[], int left, int right);
void swap(char *v[], int i, int j);

/* sort input lines */
int main()
{
	int nlines;                 /* number of input lines */
	char *lineptr[MAXLINES];    /* pointers to text lines */
	char linestore[MAXSTORE];   /* storage array */

	if ((nlines = readlines(lineptr, linestore, MAXLINES)) >= 0) {
		qsort(lineptr, 0, nlines - 1);
		writelines(lineptr, nlines);
		return 0;
	} else {
		printf("error: input too big to sort\n");
		return 1;
	}
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

/* readlines:  read input lines */
int readlines(char *lineptr[], char *lnstore, int maxlines)
{
	int len, nlines;
	char line[MAXLEN];
	char *p = lnstore;               /* current position in storage */
	char *lnend = lnstore + MAXSTORE;    /* end position of storage */

	nlines = 0;
	while ((len = getline(line, MAXLEN)) > 0)
		if (nlines >= maxlines || p + len > lnend )
			return -1;
		else {
			line[len - 1] = '\0';  /* delete newline */
			strcpy(p, line);
			lineptr[nlines++] = p;
			p += len;  /* advance pointer to next empty section */
		}
	return nlines;
}

/* writelines:  write output lines */
void writelines(char *lineptr[], int nlines)
{
	while (nlines-- > 0)
		printf("%s\n", *lineptr++);
}

/* qsort:  sort v[left]...v[right] into increasing order */
void qsort(char *v[], int left, int right)
{
	int i, last;

	if (left >= right)   /* do nothing if array contains */
		return;          /* fewer than two elements */
	swap(v, left, (left + right)/2);
	last = left;
	for (i = left + 1; i <= right; i++)
		if (strcmp(v[i], v[left]) < 0)
			swap(v, ++last, i);
	swap(v, left, last);
	qsort(v, left, last - 1);
	qsort(v, last + 1, right);
}

/* swap:  interchange v[i] and v[j] */
void swap(char *v[], int i, int j)
{
	char *temp;

	temp = v[i];
	v[i] = v[j];
	v[j] = temp;
}