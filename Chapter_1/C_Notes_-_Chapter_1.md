# The C Programming Language 2nd Edition — Anotações

## Chapter 1: A Tutorial Introduction

### 1.1 Getting Started

Exemplo de programa "hello, world" básico:

```C
#include <stdio.h>       // inclui info. sobre a biblioteca padrão
                         // as declarações de main são cercadas por chaves
main()                   // define função `main` que não recebe argumentos
{
    printf("hello, world\n");   /* main chama função `printf` da bibloteca
                                para imprimir esta sequência de caracteres */
                                // `\n` representa o caractere novalinha
}
```

Salvo em um sistema UNIX como `hello.c`, pode ser compilado com o comando:
`cc hello.c`

A compilação irá produzir um arquivo executável `a.out`, que, ao ser executado,
irá imprimir:

```text
hello, world
```

Um programa em C consiste de funções e variáveis

* Funções: Contém *declarações* que especificam as operações computacionais a
serem realizadas.
* Variáveis: armazenam valores usados durante a computação

Função `main`: especial. O programa sempre começa a ser executado do começo
da `main`.

`#include <stdio.h>`: diz ao compilador para incluir informações sobre a
biblioteca padrão de entrada/saída.

Argumentos: método de comunicação de dados entre funções. Denotado por
parênteses ao redor dos argumentos após o nome da função. No exemplo, a função
`main` é declarada como uma função que não espera argumentos, indicado pela
lista vazia `()`.

Algumas sequências de escape úteis:

* `\n` → nova linha
* `\t` → tab
* `\b` → backspace
* `\"` → aspas
* `\\` → contra barra

### 1.2 Variables and Arithmetic Expressions

Exemplo de programa que converte temperaturas em Fahrenheit para Celsius
através da seguinte fórmula: °C = (5/9)(°F-32)

```C
#include <stdio.h>

/* print Fahrenheit-Celsius table for fahr = 0, 20,..., 300 */
main()
{
    int fahr, celsius;
    int lower, upper, step;

    lower = 0;
    upper = 300;
    step = 20;

    fahr = lower
    while (fahr <= upper) {
        celsius = 5 * (fahr - 32) / 2;
        printf("%d\t%d\n", fahr, celsius);
        fahr = fahr + step;
    }
}
```

A execução deste programa resulta na seguinte tabela:

```text
1   -17
20  -6
40  4
60  15
80  26
100 37
120 48
140 60
160 71
180 82
200 93
220 104
240 115
260 126
280 137
300 148
```

Elementos do programa:

* `/* exemplo */`: representa uma ou mais linhas de comentário. Servem para
  tornar o programa mais fácil de ser compreendido. Todos os caracteres entre
  `/*` e `*/` são ignorados pelo compilador.
* `int fahr, celsius;`: declaração de variáveis, mais especificamente números
  do tipo inteiro. Em C, todas as variáveis devem ser declaradas antes de
  poderem ser utilizadas, usualmente no início da função antes de qualquer
  declarações executáveis.
  - Tipo `int`: indica que as variáveis listadas são números inteiros. A faixa
    de valores depende da máquina.
    + `int`s de *16-bits*: entre *-32768* e *+32767*.
    + `int`s de *32-bits*: entre *-2147483648* e *+2147483647*.
  - Tipo `float`: indica que as variáveis listadas são do tipo ponto-flutuante,
    i.e., números que podem possuir parte fracionária. Costumam ser quantidades
    de *32-bits* com pelo menos *seis dígitos significativos* e magnitude de
    valores entre *10^(-38)* e *10^38*.

Dentre os diversos tipos de dados em C, podemos também citar:

* `char` → character (caractere), um único byte.
* `short` → inteiro curto.
* `long` → inteiro longo.
* `double` → ponto-flutuante de precisão dupla.

O tamanho desses objetos depende da máquina.

<!-- HTML Table Preview =======================================================
 ┌─────────────────┬───┬──────────────────────────────┐
 │ • `lower = 0`   │   │                              │
 ├─────────────────┤ ⎫ │ Declarações de atribuição.   │
 │ • `upper = 300` │ ⎬ │ Atribui às variáveis os seus │
 ├─────────────────┤ ⎭ │ valores iniciais.            │
 │ • `step = 20`   │   │                              │
 └─────────────────┴───┴──────────────────────────────┘
=========================================================================== -->

<table>
  <tbody>
    <tr>
        <td>• <code>lower = 0</code></td>
        <td rowspan="3"><b>⎫<br>⎬<br>⎭</b></td>
        <td rowspan="3">Declarações de atribuição.<br>
                        Atribui às variáveis os seus<br>
                        valores iniciais
    </tr>
    <tr>
        <td>• <code>upper = 300</code></td>
    </tr>
    <tr>
        <td>• <code>step = 20</code></td>
    </tr>
  </tbody>
</table>

Para o cálculo de cada linha da tabela é usado um laço `while`, que repete uma
vez por linha da saída.

```C
while (fahr <= upper) {
    ...
}
```

Funcionamento do laço `while`:
A condição entre parênteses é testada. Caso verdadeira, o corpo do laço é
executado. Enquanto for verdadeira, o corpo do laço será reexecutado.

-------------------------------------------------------------------------------

**OBS**: Caso o corpo do laço seja composto de apenas uma declaração, ele pode
ser escrito sem chaves. Exemplo:

```C
while (i < j)
    i = 2 * i;
```

-------------------------------------------------------------------------------

Sempre ter cuidado com a indentação para garantir a legibilidade do código!

A principal lógica do programa se dá no corpo do laço através da atribuição:

```C
celsius = 5 * (fahr - 32) / 9;
```

IMPORTANTE: Devido a particularidades nas operações com `int`s, se faz
necessário multiplicar por 5 para em seguida dividir por 9. Caso a conta
`(fahr-32)` fosse multiplicada diretamente por 5/9, o resultado seria zero.
Como 5/9 resulta em um número com parte fracionária (5/9 ≈ 0.566) e a variável
é do tipo inteiro, a parte fracionária é truncada, isto é, descartada, de
maneira que uma operação em uma operação com inteiros o resultado de 5/9 é
igual a zero.

* `printf("%d\t%d\n", fahr, celsius);`: O `printf` é uma função de formatação
  de saída de propósito generalizado.
  - 1º argumento: `"%d\t%d\n"`: string a ser impressa. Cada `%□` indica um
      local onde os próximos argumentos serão substituídos, onde □ representa
      um caractere indicando o tipo de dado do argumento.
  - 2º e 3º argumentos: `fahr, celsius`: serão substituídos no local de cada
      `%d`, respectivamente.

-------------------------------------------------------------------------------

**OBS**: `printf` não é uma função nativa da linguagem C, e sim parte da
biblioteca padrão de funções `stdio.h`.

-------------------------------------------------------------------------------

O programa previamente escrito possui algumas características que podem ser
melhoradas.

* 1º problema: os dígitos da tabela não estão alinhados à direita.

Este problema é trivial de ser resolvido. Pode-se especificar a largura de cada
`%d` com um número, por exemplo: `printf("%3d%6d\n", fahr, celsius);`

Isto resulta em uma tabela onde o primeiro valor se encontra em um campo de
três dígitos de largura e o segundo valor em um campo com seis dígitos de
largura:

```text
  0   -17
 20     6
 40     4
 60    15
 80    26
100    37
...   ...
```

* 2º problema: a conversão de temperaturas não é muito acurada.

Este problema, mais grave, se dá devido ao uso de aritmética inteira. Como
exemplo, a temperatura de 0°F é aproximadamente -17.8°C e não -17°C. São
necessárias mudanças no programa para a realização de aritmética de ponto
flutuante.

```C
#include <stdio.h>

/* print Fahrenheit-Celsius table for fahr = 0, 20,..., 300, floating-point
   version */

main()
{
    float fahr, celsius;
    float lower, upper, step;

    lower = 0;
    upper = 300;
    step = 20;

    fahr = lower;
    while (fahr <= upper){
        celsius = (5.0/9.0) * (fahr - 32.0);
        printf("%3.0f%6.1f\n", fahr, celsius);
        fahr = fahr + step;
    }
}
```

Principais diferenças:

* `fahr` e `celsius` são do tipo `float`.
* Fórmula de conversão escrita naturalmente.

-------------------------------------------------------------------------------

**OBS**: Ao se utilizar um ponto decimal em uma constante indica-se que o seu
valor é do tipo ponto-flutuante.

* 5.0/9.0: **divisão de `float`s**, **resultado é `float`**
* 5.0/9: divisão de **`float` por `int`**, `int` é convertido em `float` antes
  do cálculo, **resultado é `float`**
* 5/9.0: divisão de **`int` por `float`**, `int` é convertido em `float` antes
  do cálculo, **resultado é `float`**
* 5/9: divisão de **`int` por `int`**, **resultado é `int`**. *Qualquer parte
  fracionária é truncada!*

Apesar da conversão automática de `int`s em `float`s em operações aritméticas
que misturem os tipos, é recomendado explicitar constantes do tipo ponto-
flutuante com a adição do ponto decimal. Por exemplo: `(fahr - 32.0)`. Tal
medida aumenta a clareza do seu programa para leitores humanos.

-------------------------------------------------------------------------------

A saída da nova versão do programa é a seguinte:

```text
  0  -17.8
 20   -6.7
 40    4.4
...    ...
```

A formatação da saída é ajustada através de parâmetros passados à `string` do
`printf`. `%3.0f`indica um número de ponto-flutuante com três dígitos de
largura e sem parte fracionária. `%6.1f` indica um número de ponto-flutuante
com seis dígitos de largura e m dígito após o ponto.

Algumas opções de formatação são as seguintes:

* `%d`    → decimal inteiro
* `%6d`   → decimal inteiro, pelo menos 6 caracteres de largura
* `%f`    → ponto-flutuante
* `%6f`   → ponto-flutuante, pelo menos 6 caracteres de largura
* `%.2f`  → ponto-flutuante, 2 caracteres após o ponto
* `%6.2f` → ponto-flutuante, pelo menos 6 caracteres de largura e 2 caracteres
  após o ponto

Outros tipos de dados reconhecidos por `printf` incluem: `%o` p/ octal, `%x` p/
hexadecimal, `%c` p/ caractere, `%s` p/ string e `%%` p/ si próprio.

-------------------------------------------------------------------------------

#### Exercícios 1.2

* [Exercise 1-3](./Exercise_1-03.c)  
* [Exercise 1-4](./Exercise_1-04.c)

-------------------------------------------------------------------------------

### 1.3 The `for` statement

Abaixo há uma variação do conversor de temperatura:

```C
#include <stdio.h>

/* print Fahrenheit-Celsius table */

main()
{
    int fahr;

    for (fahr = 0, fahr <= 300; fahr = fahr + 20)
        printf("%3d%6.1f\n", fahr, (5.0/9.0) * (fahr - 32));
}
```

Principal mudança: eliminação da maioria das variáveis. Somente `fahr` é
mantida e foi mudada para um tipo `int`.

Os limites superior e inferior e o tamanho do passo foram transformados em
constantes e a expressão de cálculo da temperatura em °C agora aparece como
terceiro argumento do `printf`.

Funcionamento do laço `for`:
Há três itens entre os parênteses, separados por ";". O primeiro item trata da
inicialização, antes de o laço ser iniciado. O segundo item é a condição de
teste; enquanto verdadeira o laço é executado. O terceiro item é o passo de
incremento, que é executado após a execução do corpo do laço. O laço é
finalizado quando a condição de teste (segundo item) se torna falsa.

Como escolher entre `while` e `for`? A escolha é arbitrária, dependendo apenas
de qual construção aparenta ser mais clara. O `for` é usualmente mais
apropriado para laços onde a inicialização e o incremento são declarações
únicas e relacionadas logicamente, pois é mais compacto que o `while`.

-------------------------------------------------------------------------------

#### Exercícios 1.3

* [Exercise 1-5](./Exercise_1-05.c)

-------------------------------------------------------------------------------

### 1.4 Symbolic Constants

É má prática esconder "números mágicos" como 300 ou 20 em um programa, pois
prejudica a compreensão do código e dificulta a alteração de valores de uma
maneira sistemática, caso seja necessária.

A melhor maneira de lidar com este problema é usar nome significativos. O uso
da linha:

```C
#define name replacement_text
```

define um *nome simbólico* ou *constante simbólica*. Qualquer ocorrência de
`name` será substituída por `replacement_text`.

```C
#include <stdio.h>

#define LOWER 0     /* lower limit of table */
#define UPPER 300   /* upper limit */
#define STEP 20     /* step size */

/* print Fahrenheit-Celsius table */
main()
{
    int fahr;

    for (fahr = LOWER; fahr <= UPPER; fahr = fahr + STEP)
        printf("%3d%6.1f\n", fahr, (5.0/9.0) * (fahr - 32));
}
```

-------------------------------------------------------------------------------

**OBS**: constantes simbólicas costumam ser escritas em caixa-alta.

-------------------------------------------------------------------------------

### 1.5 Character Input and Output

Consideraremos uma família de programas para o processamento de dados de
caractere.

O modelo de entrada e saída (E/S) suportado pela biblioteca padrão é baseado em
fluxos de caracteres. Um fluxo de texto (text stream) é uma sequência de
caracteres dividida em linhas; cada linha consiste em zero ou mais caracteres
seguidas por um caractere "nova linha".

A biblioteca padrão oferece diversas funções para a leitura ou escrita de um
caractere de cada vez. As mais simples são a `getchar`e `putchar`.

* `getchar`: cada vez que é chamada lê o próximo caractere de entrada de um
  fluxo de texto e o retorna como o seu valor. Ex: `c = getchar();`.
* `putchar`: cada vez que é chamada imprime o conteúdo da variável inteira
  `c` como um caractere, usualmente para a tela. Ex: `putchar(c);`.

#### 1.5.1 File Copying

Exemplo de programa que copia sua entrada para a sua saída um caractere por
vez:

```C
#include <stdio.h>

/* copy input to output; 1st version */
main()
{
    int c;

    c = getchar();
    while (c != EOF){        //O operador != significa "não é igual a"
        putchar(c)
        c = getchar();
    }
}
```

Todos os caracteres (na tela ou no teclado) são armazenados internamente como
um padrão de bits. O tipo `char` é específico para armazenar dados de
caractere, mas qualquer tipo inteiro pode ser usado. O tipo `int` foi utilizado
por um motivo importante.

Para se distinguir o final de uma entrada de outros dados válidos, é necessário
saber se o último caractere obtido é o `EOF` (end of file). A variável `c`
precisa ser declarada como um tipo grande o suficiente para armazenar tanto um
caractere quando o `EOF`.

Programadores de C mais experientes podem escrever esse programa de uma forma
mais compacta ao colocar a atribuição `c = getchar();` dentro do teste do laço
`while`:

```C
#include <stdio.h>

/* copy input to output; 2nd version */
main()
{
    int c;

    while ((c = getchar()) != EOF)
        putchar(c);
}
```

Esta é uma versão mais compacta do mesmo programa. Uma importante observação a
ser fazer é que os parênteses ao redor da atribuição dentro da condição são
necessários. A precedência de `!=` é maior do que a do `=`. Caso os parênteses
sejam omitidos a expressão:

```C
c = getchar() != EOF
```

é equivalente a:

```C
c = (getchar() != EOF)
```

Tendo o efeito indesejado de definir `c` como 0 ou 1, dependendo se a chamada
de `getchar` atingiu ou não o final do arquivo.

-------------------------------------------------------------------------------

##### Exercícios 1.5.1

* [Exercise 1-6](./Exercise_1-06.c)
* [Exercise 1-7](./Exercise_1-07.c)

-------------------------------------------------------------------------------

#### 1.5.2 Character Counting

O próximo programa conta caracteres; é similar ao programa de cópia.

```C
#include <stdio.h>

/* count characters in input, 1st version */
main()
{
    long nc;

    nc = 0;
    while (getchar() != EOF)
        ++nc;
    printf("%ld\n", nc);
}
```

A declaração `++nc` apresenta um novo operador, `++`, que significa *incremento
por um*; equivalente a `nc = nc + 1`. Mais detalhes no capítulo 2.

O programa de contagem de caracteres acumula sua contagem em um `long` ao invés
de um `int`. `long`s são pelo menos 32-bits. Como em algumas máquinas o tipo
`int` é 16-bits, com um valor máximo de 32767, algumas entradas poderiam causar
um overflow. `%ld` representa um argumento `long` ao `printf`.

O uso de um `double` (double precision `float`) permite o armazenamento de
números ainda maiores. Também é possível utilizar uma laço `for` para
reescrever o programa.

```C
#include <stdio.h>

/* count characters in input; 2nd version */
main()
{
    double nc;

    for (nc = 0; getchar() != EOF; ++nc)
        ;
    printf("%.0f\n", nc);
}
```

`printf` usa `%f` tanto para `float` quanto `double`; `%.0f` suprime a parte
decimal do número.

O corpo desse laço é vazio, pois todo o trabalho necessário já é realizado pelo
teste e o incremento. As regras gramaticais do C requerem que a declaração
`for` possua um corpo. O uso de um ponto-e-vírgula isolado, chamado de um *null
statement* (declaração nula), satisfaz esse requerimento.

-------------------------------------------------------------------------------

**OBS**: Nota-se que se uma entrada nula é fornecida ao programa, o teste do
laço falha após a primeira chamada de `getchar()`, produzindo zero, a resposta
certa. A vantagem do uso de laços como `for` e `while` é que o teste se dá
antes da execução do corpo; se o teste é falso, o corpo não é executado.
Programas devem saber lidar com entradas de tamanho zero e outras condições de
contorno.

-------------------------------------------------------------------------------

#### 1.5.3 Line Counting

Este próximo programa conta linhas de entrada. Como cada linha é terminada por
um "nova linha", basta contar os "nova linha".

```C
#include <stdio.h>

/* count lines in input */
main()
{
    int c, nl;

    nl = 0;
    while ((c = getchar()) != EOF)
        if (c == '\n')
            ++nl;
    printf("%d\n", nl);
}
```

Algumas observações podem ser feitas a respeito deste programa:

* O sinal `==` indica comparação, sendo assim diferente do `=` que é utilizado
  atribuição. ATENÇÃO: ter **muito cuidado** para não escrever um `=` quando se
  deseja realizar uma comparação!
* Um caractere escrito entre aspas simples representa um valor inteiro igual ao
  valor do caractere no conjunto de caracteres da máquina. Isto é conhecido
  como um *character constant*. Por exemplo: `'A'` vale `65` na tabela ASCII.
  Sequências de escape como `\n` também são *character constants* válidas;
  `\n` equivale a `10` na tabela ASCII.

-------------------------------------------------------------------------------

##### Exercícios 1.5.3

* [Exercise 1-8](./Exercise_1-08.c)
* [Exercise 1-9](./Exercise_1-09.c)
* [Exercise 1-10](./Exercise_1-10.c)

-------------------------------------------------------------------------------

#### 1.5.4 Word Counting

Este programa conta linhas, palavras e caracteres. Considera-se uma palavra
qualquer sequência de caracteres que não contém um espaço, tab ou nova linha.
Esta é uma versão simplificada do programa `wc` do UNIX.

```C
#include <stdio.h>

#define IN 1 /* inside a word */
#define OUT 0 /* outside a word */

/* count lines, words, and characters in input */

main()
{
    int c, nl, nw, nc, state;

    state = OUT;
    nl = nw = nc = 0;
    while ((c = getchar()) != EOF) {
        ++nc;
        if (c == '\n')
            ++nl;
        if (c == ' ' || c == '\n' || c = '\t')
            state = OUT;
        else if (state == OUT) {
            state = IN;
            ++nw;
        }
    }
    printf("%d %d %d\n", nl, nw, nc);
}
```

Uma breve descrição do funcionamento deste programa: para cada primeiro
caractere de uma palavra, uma nova palavra é contada. A variável `state`
acompanha se o programa está, ou não, em uma palavra atualmente.

Na linha `nl = nw = nc = 0;` pode-se notar o uso de uma multi-atribuição
simultânea, uma forma mais curta de definir todas as variáveis como zero.

O uso do operador `||` (OR/OU-Lógico) se aproveita de um curto-circuito, de
maneira que não se faz necessário analisar as outras expressões caso uma delas
seja verdadeira.

O uso dos condicionais `if/else` é intuitivo. Caso o teste no `if` seja
verdadeiro, a sua declaração é executada. Caso contrário somente a declaração
do `else` é executada.

-------------------------------------------------------------------------------

##### Exercícios 1.5.4

> *Exercise 1-11*: How would you test the word count program? What kinds of
> input are most likely to uncover bugs if there are any?

**R.**: A realização de testes de unidade pode ajudar a encontrar bugs ou casos
previamente não considerados (*edge cases*). O uso de palavras grandes,
pequenas e hifenizadas podem cobrir a maioria dos casos. Já para as condições
de contorno pode-se testar:

* Palavras com múltiplos espaços;
* Textos maiores que 2GB;
* Palavras hifenizadas sem espaço;
* Palavras com caracteres não-ASCII;
* Arquivos com diferentes codificações
* Caracteres de pontuação cercados por espaço em branco;
* Textos sem palavras;
* Textos com todas as palavras em uma única linha;

e muitos outros casos.

-------------------------------------------------------------------------------

* [Exercise 1-12](./Exercise_1.12.c)

-------------------------------------------------------------------------------

### 1.6 Arrays

Iremos escrever um programa para contar o número de ocorrências de cada dígito,
caracteres em branco (espaço, tab, nova linha), e outros caracteres.

Como há doze categorias de entrada é conveniente utilizar um vetor (array) para
guardar a ocorrência de cada um dos dígitos ao invés de utilizar dez variáveis.
O código do programa segue abaixo:

```C
#include <stdio.h>

/* count digits, white space, others */
main()
{
    int c, i, nwhite, nother;
    int ndigit[10];

    nwhite = nother = 0;
    for (i = 0; i < 10; ++i)
        ndigit[i] = 0;

    while ((c = getchar()) != EOF)
        if (c >= '0' && c <= '9')
            ++ndigit[c - '0'];
        else if (c == ' ' || c == '\n' || c == '\t')
            ++nwhite;
        else
            ++nother;

    printf("digits =");
    for (i = 0; i < 10; ++i)
        printf(" %d"m ndigit[i]);
    printf(", white space = %d, other = %d\n", nwhite, nother);
}
```

A saída deste programa tendo como entrada a si mesmo é:

```text
digits = 9 3 0 0 0 0 0 0 0 1, white space = 123, other = 345
```

A declaração `int ndigit[10]` declara `ndigit` como um vetor de 10 inteiros.
Os subscritos de um vetor sempre começam do zero em C, então os elementos são
`ndigit[0], ndigit[1], ..., ndigit[9]`. Isto se reflete nos laços `for` que
inicializam e imprimem o vetor.

Um subscrito pode ser qualquer expressão inteira, o que inclui variáveis
inteiras como `i`, e constantes inteiras.

Este programa depende das propriedades da representação de caracteres dos
dígitos  O teste `if(c >= '0' && c <= '9')` determina se o caractere em `c` é
um dígito. Se for, o valor numérico daquele dígito é `c - '0'`. Isto só
se `'0', '1', ..., '9'` tem valores crescentes consecutivamente. Felizmente,
isto é válido para todos os conjuntos de caracteres.

Por definição, `char`s são apenas inteiros pequenos, então variáveis `char`s e
constantes são idênticas a `int`s em operações aritméticas. Isto é natural e
conveniente; por exemplo `c - '0'` é uma expressão inteira com um valor entre 0
e 9 correspondendo ao caractere `'0'` ao `'9'` armazenado em `c`, e portanto
um subscrito válido para o vetor `ndigit`.

A sequência no laço `while` decide se o caractere é um dígito, branco, ou outro
tipo.

-------------------------------------------------------------------------------

**OBS**: O padrão condicional `if/else if/.../else` representa um decisão
multi-caminho. Se o último `else` for omitido e nenhum dos condicionais
anteriores for verdadeiro, nada será feito. O uso da declaração `switch` que
será discutida no capítulo 4, é uma alternativa para essa construção.

-------------------------------------------------------------------------------

#### Exercícios 1.6

* [Exercise 1-13](./Exercise_1-13.c)
* [Exercise 1-14](./Exercise_1-14.c)

-------------------------------------------------------------------------------

### 1.7 Functions

Uma função provê uma maneira conveniente de se encapsular alguma computação,
que pode então ser usada sem se preocupar a respeito de sua implementação.
Funções bem implementadas permitem ignorar *como* um trabalho é feito, saber
*o quê* é feito é suficiente.

Como o C não possui um operador de exponenciação, iremos escrever uma função
`power(m,n)`, por razões ilustrativas, para elevar um inteiro `m` a uma
potência inteira positiva `n`. A biblioteca padrão já possui uma função
`pow(x,y)` que calcula $x^y$.

```C
#include <stdio.h>

int power(int m, int n);

/* test power function */
main()
{
    int i;

    for (i = 0; i < 10; ++i)
        printf("%d %d %d\n", i, power(2,i), power(-3,i));
    return 0;
}

/* power: raise base to n-th power; n >= 0 */
int power(int base, int n){
    int i, p;

    p = 1;
    for (i = 1; i <= n; ++i)
        p = p * base;
    return p;
}
```

-------------------------------------------------------------------------------

**OBS**: A linha `int power(int m, int n)` representa a *declaração* da função.
O bloco de código na parte de baixo é a *definição* da função.

A partir da versão 1999 do padrão ISO C, é ilegal (uma violação de restrição)
chamar uma função sem uma declaração visível; a declaração precisa preceder a
chamada.

Para um simples programa como este, pode-se simplesmente escrever a
definição completa de `power()` antes da definição de `main()` (pois uma
definição também provê uma declaração), mas para casos mais complexos (como
chamadas recursivas) frequentemente é necessário prover uma declaração
separada.

Para programas maiores, é comum coletar todas as *declarações* de funções em um
arquivo de cabeçalho (`foo.h`, por exemplo), e as definições correspondentes em
um arquivo fonte (`foo.c`, por exemplo). Uma diretiva `#include "foo.h"` é
usada para fazer as declarações visíveis em outros arquivos. Isto é
frequentemente visto mais a frente no livro.

(Nas versões de 1990 e anteriores do C, que é o que o K&R2 cobre, existem casos
onde você pode chamar uma função sem uma declaração visível -- mas ainda é uma
boa ideia prover declarações explícitas de qualquer forma.)

Incidentalmente, a declaração do programa principal na verdade deveria ser
`int main(void)` ao invés de apenas `main()`.

Terminologia: um "protótipo" é uma declaração de função que especifica os tipos
dos parâmetros.

```C
int power(int base, int n);     /* uma declaração que também é um protótipo */
int power(int, int);            /* a mesma coisa */
int power();                    /* uma declaração mas não um protótipo */
```

(Nomes de parâmetros são necessários em uma definição, mas opcionais em uma
declaração individual.)

Como um caso especial, o protótipo para uma função sem parâmetros usa `(void)`,
pois parênteses vazios já indicam uma declaração não-prototípica. Então
`int main(void)` é um protótipo, mas `int main()` não é.

Declarações não-prototípicas são "obsolescentes", o que significa que elas
podem em teoria ser removidas em um futuro padrão da linguagem. Mas elas são
obsolescentes desde 1989, e até mesmo no novo padrão ISO C de 2011 o comitê não
achou apropriado removê-las.

-------------------------------------------------------------------------------

**Excelente resposta de Keith Thompson no
[stackoverflow](https://stackoverflow.com/questions/8827170)**

-------------------------------------------------------------------------------

Definições de funções podem aparecer em qualquer ordem, em um arquivo fonte ou
vários, apesar de nenhuma função poder ser dividida entre arquivos.

A função `power` é chamada duas vezes por `main`, na linha
`printf("%d %d %d\n", i, power(2,i), power(-3,i));`. As chamadas de `power`
como argumento no `printf` tem tipo inteiro (`%d`) pois a função `power`, como
previamente declarada, tem como retorno um `int`.

* Variável → argumento real
* Parâmetro → argumento formal

A primeira linha de uma função, como `int power(int base, int n)` declara os
tipos e nomes dos parâmetros, e o tipo do resultado que a função retorna. Os
nomes usados para os parâmetros de `power` são locais a ela, de maneira que
outras rotinas podem usar os mesmos nomes para suas variáveis sem risco de
conflito.

O retorno da função é dada pela linha `return p`, onde `p` pode ser qualquer
expressão. Uma função não precisa retornar um valor, sendo possível assim
retornar somente por uma questão de controle de fluxo.

A função `main`, como qualquer outra, pode retornar um valor; este valor é
retornado ao ambiente de execução do programa. Por costume:

* retorno == 0 → terminação normal
* retorno != 0 → erro ou condição não-usual de terminação.

A declaração `int power(int base, int n);` é um *protótipo de função*. Ela diz
a `main` que `power` é uma função que espera dois argumentos `int` e retorna um
`int`. Este protótipo tem que concordar com a definição e usos de `power`, caso
contrário isto é considerado um erro.

Os nomes dos parâmetros do protótipo de uma função não precisam ser iguais aos
nomes dos parâmetros da definição da função, sendo, inclusive, opcionais; o
protótipo poderia ter sido escrito como `int power(int, int)`. Nomes
bem-escolhidos, porém, são boa documentação.

-------------------------------------------------------------------------------

#### Exercícios 1.7

* [Exercise 1-15](./Exercise_1.15.c)

-------------------------------------------------------------------------------

### 1.8 Arguments - Call by Value

Um aspecto de funções em C que pode ser não-familiar a programadores de outras
linguagens (como Fortran), é que todos os argumentos de uma função são passados
"por valor". A função chamada é passada cópias dos valores dos argumentos ao
invés dos argumentos em si.

Abaixo há um exemplo de uma versão de `power` que faz uso deste recurso.

```C
/* power: raise base to n-th power; n >= 0; version 2 */
int power(int base, int n)
{
    int p;

    for (p = 1; n > 0; --n)
        p = p * base;
    return p;
}
```

O parâmetro `n` é utilizado como uma variável temporária, e é decrementado até
chegar a zero. Não há necessidade de uma variável `i`. O que quer que seja
feito a `n` dentro de `power` não tem efeito no argumento original.

Caso seja necessário, é possível fazer uma função modificar diretamente o valor
de uma variável. Neste caso, a chamada deve prover o endereço da variável (um
*ponteiro* para a variável) e a função deve declarar seu argumento como do tipo
ponteiro. Ponteiros são cobertos no Capítulo 5.

Isto é diferente para vetores. Quando um vetor é usado como argumento de uma
função, o endereço do início do vetor é passado, não uma cópia dos elementos do
vetor.

### 1.9 Character Arrays

O tipo de vetor mais comum em C é o vetor de caracteres. Para melhor ilustrar o
uso desta estrutura, escreveremos um programa que lê um conjunto de linhas de
texto e imprime a mais longa.

Iremos dividir esse programa em duas funções: uma que lê a próxima linha
(`getline`) e outra que salva a nova linha caso ela seja a mais longa que a
linha mais longa anterior.

```C
#include <stdio.h>
#define MAXLINE 1000    /* maximum input line length */

int getline(char line[], int maxline);
void copy(char to[], char from[]);

/* print the longest input line */
main()
{
    int len;            /* current line length */
    int max;            /* maximum length seen so far */
    char line[MAXLINE];     /* current input line */
    char longest[MAXLINE];  /* longest line saved here */

    max = 0;
    while ((len = getline(line, MAXLINE)) > 0)
        if (len > max) {
            max = len;
            copy(longest, line);
        }
    if (max > 0)    /* there was a line */
        printf("%s", longest);
    return 0;
}

/* getline: read a line into s, return length */
int getline(char s[], int lim)
{
    int c, i;

    for (i=0; i<lim-1 && (c=getchar())!=EOF && c!='\n'; ++i)
        s[i] = c;
    if (c == '\n') {
        s[i] = c;
        ++i;
    }
        s[i] = '\0';
    return i;
}

/* copy: copy 'from' into 'to'; assume to is big enough */
void copy(char to[], char from[])
{
    int i;

    i = 0;
    while ((to[i] = from[i]) != '\0')
        ++i
}
```

As funções `main` e `getline` se comunicam através de um par de argumentos e o
valor de retorno. Nota-se que o segundo argumento de `getline` indica para a
função o tamanho limite do vetor de entrada.

Funções que não possuem um valor de retorno, são do tipo `void`, como é o caso
de `copy`.

`getline` coloca o caractere `'\0'` (o *caractere nulo*, cujo valor é zero) no
final do vetor que este cria, determinando, assim, o final da sequência de
caracteres.

Para toda string constant como `"hello\n"`, que aparace em um programa em C,
esta é armazenada em um vetor de caracteres contendo os caracteres da string e
terminado com um `'\0'`.

    ┌─────┬─────┬─────┬─────┬─────┬──────┬──────┐
    │  h  │  e  │  l  │  l  │  o  │  \n  │  \0  │
    └─────┴─────┴─────┴─────┴─────┴──────┴──────┘

A especificação do formato `%s` do `printf` espera que o argumento seja uma
string representada desta forma. `copy` também depende do fato de que o seu
argumento de entrada é terminado por `'/0'`. É importante notar que `'/0'` não
faz parte do texto normal.

Uma consideração deve ser dada ao gerenciamento de memória do programa. Apesar
de este exemplo ser simples, deve se ter cuidado para não inserir mais dados do
que um vetor pode armazernar. Neste programa, `lim` impede que mais dados sejam
inseridos do que foi alocado ao vetor. Overflows podem ser catastróficos em
programas maiores, resultando em graves problemas e possíveis falhas de
segurança.

-------------------------------------------------------------------------------

#### Exercícios 1.9

* [Exercise 1-16](./Exercise_1-16.c)
* [Exercise 1-17](./Exercise_1-17.c)
* [Exercise 1-18](./Exercise_1-18.c)
* [Exercise 1-19](./Exercise_1-19.c)

-------------------------------------------------------------------------------

### 1.10 External Variables and Scope

Variáveis declaradas em uma função são privadas ou locais aquela função.
Nenhuma outra função pode ter acesso direto a elas (`line`, `longest`, etc só
são acessíveis em `main`). Varíaveis com o mesmo nome em diferentes funções
(como `i` em `getline` e `i` em `copy`) também não possuem relação entre si.
Variáveis só existem enquanto a função é chamada, desaparecendo após a sua
saída; estas possuem o nome de *variáveis automáticas*.

Variáveis automáticas não retem seu valor entre chamadas, sendo necessário a
definição de seus valores a cada chamada, caso contrário, elas irão conter
lixo.

Uma alternativa é utilizar varíaveis externas a todas as funções. Como
variáveis externas são globalmente acessíveis, elas podem ser usadas ao invés
de listas de argumentos para a comunicação de dados entre funções. Além disso,
elas retém sua existência permanentemente, mantendo assim seus valores.

Uso de uma variável externa:

* *definição*: necessária uma única vez, fora de qualquer função, **reserva
  espaço para a variável**.
* *declaração*: uma variável também precisa ser declarada em cada função que
  quer acessá-la; isto determina o tipo da variável, **espaço não é alocado**.
  A declaração pode ser um `extern` explícito ou ser implícito do contexto.

Abaixo segue uma nova versão do programa longest-line com variáveis externas.

```C
#include <stdio.h>

#define MAXLINE 1000    /* maximum input line size */

int max;                /* maximum length seen so far */
char line[MAXLINE];     /* current input line */
char longest[MAXLINE];  /* longest line saved here */

int getline(void);
void copy(void);


/* print longest input line; specialized version */
main()
{
    int len;
    extern int max;
    extern char longest[];

    max = 0;
    while ((len = getline ()) > 0)
        if (len > max) {
            max = len;
            copy();
        }
    if (max > 0)    /* there was a line */
        printf("%s", longest);
    return 0;
}

/* getline:  specialized version */
int getline(void)
{
    int c, i;
    extern char line[];

    for (i = 0; i < MAXLINE - 1
        && (c=getchar()) != EOF && c != '\n'; ++i)
            line[i] = c;
    if (c == '\n') {
        line[i] = c;
        ++i;
    }
    line[i] = '\0';
    return i;
}

/* copy:  specialized version */
void copy(void)
{
    int i;
    extern char line[], longest[];

    i = 0;
    while ((longest[i] = line[i]) != '\0')
        ++i;
}
```

As variáveis externas são definidas nas primeiras linhas das funções acima, que
afirmam seu tipo e alocam armazenamento. Definições externas são sintaticamente
iguais a definições de variáveis locais. Antes de uma função poder usar uma
variável externa, o nome da variável precisa ser passado a função; isto pode
ser feito usando a palavra reservada `extern`.

Em alguns casos a declaração `extern` pode ser omitida. Se a definição de uma
variável externa ocorre diretemante no arquivo fonte antes de seu uso em alguma
função, então não é necessário o uso de `extern`. Neste exemplo, o uso desta
declaração se faz redundante.

No caso de um programa que é dividido entre vários arquivos, se uma variável é
declara em um *arquivo1* e usada no *arquivo2* e *arquivo3*, as declarações
`extern` se fazem necessárias. O mais comum é agrupar todas as declarações
`extern` de variáveis e funções em um arquivo separado, conhecido como
*header*, incluído com um `#include` no início de cada arquivo fonte (Ex:
`<stdio.h>`).

As versões especializadas de `getline` e `copy` não possuem argumentos, mas
usam a palavra `void` para explicitar uma lista vazia por razões de
compatibilidade com programas C mais antigos.

-------------------------------------------------------------------------------

**OBS**: Prestar atenção na diferença entre "definição" e "declaração"
previamente citadas!

-------------------------------------------------------------------------------

Apesar de parecer simplificar comunicações, o uso de variáveis externas possui
diversos riscos e desvantagens: variáveis podem ser mudadas de maneiras
inesperadas e o programa se torna mais difícil de modificar. A segunda versão
deste programa é inferior a primeira, tanto por estas razões quanto pelo fato
de que ele destrói a generalização e versatilidade das duas funções.

-------------------------------------------------------------------------------

#### Exercícios 1.10

* [Exercise 1-20](./Exercise_1-20.c)
* [Exercise 1-21](./Exercise_1-21.c)
* [Exercise 1-22](./Exercise_1-22.c)
* [Exercise 1-23](./Exercise_1-23.c)
* [Exercise 1-24](./Exercise_1-24.c)

-------------------------------------------------------------------------------
