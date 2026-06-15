# Computação de Alto Desempenho (ECI) — Trabalho 1

[![MPI](https://img.shields.io/badge/MPI-OpenMPI-blue.svg)](https://www.open-mpi.org/)
[![Language](https://img.shields.io/badge/Language-C-green.svg)](https://en.wikipedia.org/wiki/C_(programming_language))
[![Platform](https://img.shields.io/badge/Platform-Linux-orange.svg)](https://en.wikipedia.org/wiki/Linux)
[![UFRJ](https://img.shields.io/badge/UFRJ-Escola%20Polit%C3%A9cnica-blue)](https://ufrj.br/)

Este repositório contém a resolução do **Trabalho 1** da disciplina de **Computação de Alto Desempenho** do curso de Engenharia de Computação e Informação (ECI) da Universidade Federal do Rio de Janeiro (UFRJ). O projeto consiste na implementação, análise e medição de algoritmos paralelos utilizando a especificação **MPI (Message Passing Interface)**.

---

## 📁 Estrutura do Repositório

O repositório está organizado rigidamente conforme os requisitos do edital, contendo uma pasta para cada conjunto de exercícios e o relatório final em formato PDF na raiz:

```text
.
├── relatorio.pdf               # Relatório analítico completo das atividades
├── ex1_hello_os/               # Exercício 1: Introspecção do SO e Topologia em Anel
│   ├── hello_os.c
│   ├── hello_ring.c
│   └── Makefile
├── ex2_trap/                   # Exercício 2: Regra do Trapézio Generalizada e Escalabilidade
│   ├── mpi_trap_generalized.c
│   └── Makefile
├── ex3_psum/                   # Exercício 3: Soma Paralela com Comunicação Ponto-a-Ponto
│   ├── mpi_psum.c
│   └── Makefile
├── ex4_coletivas/              # Exercício 4: Práticas de Comunicação Coletiva (Gather/Reduce)
│   ├── hello_gather.c
│   ├── minmax.c
│   └── Makefile
├── ex5_vecadd/                 # Exercício 5: Soma de Vetores com Scatter, Gather e Allgather
│   ├── mpi_vecadd_gather.c
│   ├── mpi_vecadd_allgather.c
│   └── Makefile
└── ex6_derived/                # Exercício 6: Tipos de Dados Derivados MPI vs Multi-Broadcast
    ├── student_struct.c
    ├── student_three_bcasts.c
    └── Makefile
## 🛠️ Descrição dos Exercícios

### [Exercício 1] Variantes do Hello World
> **Enunciado original:** > - (a) Faça cada processo reportar não apenas seu rank MPI, mas também os fatos do SO: seu PID e o núcleo de CPU em que está rodando.
> - (b) Variante em anel: O processo $k$ envia sua saudação ao processo $(k+1) \bmod p$ e recebe do processo $(k-1+p) \bmod p$ evitando deadlocks.

* `hello_os.c`: Programa introspectivo que consulta dados do sistema operacional (`getpid` e `sched_getcpu`) para mapear o escalonamento dinâmico de processos concorrentes sobre os núcleos de CPU físicos.
* `hello_ring.c`: Implementação de uma topologia de rede em anel lógico usando a primitiva atômica e segura `MPI_Sendrecv` para evitar cenários de deadlock.

---

### [Exercício 2] Regra do Trapézio, Generalizada
> **Enunciado original:** > - (a) Balanceamento de carga para $n$ arbitrário (sem assumir que $n$ é divisível por $p$).
> - (b) Estudo de escalabilidade forte medindo o tempo $T_p$, o Speedup $S_p$ e a Eficiência $E_p$.
> - (c) Verificação empírica da convergência $O(h^2)$ da regra do trapézio.

* `mpi_trap_generalized.c`: Cálculo de integração numérica para funções contínuas arbitrariamente divididas. Implementa balanceamento dinâmico de carga e inclui suporte para análises de escalabilidade forte e convergência empírica de segunda ordem em espaço bi-logarítmico.

---

### [Exercício 3] Soma Paralela (Ponto-a-Ponto)
> **Enunciado original:** O processo 0 gera um vetor de $N$ doubles, distribui $N/p$ elementos a cada processo via laço de `MPI_Send`. Cada rank calcula uma soma local e envia de volta ao rank 0, que reduz por adição e compara o erro relativo com a soma serial.

* `mpi_psum.c`: Pipeline manual de dispersão e redução de um vetor com $10^5$ elementos de ponto flutuante via laços explícitos de comunicação ponto-a-ponto. Demonstra desvios aritméticos causados pela perda de associatividade da norma IEEE 754 na soma paralela.

---

### [Exercício 4] Prática de Comunicação Coletiva
> **Enunciado original:** > - (a) Reescreva o Hello World de modo que o processo 0 use `MPI_Gather` para coletar as saudações em um único vetor.
> - (b) Distribua um vetor de doubles via `MPI_Scatter` e calcule o máximo e o mínimo global usando `MPI_Reduce`.

* `hello_gather.c`: Refatoração do Hello World utilizando funções de coleta para centralizar dados estruturados de texto em ordem estrita de rank.
* `minmax.c`: Dispersão de uma carga massiva e cálculo simultâneo dos extremos absolutos globais através das primitivas `MPI_MIN` e `MPI_MAX` consolidadas em chamadas unificadas de redução.

---

### [Exercício 5] Soma Paralela de Vetores (Scatter / Gather)
> **Enunciado original:** O processo 0 inicializa dois vetores, `MPI_Scatter` distribui os blocos, cada processo calcula a soma $z = x + y$, e o `MPI_Gather` coleta de volta. Estenda o programa com uma versão usando `MPI_Allgather`.

* `mpi_vecadd_gather.c`: Soma paralela clássica de dois blocos lineares de vetores com consolidação exclusiva no processo raiz.
* `mpi_vecadd_allgather.c`: Extensão que combina coleta e difusão de dados de forma omnidirecional, reconstruindo o vetor resultante de maneira síncrona em todas as memórias isoladas do cluster.

---

### [Exercício 6] Um Tipo de Dado Derivado MPI
> **Enunciado original:** Defina um tipo derivado para uma estrutura customizada (`Student`). Transmita os dados usando uma única chamada `MPI_Bcast` com `offsetof` e compare com um programa equivalente que usa três chamadas separadas.

* `student_struct.c`: Construção e validação de layouts heterogêneos personalizados na memória via `MPI_Type_create_struct`. Permite o envio de dados complexos agrupados pagando a latência de rede apenas uma vez.
* `student_three_bcasts.c`: Versão "ingênua" que fragmenta o envio da estrutura em 3 chamadas consecutivas, servindo como base comparativa para a análise de overhead de comunicação.

---

## 🚀 Como Compilar e Executar

Cada diretório possui um arquivo `Makefile` autônomo projetado para seguir estritamente as regras de compilação da disciplina.

### Comandos Padrão (Ambiente com Núcleos Suficientes)
Para compilar, executar com os parâmetros padrão definidos pelo edital e limpar os arquivos binários gerados, entre na pasta do exercício desejado e utilize os comandos:

```bash
# 1. Compilar o código-fonte gerando os binários com flags de otimização
make

# 2. Executar o programa paralelizado no cluster
make run

# 3. Remover os executáveis locais e manter a pasta limpa
make clean
