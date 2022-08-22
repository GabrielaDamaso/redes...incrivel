#include<SocketClass.h>
#include<servidorHttp.h>
#include <iostream>
int main(){
    string caminho;
    std::cout<<"Informe o caminho do diretório: ";
    cin>> caminho;

    ServidorHttp* http = new ServidorHttp(1010, "9.9.9.9", caminho);

    http->iniciarServidor();
    delete http;
    http = nullptr;

    return 0;
}
