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
#include "mimetype.h"


using namespace std;

class RespostaServidor
{
    public:
        RespostaServidor() {};
        virtual ~RespostaServidor() {};
        void getResponse(int thread_id, int clientSockfd, sockaddr_in endereçoCliente, std::string dir);
        int getControl(int thread_id, int clientSockfd, sockaddr_in endereçoCliente, std::string raiz, std::string difusao, std::string dir);
        std::vector<string> split(std::string x, char delete);
        bool arqStream(std::string raiz, int &len, std::string &n);
        void readarquivo(fstream &arquivo, std::string &n, int len);
        std::string getStatus(int resposta, int len, std::string difusao);
        int	operator()(int thread_id, int clientSockfd, sockaddr_in endereçoCliente, std::string dir)
        {
            getResponse(thread_id, clientSockfd, endereçoCliente, dir);
            return (0);
        }
    private:
        SocketClass socli; //mudar esse socli dps e descobrir oq é len
};

#endif
