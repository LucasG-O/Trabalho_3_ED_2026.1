# Matchmaking System — C++

## Descrição

Sistema de matchmaking para jogadores implementado em C++. A aplicação mantém uma fila de jogadores aguardando partida e oferece as seguintes operações:

- Inserção e remoção de jogadores por ID
- Ordenação por score (e timestamp como critério de desempate) via **Insertion Sort** ou **Merge Sort**
- Formação de grupos balanceados com diferença máxima de score configurável
- Consulta e exibição dos jogadores na fila

O projeto foi desenvolvido para a disciplina de Estruturas de Dados, com foco em algoritmos de ordenação, gerenciamento manual de memória e análise de complexidade.

---

## Organização dos arquivos

```
Trabalho_3_ED_2026.1/
├── Player.hpp        # Declaração da classe Player (id, name, score, timestamp)
├── Player.cpp        # Implementação dos métodos de Player
├── Matchmaking.hpp   # Declaração da classe Matchmaking e constante MAX_PLAYERS
├── Matchmaking.cpp   # Implementação das operações de matchmaking
└── main.cpp          # Testes funcionais e de desempenho
```

| Arquivo | Responsabilidade |
|---|---|
| `Player.hpp / .cpp` | Modela um jogador com seus atributos e getters |
| `Matchmaking.hpp / .cpp` | Gerencia a fila de jogadores e implementa os algoritmos |
| `main.cpp` | Executa os casos de teste e mede o tempo de ordenação |

---

## Instruções de compilação

### Pré-requisito

Compilador C++ com suporte a C++11 ou superior (g++ ou equivalente).

### Compilar com g++

```bash
g++ -std=c++11 -o matchmaking main.cpp Player.cpp Matchmaking.cpp
```

### Compilar

```bash
g++ main.cpp Matchmaking.cpp Player.cpp -o matchmaking
```

---

## Instruções de execução

Após compilar, execute o binário gerado:

```bash
# Linux / macOS
./matchmaking

# Windows
matchmaking.exe
```

A saída exibirá o resultado de cada teste diretamente no terminal.

---

## Testes no main.cpp

O `main.cpp` contém **8 testes** executados em sequência:

| # | Descrição | O que verifica |
|---|---|---|
| 1 | **Inserção básica** | Insere 5 jogadores com scores e timestamps variados e exibe a fila na ordem de inserção |
| 2 | **Insertion Sort com desempate** | Ordena por score crescente; jogadores com mesmo score são ordenados pelo timestamp |
| 3 | **Remoção por ID** | Remove a jogadora Luzia (ID 3) e confirma que os elementos são compactados |
| 4 | **Novos jogadores + Merge Sort** | Insere mais 3 jogadores e reordena toda a fila com Merge Sort |
| 5 | **Formação de grupo válida** | Tenta formar um grupo de 3 jogadores com delta ≤ 100; imprime o grupo e exibe a fila restante |
| 6 | **Formação de grupo sem sucesso** | Tenta formar grupo com delta ≤ 10 (impossível com os dados atuais); espera retorno `nullptr` |
| 7 | **getWaitingPlayers** | Recupera uma cópia dinâmica da fila e imprime quantos jogadores foram retornados |
| 8 | **Teste de desempenho** | Insere 20.000 jogadores aleatórios e mede, separadamente, o tempo do Insertion Sort e do Merge Sort |

> **Nota sobre o teste de desempenho (Teste 8):** o número de jogadores pode ser ajustado alterando a variável `numPlayers` na linha 84 do `main.cpp`. Para coletar dados comparativos para o relatório, experimente valores como 1.000, 5.000, 10.000 e 20.000.

---

## Autores

Projeto desenvolvido para fins acadêmicos na disciplina de Estruturas de Dados.
- Gabriel Bittencourt Dias
- Lucas Gabriel
