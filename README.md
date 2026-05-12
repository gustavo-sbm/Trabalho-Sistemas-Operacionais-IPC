# Fábrica Inteligente de Veículos
Trabalho 1 – Sistemas Operacionais – Processos

Este projeto é uma simulação de um sistema de controle de fábrica focada no estudo de **Comunicação entre Processos (IPC)**. O objetivo é demonstrar como múltiplos processos podem interagir de forma coordenada utilizando *Pipes*.

## 📌 Sobre o Projeto

No cenário proposto, cada atendimento de veículo é tratado como um processo independente. A estrutura segue as seguintes premissas:

* **Comunicação:** Ocorre via **Pipes**.
* **Escalonamento:** Cada robô atende apenas um veículo por vez.
* **Sincronização:** Se todos os robôs estiverem ocupados, o veículo entra em uma fila de espera.

## 🛠️ Tecnologias Utilizadas

* **Linguagem:** C++ (Padrão C++20)
* **Conceitos de SO:** Criação de processos, Pipes e manipulação de arquivos.

## 🚀 Como Executar

### 1. Pré-requisitos

Certifique-se de ter um compilador C++ atualizado (GCC ou Clang) que suporte a versão C++20.

### 2. Compilação

Abra o terminal na pasta do projeto e execute:
```bash
g++ -std=c++20 *.cpp -o fabrica
```

### 3. Execução
```bash
./fabrica
```

---

# Guia de Uso

## Passo 1: Configuração Inicial

Na primeira linha da execução, digite a quantidade de robôs e a capacidade máxima de veículos simultâneos na fábrica.

**Exemplo:** `3 10`

### Regras de Validação:

> [!IMPORTANT]
> O sistema aceita apenas os seguintes intervalos:
> * $1 \le \text{quantidade de robôs} \le 100$
> * $\text{quantidade de robôs} \le \text{quantidade de veículos} \le (\text{quantidade de robôs} \times 4)$

---

## Passo 2: Adicionar Tarefas

Após a configuração, você pode enviar tarefas informando o identificador do veículo e a tarefa desejada:

**Exemplo:** `4 instalar motor turbo`

Para encerrar o atendimento de um veículo, envie:

**Exemplo:** `4 fim`

---

## Passo 3: Fila de Espera

Quando todos os robôs estiverem ocupados, o veículo entrará automaticamente em uma fila de espera.

* **Fluxo:** O veículo aguarda junto com suas respectivas tarefas.
* **Atendimento:** Assim que um robô for liberado, o próximo veículo da fila será prontamente atendido.

---

## Passo 4: Encerramento

Para encerrar o programa, envie:

```
FIM
```

---

## 📄 Exemplo Completo

### Entrada
```
3 10
4 instalar motor turbo
3 pintura preta
8 revisao freios
3 instalar sensor estacionamento
5 troca oleo
4 polimento completo
8 alinhamento rodas
5 calibragem pneus
5 fim
3 instalacao led interno
4 fim
3 fim
8 teste rodagem
4 revisao eletrica
4 higienizacao interna
1 pintura vermelha
4 fim
8 diagnostico scanner
1 instalar central multimidia
1 fim
8 fim
FIM
```

### Arquivos Gerados

**Robo_1.txt**
```
Robo_1

Veiculo 4:
- instalar motor turbo
- polimento completo

Veiculo 5:
- troca oleo
- calibragem pneus

Veiculo 4:
- revisao eletrica
- higienizacao interna
```

**Robo_2.txt**
```
Robo_2

Veiculo 3:
- pintura preta
- instalar sensor estacionamento
- instalacao led interno

Veiculo 1:
- pintura vermelha
- instalar central multimidia
```

**Robo_3.txt**
```
Robo_3

Veiculo 8:
- revisao freios
- alinhamento rodas
- teste rodagem
- diagnostico scanner
```
