#include "restaurante_futuristico.hpp"

#include <iostream>
#include <csignal>
#include <ostream>
#include <queue>
#include <string>
#include <unistd.h>
#include <fstream>
#include <sstream>
#include <sys/wait.h>
#include <fcntl.h>

Atendimento::Atendimento(unsigned int mesa, unsigned int chefId) {
	if(pipe(fd) < 0) {
		perror("Pipe erro");
		exit(EXIT_FAILURE);
	}
	
    pid = fork();
    
    if (pid < 0){
        perror("Fork erro");
        exit(EXIT_FAILURE);
    }

    if(pid == 0) {
        close(fd[1]);
        for(int i = 3; i < 1024; i++) {
            if (i != fd[0]) close(i);
        }
        iniciar(mesa, chefId);
        exit(0);
    }
    
    if(pid>0){
        close(fd[0]);
    }
}

void Atendimento::prepararPedido(const std::string &pedido) const{
    std::string pedidoFormatado = "  -" + pedido + "\n";
    write(fd[1], pedidoFormatado.c_str(), pedidoFormatado.size());
}

void Atendimento::iniciar(unsigned int mesa, unsigned int chefId){
    std::string nomeArquivo = "ChefeCozinha_" + std::to_string(chefId) + ".txt";

    std::ofstream arquivo(nomeArquivo, std::ios::app);

    arquivo << "\nMesa " << std::to_string(mesa) << std::endl;
    
    char buffer[256];
    while(true) {
        const ssize_t n = read(fd[0], buffer, sizeof(buffer) - 1);
        if (n<=0) break;
        
        buffer[n]='\0';
        
        arquivo << buffer;
        arquivo.flush();
    }
}

Atendimento::~Atendimento(){
    if(pid>0){
        close(fd[1]);
        waitpid(pid, NULL, 0);
    } else {
        close(fd[0]);
    }
}

Chef::Chef(unsigned int id) : id(id),atendimento(nullptr){
    std::string nomeArquivo = "ChefeCozinha_" + std::to_string(id) + ".txt";
    std::ofstream arquivo(nomeArquivo);
    arquivo << "ChefeCozinha_" << std::to_string(id) << std::endl;
};

void Chef::iniciarAtendimento(unsigned int mesa){
    atendimento = new Atendimento(mesa, id);
}

void Chef::encerrarAtendimento() {
    delete atendimento;
    atendimento = nullptr;
}

void Chef::prepararPedido(const std::string &pedido, unsigned int mesa) {
    if (atendimento == nullptr){
        iniciarAtendimento(mesa);
    }

    atendimento->prepararPedido(pedido);
}


void Restaurante::tirarMesaDeAtendimento(const int &mesa) {
    if (mapaChefsAtendendo.contains(mesa)){
        Chef* chef = mapaChefsAtendendo[mesa];
        chef->encerrarAtendimento();
        mapaChefsAtendendo.erase(mesa);
        filaChefsLivres.push(chef);
    }
}

void Restaurante::adicionarMesaParaAtendimento(const int &mesa, const std::string pedido){
    if (!filaChefsLivres.empty()){
        Chef* chef = filaChefsLivres.front();
        filaChefsLivres.pop();
        mapaChefsAtendendo[mesa] = chef;
        processar(pedido, mesa);
    } else {
        if (!mapaDePedidoAguardando.contains(mesa)){
            filaMesasAguardando.push(mesa);
            mapaDePedidoAguardando[mesa] = std::queue<std::string>();
        }
        mapaDePedidoAguardando[mesa].push(pedido);
    }
}

void Restaurante::consumirPedidosAguardando(){
    bool temFim = true;
    while (temFim && !filaMesasAguardando.empty()) {
        temFim = false;
        int mesa = filaMesasAguardando.front();
        int i = 0;
        while (!mapaDePedidoAguardando[mesa].empty()){
            std::string pedido = mapaDePedidoAguardando[mesa].front();
            mapaDePedidoAguardando[mesa].pop();
            i++;
            if (i==1){
                if (pedido != "fim") {
                    adicionarMesaParaAtendimento(mesa, pedido);
                    continue;
                }
                
            } 
            
            if (pedido == "fim") {
                tirarMesaDeAtendimento(mesa);
                temFim = true;
                break;
            } 
            processar(pedido, mesa);
            
        }
        mapaDePedidoAguardando.erase(mesa);
        filaMesasAguardando.pop();
    }
}

void Restaurante::adicionarChef(unsigned int &id){
    Chef* chef = new Chef(id);
    filaChefsLivres.push(chef);
}

void Restaurante::processar(const std::string& pedido, const int &mesa) {
    mapaChefsAtendendo[mesa]->prepararPedido(pedido, mesa);
}

void Restaurante::iniciar(int qtdMesaRestaurante){
    while (true){
        std::string entrada;
        std::getline(std::cin, entrada);
        if (entrada == "FIM") break;

        int mesa;
        std::string pedido;
        std::istringstream iss(entrada);

        iss >> mesa;
        iss.ignore();
        std::getline(iss, pedido);

        if (mesa < 0 || mesa > qtdMesaRestaurante) {
            std::cout << "MESA NÃO EXISTE";
            continue;
        }

        if (mapaChefsAtendendo.contains(mesa)) {
            if(pedido.empty() || pedido == "fim") {
                tirarMesaDeAtendimento(mesa);
                if(!filaMesasAguardando.empty()){
                    consumirPedidosAguardando();
                } 
                
            } else {
                processar(pedido, mesa);
            } 
        } else {
            adicionarMesaParaAtendimento(mesa, pedido);
        }
    }    
}
