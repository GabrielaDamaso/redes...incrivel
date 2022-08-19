#include "servidorHttp.h"

ServidorHttp::ServidorHttp(int porta, string host, string caminho){
    this.caminho = caminho;   // definindo caminho desejado p criar o servidor
    servidorSock SocketClass(porta, host);   //instanciando objeto socket
}

void ServidorHttp::iniciarServidor(){
    int i=0;
    respostaServidor resposta;

    servidorSock.listenSocket(10);  //permite 10 conexões ao mesmo tempo

    while(true){
        int socketAux = servidorSock.askOK();     //conexão aceita
        servidorSock.tempoAberto(socketAux, 60)    //limte de 60 segundos p a conexão mandar requisições

        std::thread(resposta, i++, socketAux, servidorSock.getEndCliente(), caminho).detach();
        //cria uma thread, passa o socket do servidor ligado ao endereço do cliente e o caminho
        //alem disso trata a resposta do servidor, adiciona 1 ao limite de conexões e "detach" separa essa thread da principal

    }
}
