# The C Programming Language 2nd Edition — Anotações

## Chapter 2: Types, Operators, and Expressions

### 2.1 Variable Names

Regras de nomeação de variáveis e constantes simbólicas:

* Nomes contém letras e números. O primeiro caractere **precisa** ser uma
  letra.
* O *underscore* (`_`) é considerado uma letra, sendo assim útil para melhorar
  a legibilidade de variáveis longas.
* **NÃO** comece o nome de variáveis com `_`; muitas rotinas de bibliotecas
  usam nomes que começam com esse caractere.
* O nome de variáveis é *case-sensitive*; `x` e `X` são variáveis distintas,
  por exemplo.
* Prática tradicional em C:
  - variáveis → caixa baixa
  - constantes simbólicas → CAIXA ALTA
* Palavras reservadas como: `if`, `else`, `int`, `float`, etc., não podem ser
  utilizadas como nome de variáveis.

-------------------------------------------------------------------------------

> Pelo menos os primeiros 31 caracteres de um nome interno são significativos.
> Para nomes de funções e variáveis externas, o número talvez seja menor que
> 31, porque nomes externos talvez sejam usados por assemblers e loaders sobre
> os quais a linguagem não possui controle. Para nomes externos, o padrão
> garante apenas a unicidade de 6 caracteres em uma caixa única.

Este parágrafo descreve uma característica do padrão ANSI C (C89/C90) que não é
relevante a revisões mais atuais da linguagem.

No ANSI C, nomes externos só são considerados únicos até 6 caracteres
*case-insensitive*. Sendo assim, `afoobar` e `aFooBar` não são distintos, assim
como `foobar1` e `foobar2` são consideradas declarações duplicadas, pois seus
6 primeiros caracteres são idênticos.

-------------------------------------------------------------------------------

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

É possível escrever `short int foo` / `long int bar`, ou simplesmente,
`short foo` / `long bar`.

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

-------------------------------------------------------------------------------

#### Exercícios 2.2

* [Exercise 2-1](./Exercise_2-1.c)

-------------------------------------------------------------------------------

### 2.3 Constants

**Constante-inteira**:

* Com sinal (*signed*):
  - `int` → `1234`
  - `long` → `123456789l` ou `123456789L` (inteiros muito grandes para um
    `int` são automaticamente interpretados como um `long`)
* Sem sinal (*unsigned*):
  - `int` → `1234u` ou `1234U`
  - `long` → `1234ul` ou `1234UL`
* Base octal (prefixo `0`):
  - `037` == 31 (*base 10*)
  - Também podem ser *`unsigned`* (`037u`), *`long`* (`037l`) ou *ambos*
    (`037ul`)
* Base hexadecimal (prefixo `0x` ou `0X`):
  - (`0x1f` ou `0X1F`) == 31 (*base 10*)
  - Também pode ser *`unsigned`* (`0x1Fu`), *`long`* (`0x1Fl`) ou *ambos*
    (`0x1Ful`)

**Constante de ponto-flutuante**:

* `double` → `123.4`, `1e-2`
* `float` → `123.4f`, `123.4F`, `1e-2f`, `1e-2F`
* `long double` → `123.4l`, `123.4L`, `1e-2l`, `1e-2L`

**Constante-caractere**:

* `'x'` → inteiro com valor equivalente ao caractere no conjunto de
  caracteres (*charset*) da máquina. Ex: `'0'` == 48 (*base 10*)
* `'\ooo'` → sequência de escape octal, onde `ooo` são um a três dígitos
  octais (0…7)
* `'\xhh'` → sequência de escape hexadecimal, onde `hh` são um ou dois
  dígitos hexadecimais (0…9, a…f, A…F)
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

-------------------------------------------------------------------------------

* **OBS**: a constante de caractere `'\0'` representa o caractere com valor
  zero, o caractere nulo. `'\0'` é escrito ao invés de 0 para enfatizar a
  natureza de caractere de alguma expressão, mas seu valor numérico é apenas
  0.

-------------------------------------------------------------------------------

**Expressão constante**: expressão que contém somente valores constantes;
  pode ser usada em qualquer lugar onde uma constante também pode.
  
```C
`#define MAXLINE 1000`  
`char line[MAXLINE + 1];`
```

**Constante-string**: também conhecida como *string literal*, consiste
  em uma sequência de zero ou mais caracteres entre aspas duplas.

* `"Eu sou uma string"`
* `"" /* a string vazia */`
* Constantes-string podem ser concatenadas: `"hello," "world"`
* Pode-se utilizar a função `strlen(s)` da biblioteca padrão para se calcular
  o comprimento de uma dada string `s`, ignorando o `\0` final.
* `strlen(s)` e outras funções de string estão declaradas no header padrão
  `<string.h>`.

-------------------------------------------------------------------------------

* **OBS**: Ter cuidado com a diferença entre:

  - `'x'` → constante-caractere
  - `"x"` → constante-string

  O primeiro é um inteiro equivalente ao caractere `x` no charset da máquina,
  o segundo é uma string contendo um caractere `x` e um `\0`.

-------------------------------------------------------------------------------

**Constante de enumeração**: é uma lista de valores inteiros constantes.

* Primeiro nome tem valor 0, segundo nome tem valor 1, etc., a não ser que
  especificado.
* Valores não especificados continuam a progressão a partir do último valor
  especificado.

```C
enum boolean { NO, YES };

enum escapes { BELL = '\a', BACKSPACE = '\b', TAB = '\t',
                NEWLINE = '\n', VTAB = '\v', RETURN = '\r' };

enum months { JAN = 1, FEB, MAR, APR, MAY, JUN,
              JUL, AUG, SEP, OCT, NOV, DEC };
                    /* FEB é 2, MAR é 3, etc. */
```

### 2.4 Declarations

Todas as variáveis precisam ser declaradas antes do uso. Algumas declarações
podem ser feitas de maneira implícita pelo contexto.

Uma declaração especifica um *tipo*, e contém uma ou mais variáveis daquele
tipo.

```C
char c;
char line[1000];
```

Uma variável também pode ser *inicializada* em sua declaração, dado o uso de um
sinal de igual (`=`) e uma expressão após o nome desta.

```C
int i = 0;
float eps = 1.0e-5;
```

* Variáveis não-automáticas: inicialização ocorre apenas uma vez; inicializador
  precisa ser um expressão constante.
* Variáveis automáticas: inicializada cada vez que a função ou bloco onde está
  localizada são entrados; inicializador pode ser qualquer expressão.
* Variáveis Externas (`extern`) e Estáticas (`static`): inicializadas como zero
  por padrão.

O qualificador `const` pode ser aplicado a declaração de qualquer variável para
especificar que o seu valor não será alterado. Para um array, `const` indica
que seus elementos não serão alterados.

```C
const double e = 2.71828182845905
const char msg[] = "warning: ";
```

A declaração `const` também pode ser usada com argumentos do tipo array, para
indicar que a função não altera aquele array.

```C
int strlen(const char[]);
```

-------------------------------------------------------------------------------

**OBS**: O resultado de uma tentativa de alteração de um `const` depende da
implementação.

-------------------------------------------------------------------------------

### 2.5 Arithmetic Operators

Operadores aritméticos binários em C: `+`, `-`, `*`, `/` e `%` (módulo).

A divisão de inteiros sempre trunca a parte fracionária. O uso de `%` em

```C
x % y
```

produz o *resto* da divisão de `x` por `y` (sendo zero no caso de divisão exata).

Um exemplo do uso de `%` é a determinação de um ano bissexto:

```C
if ((year % 4 == 0 && year % 100 != 0) || year % 400 == 0)
    printf("%d is a leap year\n", year);
else
    printf("%d is not a leap year\n", year);
```

-------------------------------------------------------------------------------

**OBS**: O operador `%` não pode ser aplicado a um `float` ou `double`. A
direção de truncagem para `/` e o sinal do resultado para `%` dependem da
máquina para operandos negativos, assim como a ação tomada no caso de um
overflow ou underflow.

-------------------------------------------------------------------------------

Precedência de operadores aritméticos:

<!-- HTML Code Preview ========================================================

              + e - (binários)  <  *, / e %  <  + e - (unários)

=========================================================================== -->

<p align="center">
  <code>+</code> e <code>-</code> (<em>binários</em>)
  <b>&nbsp;&lt;&nbsp;</b> <code>*</code>, <code>/</code> e <code>%</code>
  <b>&nbsp;&lt;&nbsp;</b> <code>+</code> e <code>-</code> (<em>unários</em>)
</p>

A associativiade de operadores aritméticos sempre se dá da *esquerda* para a
*direita*.

### 2.6 Relational and Logical Operators

* Operadores relacionais em C: `>`, `>=`, `<` e `<=`. Todos possuem a mesma
  precedência e menor precedência que operadores aritméticos.

* Operadores de equalidade em C: `==` e `!=`. Possuem menor precedência que
  operadores relacionais.

* Operadores lógicos em C: `&&` e `||`. `&&` possui maior precedência que `||`;
  ambos possuem menor precedência que operadores de equalidade e relacionais.

Expressões conectadas por `&&` ou `||` são avaliadas da esquerda para a
direita, e a avaliação para assim que a verdade ou falsidade do resultado é
conhecido. O nome desta característica é *curto-circuito* (*short-circuit*); a
maioria dos programas em C depende dessa propriedade.

Exemplo:

```C
for (i=0; i<lim-1 && (c=getchar()) != '\n' && c != EOF; ++i)
    s[i] = c;
```

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

```C
if (!valid)
```

ao invés de 

```C
if (valid == 0)
```

a escolha da melhor forma não é bem definida. Neste exemplo, o uso da primeira
forma é mais legível ("if **not** valid"/"se **não** válido"), porém construções
mais complicadas podem ser mais difíceis de entender.

-------------------------------------------------------------------------------

#### Exercícios 2.6

* [Exercise 2-2](./Exercise_2-2.c)

-------------------------------------------------------------------------------

### 2.7 Type Conversions

