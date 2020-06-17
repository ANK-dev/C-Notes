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

* **Constante-inteira**
  - Com sinal (*signed*):
    + `int` → `1234`
    + `long` → `123456789l` ou `123456789L` (inteiros muito grandes para um
      `int` são automaticamente interpretados como um `long`)
  - Sem sinal (*unsigned*):
    + `int` → `1234u` ou `1234U`
    + `long` → `1234ul` ou `1234UL`
  - Base octal (prefixo `0`):
    + `037` == 31 (*base 10*)
    + Também podem ser *`unsigned`* (`037u`), *`long`* (`037l`) ou *ambos*
      (`037ul`)
  - Base hexadecimal (prefixo `0x` ou `0X`):
    + (`0x1f` ou `0X1F`) == 31 (*base 10*)
    + Também pode ser *`unsigned`* (`0x1Fu`), *`long`* (`0x1Fl`) ou *ambos*
      (`0x1Ful`)
* **Constante de ponto-flutuante**
  - `double` → `123.4`, `1e-2`
  - `float` → `123.4f`, `123.4F`, `1e-2f`, `1e-2F`
  - `long double` → `123.4l`, `123.4L`, `1e-2l`, `1e-2L`
* **Constante-caractere**
  - `'x'` → inteiro com valor equivalente ao caractere no conjunto de
    caracteres (*charset*) da máquina. Ex: `'0'` == 48 (*base 10*)
  - `'\ooo'` → sequência de escape octal, onde `ooo` são um a três dígitos
    octais (0…7)
  - `'\xhh'` → sequência de escape hexadecimal, onde `hh` são um ou dois
    dígitos hexadecimais (0…9, a…f, A…F)
  - o conjunto completo de sequências de escape é:

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

  -----------------------------------------------------------------------------

  - **OBS**: a constante de caractere `'\0'` representa o caractere com valor
    zero, o caractere nulo. `'\0'` é escrito ao invés de 0 para enfatizar a
    natureza de caractere de alguma expressão, mas seu valor numérico é apenas
    0.

  -----------------------------------------------------------------------------

* **Expressão constante**: expressão que contém somente valores constantes;
  pode ser usada em qualquer lugar onde uma constante também pode.
  
  ```C
  `#define MAXLINE 1000`  
  `char line[MAXLINE + 1];`
  ```

* **Constante-string**: também conhecida como *string literal*, consiste
  em uma sequência de zero ou mais caracteres entre aspas duplas.
  - `"Eu sou uma string"`
  - `"" /* a string vazia */`
  - Constantes-string podem ser concatenadas: `"hello," "world"`
  - Pode-se utilizar a função `strlen(s)` da biblioteca padrão para se calcular
    o comprimento de uma dada string `s`, ignorando o `\0` final.
  - `strlen(s)` e outras funções de string estão declaradas no header padrão
    `<string.h>`.

  -----------------------------------------------------------------------------

  - **OBS**: Ter cuidado com a diferença entre:

    + `'x'` → constante-caractere
    + `"x"` → constante-string

    O primeiro é um inteiro equivalente ao caractere `x` no charset da máquina,
    o segundo é uma string contendo um caractere `x` e um `\0`.

  -----------------------------------------------------------------------------

* **Constante de enumeração**: é uma lista de valores inteiros constantes.
  - Primeiro nome tem valor 0, segundo nome tem valor 1, etc.…, a não ser que
    especificado.
  - Valores não especificados continuam a progressão a partir do último valor
    especificado.  
    &nbsp;

  ```C
  enum boolean { NO, YES };

  enum escapes { BELL = '\a', BACKSPACE = '\b', TAB = '\t',
                 NEWLINE = '\n', VTAB = '\v', RETURN = '\r' };

  enum months { JAN = 1, FEB, MAR, APR, MAY, JUN,
                JUL, AUG, SEP, OCT, NOV, DEC };
                      /* FEB é 2, MAR é 3, etc. */
  ```

### 2.4 Declarations

