# The C Programming Language 2nd Edition — Anotações

## Chapter 2: Types, Operators, and Expressions

### 2.1 Variable Names

Regras de nomeação de variáveis e constantes simbólicas:

* Nomes contém letras e números. O primeiro caractere **precisa** ser uma letra.
* O _underscore_ (`_`) é considerado uma letra, sendo assim útil para melhorar a
  legibilidade de variáveis longas.
* **NÃO** comece o nome de variáveis com `_`; muitas rotinas de bibliotecas usam
  nomes que começam com esse caractere.
* O nome de variáveis é _case-sensitive_; `x` e `X` são variáveis distintas, por
  exemplo.
* Prática tradicional em C:
  - variáveis → caixa baixa
  - constantes simbólicas → CAIXA ALTA
* Palavras reservadas como: `if`, `else`, `int`, `float`, etc., não podem ser
  utilizadas como nome de variáveis.

--------------------------------------------------------------------------------

> Pelo menos os primeiros 31 caracteres de um nome interno são significativos.
> Para nomes de funções e variáveis externas, o número talvez seja menor que 31,
> porque nomes externos talvez sejam usados por assemblers e loaders sobre os
> quais a linguagem não possui controle. Para nomes externos, o padrão garante
> apenas a unicidade de 6 caracteres em uma caixa única.

Este parágrafo descreve uma característica do padrão ANSI C (C89/C90) que não é
relevante a revisões mais atuais da linguagem.

No ANSI C, nomes externos só são considerados únicos até 6 caracteres
_case-insensitive_. Sendo assim, `afoobar` e `aFooBar` não são distintos, assim
como `foobar1` e `foobar2` são consideradas declarações duplicadas, pois seus 6
primeiros caracteres são idênticos.

--------------------------------------------------------------------------------

### 2.2 Data Types and Sizes

Só há alguns tipos de dados básicos em C:

* `char` → um único byte (8 bits), capaz de armazenar um único caractere do
  conjunto de caracteres local.
* `int` → um inteiro, tipicamente refletindo o tamanho natural de inteiros na
  máquina do hospedeiro.
* `float` → ponto-flutuante de precisão única.
* `double` → ponto-flutuante de precisão dupla.

Também há alguns qualificadores que podem ser aplicados a esses tipos básicos.

* `short` → pelo menos 16 bits.
* `long` → pelo menos 32 bits.
* `signed` → valores negativos ou positivos; aplicável a `char`s e `int`s
* `unsigned` → somente zero ou valores positivos, seguindo as regras da
  aritmética módulo 2ⁿ; aplicável a `char`s e `int`s

É possível escrever `short int foo` / `long int bar`, ou simplesmente, `short
foo` / `long bar`.

O tamanho de um `int` pode ser 16 bits ou 32 bits, com a garantia de que ele
possuirá pelo menos 16 bits.

Assim temos:

<!-- HTML Code Preview ========================================================

      `short` (16 bits) ≤ `int` (16 bits ou 32 bits) ≤ `long` (≥32 bits)

=========================================================================== -->

<p align="center">
  <code>short</code> (<strong>16 bits</strong>)
≤ <code>int</code> (<strong>16 bits</strong> ou <strong>32 bits</strong>)
≤ <code>long</code> (<strong>≥32 bits</strong>)
</p>

O tipo `long double` indica ponto-flutuante de precisão estendida. O tamanho de
pontos-flutuantes dependem da implementação; `float`, `double` e `long double`
podem representar um, dois ou três tamanhos distintos.

Os cabeçalhos padrão `<limits.h>` e `<float.h>` contém constantes simbólicas
para todos esses tamanhos, além de outras propriedades da máquina e compilador.

--------------------------------------------------------------------------------

#### Exercícios 2.2

* [Exercise 2-1](./Exercise_2-01.c)

--------------------------------------------------------------------------------

### 2.3 Constants

**Constante-inteira**:

* Com sinal (_signed_):
  - `int` → `1234`
  - `long` → `123456789l` ou `123456789L` (inteiros muito grandes para um `int`
    são automaticamente interpretados como um `long`)
* Sem sinal (_unsigned_):
  - `int` → `1234u` ou `1234U`
  - `long` → `1234ul` ou `1234UL`
* Base octal (prefixo `0`):
  - `037` == 31 (_base 10_)
  - Também podem ser _`unsigned`_ (`037u`), _`long`_ (`037l`) ou _ambos_
    (`037ul`)
* Base hexadecimal (prefixo `0x` ou `0X`):
  - (`0x1f` ou `0X1F`) == 31 (_base 10_)
  - Também pode ser _`unsigned`_ (`0x1Fu`), _`long`_ (`0x1Fl`) ou _ambos_
    (`0x1Ful`)

**Constante de ponto-flutuante**:

* `double` → `123.4`, `1e-2`
* `float` → `123.4f`, `123.4F`, `1e-2f`, `1e-2F`
* `long double` → `123.4l`, `123.4L`, `1e-2l`, `1e-2L`

**Constante-caractere**:

* `'x'` → inteiro com valor equivalente ao caractere no conjunto de caracteres
  (_charset_) da máquina. Ex: `'0'` == 48 (_base 10_)
* `'\ooo'` → sequência de escape octal, onde `ooo` são um a três dígitos octais
  (0…7)
* `'\xhh'` → sequência de escape hexadecimal, onde `hh` são um ou dois dígitos
  hexadecimais (0…9, a…f, A…F)
* o conjunto completo de sequências de escape é:

  | Sequência |  Descrição                |
  | :-------: | ------------------------- |
  | `\a`      | alerta (bell)             |
  | `\b`      | backspace                 |
  | `\f`      | alimentação de formulário |
  | `\n`      | nova linha                |
  | `\r`      | retorno de carro          |
  | `\t`      | tabulação horizontal      |
  | `\v`      | tabulação vertical        |
  | `\\`      | contra barra              |
  | `\?`      | interrogação              |
  | `\'`      | aspas simples             |
  | `\"`      | aspas duplas              |
  | `\ooo`    | número octal              |
  | `\xhh`    | número hexadecimal        |

--------------------------------------------------------------------------------

* **OBS**: a constante de caractere `'\0'` representa o caractere com valor
  zero, o caractere nulo. `'\0'` é escrito ao invés de 0 para enfatizar a
  natureza de caractere de alguma expressão, mas seu valor numérico é apenas
  0.

--------------------------------------------------------------------------------

**Expressão constante**: expressão que contém somente valores constantes; pode
  ser usada em qualquer lugar onde uma constante também pode.

~~~ C
`#define MAXLINE 1000`
`char line[MAXLINE + 1];`
~~~

**Constante-string**: também conhecida como _string literal_, consiste em uma
  sequência de zero ou mais caracteres entre aspas duplas.

* `"Eu sou uma string"`
* `"" /* a string vazia */`
* Constantes-string podem ser concatenadas: `"hello," "world"`
* Pode-se utilizar a função `strlen(s)` da biblioteca padrão para se calcular o
  comprimento de uma dada string `s`, ignorando o `\0` final.
* `strlen(s)` e outras funções de string estão declaradas no header padrão
  `<string.h>`.

--------------------------------------------------------------------------------

* **OBS**: Ter cuidado com a diferença entre:

  - `'x'` → constante-caractere
  - `"x"` → constante-string

  O primeiro é um inteiro equivalente ao caractere `x` no charset da máquina, o
  segundo é uma string contendo um caractere `x` e um `\0`.

--------------------------------------------------------------------------------

**Constante de enumeração**: é uma lista de valores inteiros constantes.

* Primeiro nome tem valor 0, segundo nome tem valor 1, etc., a não ser que
  especificado.
* Valores não especificados continuam a progressão a partir do último valor
  especificado.

~~~ C
enum boolean { NO, YES };

enum escapes { BELL = '\a', BACKSPACE = '\b', TAB = '\t',
                NEWLINE = '\n', VTAB = '\v', RETURN = '\r' };

enum months { JAN = 1, FEB, MAR, APR, MAY, JUN,
              JUL, AUG, SEP, OCT, NOV, DEC };
                    /* FEB é 2, MAR é 3, etc. */
~~~

### 2.4 Declarations

Todas as variáveis precisam ser declaradas antes do uso. Algumas declarações
podem ser feitas de maneira implícita pelo contexto.

Uma declaração especifica um _tipo_, e contém uma ou mais variáveis daquele
tipo.

~~~ C
char c;
char line[1000];
~~~

Uma variável também pode ser _inicializada_ em sua declaração, dado o uso de um
sinal de igual (`=`) e uma expressão após o nome desta.

~~~ C
int i = 0;
float eps = 1.0e-5;
~~~

* Variáveis não-automáticas: inicialização ocorre apenas uma vez; inicializador
  precisa ser um expressão constante.
* Variáveis automáticas: inicializada cada vez que a função ou bloco onde está
  localizada são entrados; inicializador pode ser qualquer expressão.
* Variáveis Externas (`extern`) e Estáticas (`static`): inicializadas como zero
  por padrão.

O qualificador `const` pode ser aplicado a declaração de qualquer variável para
especificar que o seu valor não será alterado. Para um array, `const` indica que
seus elementos não serão alterados.

~~~ C
const double e = 2.71828182845905
const char msg[] = "warning: ";
~~~

A declaração `const` também pode ser usada com argumentos do tipo array, para
indicar que a função não altera aquele array.

~~~ C
int strlen(const char[]);
~~~

--------------------------------------------------------------------------------

**OBS**: O resultado de uma tentativa de alteração de um `const` depende da
implementação.

--------------------------------------------------------------------------------

### 2.5 Arithmetic Operators

Operadores aritméticos binários em C: `+`, `-`, `*`, `/` e `%` (módulo).

A divisão de inteiros sempre trunca a parte fracionária. O uso de `%` em

~~~ C
x % y
~~~

produz o _resto_ da divisão de `x` por `y` (sendo zero no caso de divisão
exata).

Um exemplo do uso de `%` é a determinação de um ano bissexto:

~~~ C
if ((year % 4 == 0 && year % 100 != 0) || year % 400 == 0)
    printf("%d is a leap year\n", year);
else
    printf("%d is not a leap year\n", year);
~~~

--------------------------------------------------------------------------------

**OBS**: O operador `%` não pode ser aplicado a um `float` ou `double`. A
direção de truncagem para `/` e o sinal do resultado para `%` dependem da
máquina para operandos negativos, assim como a ação tomada no caso de um
overflow ou underflow.

--------------------------------------------------------------------------------

Precedência de operadores aritméticos:

<!-- HTML Code Preview ========================================================

              + e - (binários)  <  *, / e %  <  + e - (unários)

=========================================================================== -->

<p align="center">
  <code>+</code> e <code>-</code> (<em>binários</em>)
  <b>&nbsp;&lt;&nbsp;</b> <code>*</code>, <code>/</code> e <code>%</code>
  <b>&nbsp;&lt;&nbsp;</b> <code>+</code> e <code>-</code> (<em>unários</em>)
</p>

A associativiade de operadores aritméticos sempre se dá da _esquerda_ para a
_direita_.

### 2.6 Relational and Logical Operators

* Operadores relacionais em C: `>`, `>=`, `<` e `<=`. Todos possuem a mesma
  precedência e menor precedência que operadores aritméticos.

* Operadores de equalidade em C: `==` e `!=`. Possuem menor precedência que
  operadores relacionais.

* Operadores lógicos em C: `&&` e `||`. `&&` possui maior precedência que `||`;
  ambos possuem menor precedência que operadores de equalidade e relacionais.

Expressões conectadas por `&&` ou `||` são avaliadas da esquerda para a direita,
e a avaliação para assim que a verdade ou falsidade do resultado é conhecido. O
nome desta característica é _curto-circuito_ (_short-circuit_); a maioria dos
programas em C depende dessa propriedade.

Exemplo:

~~~ C
for (i=0; i<lim-1 && (c=getchar()) != '\n' && c != EOF; ++i)
    s[i] = c;
~~~

Ordem de checagem:

1. `i<lim-1` → É necessário saber se há espaço restante no array `s`; se não,
   não se deve ler o próximo caractere.
2. `(c=getchar())` → É necessário se obter `c` antes de compará-lo com outros
   valores.
3. `(c=getchar()) != '\n'` → Compara-se `c` com `\n`.
4. `i<lim-1 && (c=getchar()) != '\n'` → Caso `c` seja o `\n` não é necessário
   verificar se `c` é o `EOF`.
5. `c != EOF` → Compara-se `c` com `EOF`.
6. `i<lim-1 && (c=getchar()) != '\n' && c != EOF` → Verifica-se se todas as
   expressões são verdadeiras.

Por definição, o valor numérico de uma expressão relacional ou lógica é 1 se a
relação for verdadeira, e 0 se a relação é falsa.

O operador unário de negação `!` converte um operando não-zero em 0, e um
operando zero em 1. Um uso comum de `!` é em construções como

~~~ C
if (!valid)
~~~

ao invés de

~~~ C
if (valid == 0)
~~~

a escolha da melhor forma não é bem definida. Neste exemplo, o uso da primeira
forma é mais legível ("if **not** valid"/"se **não** válido"), porém construções
mais complicadas podem ser mais difíceis de entender.

--------------------------------------------------------------------------------

#### Exercícios 2.6

* [Exercise 2-2](./Exercise_2-02.c)

--------------------------------------------------------------------------------

### 2.7 Type Conversions

Em C, quando um operador possui operandos de diferentes tipos, estes são
convertidos seguindo algumas regras.

Geralmente, conversões automáticas transformam um operando mais "estreito" em um
operando mais "largo", sem perda de informações. Ex.: `int` → `float`.
Expressões que resultam em perda de informações como `float` → `int`, podem
mostrar um alerta, mas são permitidas. Expressões que não fazem sentido, como
usar um `float` como subscrito (índice), não são permitidas.

Um `char` é apenas um inteiro pequeno, o que garante uma certa flexibilidade de
uso em operações aritméticas e transformação de caracteres. Abaixo segue a
função `atoi`, que converte uma string de dígitos no equivalente numérico.

~~~ C
/* atoi:  convert s to integer */
int atoi(char s[])
{
  int i, n;

  n = 0;
  for (i = 0; s[i] >= '0' && s[i] <= '9'; ++i)
      n = 10 * n + (s[i] - '0');
  return n;
}
~~~

Onde `s[i] - '0'` resulta no valor numérico do caractere armazenado em `s[i]`,
pois os caracteres `'0'`, `'1'`, etc., formam uma sequência contínua crescente.

Uma outra função de conversão de `char` em `int` é a função `lower`, que retorna
o caractere minúsculo equivalente no charset ASCII. Caso o caractere de
entrada não seja uma letra maiúscula, `lower` o retorna sem alterações.

~~~ C
/* lower:  convert c to lower case; ASCII only */
int lower(int c)
{
  if (c >= 'A' && c <= 'Z')
      return c + 'a' - 'A';
  else
      return c;
}
~~~

--------------------------------------------------------------------------------

**OBS**: Esta função funciona em ASCII pois os caracteres maiúsculos e
minúsculos possuem uma distância fixa entre si e cada alfabeto é contínuo. A
mesma função não funcionaria para o charset EBCDIC pois seu alfabeto não é
contínuo.

--------------------------------------------------------------------------------

O cabeçalho padrão `<ctype.h>`, define uma família de funções que provê testes
e conversões independentes de conjuntos de caracteres. A função `lower` pode ser
substituída pela função `tolower(c)` e o teste `c >= '0' && c <= '9'`
por `isdigit(c)`.

Há um detalhe a respeito da conversão de caracteres em inteiros. A linguagem não
especifica se `char`s são quantidades com sinal ou sem sinal. A conversão de um
`char` em um `int` varia de máquina para máquina, tendo duas possibilidades:

* _sign extension_: o bit mais a esquerda é copiado para os novos bits; `char` é
  convertido em inteiro negativo.

  Ex.: Caractere Extended ASCII 234(dec) = "Ω"

  `char` (8 bits)

      ┌───┬───┬───┬───┬───┬───┬───┬───┐
      │(1)│ 1 │ 1 │ 0 │ 1 │ 0 │ 1 │ 0 │ == 234(dec)
      └───┴───┴───┴───┴───┴───┴───┴───┘
        ↑
        bit mais a esquerda

  `int`  (16 bits)

      ┌───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┐
      │(1)│(1)│(1)│(1)│(1)│(1)│(1)│(1)│ 1 │ 1 │ 1 │ 0 │ 1 │ 0 │ 1 │ 0 │ == -6(dec)
      └───┴───┴───┴───┴───┴───┴───┴───┴───┴───┴───┴───┴───┴───┴───┴───┘
        ↑   ↑   ↑   ↑   ↑   ↑   ↑   ↑
                novos bits

* _zero extension_: os novos bits são preenchidos com zero; `char` se mantém
  como inteiro positivo.

  Ex.: Caractere Extended ASCII 234(dec) = "Ω"

  `char` (8 bits)

      ┌───┬───┬───┬───┬───┬───┬───┬───┐
      │ 1 │ 1 │ 1 │ 0 │ 1 │ 0 │ 1 │ 0 │ == 234(dec)
      └───┴───┴───┴───┴───┴───┴───┴───┘

  `int`  (16 bits)

      ┌───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┐
      │(0)│(0)│(0)│(0)│(0)│(0)│(0)│(0)│ 1 │ 1 │ 1 │ 0 │ 1 │ 0 │ 1 │ 0 │ == 234(dec)
      └───┴───┴───┴───┴───┴───┴───┴───┴───┴───┴───┴───┴───┴───┴───┴───┘
        ↑   ↑   ↑   ↑   ↑   ↑   ↑   ↑
                  novos bits

A definição do C garante que qualquer caractere no conjunto de caracteres
imprimíveis da máquina jamais será negativo (como exemplo, nenhum caractere do
conjunto ASCII padrão (7-bit) será interpretado como um valor negativo),
conjuntos arbitários de bits armazendos em um `char`, porém, não possuem essa
garantia. Para maior portabilidade, é recomendado especificar os qualificadores
`signed` ou `unsigned` quando se armazenar dados que não são caracteres em
variáveis do tipo `char`.

--------------------------------------------------------------------------------

**OBS**: Expressões relacionais e lógicas são definidas como tendo o valor 1 se
verdadeiras, e o valor 0 se falsas. Outras funções como `isdigit` podem retornar
qualquer valor não-zero para verdadeiro. Em C, temos que qualquer valor
**não-zero** é considerado **verdadeiro,** e **zero** é **falso.** Isso é válido
para qualquer teste em `if`, `while`, `for`, etc.

--------------------------------------------------------------------------------

Como já citado anteriormente, expressões aritméticas com operandos de diferentes
tipos são automaticamente convertidas, sempre de um tipo "menor" / "estreito"
para um tipo "maior" / "largo". Para operandos `signed` as seguintes regras se
aplicam, nesta ordem:

1. `long double` + outro; outro → `long double`
2. `double` + outro; outro → `double`
3. `float` + outro; outro → `float`
4. `char` → `int`; `short` → `int`
5. `long` + outro; outro → `long`

As regras de conversão são mais complicadas quando operandos `unsigned` estão
envolvidos, pois dependem do tamanho dos diferentes tipos inteiros em cada
máquina. Assumindo `int` como 16 bits e `long` como 32 bits, temos:

* `-1L` < `1U`; pois `1U` é promovido a `signed long`
* `-1L` > `1UL`; pois `-1L` é promovido a `unsigned long`, tornando-se um número
  positivo grande.

Inteiros grandes são convertidos para inteiros menores ou para `char`s
descartando os bits de maior ordem excedentes.

Conversão de `float` → `int` trunca qualquer parte fracionária. Conversão de
`double` → `float` pode ser truncada ou arredondada dependendo da implementação.

Como o argumento de uma chamada de função também é uma expressão, conversões de
tipos também ocorrem quando argumentos são passados para funções. Caso não haja
um protótipo de função, `char` e `short` → `int`, `float` → `double`.

Conversões de tipos explícitas podem ser forçadas ("coagidas") em qualquer
expressão com o uso de um operador unário chamado de _cast_, que possue a
seguinte estrutura:

    (type-name) expression

onde a expressão é convertida para o tipo explicitado entre parênteses.

Um exemplo de casting pode ser visto na função `rand` da biblioteca padrão:

~~~ C
unsigned long int next = 1;

/* rand:  return pseudo-random integer on 0..32767 */
int rand(void)
{
    next = next * 1103515245 + 12345;
    return (unsigned int)(next/65536) % 32768;
}

/* srand:  set seed for rand() */
void srand(unsigned int seed)
{
  next = seed;
}
~~~

--------------------------------------------------------------------------------

#### Exercícios 2.7

* [Exercise 2-3](./Exercise_2-03.c)

--------------------------------------------------------------------------------

### 2.8 Increment and Decrement Operators

A linguagem C possui dois operadores para incremento e decremento de variáveis:

* `++` → _incremento em 1_
  - `x = ++n` → **pré**-incremento; se `n` = 5, então `x` = 6 e `n` = 6
  - `x = n++` → **pós**-incremento; se `n` = 5, então `x` = 5 e `n` = 6
* `--` → _decremento em 1_
  - `x = --n` → **pré**-decremento; se `n` = 5, então `x` = 4 e `n` = 4
  - `x = n--` → **pós**-decremento; se `n` = 5, então `x` = 5 e `n` = 4

Em casos onde apenas o efeito do incremento/decremento importa, e não o valor em
si, tanto a notação em _prefixo_ quanto a em _pósfixo_ possuem o mesmo
comportamento.

Abaixo temos alguns exemplos de situações onde o uso da notação em prefixo ou
pósfixo fazem diferença no comportamento da função:

~~~ C
/* squeeze:  delete all c from s */
void squeeze(char s[], int c)
{
  int i, j;

  for (i = j = 0; s[i] != '\0'; i++)
      if (s[i] != c)
          s[j++] = s[i];
  s[j] = '\0';
}
~~~

Cada vez que um não-`c` ocorre, ele é copiado para o posição `j` atual, e só
então `j` é incrementado para estar pronto para o próximo caractere.

--------------------------------------------------------------------------------

~~~ C
/* strcat:  concatenate t to end of s; s must be big enough */
void strcat(char s[], char t[])
{
  int i, j;

  i = j = 0;
  while (s[i] != '\0')    /* find end of s */
    i++;
  while ((s[i++] = t[j++]) != '\0')   /* copy t */
    ;
}
~~~

Conforme cada caractere é copiado de `t` para `s`, o `++` pósfixo é aplicado
para ambos `i` e `j` para garantir que eles estejam na posição para a próxima
iteração através do laço.

--------------------------------------------------------------------------------

#### Exercícios 2.8

* [Exercise 2-4](./Exercise_2-04.c)
* [Exercise 2-5](./Exercise_2-05.c)

--------------------------------------------------------------------------------

### 2.9 Bitwise Operators

Em C há seis operadores para manipulação de bits, sendo utilizáveis somente com
`char`, `short`, `int` e `long`; `signed` ou `unsigned`.

* `&`  → E-lógico bit-a-bit (AND)
* `|`  → OU-lógico inclusivo bit-a-bit (OR)
* `^`  → OU-lógico exclusivo bit-a-bit (XOR)
* `<<` → shift à esquerda
* `>>` → shift à direita
* `~`  → complemento a um

**E-lógico bit-a-bit (`&`) (AND)**: usado com frequência para mascarar uma certa
quantidade de bits.

    n = n & 0177;

            ────────────┬────────────┬────────────┬────────────
        n =  1  1  0  1 │ 1  1  1  0 │ 1  0  1  0 │ 1  1  0  1
            ────────────┴────────────┴────────────┴────────────
             &  &  &  &   &  &  &  &   &  &  &  &   &  &  &  &
            ────────────┬────────────┬────────────┬────────────
     0177 =  0  0  0  0 │ 0  0  0  0 │ 0  1  1  1 │ 1  1  1  1
            ────────────┴────────────┴────────────┴────────────
             =  =  =  =   =  =  =  =   =  =  =  =   =  =  =  =
            ────────────┬────────────┬────────────┬────────────
        n =  0  0  0  0 │ 0  0  0  0 │ 0 (0)(1)(0)│(1)(1)(0)(1)
            ────────────┴────────────┴────────────┴────────────
                                          ↑  ↑  ↑   ↑  ↑  ↑  ↑
                                     somente esses bits permanecem

<br>

**OU-lógico bit-a-bit (`|`) (OR)**: usado para ligar bits.

    x = x | SET_ON;

             ────────────┬────────────
         x =  1  0  1 (0)│ 0  1 (0)(0)
             ────────────┴────────────
              |  |  |  |   |  |  |  |
             ────────────┬────────────
    SET_ON =  0  0  0  1 │ 0  0  1  1
             ────────────┴────────────
              =  =  =  =   =  =  =  =
             ────────────┬────────────
         x =  1  0  1 (1)│ 0  1 (1)(1)
             ────────────┴────────────
                       ↑        ↑   ↑
                        bits ligados

<br>

**OU-lógico exclusivo bit-a-bit (`^`) (XOR)**: coloca um em cada posição onde os
bits entre os operandos diferem, e zero onde eles são iguais. Útil para inversão
de bits associado a uma máscara: qualquer bit **XOR** com 1 resulta na inversão
do mesmo; qualquer bit **XOR** com 0 resulta no próprio bit.

     diff = a ^ b;

           ────────────┬────────────┬────────────┬────────────
       a = (1) 1 (0)(1)│(1)(1)(1) 0 │(1)(0)(1) 0 │(1)(1)(0)(1)
           ────────────┴────────────┴────────────┴────────────
            ^  ^  ^  ^   ^  ^  ^  ^   ^  ^  ^  ^   ^  ^  ^  ^
           ────────────┬────────────┬────────────┬────────────
       b =  1  0  1  1 │ 1  1  1  0 │ 1  1  1  0 │ 1  1  1  1 
           ────────────┴────────────┴────────────┴────────────
            =  =  =  =   =  =  =  =   =  =  =  =   =  =  =  =
           ────────────┬────────────┬────────────┬────────────
    diff = (0) 1 (1)(0)│(0)(0)(0) 0 │(0)(1)(0) 0 │(0)(0)(1)(0)
           ────────────┴────────────┴────────────┴────────────
            ↑     ↑  ↑   ↑  ↑  ↑      ↑  ↑  ↑      ↑  ↑  ↑  ↑
                  somente estes bits foram invertidos

--------------------------------------------------------------------------------

**OBS**: Cuidado com a diferença entre os operadores bit-a-bit `&` e `|`, e os
operadores lógicos `&&` e `||`. Para `x = 1` e `y = 2`:

* `x & y`  → 0
* `x && y` → 1

--------------------------------------------------------------------------------

**Shift-à-esquerda (`<<`) e shift-à-direita (`>>`)**: move os bits do operando a
esquerda pela quantidade (positiva) do operando a direita.

    x = x << 2;

             ────────────┬────────────┬────────────┬────────────
         x = {1  1  0  1}│{1  1  1  0}│{1  0  1  0}│{1  1  0  1}
             ────────────┴────────────┴────────────┴────────────
                                    << 2
             ────────────┬────────────┬────────────┬────────────
    x << 2 =  0  1}{1  1 │ 1  0}{1  0 │ 1  0}{1  1 │ 0  1}(0)(0)
             ────────────┴────────────┴────────────┴────────────
                                                           ↑  ↑
                                                   preenchido com zero

<br>

    x = x >> 2;

             ────────────┬────────────┬────────────┬────────────
         x = {1  1  0  1}│{1  1  1  0}│{1  0  1  0}│{1  1  0  1}
             ────────────┴────────────┴────────────┴────────────
                                    >> 2
             ────────────┬────────────┬────────────┬────────────
    x >> 2 = (1)(1){1  1 │ 0  1}{1  1 │ 1  0}{1  0 │ 1  0}{1  1
             ────────────┴────────────┴────────────┴────────────
              ↑  ↑
       arithmetic shift -- preenche com bit mais a esquerda (sinal)

    ou...
                                    >> 2
             ────────────┬────────────┬────────────┬────────────
    x >> 2 = (0)(0){1  1 │ 0  1}{1  1 │ 1  0}{1  0 │ 1  0}{1  1
             ────────────┴────────────┴────────────┴────────────
              ↑  ↑
       logical shift -- preenche com zero

<br>

**Complemento a um (`~`)**: inverte os bits de um inteiro; 0 para 1 e
vice-versa.

    x = x & ~077;

           ─────────┬─────────┬─────────┬─────────┬─────────┬─────────┬─────────┬─────────
     077 =  0 0 0 0 │ 0 0 0 0 │ 0 0 0 0 │ 0 0 0 0 │ 0 0 0 0 │ 0 0 0 0 │ 0 0 1 1 │ 1 1 1 1
           ─────────┴─────────┴─────────┴─────────┴─────────┴─────────┴─────────┴─────────
           ─────────┬─────────┬─────────┬─────────┬─────────┬─────────┬─────────┬─────────
    ~077 =  1 1 1 1 │ 1 1 1 1 │ 1 1 1 1 │ 1 1 1 1 │ 1 1 1 1 │ 1 1 1 1 │ 1 1 0 0 │ 0 0 0 0
           ─────────┴─────────┴─────────┴─────────┴─────────┴─────────┴─────────┴─────────
            & & & &   & & & &   & & & &   & & & &   & & & &   & & & &   & & & &   & & & &
           ─────────┬─────────┬─────────┬─────────┬─────────┬─────────┬─────────┬─────────
       x =  1 0 1 1 │ 1 0 1 0 │ 0 1 0 1 │ 1 1 1 0 │ 1 0 1 1 │ 1 0 1 0 │ 0 0 0 1 │ 0 0 0 1
           ─────────┴─────────┴─────────┴─────────┴─────────┴─────────┴─────────┴─────────
            = = = =   = = = =   = = = =   = = = =   = = = =   = = = =   = = = =   = = = =
           ─────────┬─────────┬─────────┬─────────┬─────────┬─────────┬─────────┬─────────
       x =  1 0 1 1 │ 1 0 1 0 │ 0 1 0 1 │ 1 1 1 0 │ 1 0 1 1 │ 1 0 1 0 │ 0 0 0 0 │ 0 0 0 0
           ─────────┴─────────┴─────────┴─────────┴─────────┴─────────┴─────────┴─────────

é preferível utilizar `~077` ao invés de `0177700` pois o primeiro é
independente do tamanho da palavra, enquanto o último assume que `x` seja uma
quantidade de 16 bits.

Para melhor ilustrar a utilidade dos operadores a nível de bit, considere a
função abaixo:

~~~ C
/* getbits:  get n bits from position p */
unsigned getbits(unsigned x, int p, int n)
{
    return (x >> (p+1-n)) & ~(~0 << n);
}
~~~

A função `getbits(x,p,n)` retorna `n` bits a partir da posição `p` de um inteiro
(unsigned) `x`. Como exemplo, pegaremos 3 bits começando da posição 4 de `x`:

    posição:  1  1  1  1   1  1
              5  4  3  2   1  0  9  8   7  6  5 (4) (3)(2) 1  0
             ────────────┬────────────┬────────────┬────────────
         x =  1  1  0  1 │ 1  1  1  0 │ 1  0  1 (0)│(1)(1) 0  1
             ────────────┴────────────┴────────────┴────────────
                                                 ↑   ↑  ↑

A expressão `x >> (p+1-n)` move os bits desejados para a extremidade direita da
palavra (é necessário somar 1 pois a posição zero é contabilizada):

    posição:  1  1  1  1   1  1
              5  4  3  2   1  0  9  8   7  6  5  4   3 (2)(1)(0)
             ────────────┬────────────┬────────────┬────────────
    x >> 2 =  0  0  1  1 │ 0  1  1  1 │ 1  0  1  0 │ 1 (0)(1)(1)
             ────────────┴────────────┴────────────┴────────────
                                                        ↑  ↑  ↑

A expressão `~(~0 << n)` provê uma máscara com `n` bits para o operador `&`:

                 ────────────┬────────────┬────────────┬────────────
            ~0 =  1  1  1  1 │ 1  1  1  1 │ 1  1  1  1 │ 1  1  1  1
                 ────────────┴────────────┴────────────┴────────────
                                        << 3
                 ────────────┬────────────┬────────────┬────────────
       ~0 << 3 =  1  1  1  1 │ 1  1  1  1 │ 1  1  1  1 │ 1  0  0  0
                 ────────────┴────────────┴────────────┴────────────
                 ────────────┬────────────┬────────────┬────────────
    ~(~0 << n) =  0  0  0  0 │ 0  0  0  0 │ 0  0  0  0 │ 0  1  1  1
                 ────────────┴────────────┴────────────┴────────────

Por fim, temos:

    x >> (p+1-n) & ~(~0 << n) =
                 ────────────┬────────────┬────────────┬────────────
                  0  0  0  0 │ 0  0  0  0 │ 0  0  0  0 │ 0 (0)(1)(1)
                 ────────────┴────────────┴────────────┴────────────
                                                            ↑  ↑  ↑
                                                          bits finais

<br>

--------------------------------------------------------------------------------

#### Exercícios 2.9

* [Exercise 2-6](./Exercise_2-06.c)
* [Exercise 2-7](./Exercise_2-07.c)
* [Exercise 2-8](./Exercise_2-08.c)

--------------------------------------------------------------------------------

### 2.10 Assignment Operators and Expressions

Expressões como `i = i + 2` podem ser escritas em uma forma mais compacta usando
operadores de atribuição (_assignment operators_), neste caso `i += 2`; estes
possuem a seguinte forma:

    expr₁ op= expr₂

que é equivalente a:

    expr₁ = (expr₁) op (expr₂)

A maioria dos operadores binários possem um operador de atribuição da forma
_op=_, onde _op_ é um dos seguintes:

* `+`
* `-`
* `*`
* `/`
* `%`
* `<<`
* `>>`
* `&`
* `^`
* `|`

Temos como exemplo a função `bitcount` que conta o número de bits 1 em seu
argumento inteiro:

~~~ C
/* bitcount:  count 1 bits in x */
int bitcount(unsigned x)
{
  int b;

  for (b = 0; x != 0; x >>= 1)
      if (x & 01)
          b++;
      return b;
}
~~~

Uma pequena observação: o motivo de `x` ser declarado como `unsigned` é para
garantir que quando ele sofrer um shift-à-direita, os bits vacantes sejam
preenchidos como zeros, e não com bits de sinal, não importando em qual máquina
este programa for executado.

O uso de operadores de atribuição torna o código mais conciso e melhor
representa a forma como pessoas normalmente pensam; além disso, potencialmente
podem tornar expressões longas mais fáceis de serem compreendidas e ajudar um
compilador a produzir código mais eficiente.

Operadores de atribuição podem aparecer em expressões, onde o tipo da expressão
de atribuição é o tipo do operando a esquerda e o seu valor é o valor após a
atribuição.

--------------------------------------------------------------------------------

#### Exercícios 2.9

* [Exercise 2-9](./Exercise_2-09.c)

--------------------------------------------------------------------------------

### 2.11 Conditional Expressions

Declarações (statements) como:

~~~ C
if (a > b)
    z = a;
else
    z = b;
~~~

onde se calcula em `z` o máximo entre `a` e `b` podem ser reescritas como uma
_expressão condicional_ utilizando-se o operador ternário (`?:`):

    expr₁ ? expr₂ : expr₃

onde a expressão _expr₁_ é avaliada. Caso verdadeira, _expr₂_ é avaliada e
torna-se o valor da expressão condicional; caso contrário, _expr₃_ é avaliada e
esta torna-se o valor da expressão condicional.

Assim temos para o exemplo anterior:

~~~ C
z = (a > b) ? a : b;    /* z = max(a, b) */
~~~

Como toda expressão condicional é uma expressão, esta pode ser utilizada em
qualquer lugar onde qualquer outra expressão pode ser utilizada.

O uso de parênteses ao redor da _expr₁_ de uma expressão condicional não é
necessário, porém é recomendado.

Abaixo temos alguns exemplos do uso de expressões condicionais:

~~~ C
for (i = 0; i < n; i++)
    printf("%6d%c", a[i], (i%10==9 || i==n-1) ? '\n' : ' ');
~~~

~~~ C
printf("You have %d item%s.\n", n, n==1 ? "": "s");
~~~

--------------------------------------------------------------------------------

#### Exercícios 2.11

* [Exercise 2-10](./Exercise_2-10.c)

--------------------------------------------------------------------------------

### 2.12 Precedence and Order of Evaluation

Abaixo temos a tabela de precedência e associativade de todos os operadores:

| Operadores                                               | Associatividade         |
| -------------------------------------------------------- | :---------------------: |
| `()` `[]` `->` `.`                                       | esquerda para a direita |
| `!` `-` `++` `--` `+` `-` `*` `&` `(`_type_`)` `sizeof`  | direita para a esquerda |
| `*` `/` `%`                                              | esquerda para a direita |
| `+` `-`                                                  | esquerda para a direita |
| `<<` `>>`                                                | esquerda para a direita |
| `<` `<=` `>` `>=`                                        | esquerda para a direita |
| `==` `!=`                                                | esquerda para a direita |
| `&`                                                      | esquerda para a direita |
| `^`                                                      | esquerda para a direita |
| `|`                                                      | esquerda para a direita |
| `&&`                                                     | esquerda para a direita |
| `||`                                                     | esquerda para a direita |
| `?:`                                                     | direita para a esquerda |
| `=` `+=` `-=` `*=` `/=` `%=` `&=` `^=` `\|=` `<<=` `>>=` | direita para a esquerda |
| `,`                                                      | esquerda para a direita |

**OBS**: `+`, `-`, e `*` unários possuem maior precedência que as formas
binárias.

A linguagem C não especifica a odem de avaliação dos operandos de um operador,
(com exceção de `&&`, `||`, `?:`, e `,`), isto significa que em uma declaração
como:

~~~ C
x = f() + g();
~~~

`f` pode ser avaliado antes de `g` e vice-versa.

A ordem da avaliação de argumentos de uma função, ou do índice de um array
também não são especificadas, o que significa que expressões como:

~~~ C
printf("%d %d\n", ++n, power(2, n));
~~~

e

~~~ C 
a[i] = i++;
~~~

podem causar apresentar diferentes resultados em diferentes compiladores, devido
a **"efeitos colaterais"**: alguma variável é alterada como subproduto da
avaliação de uma expressão.

O ideal é sempre evitar de se escrever código que dependa apenas da ordem de
avaliação das expressões.