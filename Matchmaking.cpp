#include "Matchmaking.hpp"
#include <iostream>
Matchmaking::Matchmaking() {
    this->size = 0;
}
Matchmaking::Matchmaking() = default;
Matchmaking::~Matchmaking() = default;

bool Matchmaking::insert(Player player){
    return false;
}

bool Matchmaking::removePlayer(int id){
    return false;
}

void Matchmaking::sortByScoreInsertion() {

}

void Matchmaking::sortByScoreMerge() {

}

Player* Matchmaking::formGroup(int groupSize, int delta, int* n){
    return nullptr;
}


Player* Matchmaking::getWaitingPlayers(int* n){
    return nullptr;
}

void Matchmaking::printWaitingPlayers() {

}
