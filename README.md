```python
readme_content = """# Computação de Alto Desempenho (ECI) — Trabalho 1

[![MPI](https://img.shields.io/badge/MPI-OpenMPI-blue.svg)](https://www.open-mpi.org/)
[![Language](https://img.shields.io/badge/Language-C-green.svg)](https://en.wikipedia.org/wiki/C_(programming_language))
[![Platform](https://img.shields.io/badge/Platform-Linux-orange.svg)](https://en.wikipedia.org/wiki/Linux)
[![UFRJ](https://img.shields.io/badge/UFRJ-Escola%20Polit%C3%A9cnica-blue)](https://ufrj.br/)

Este repositório contém a resolução do **Trabalho 1** da disciplina de **Computação de Alto Desempenho** do curso de Engenharia de Computação e Informação (ECI) da Universidade Federal do Rio de Janeiro (UFRJ). O projeto consiste na implementação, análise e medição de algoritmos paralelos utilizando a especificação **MPI (Message Passing Interface)**.

---


## 📁 Estrutura do Repositório

O repositório está organizado rigidamente conforme os requisitos do edital, contendo uma pasta para cada conjunto de exercícios e o relatório final em formato PDF na raiz:


```

```text
README.md criado com sucesso.

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

```

---

## 🛠️ Descrição dos Exercícios

### [Exercício 1] Variantes do Hello World

* **`hello_os.c`**: Programa introspectivo que consulta dados do sistema operacional (`getpid` e `sched_getcpu`) para mapear o escalonamento dinâmico de processos concorrentes sobre os núcleos de CPU físicos.
* **`hello_ring.c`**: Implementação de uma topologia de rede em anel lógico usando a primitiva atômica e segura `MPI_Sendrecv` para evitar cenários de *deadlock*.

### [Exercício 2] Regra do Trapézio Generalizada

* **`mpi_trap_generalized.c`**: Cálculo de integração numérica para funções contínuas arbitrariamente divididas. Implementa balanceamento dinâmico de carga para casos onde o número de trapézios $n$ não é perfeitamente divisível pelo número de processos $p$ ($p \nmid n$). Inclui análise de escalabilidade forte e convergência empírica de segunda ordem $O(h^2)$.

### [Exercício 3] Soma Paralela Ponto-a-Ponto

* **`mpi_psum.c`**: Pipeline manual de dispersão e redução de um vetor com $10^5$ elementos de ponto flutuante via laços explícitos de `MPI_Send` e `MPI_Recv`. Demonstra e discute desvios aritméticos causados pela perda de associatividade da norma IEEE 754.

### [Exercício 4] Comunicação Coletiva Base

* **`hello_gather.c`**: Refatoração do Hello World utilizando `MPI_Gather` para centralizar dados estruturados de texto em ordem estrita de rank.
* **`minmax.c`**: Dispersão via `MPI_Scatter` de uma carga massiva e cálculo simultâneo dos extremos absolutos globais através das primitivas `MPI_MIN` e `MPI_MAX` em chamadas unificadas de `MPI_Reduce`.

### [Exercício 5] Soma Paralela de Vetores

* **`mpi_vecadd_gather.c`**: Soma paralela clássica de dois blocos lineares de vetores com consolidação exclusiva no processo raiz via `MPI_Gather`.
* **`mpi_vecadd_allgather.c`**: Extensão de engenharia que combina coleta e difusão de dados através do `MPI_Allgather`, reconstruindo o vetor final completo de forma simultânea em todas as memórias isoladas do cluster.

### [Exercício 6] Tipos de Dados Derivados

* **`student_struct.c`**: Construção e validação de layouts heterogêneos personalizados na memória via `MPI_Type_create_struct` e `offsetof`. Permite o envio unificado de dados complexos em apenas 1 transação de rede.
* **`student_three_bcasts.c`**: Versão comparativa que fragmenta o envio da estrutura em 3 chamadas consecutivas de `MPI_Bcast`, servindo de base para o estudo empírico de penalidades por latência (*overhead*).

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

```

### Execução Manual Direta

Caso queira disparar testes com números customizados de processos, todos os binários aceitam a sintaxe nativa do MPI:

```bash
# Compilação padrão exigida
mpicc -O2 -Wall -o <nome_do_programa> <nome_do_programa>.c -lm

# Execução com p processos
mpiexec -n <p> ./<nome_do_programa>

```

### 💡 Nota para Execução em Máquinas com Poucos Núcleos (Oversubscribe)

Caso realize testes locais em um ambiente de desenvolvimento pessoal que possua limitação de núcleos físicos de CPU (por exemplo, um notebook dual-core), as diretivas MPI nativas bloquearão execuções com $p > \text{núcleos}$. Para contornar este comportamento e testar o fatiamento de tempo concorrente do Sistema Operacional, adicione a flag de sobre-alocação:

```bash
mpiexec --oversubscribe -n 8 ./<nome_do_programa>

```

*(Nota: Os arquivos Makefile finais enviados neste repositório encontram-se limpos e sem essa flag, configurados para execução direta no ambiente de produção/cluster do professor).*
"""

with open("README.md", "w", encoding="utf-8") as f:
f.write(readme_content)

print("README.md criado com sucesso.")

```
O seu arquivo Markdown do README está pronto e foi gerado!
[file-tag: code-generated-file-0-1781490558708208791]

Além de você poder baixar o arquivo `.md` completo pelo link acima para colar na raiz do seu repositório, aqui está uma prévia de como ele vai ficar renderizado lá no GitHub. Ele foi pensado para ficar com uma cara super profissional, com *badges* (aqueles escudinhos coloridos no topo), formatação limpa e explicações claras para cada etapa do seu trabalho.

***

# Computação de Alto Desempenho (ECI) — Trabalho 1

[![MPI](https://img.shields.io/badge/MPI-OpenMPI-blue.svg)](https://www.open-mpi.org/)
[![Language](https://img.shields.io/badge/Language-C-green.svg)](https://en.wikipedia.org/wiki/C_(programming_language))
[![Platform](https://img.shields.io/badge/Platform-Linux-orange.svg)](https://en.wikipedia.org/wiki/Linux)
[![UFRJ](https://img.shields.io/badge/UFRJ-Escola%20Polit%C3%A9cnica-blue)](https://ufrj.br/)

Este repositório contém a resolução do **Trabalho 1** da disciplina de **Computação de Alto Desempenho** do curso de Engenharia de Computação e Informação (ECI) da Universidade Federal do Rio de Janeiro (UFRJ). O projeto consiste na implementação, análise e medição de algoritmos paralelos utilizando a especificação **MPI (Message Passing Interface)**.

---

## 👨‍💻 Autor

- **Nome:** Matheus Nunes da Silva
- **DRE:** 125381155
- **Professor:** Adriano Côrtes
- **Instituição:** Universidade Federal do Rio de Janeiro (UFRJ)
- **Data:** 28 de abril de 2026

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

```

---

## 🛠️ Descrição dos Exercícios

### [Exercício 1] Variantes do Hello World

* **`hello_os.c`**: Programa introspectivo que consulta dados do sistema operacional (`getpid` e `sched_getcpu`) para mapear o escalonamento dinâmico de processos concorrentes sobre os núcleos de CPU físicos.
* **`hello_ring.c`**: Implementação de uma topologia de rede em anel lógico usando a primitiva atômica e segura `MPI_Sendrecv` para evitar cenários de *deadlock*.

### [Exercício 2] Regra do Trapézio Generalizada

* **`mpi_trap_generalized.c`**: Cálculo de integração numérica para funções contínuas arbitrariamente divididas. Implementa balanceamento dinâmico de carga para casos onde o número de trapézios $n$ não é perfeitamente divisível pelo número de processos $p$ ($p \nmid n$). Inclui análise de escalabilidade forte e convergência empírica de segunda ordem $O(h^2)$.

### [Exercício 3] Soma Paralela Ponto-a-Ponto

* **`mpi_psum.c`**: Pipeline manual de dispersão e redução de um vetor com $10^5$ elementos de ponto flutuante via laços explícitos de `MPI_Send` e `MPI_Recv`. Demonstra e discute desvios aritméticos causados pela perda de associatividade da norma IEEE 754.

### [Exercício 4] Comunicação Coletiva Base

* **`hello_gather.c`**: Refatoração do Hello World utilizando `MPI_Gather` para centralizar dados estruturados de texto em ordem estrita de rank.
* **`minmax.c`**: Dispersão via `MPI_Scatter` de uma carga massiva e cálculo simultâneo dos extremos absolutos globais através das primitivas `MPI_MIN` e `MPI_MAX` em chamadas unificadas de `MPI_Reduce`.

### [Exercício 5] Soma Paralela de Vetores

* **`mpi_vecadd_gather.c`**: Soma paralela clássica de dois blocos lineares de vetores com consolidação exclusiva no processo raiz via `MPI_Gather`.
* **`mpi_vecadd_allgather.c`**: Extensão de engenharia que combina coleta e difusão de dados através do `MPI_Allgather`, reconstruindo o vetor final completo de forma simultânea em todas as memórias isoladas do cluster.

### [Exercício 6] Tipos de Dados Derivados

* **`student_struct.c`**: Construção e validação de layouts heterogêneos personalizados na memória via `MPI_Type_create_struct` e `offsetof`. Permite o envio unificado de dados complexos em apenas 1 transação de rede.
* **`student_three_bcasts.c`**: Versão comparativa que fragmenta o envio da estrutura em 3 chamadas consecutivas de `MPI_Bcast`, servindo de base para o estudo empírico de penalidades por latência (*overhead*).

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

```

### Execução Manual Direta

Caso queira disparar testes com números customizados de processos, todos os binários aceitam a sintaxe nativa do MPI:

```bash
# Compilação padrão exigida
mpicc -O2 -Wall -o <nome_do_programa> <nome_do_programa>.c -lm

# Execução com p processos
mpiexec -n <p> ./<nome_do_programa>

```
