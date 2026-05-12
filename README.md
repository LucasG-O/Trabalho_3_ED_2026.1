# Matchmaking System - C++

## Descrição

Este projeto implementa um sistema simples de matchmaking para jogadores utilizando C++. O sistema permite:

* Inserir jogadores na fila
* Remover jogadores
* Ordenar jogadores por score e tempo de espera
* Formar grupos balanceados
* Listar jogadores aguardando

O projeto foi desenvolvido com foco em:

* Estruturas de dados
* Algoritmos de ordenação
* Manipulação manual de memória
* Complexidade computacional
* Programação orientada a objetos

---

# Estrutura do Projeto

```text
Matchmaking
├── Matchmaking.hpp
├── Matchmaking.cpp
├── Player.hpp
├── Player.cpp
└── main.cpp
```

---

# Classe Player

A classe `Player` representa um jogador na fila de matchmaking.

## Atributos esperados

| Atributo  | Descrição                      |
| --------- | ------------------------------ |
| id        | Identificador único do jogador |
| name      | Nome do jogador                |
| score     | Ranking/MMR do jogador         |
| timestamp | Momento de entrada na fila     |

## Métodos utilizados

```cpp
getId()
getName()
getScore()
getTimestamp()
```

---

# Classe Matchmaking

A classe `Matchmaking` é responsável por armazenar e organizar os jogadores.

---

# Funcionalidades

## Inserção de jogadores

```cpp
bool insert(Player player)
```

Insere um jogador na fila caso exista espaço disponível.

### Complexidade

```text
O(1)
```

---

## Remoção de jogadores

```cpp
bool removePlayer(int id)
```

Remove um jogador da fila através do ID.

Após a remoção, os elementos são deslocados para evitar espaços vazios.

### Complexidade

```text
O(n)
```

---

# Ordenação

O sistema possui duas implementações de ordenação:

---

## Insertion Sort

```cpp
void sortByScoreInsertion()
```

Ordena os jogadores utilizando:

1. Score crescente
2. Timestamp crescente em caso de empate

### Complexidade

| Caso        | Complexidade |
| ----------- | ------------ |
| Melhor caso | O(n)         |
| Médio caso  | O(n²)        |
| Pior caso   | O(n²)        |

---

## Merge Sort

```cpp
void sortByScoreMerge()
```

Implementação recursiva do algoritmo Merge Sort.

A ordenação utiliza:

1. Score crescente
2. Timestamp crescente em caso de empate

### Complexidade

```text
O(n log n)
```

---

## Método merge

```cpp
Player* merge(Player arr1[], int n,
              Player arr2[], int m)
```

Responsável por intercalar dois vetores ordenados.

---

## Método mergeSort

```cpp
Player* mergeSort(Player arr[], int n)
```

Divide recursivamente o vetor até obter subvetores unitários.

---

# Formação de grupos

```cpp
Player* formGroup(int groupSize, int delta, int* n)
```

Forma grupos balanceados considerando:

* tamanho do grupo
* diferença máxima de score (`delta`)

Um grupo é válido quando:

```text
maxScore - minScore <= delta
```

Como os jogadores estão ordenados por score, basta verificar:

* menor score do grupo
* maior score do grupo

Isso evita comparações desnecessárias.

### Complexidade

```text
O(n)
```

---

# Jogadores aguardando

```cpp
Player* getWaitingPlayers(int* n)
```

Retorna uma cópia dos jogadores presentes na fila.

---

# Impressão da fila

```cpp
void printWaitingPlayers()
```

Exibe todos os jogadores atualmente aguardando matchmaking.

---

# Gerenciamento de memória

O projeto utiliza:

```cpp
new[]
delete[]
```

para gerenciamento manual de memória dinâmica.

As alocações realizadas durante o Merge Sort e formação de grupos são liberadas corretamente utilizando `delete[]`.

---

# Critério de ordenação

A ordenação segue o seguinte critério:

1. Menor score primeiro
2. Em caso de empate, menor timestamp primeiro

Exemplo:

| Jogador | Score | Timestamp |
| ------- | ----- | --------- |
| A       | 1200  | 10        |
| B       | 1200  | 15        |

Resultado:

```text
A antes de B
```

---

# Exemplo de uso

```cpp
Matchmaking mm;

mm.insert(Player(1, "Gabriel", 1200, 10));
mm.insert(Player(2, "Lucas", 1250, 12));
mm.insert(Player(3, "Ana", 1210, 15));

mm.sortByScoreMerge();

int n;
Player* group = mm.formGroup(2, 100, &n);

mm.printWaitingPlayers();
```

---

# Conceitos aplicados

Este projeto utiliza diversos conceitos fundamentais de Ciência da Computação:

* Programação Orientada a Objetos
* Arrays estáticos e dinâmicos
* Ponteiros
* Recursão
* Algoritmos de ordenação
* Complexidade assintótica
* Manipulação manual de memória
* Estabilidade em ordenação

---

# Possíveis melhorias futuras

Algumas melhorias que poderiam ser implementadas:

* Uso de `std::vector`
* Smart pointers
* Matchmaking por regiões
* Sistema de prioridades
* Balanceamento mais avançado
* Busca binária para grupos
* Persistência em arquivo
* Concorrência/thread-safe

---

# Autor

Projeto desenvolvido para fins acadêmicos em disciplina de Estruturas de Dados / Programação Orientada a Objetos.
