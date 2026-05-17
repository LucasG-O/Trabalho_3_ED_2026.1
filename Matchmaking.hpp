#ifndef MATCHMAKING_HPP
#define MATCHMAKING_HPP

#include "Player.hpp"
#define MAX_PLAYERS 100000
class Matchmaking {

private:

    Player players[MAX_PLAYERS]; // Fila de jogadores esperando para formar grupos
    int size;
    Player* merge(Player* left, int leftSize, Player* right, int rightSize);
    Player* mergeSort(Player arr[], int n);

public:

    Matchmaking();
    ~Matchmaking();

    bool insert(Player player);
    bool removePlayer(int id);

    void sortByScoreInsertion();
    void sortByScoreMerge();

    Player* formGroup(int groupSize, int delta, int* n);

    Player* getWaitingPlayers(int* n);

    void printWaitingPlayers();

    // Outros métodos auxiliares, se necessário
};
#endif