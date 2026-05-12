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

void Matchmaking::sortByScoreMerge() {
    if (this->size <= 1) {
        return; // Já está ordenado
    }
    int mid = this->size / 2;
    Matchmaking left, right;

    for (int i = 0; i < mid; i++) {
        left.insert(this->players[i]);
    }
    for (int i = mid; i < this->size; i++) {
        right.insert(this->players[i]);
    }

    left.sortByScoreMerge();
    right.sortByScoreMerge();

    // Merge
    int i = 0, j = 0, k = 0;
    while (i < left.size && j < right.size) {
        if (left.players[i].getScore() < right.players[j].getScore() || 
            (left.players[i].getScore() == right.players[j].getScore() && left.players[i].getTimestamp() < right.players[j].getTimestamp())) {
            this->players[k] = left.players[i];
            k++; i++;
        } else {
            this->players[k] = right.players[j];
            k++; j++;
        }
    }
    while (i < left.size) {
        this->players[k] = left.players[i];
        k++; i++;
    }
    while (j < right.size) {
        this->players[k] = right.players[j];
        k++; j++;
    }

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
