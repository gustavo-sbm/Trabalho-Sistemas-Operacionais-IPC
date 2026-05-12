#include "fabrica.hpp"

#include <iostream>
#include <csignal>
#include <ostream>
#include <queue>
#include <string>
#include <unistd.h>
#include <fstream>
#include <sstream>
#include <sys/wait.h>
#include <cstring>

Atendimento::Atendimento(unsigned int veiculo, unsigned int botId) {
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
        iniciar(veiculo, botId);
    }
    
    if(pid>0){
        close(fd[0]);
    }
}

void Atendimento::prepararTarefa(const std::string &tarefa) const{
    
    write(fd[1], tarefa.c_str(), tarefa.size());
}

void Atendimento::iniciar(unsigned int veiculo, unsigned int botId){
    std::string nomeArquivo = "Robo_" + std::to_string(botId) + ".txt";

    std::ofstream arquivo(nomeArquivo, std::ios::app);

    arquivo << "\nVeiculo " << std::to_string(veiculo) << std::endl;
    
    char buffer[256];
    while(true) {
        const ssize_t n = read(fd[0], buffer, sizeof(buffer) - 1);
        if (n<=0) break;
        
        buffer[n]='\0';

        char *token = strtok(buffer, "\n");
        while (token != NULL){
            if(strncmp(token, "fim", 3) == 0){ 
                arquivo.flush();
                _exit(0);}
            arquivo << " -  " << token << "\n";
            token = strtok(NULL, "\n");
        }
        arquivo.flush();
    }
}

Atendimento::~Atendimento(){
    if(pid>0){
       
        prepararTarefa("fim");
        close(fd[1]);
        waitpid(pid, nullptr, 0);
        

    } else {
        close(fd[0]);
    }
}

Bot::Bot(unsigned int id) : id(id),atendimento(nullptr){
    std::string nomeArquivo = "Robo_" + std::to_string(id) + ".txt";
    std::ofstream arquivo(nomeArquivo);
    arquivo << "Robo_" << std::to_string(id) << std::endl;
};

void Bot::iniciarAtendimento(unsigned int veiculo){
    atendimento = new Atendimento(veiculo, id);
}

void Bot::encerrarAtendimento() {
    delete atendimento; 
    atendimento = nullptr;
}

void Bot::prepararTarefa(const std::string &tarefa, unsigned int veiculo) {
    if (atendimento == nullptr){
        iniciarAtendimento(veiculo);
    }

    atendimento->prepararTarefa(tarefa);
}


void Fabrica::tirarVeiculoDeAtendimento(const int &veiculo) {
    if (mapaBotsAtendendo.contains(veiculo)){
        Bot* bot = mapaBotsAtendendo[veiculo];
        bot->encerrarAtendimento();
        mapaBotsAtendendo.erase(veiculo);
        filaBotsLivres.push(bot);
    }
}

void Fabrica::adicionarVeiculoParaAtendimento(const int &veiculo, const std::string tarefa){
    if (!filaBotsLivres.empty()){
        Bot* bot = filaBotsLivres.front();
        filaBotsLivres.pop();
        mapaBotsAtendendo[veiculo] = bot;
        processar(tarefa, veiculo);
    } else {
        if (!mapaDeTarefasAguardando.contains(veiculo)){
            filaVeiculosAguardando.push(veiculo);
            mapaDeTarefasAguardando[veiculo] = std::queue<std::string>();
        }
        mapaDeTarefasAguardando[veiculo].push(tarefa);
    }
}

void Fabrica::consumirTarefasAguardando(){
    bool temFim = true;
    while (temFim && !filaVeiculosAguardando.empty()) {
        temFim = false;
        int veiculo = filaVeiculosAguardando.front();
        int i = 0;
        while (!mapaDeTarefasAguardando[veiculo].empty()){
            std::string tarefa = mapaDeTarefasAguardando[veiculo].front();
            mapaDeTarefasAguardando[veiculo].pop();
            i++;
            if (i==1){
                if (tarefa != "fim") {
                    adicionarVeiculoParaAtendimento(veiculo, tarefa);
                    continue;
                }
                
            } 
            
            if (tarefa == "fim") {
                tirarVeiculoDeAtendimento(veiculo);
                temFim = true;
                break;
            } 
            processar(tarefa, veiculo);
            
        }
        mapaDeTarefasAguardando.erase(veiculo);
        filaVeiculosAguardando.pop();
    }
}

void Fabrica::adicionarBot(unsigned int &id){
    Bot* bot = new Bot(id);
    filaBotsLivres.push(bot);
}

void Fabrica::processar(const std::string& tarefa, const int &veiculo) {
    std::string tarefaFormatada = tarefa + "\n";
    mapaBotsAtendendo[veiculo]->prepararTarefa(tarefaFormatada, veiculo);
}

void Fabrica::iniciar(int qtdVeiculosFabrica){
    while (true){
        std::string entrada;
        std::getline(std::cin, entrada);
        if (entrada == "FIM") break;

        int veiculo;
        std::string tarefa;
        std::istringstream iss(entrada);

        iss >> veiculo;
        iss.ignore();
        std::getline(iss, tarefa);

        

        if (veiculo < 0 || veiculo > qtdVeiculosFabrica) {
            std::cout << "VEICULO NÃO EXISTE";
            continue;
        }

        if (mapaBotsAtendendo.contains(veiculo)) {
            if(tarefa.empty() || tarefa == "fim") {
                tirarVeiculoDeAtendimento(veiculo);
                if(!filaVeiculosAguardando.empty()){
                    consumirTarefasAguardando();
                } 
                
            } else {
                processar(tarefa, veiculo);
            } 
        } else {
            adicionarVeiculoParaAtendimento(veiculo, tarefa);
        }
    }    
}
