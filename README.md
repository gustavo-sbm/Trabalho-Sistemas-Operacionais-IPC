# Trabalho-Sistemas-Operacionais-IPC
Este projeto é uma simulação de um sistema de restaurante focada no estudo de **Comunicação entre Processos (IPC)**. O objetivo é demonstrar como múltiplos processos podem interagir de forma coordenada utilizando *Pipes*.

## 📌 Sobre o Projeto

No cenário proposto, cada atendimento é tratado como um processo independente. A estrutura segue as seguintes premissas:
* **Comunicação:** Ocorre via **Pipes**.
* **Escalonamento:** Cada Chef atende apenas uma mesa por vez.
* **Sincronização:** Se todos os chefs estiverem ocupados, a mesa entra em uma fila de espera.

## 🛠️ Tecnologias Utilizadas

* **Linguagem:** C++ (Padrão C++20)
* **Conceitos de SO:** Criação de processos, Pipes e manipulação de arquivos.

## 🚀 Como Executar

### 1. Pré-requisitos
Certifique-se de ter um compilador C++ atualizado (GCC ou Clang) que suporte a versão C++20.

### 2. Compilação
Abra o terminal na pasta do projeto e execute:
```bash
g++ -std=c++20 *.cpp -o restaurante
```

### 3. Execução
```bash
./restaurante
```

# Guia de Uso

---

## Passo 1: Configuração Inicial
Na primeira linha da execução, digite a quantidade de mesas e chefs que o seu restaurante terá.

**Exemplo:** `3 10`

### Regras de Validação:
> [!IMPORTANT]  
> O sistema aceita apenas os seguintes intervalos:
> * $1 \le \text{quantidade de chefs} \le 100$
> * $\text{quantidade de chefs} \le \text{quantidade de mesas} \le (\text{quantidade de chefs} \times 4)$

---

## Passo 2: Adicionar Pedidos
Após a configuração, você pode adicionar os pedidos informando o número da mesa e o item:

**Exemplo:** `1 uva`

---

## Passo 3: Fila de Espera
Quando todos os chefs estiverem ocupados, a mesa entrará automaticamente em uma fila de espera.

* **Fluxo:** A mesa aguarda junto com seus respectivos pedidos.
* **Atendimento:** Assim que um chef for liberado, a próxima mesa da fila será prontamente atendida.
*
