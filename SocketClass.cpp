/******************************************
 * Trabalho de Redes de Computadores      *
 * IFMG - BAMBUÍ 08/2022                  *
 * Alunos:                                *
 * Higor Pereira,                         *
 * Yanky Jhonatha,                        *
 * Gabriela Dâmaso.                       *
 *                                        *
 ******************************************/



#include "SocketClass.h"


SocketClass::SocketClass(int porta, std::string host)
{
    //ctor
    socketAux=socket(AF_INET,SOCK_STREAM, 0);
    int aux = 1;
    if(setSocket(socketAux,SOL_SOCKET, SO_REUSEADDR,&aux,sizeof(int)) == -1){
        std::cout <<" Não foi possível criar o socket de maneira adequada.\n";

    }

    criarConfigSocket(servidorEndereço, porta, host);
    if(bind(socketAux,(struct sockaddr*)&servidorEndereço, sizeof(servidorEndereço)) ==-1){
      std::cout << "Erro, verifique se a porta já não está ocupada.\n"  ;
        close(socketAux);
    }

    std::cout <<"Ouvindo a porta: " << porta << std::endl;
}



void SocketClass::criarConfigSocket(struct sockaddr_in& servidor,int porta, std::string host){

    inet_aton(host.c_str(), &servidor.sin_addr);
    servidor.sin_port = htons(porta);
    servidor.sin_family = AF_INET;
    memset(servidor.sin_zero, '\0', sizeof(servidor.sin_zero));
}



int SocketClass::bindsock(int& socketAux, struct sockaddr_in& servidor){
    return bind(socketAux, (struct sockaddr*)&servidor, sizeof(servidor));
}



int SocketClass::listenSocket(int req) {

    return listen(socketAux, req);
}



int SocketClass::askOK() {

    return accept(socketAux, (struct sockaddr*)&endereçoCliente, &tamanhoEndCliente);
}



Bufferzin SocketClass::bufferReceptor(int &socketAux){

    Buffer datarec;
    datarec.tamBuffer = recv(socketAux, datarec.dadosC, maxSizeRecv, 0);
    return datarec;
}



int SocketClass::asksendSocket(int &socketAux, std::string x) {

    return send(socketAux, x.c_str(), x.size(), 0);
}



void SocketClass::setTimeOut(int &socketAux, int tempo) { //Determinação do timer de conexão

    valortempo tv;
    tv.tv_sec = tempo;
    tv.tv_usec = 0;
    setsockopt(socketAux, SOL_SOCKET, SO_RCVTIMEO,(char *)&tv,sizeof(struct valortempo));
}



sockaddr_in SocketClass::getEndCliente() {

    return receberEndCliente;
}



void SocketClass::xSocket(int &socketAux) {

    close(socketAux);
}



void SocketClass::xSocket(int &socketAux) {

    close(socketAux);
}


