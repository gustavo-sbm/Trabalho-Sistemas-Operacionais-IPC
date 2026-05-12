#pragma once
#include <queue>
#include <string>
#include <unordered_map>

class Atendimento final{
    public:
        Atendimento(unsigned int veiculo, unsigned int botId);
        
        ~Atendimento();
    
        
        void prepararTarefa(const std::string &pedido) const;
    
    private:
        pid_t pid{-1};
        int fd[2]{-1, -1};
        

        void iniciar(unsigned int veiculo, unsigned int botId);
        
    
};

class Bot {
    public:
        explicit Bot(unsigned int id);
        
        void prepararTarefa(const std::string &tarefa, unsigned int veiculo);
        
        void iniciarAtendimento(unsigned int veiculo);
        
        void encerrarAtendimento();

    private:
        const unsigned int id;
        Atendimento *atendimento;
};

class Fabrica {
public:
    void adicionarVeiculoParaAtendimento(const int &veiculo , const std::string tarefa);
    void adicionarBot(unsigned int &id);
    void processar(const std::string& tarefa, const int &veiculo);
    void consumirTarefasAguardando();
    void tirarVeiculoDeAtendimento(const int &veiculo);
    void iniciar(int qtdVeiculoFabrica);
    void atenderTarefa(int veiculo, const std::string &tarefa);

private:
    std::queue<int> filaVeiculosAguardando;
    std::unordered_map<int, std::queue<std::string>> mapaDeTarefasAguardando;
    std::queue<Bot*> filaBotsLivres;
    std::unordered_map<int, Bot*> mapaBotsAtendendo;
};
