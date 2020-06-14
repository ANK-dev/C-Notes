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
