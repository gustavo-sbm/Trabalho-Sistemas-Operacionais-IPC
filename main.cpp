#include <csignal>
#include <cstdlib>
#include <iostream>
#include <signal.h>
#include "fabrica.hpp"

int main() {

    Fabrica f;
    int qtdBots;
    int qtdVeiculos;
    std::cin >> qtdBots;
    std::cin.ignore();
    std::cin >> qtdVeiculos;
    std::cin.ignore();

    if (qtdBots < 1 || qtdBots > 100 ){
        std::cout << "QUANTIDADE DE BOTS INVALIDA";
        return EXIT_FAILURE;
    }

    if (qtdVeiculos < qtdBots || qtdVeiculos > qtdBots*4){
        std::cout << "QUANTIDADE DE VEICULOS INVALIDOS";
        return EXIT_FAILURE;
    }

    for (int i = 0; i < qtdBots; i++){
        unsigned int id = i+1;
        f.adicionarBot(id);
    }

    f.iniciar(qtdVeiculos);



    return EXIT_SUCCESS;
}
