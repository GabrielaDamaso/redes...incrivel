/******************************************
 * Trabalho de Redes de Computadores      *
 * IFMG - BAMBUÍ 08/2022                  *
 * Alunos:                                *
 * Higor Pereira,                         *
 * Yanky Jhonatha,                        *
 * Gabriela Dâmaso.                       *
 *                                        *
 ******************************************/

#ifndef RESPOSTASERVIDOR_H
#define RESPOSTASERVIDOR_H

#include "SocketClass.h"
#include <vector>
#include <string>
#include <fstream>
#include <ctime>
#include "guardaTipo.h"


using namespace std;

class RespostaServidor
{
    public:
        RespostaServidor() {};
        virtual ~RespostaServidor() {};
        void getResponse(int thread_id, int clientSockfd, sockaddr_in endereçoCliente, std::string caminho);
        int getControl(int thread_id, int clientSockfd, sockaddr_in endereçoCliente, std::string raiz, std::string difusao, std::string caminho);
        std::vector<string> split(std::string x, char delete);
        bool arqStream(std::string raiz, int &len, std::string &n);
        void readarquivo(fstream &arquivo, std::string &n, int len);
        std::string getStatus(int resposta, int len, std::string difusao);
        int	operator()(int thread_id, int clientSockfd, sockaddr_in endereçoCliente, std::string caminho)
        {
            getResponse(thread_id, clientSockfd, endereçoCliente, caminho);
            return (0);
        }
    private:
        SocketClass cleanSock; //mudar esse socli dps
};

#endif
