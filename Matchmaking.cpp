#include "Matchmaking.hpp"
#include <iostream>

Matchmaking::Matchmaking() {
    this->size = 0;
}

bool Matchmaking::insert(Player player){
    if (this->size == MAX_PLAYERS) {
        return false; // players cheia
    }

    this->players[this->size] = player;
    this->size++;
    return true;
}

bool Matchmaking::removePlayer(int id){
    for (int i = 0; i < this->size; i++) {
        if (this->players[i].getId() == id) {
            // Remover o jogador e deslocar elementos
            for (int j = i; j < this->size - 1; j++) {
                this->players[j] = this->players[j + 1];
            }
            this->size--;
            return true; // Jogador removido com sucesso
        }
    }
    return false;
}

void Matchmaking::sortByScoreInsertion() {
    for(int i = 1; i < this->size; i++){
        Player key = this->players[i];
        int j = i - 1;
        while(j >= 0 && (this->players[j].getScore() > key.getScore()||(
            this->players[j].getScore() == key.getScore() && this->players[j].getTimestamp() > key.getTimestamp()))){
            this->players[j + 1] = this->players[j];
            j--;
        }
        this->players[j + 1] = key;
    }
}   

Player* Matchmaking::merge(Player arr1[], int n,
                           Player arr2[], int m) {

    Player* merged = new Player[n + m];

    int i = 0;
    int j = 0;

    while (i < n && j < m) {

        bool leftComesFirst =
            (arr1[i].getScore() < arr2[j].getScore()) ||
            (arr1[i].getScore() == arr2[j].getScore() && arr1[i].getTimestamp() < arr2[j].getTimestamp());

        if (leftComesFirst) {
            merged[i + j] = arr1[i];
            i++;
        } else {
            merged[i + j] = arr2[j];
            j++;
        }
    }

    while (i < n) {
        merged[i + j] = arr1[i];
        i++;
    }

    while (j < m) {
        merged[i + j] = arr2[j];
        j++;
    }

    return merged;
}

Player* Matchmaking::mergeSort(Player arr[], int n) {

    if (n == 1) {

        Player* single = new Player[1];

        single[0] = arr[0];

        return single;
    }

    int mid = n / 2;

    Player* left = mergeSort(arr, mid);
    Player* right = mergeSort(arr + mid, n - mid);

    Player* sorted = merge(left, mid, right, n - mid);

    delete[] left;
    delete[] right;
    return sorted;
}

void Matchmaking::sortByScoreMerge() {

    if (this->size <= 1)
        return;

    Player* sorted = mergeSort(this->players, this->size);

    for (int i = 0; i < this->size; i++) {
        this->players[i] = sorted[i];
    }

    delete[] sorted;
}


Player* Matchmaking::formGroup(int groupSize, int delta, int* n){
    if (this->size < groupSize) {
        *n = 0; // Não há jogadores suficientes para formar um grupo
        return nullptr;
    }
    int last; 
    int min;
    int max;

    for (int i = 0; i <= this->size - groupSize; i++) {
        last = i + groupSize - 1; // Pega o último jogador possível para o grupo
        min = this->players[i].getScore();
        max = this->players[last].getScore();
        if (max - min <= delta) {
            Player* group = new Player[groupSize];
            for (int j = 0; j < groupSize; j++) {
                group[j] = this->players[i + j];
            }
            for (int k = last + 1; k < this->size; k++) {
                this->players[k - groupSize] = this->players[k];
            }
            this->size -= groupSize;
            for (int t = this->size; t < this->size + groupSize; t++) {
                this->players[t] = Player(); // Limpa as posições restantes
            }
            *n = groupSize;
            return group; // Grupo formado com sucesso
        }
    }
    return nullptr;
}


Player* Matchmaking::getWaitingPlayers(int* n){
    if (this->size == 0) {
        *n = 0; // Não há jogadores esperando
        return nullptr;
    }
    *n = this->size; 
    Player* waitingPlayers = new Player[this->size];
    for(int i = 0; i < *n; i ++){
        waitingPlayers[i] = this->players[i];
    }
    return waitingPlayers;
}

void Matchmaking::printWaitingPlayers() {
    std::cout << "Waiting Players:" << std::endl;
    if (this->size == 0) {
        std::cout << "(empty)" << std::endl;
        return;
    }
    for (int i = 0; i < this->size; i++) {
        std::cout << "[" << this->players[i].getId() 
                  << " | " << this->players[i].getName() 
                  << " | " << this->players[i].getScore() 
                  << " | " << this->players[i].getTimestamp() 
                  << "]" << std::endl;
    }
}
