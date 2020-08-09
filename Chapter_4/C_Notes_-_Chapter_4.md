# The C Programming Language 2nd Edition — Anotações

## Chapter 4: Functions and Program Structure

### 4.1 Basics of Functions

Iremos escrever um programa que imprime cada linha de uma entrada que contém um
determinado "padrão" ou string de caracteres (similar ao funcionamento do
programa `grep`).

Dado o seguinte conjunto de linhas:

    Ah Love! could you and I with Fate conspire
    To grasp this sorry Scheme of Things entire,
    Would not we shatter it to bits -- and then
    Re-mould it nearer to the Heart's Desire!

o padrão de letras "`ould`" irá produzir a saída

    Ah Love! could you and I with Fate conspire
    Would not we shatter it to bits -- and then
    Re-mould it nearer to the Heart's Desire!

A tarefa se resume, basicamente, a três partes:

    while (_there's another line_)
        if (_the line contains the pattern_)
            _print it_

Subdividiremos o programa em pequenas funções; isto facilitará a implementação e
permitirá, caso necessário, a reutilização das funções em outros programas.

Utilizaremos as funções `getline` e `printf` para os papéis de
_there's another line_ e _print it_, respectivamente; note que esta
implementação de `getline` é ligeiramente diferente da implementada previamente
no Capítulo 1.

Para o caso de _the line contains a pattern_, iremos escrever a função
`strindex(s,t)` que retorna o índice, na string `s`, onde a string `t` começa,
ou `-1` caso `s` não contenha `t`. (A biblioteca padrão provê uma função
`strstr` que é similar a `strindex`, mas que retorna um ponteiro ao invés de um
índice).

Dada esta introdução, abaixo temos o programa em sua íntegra:

~~~ C
#include <stdio.h>
#define MAXLINE 1000    /* maximum input line length */

int getline(char line[], int max);
int strindex(char source[], char searchfor[]);

char pattern[] = "ould";    /* pattern to search for */

/* find all lines matching pattern */
main()
{
    char line[MAXLINE];
    int found = 0;

    while (getline(line, MAXLINE) > 0)
        if (strindex(line, pattern) >= 0) {
              printf("%s", line);
              found++;
        }
    return found;
}

/* getline:  get line into s, return length */
int getline(char s[], int lim)
{
    int c, i;

    i = 0;
    while (--lim > 0 && (c=getchar()) != EOF && c != '\n')
        s[i++] = c;
    if (c == '\n')
        s[i++] = c;
    s[i] = '\0';
    return i;
}

/* strindex:  return index of t in s, -1 if none */
int strindex(char s[], char t[])
{
    int i, j, k;

    for (i = 0; s[i] != '\0'; i++) {
        for (j=i, k=0; t[k]!='\0' && s[j]==t[k]; j++, k++)
            ;
        if (k > 0 && t[k] == '\0')
            return i;
    }
    return -1;
}
~~~

Cada definição de função tem a forma:

    _return-type_ _function-name_(_argument declarations_)
    {
        _declarations and statements_
    }

Várias partes podem estar ausentes; uma função mínima é:

    dummy() {}

que não faz nada e não retorna nada. Uma função faz-nada como esta as vezes é
útil como um placeholder durante o desenvolvimento de um programa. Se o tipo de
retorno é omitido, `int` é assumido.

Um progrma é apenas um conjunto de definições de variáveis e funções. A
comunicação entre funções ocorre através de argumentos e valores retornados
pelas funções, e por variáveis externas. Funções podem aparecer em qualquer
ordem no arquivo fonte, e o programa fonte pode ser dividido em múltiplos
arquivos, desde que nenhuma função seja dividida.

A instrução `return` é o mecanismo para retornar um valor da função chamada para
o seu chamante. Qualquer expressão pode aparecer após `return`:

    return _expression_;

A _expression_ será convertida para o tipo do retorno da função se necessário.
Parênteses são usados com frequência ao redor da _expression_, porém são
opcionais.

A função chamante é livre para ignorar o valor retornado. Além disso, não é
necessário haver uma expressão após `return`; neste caso, nenhum valor é
retornado ao chamante. O controle tamém retorna ao chamante sem nenhum valor se
a execução "cai além do final" da função ao chegar no fecha chaves direito. Não
é ilegal, mas provavelmente é um sinal de problemas, se a função retorna um
valor de um lugar e nenhum valor de outro. Em qualquer caso, se uma função não
retornar um valor, seu "valor" com certeza será lixo.

O programa de busca de padrões retorna um status a partir da `main`, o número de
correspondências encontradas. Este valor está disponível para uso pelo ambiente
que chamou o programa.

<!-- ENXUGAR SEÇÃO ACIMA -->

--------------------------------------------------------------------------------

Para a compilação de um programa C em um sistema UNIX, usa-se o comando `cc`
previamente mencionado no capítulo 1. Dado que as funções do programa estejam em
arquivos separados `main.c`, `getline.c`, e `strindex.c`, o comando:

    cc main.c getline.c strindex.c

compila os três arquivos, gerando como saída três arquivos de objeto compilado:
`main.o`, `getline.o`, e `strindex.o`; estes são linkados em um arquivo
executável com nome padrão de `a.out`. Caso haja um erro durante a compilação em
um dos arquivos, no `main.c`, por exemplo, este arquivo pode ser recompilado
individualmente em conjunto com os arquivos de objeto anteriores, com o comando:

    cc main.c getline.o strindex.o

--------------------------------------------------------------------------------

#### Exercícios 4.1

* [Exercise 4-1](./Exercise_4-01.c)

--------------------------------------------------------------------------------