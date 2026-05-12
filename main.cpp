#include <iostream>
#include "Matchmaking.hpp"
#include "Player.hpp"
#include <chrono>
#include <cstdlib>

int main() {
    Matchmaking matchmaking;

    // 1. Insercao de jogadores e exibicao do estado inicial
    std::cout << "Teste 1: Insercao basica\n";
    matchmaking.insert(Player(1, "Anastacia", 1000, 5));
    matchmaking.insert(Player(2, "Ivonete", 900, 2));
    matchmaking.insert(Player(3, "Luzia", 1000, 1));     // Empata em score com Anastacia
    matchmaking.insert(Player(4, "Sebastiao", 900, 4));  // Empata em score com Ivonete
    matchmaking.insert(Player(5, "Bittencourt", 1200, 3));
    matchmaking.printWaitingPlayers();
    std::cout << "\n";

    // 2. Ordenacao com Insertion Sort e desempate
    std::cout << "Teste 2: Ordenacao (Insertion Sort) com desempate de timestamp\n";
    matchmaking.sortByScoreInsertion();
    matchmaking.printWaitingPlayers();
    std::cout << "\n";

    // 3. Remocao de jogador
    std::cout << "Teste 3: Removendo a jogadora Luzia (ID 3)\n";
    matchmaking.removePlayer(3);
    matchmaking.printWaitingPlayers();
    std::cout << "\n";

    // 4. Insercao de novos jogadores e ordenacao com Merge Sort
    std::cout << "Teste 4: Inserindo novos jogadores e reordenando com Merge Sort\n";
    matchmaking.insert(Player(6, "Felipe", 1050, 6));
    matchmaking.insert(Player(7, "Gustavo", 800, 7));
    matchmaking.insert(Player(8, "Helena", 1050, 8));
    
    matchmaking.sortByScoreMerge();
    matchmaking.printWaitingPlayers();
    std::cout << "\n";

    // 5. Formacao bem sucedida de grupo
    std::cout << "Teste 5: Formacao de grupo (tamanho 3, delta 100)\n";
    int n_group = 0;
    Player* group = matchmaking.formGroup(3, 100, &n_group);
    
    if (group != nullptr) {
        std::cout << "Grupo formado (" << n_group << " jogadores):\n";
        for (int i = 0; i < n_group; i++) {
            std::cout << "[" << group[i].getId() << " | " << group[i].getName() 
                      << " | " << group[i].getScore() << " | " << group[i].getTimestamp() << "]\n";
        }
        delete[] group; // Previne vazamento de memoria
    }
    
    std::cout << "Fila apos formar grupo:\n";
    matchmaking.printWaitingPlayers();
    std::cout << "\n";

    // 6. Tentativa de formacao de grupo sem sucesso
    std::cout << "Teste 6: Tentativa de formacao sem sucesso (delta 10)\n";
    Player* no_group = matchmaking.formGroup(3, 10, &n_group);
    
    if (no_group == nullptr) {
        std::cout << "Nenhum grupo valido encontrado. (Retornou nullptr e n = " << n_group << ")\n";
    }
    std::cout << "\n";

    // 7. Recuperacao de dados
    std::cout << "Teste 7: Recuperacao de dados dinamica (getWaitingPlayers)\n";
    int n_waiting = 0;
    Player* waiting_list = matchmaking.getWaitingPlayers(&n_waiting);
    
    if (waiting_list != nullptr) {
        std::cout << "Foram recuperados " << n_waiting << " jogadores da fila.\n";
        delete[] waiting_list; // Previne vazamento de memoria
    }
    std::cout << "\n";

    // 8. Testes de desempenho para o relatorio
    std::cout << "Iniciando testes de desempenho...\n";
    Matchmaking matchInsertion;
    Matchmaking matchMerge;
    int numPlayers = 20000; // Ajuste para coletar dados pro relatorio

    for (int i = 0; i < numPlayers; i++) {
        int randomScore = rand() % 3000; 
        int randomTime = rand() % 50000; 
        Player p(i, "Bot", randomScore, randomTime);
        matchInsertion.insert(p);
        matchMerge.insert(p);
    }

    // Medicao do Insertion Sort
    auto startIns = std::chrono::high_resolution_clock::now();
    matchInsertion.sortByScoreInsertion();
    auto endIns = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> diffIns = endIns - startIns;
    std::cout << "Tempo do Insertion Sort: " << diffIns.count() << " s\n";

    // Medicao do Merge Sort
    auto startMerge = std::chrono::high_resolution_clock::now();
    matchMerge.sortByScoreMerge();
    auto endMerge = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> diffMerge = endMerge - startMerge;
    std::cout << "Tempo do Merge Sort:     " << diffMerge.count() << " s\n";

    return 0;
}