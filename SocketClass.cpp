#include "SocketClass.h"


SocketClass::SocketClass(int porta, string host)
{
    //ctor
    socketAux=socket(AF_INET,SOCK_STREAM, 0);
    int aux = 1;
    if(setSocket(socketAux,SOL_SOCKET, SO_REUSEADDR,&aux,sizeof(int)) == -1){
        cout <<" Não foi possível criar o socket de maneira adequada.\n";

    }

    criarConfigSocket(servidorEndereço, porta, host);
    if(bind(socketAux,(struct sockaddr*)&servidorEndereço, sizeof(servidorEndereço)) ==-1){
      cout << "Erro, verifique se a porta já não está ocupada.\n"  ;
        close(socketAux);
    }

    cout <<"Ouvindo a porta: " << porta << endl;
}



SocketClass::criarConfigSocket(struct sockaddr_in& servidor,int porat, string host){
    inet_aton(host.c_str(), &servidor.sin_addr);
    servidor.sin_port = htons(port);
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

    return accept(socketAux, (struct sockaddr*)&endereçoCliente, &endereçoClienteTamanho);
}



databuff SocketClass::bufferReceptor(int &socketAux){

    databuff datarec;
    datarec.bufflen = recv(socketAux, datarec.dataChar, maxSizeRecv, 0);
    return datarec;
}



int SocketClass::asksendSocket(int &socketAux, string x) {

    return send(socketAux, x.c_str(), x.size(), 0);
}



void SocketClass::void Socket::setTimeOut(int &socketAux, int tempo) { //Determinação do timer de conexão

    valortempo tv;
    tv.tv_sec = tempo;
    tv.tv_usec = 0;
    setsockopt(socketAux, SOL_SOCKET, SO_RCVTIMEO,(char *)&tv,sizeof(struct valortempo));
}



(int &socketAux, int tempo) {

    valortempo tv;
    tv.tv_sec = tempo;
    tv.tv_usec = 0;
    setsockopt(socketAux, SOL_SOCKET, SO_RCVTIMEO,(char *)&tv,sizeof(struct valortempo));
}



sockaddr_in SocketClass::getEndereçoCliente() {

    return endereçoCliente;
}



void SocketClass::xSocket(int &socketAux) {

    close(socketAux);
}



void SocketClass::xSocket(int &socketAux) {

    close(socketAux);
}


