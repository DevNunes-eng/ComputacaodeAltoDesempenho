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

```bash
# 1. Compilar o código-fonte gerando os binários com flags de otimização
make

# 2. Executar o programa paralelizado no cluster
make run

# 3. Remover os executáveis locais e manter a pasta limpa
make clean
