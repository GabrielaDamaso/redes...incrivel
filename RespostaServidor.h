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
        void getResponse(int thread_id, int clientSockfd, sockaddr_in endereçoCliente, string dir);
        int getControl(int thread_id, int clientSockfd, sockaddr_in endereçoCliente, string raiz, string difusao, string dir);
        vector<string> split(string x, char delete);
        bool arqStream(string raiz, int &len, string &n);
        void readarquivo(fstream &arquivo, string &n, int len);
        string getStatus(int resposta, int len, string difusao);
        int	operator()(int thread_id, int clientSockfd, sockaddr_in endereçoCliente, string dir)
        {
            getResponse(thread_id, clientSockfd, endereçoCliente, dir);
            return (0);
        }
    private:
        SocketClass socli; //mudar esse socli dps e descobrir oq é len
};

#endif
