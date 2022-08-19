#ifndef SOCKETCLASS_H
#define SOCKETCLASS_H
//bibliotecas para utilização no socket
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>
#include <arpa/inet.h> //p disponibilizar tipos como in_port_t ou estruturas in_addr

#include <string.h>
#include <iostream>
class SocketClass //classe do socket para manter as relações
{
    public:

        SocketClass();             //instanciação da classe
        virtual ~SocketClass();

        SocketClass(int porta, std::string host);

        void configSocket(struct endereçoSocket &servidor, int porta, string host); //config do socket

        int connectionSocket(int &socketAux, struct endereçoSocket &endereçoCliente); // conexão do socket

        int listenSocket(int req ) //ouvindo requisições do socket

        int askOK();          //aceita as requisições do socket

        databuff bufferReceptor(int &socketAux);

        int asksendSocket(int &socketAux, string x); //resultado de requisições

        void tempoAberto(int &socketAux, int tempo); //tempo de conexão do socket

        void xSocket(); //fecha socket on

        void xSocket(int &socketAux); //fecha socket

        sockaddr_in getEndCliente();  //pega o endereço do cliente... tipo sockaddr_in

    protected:



    private:

        int socketAux; //variável para auxiliar durante operações do socket

        struct sockaddr_in conectEndServer;                 //funciona como auxiliar para pegar o endereço do servidor

        struct sockaddr_in receberEndCliente;              //funciona como auxiliar  para receber o endereço do cliente

        socklen_t tamanhoEndCliente;     // captura tamanho do endereço do cliente

};

#endif // SOCKETCLASS_H
