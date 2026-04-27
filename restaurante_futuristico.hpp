#pragma once
#include <queue>
#include <string>
#include <unordered_map>

class Atendimento final{
    public:
        Atendimento(unsigned int mesa, unsigned int chefId);
        
        ~Atendimento();
    
        
        void prepararPedido(const std::string &pedido) const;
    
    private:
        pid_t pid{-1};
        int fd[2]{-1, -1};
        

        void iniciar(unsigned int mesa, unsigned int chefId);
        
    
};

class Chef {
    public:
        explicit Chef(unsigned int id);
        
        void prepararPedido(const std::string &pedido, unsigned int mesa);
        
        void iniciarAtendimento(unsigned int mesa);
        
        void encerrarAtendimento();

    private:
        const unsigned int id;
        Atendimento *atendimento;
};

class Restaurante {
public:
    void adicionarMesaParaAtendimento(const int &mesa , const std::string pedido);
    void adicionarChef(unsigned int &id);
    void processar(const std::string& pedido, const int &mesa);
    void consumirPedidosAguardando();
    void tirarMesaDeAtendimento(const int &mesa);
    void iniciar(int qtdMesaRestaurante);
    void atenderPedido(int mesa, const std::string &pedido);

private:
    std::queue<int> filaMesasAguardando;
    std::unordered_map<int, std::queue<std::string>> mapaDePedidoAguardando;
    std::queue<Chef*> filaChefsLivres;
    std::unordered_map<int, Chef*> mapaChefsAtendendo;
};
