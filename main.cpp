#include <cstdlib>
#include <iostream>
#include <signal.h>
#include "restaurante_futuristico.hpp"

int main() {
    signal(SIGCHLD, SIG_IGN);
    Restaurante r;
    int qtdChefs;
    int qtdMesas;
    std::cin >> qtdChefs;
    std::cin.ignore();
    std::cin >> qtdMesas;
    std::cin.ignore();

    if (qtdChefs < 1 || qtdChefs > 100 ){
        std::cout << "QUANTIDADE DE CHEFS INVALIDA";
        return EXIT_FAILURE;
    }

    if (qtdMesas < qtdChefs || qtdMesas > qtdChefs*4){
        std::cout << "QUANTIDADE DE MESAS INVALIDAS";
        return EXIT_FAILURE;
    }

    for (int i = 0; i < qtdChefs; i++){
        unsigned int id = i+1;
        r.adicionarChef(id);
    }

    r.iniciar(qtdMesas);



    return EXIT_SUCCESS;
}
