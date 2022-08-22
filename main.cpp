#include<SocketClass.h>
#include<servidorHttp.h>
#include <iostream>
int main(){
    std::string  caminho;    // declara  a variavel caminho
    std::cout<<"Informe o caminho do diretório: "; //solicita ao usuario informar onde está o diretório
    cin>> caminho; //lê a resposta do usuário

    ServidorHttp* http = new ServidorHttp(1010, "9.9.9.9", caminho);

    http->iniciarServidor(); //o http inicia o servidor 
    delete http; //deleta o http
    http = nullptr;

    return 0;
}
