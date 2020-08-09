# The C Programming Language 2nd Edition — Anotações

## Chapter 3: Control Flow

### 3.1 Statements and Blocks

Qualquer expressão vira uma _instrução_ (_statement_), quando seguido de um
ponto-e-vírgula:

~~~ C
x = 0;
i++;
printf(…);
~~~

Chaves (`{` e `}`) são utilizadas para agrupar declarações e instruções em uma
_instrução composta_ (_compound statement_) ou _bloco_, de maneira que estas são
sintaticamente equivalentes a uma única instrução.

### 3.2 If-Else

A instrução `if-else` é usada para expressar decisões:

    if (expression)
        statement₁
    else
        statement₂

o `else` é opcional. A _expression_ é avaliada e, caso **verdadeira** (valor
não-zero), o _statement₁_ é executado. Se _expression_ for **falsa** (valor
zero) e uma seção `else` existir, somente _statement₂_ é executado.

Como um `if` teste o valor numérico da expressão é possível escrever

    if (expression)

em vez de

    if (expression != 0)

Em alguns casos essa simplificação é mais natural de ser lida, em outros, pode
tornar o código difícil de ser compreendido.

--------------------------------------------------------------------------------

**OBS**: Deve-se ter cuidado ao se escrever sequências de `if` aninhados que não
possuam um `else` correspondente. Situações onde as chaves são omitidas podem
levar a ambiguidade de interpretação como no exemplo abaixo:

~~~ C
if (n >= 0)
    for (i = 0; i < n; i++)
        if (s[i] > 0) {
            printf("…");
            return i;
        }
else        /* WRONG */
  printf("error -- n is negative\n");
~~~

Apesar de a indentação mostrar que o `else` deve ser a alternativa do `if` mais
externo, o compilador irá associá-lo ao `if` interno. Estes tipos de bugs
costumam ser bastante difíceis de encontrar, portanto recomenda-se utilizar
chaves sempre quando houver `if`s aninhados.

### 3.3 Else-If

A construção

    if (_expression_)
        _statement_
    else if (_expression_)
        _statement_
    else if (_expression_)
        _statement_
    else if (_expression_)
        _statement_
    else
        _statement_

ocorre com bastante frequência, pois é a maneira mais geral de se escrever uma
decisão multi-caminho. O seu funcionamento é bastante simples:

* cada _expression_ é avaliada em ordem:
  - caso **verdadeira**: o _statement_ associado é executado, e a cadeia de
    avaliações é encerrada.
  - caso **falsa**: a próxima _expression_ é avaliada.

a parte `else` é responsável pelo caso "nenhuma das anteriores", onde nenhuma
das outras condições foi satisfeita. Caso não haja nenhuma ação a ser tomada por
padrão, o `else` pode ser omitido.

Como demonstração de uma decisão de três caminhos, temos um algoritmo de busca
binária como exemplo abaixo:

~~~ C
/* binsearch:  find x in v[0] <= v[1] <= ... <= v[n-1] */
int binsearch(int x, int v[], int n)
{
    int low, high, mid;

    low = 0;
    high = n - 1;
    while (low <= high) {
        mid = (low+high) / 2;
        if (x < v[mid])
            high = mid - 1;
        else if (x > v[mid])
            low = mid + 1;
        else      /* found match */
            return mid;
    }
    return -1;    /* no match */
}
~~~

--------------------------------------------------------------------------------

#### Exercícios 3.3

* [Exercise 3-1](./Exercise_3-01.c)

--------------------------------------------------------------------------------

### 3.4 Switch

A instrução `switch` é uma decisão multi-caminho que testa se uma expressão é
igual a um dentre diversos valores _constantes_ inteiros em cada `case`,
ramificando-se conformemente.

    switch (_expression_) {
        case _const-expr_:   _statements_
        case _const-expr_:   _statements_
        default:    _statements_
    }

caso a _expression_ não corresponda a nenhum `case`, o caso `default` é
executado (o mesmo é opcional).

Abaixo temos o mesmo programa de contagem de dígitos, espaço em branco, e
caracteres do Capítulo 1, porém reescrito para utilizar um `switch`:

~~~ C
#include <stdio.h>

main()  /* count digits, white space, others */
{
    int c, i, nwhite, nother, ndigit[10];

    nwhite = nother = 0;
    for (i = 0; i < 10; i++)
        ndigit[i] = 0;
    while ((c = getchar()) != EOF) {
        switch (c) {
        case '0': case '1': case '2': case '3': case '4':
        case '5': case '6': case '7': case '8': case '9':
            ndigit[c-'0']++;
            break;
        case ' ':
        case '\n':
        case '\t':
            nwhite++;
            break;
        default:
            nother++;
            break;
        }
    }
    printf("digits =");
    for (i = 0; i < 10; i++)
        printf(" %d", ndigit[i]);
    printf(", white space = %d, other = %d\n",
        nwhite, nother);
    return 0;
}
~~~

A instrução `break` causa uma saída imediata do `switch`. Essa mesma instrução
pode ser usada para realizar uma saída prematura de laços `while`, `for`, e
`do`.

Caso o `break` esteja ausente, a execução segue o princípio do _fallthrough_,
onde, após o final da execução de um caso, o próximo é executado. Os casos dos
dígitos acima fazem uso desse comportamento.

--------------------------------------------------------------------------------

**OBS**: Deve-se ter atenção ao usar o `switch` — caso um `break` seja esquecido
ao final de um caso, o _fallthrough_ irá executar o próximo! Isso pode resultar
em comportamentos inesperados e indesejados.

--------------------------------------------------------------------------------

#### Exercícios 3.4

* [Exercise 3-2](./Exercise_3-02.c)

--------------------------------------------------------------------------------

### 3.6 Loops—While and For

O laço `while` possui a seguinte estrutura:

    while (_expression_)
        _statement_

onde _expression_ é avaliada. Caso **verdadeira** (não-zero), _statement_ é
executado. A _expression_ é reavaliada até ser **falsa** (zero), e a execução
continua após o _statement_.

O laço `for` possui a seguinte estrutura:

    for (_expr₁_; _expr₂_; _expr₃_)
        _statement_

que é equivalente a

    _expr₁_;
    while (_expr₂_) {
        _statement_
        _expr₃_;
    }

exceto pelo comportamento do `continue`.

Dentre os componentes do laço `for`, frequentemente, _expr₁_ e _expr₃_ são
atribuições ou chamadas de funções e _expr₂_ é uma expressão relacional. É
possível omitir qualquer um desses itens, desde que se mantenha o
ponto-e-vírgula. Se _expr₂_ não estiver presente, ele é tomada como sempre
verdadeiro, de maneira que

~~~ C
for (;;) {
    …
}
~~~

resulta em um laço "infinito", que deve ser quebrado por um `break` ou `return`.

A escolha dentre o uso de um `while` ou um `for` é de preferência pessoal. O
`for`, porém, costuma ser mais adequado quando se há uma inicialização e
incremento, pois mantém as instruções de controle do laço próximas e visíveis.

Um último operador em C é a vírgula `,`. Este permite o uso de múltiplas
expressões nas diferentes partes da instrução `for`, possibilitando, assim, o
processamento de dois índices em paralelo. Isso é melhor ilustrado na função
`reverse(s)`:

~~~C
#include <string.h>

/* reverse:  reverse string s in place */
void reverse(char s[])
{
    int c, i, j;

    for (i = 0, j = strlen(s)-1; i < j; i++, j--) {
        c = s[i];
        s[i] = s[j];
        s[j] = c;
    }
}
~~~

--------------------------------------------------------------------------------

**OBS**: As vírgulas que separam argumentos de funções, variáveis em
declarações, etc., **não** são operadores vírgula, e não garantem a avaliação da
esquerda para a direita.

--------------------------------------------------------------------------------

Operadores vírgula devem ser usados com pouca frequência. Os melhores usos para
o mesmo são em construções fortemente relacionadas entre si:

* _laço `for`_ com múltiplos índices (como em `reverse`)
* _macros_ onde uma computação de múltiplos passos deve ser uma única expressão
* _troca de elementos_ (pode-se considerar como uma única operação)

A troca de elementos em `reverse` pode ser modificada para utilizar o operador
vírgula:

~~~ C
for (i = 0, j = strlen(s)-1; i < j; i++; j--)
    c = s[i], s[i] = s[j], s[j] = c;
~~~

--------------------------------------------------------------------------------

#### Exercícios 3.5

* [Exercise 3-3](./Exercise_3-03.c)

--------------------------------------------------------------------------------

### 3.6 Loops—Do-while

Enquanto os laços `for` e `while` verificam a condição de término no topo, o
laço `do-while` a verifica após o corpo do laço, o que garante que o mesmo seja
executado _pelo menos_ uma vez.

A sintaxe deste laço é:

    do
        _statement_
    while (_expression_);

O _statement_ é executado, e só então a _expression_ é avaliada. Se _expression_
for verdadeira, então o _statement_ é executado de novo e assim por diante até
_expression_ ser falsa.

Apesar de ser menos usado que os laços `while` e `for`, o `do-while` possui
grande utilidade em certas ocasiões. A função `itoa` (o inverso de `atoi`), faz
uso do mesmo, como podemos ver abaixo:

~~~ C
/* itoa:  convert n to characters in s */
void itoa(int n, char s[])
{
    int i, sign;

    if ((sign = n) < 0)  /* record sign */
        n = -n;          /* make n positive */
    i = 0;
    do {       /* generate digits in reverse order */
        s[i++] = n % 10 + '0';   /* get next digit */
    } while ((n /= 10) > 0);     /* delete it */
    if (sign < 0)
        s[i++] = '-';
    s[i] = '\0';
    reverse(s);
}
~~~

O `do-while` é necessário pois pelo menos um caractere deve ser incluso no array
`s`, mesmo se `n` for zero. Chaves também foram usadas ao redor da única
instrução do corpo do laço `do-while`, pois, apesar de desnecessárias, evita
que a parte `while` seja confundida pelo _começo_ de um laço `while`.

--------------------------------------------------------------------------------

#### Exercícios 3.6

* [Exercise 3-4](./Exercise_3-04.c)
* [Exercise 3-5](./Exercise_3-05.c)
* [Exercise 3-6](./Exercise_3-06.c)

--------------------------------------------------------------------------------

### 3.7 Break and Continue

A instrução `break` permite a saída de um laço prematuramente — antes do teste
em seu início ou final — assim como o término de uma cláusula do `switch`.

Na função a seguir, `trim` — que remove espaços em branco, tabs e novalinhas em
excesso à direita (_trailing_) do final de uma string — usa `break` para sair do
laço quando o primeiro caractere não-em-branco, não-tab e não-novalinha é
encontrado.

~~~ C
/* trim:  remove trailing blanks, tabs, newlines */
int trim(char s[])
{
    int n;

    for (n = strlen(s)-1; n >= 0; n--)
        if (s[n] !- ' ' && s[n] != '\t' && s[n] != '\n')
            break;
    s[n+1] = '\0';
    return n;
}
~~~

A instrução `continue` é relacionada à `break`, porém é muito menos usada; esta
faz a próxima iteração do laço na qual está contida começar. No caso dos laços
`while` e `do`, a parte do teste é executada imediatamente; no caso do `for`, a
parte do teste e incremento são executadas.

Como exemplo, este trecho de código processa somente os elementos não-negativos
no array `a`; elementos negativos são pulados:

~~~ C
for (i = 0; i < n; i++) {
    if (a[i] < 0)   /* skip negative elements */
        continue;
    …   /* do positive elements */
}
~~~

A instrução `continue` é frequentemente utilizada quando o trecho do laço que
segue é complicado, de maneira que a inversão de um teste e a indentação de
outro nível iria tornar o aninhamento muito profundo.

### 3.8 Goto and Labels

O uso do `goto` permite que o fluxo de controle do programa seja arbitrariamente
desviado. O destino deste é indicado por um rótulo (_label_) da forma `label:`,
onde `label` pode ser qualquer nome que descreve adequadamente aquela seção.

Apesar de ser considerado desnecessário e frequentemente danoso ([Dijkstra,
1968][0]), este pode ser útil em algumas situações específicas, como para sair
de dois ou mais laços aninhados, no caso de um erro:

    for ( … )
        for ( … ) {
            …
            if (disaster)
                goto error;
        }
      …

    error:
        _clean up the mess_

Um rótulo pode ser anexado a qualquer instrução na mesma função do `goto`. O
escopo de um rótulo é a função inteira.

Como exemplo, considere o problema de determinar se dois arrays `a` e `b` têm
um elemento em comum. Escrevendo o mesmo com uso de `goto` temos:

~~~ C
    for (i = 0; i < n; i++)
        for (j = 0; j < m; j++)
            if (a[i] == b[j])
                goto found;
    /* didn't find any common element */
    …
found:
    /* got one: a[i] == b[j] */
    …
~~~

Este código, assim como todos que utilizam `goto`, pode ser reescrito para não
utilizar o mesmo, porém ao custo de alguns testes repetidos e uma variável
extra. Reescrevendo a busca pelo array, temos:

~~~ C
found = 0;
for (i = 0; i < n && !found; i++)
    for (j = 0; j < m && !found; j++)
        if (a[i] == b[j])
            found = 1;
if (found)
    /* got one:  a[i-1] == b[j-1] */
    …
else
    /* didn't find any common element */
    …
~~~

Exceto pelos exemplos aqui listados, códigos que utilizam instruções `goto`
costumam ser mais difíceis de entender e manter do que códigos sem `goto`s.

[0]: https://homepages.cwi.nl/~storm/teaching/reader/Dijkstra68.pdf
     "Go To Statement Considered Harmful — Dijkstra, 1968"
