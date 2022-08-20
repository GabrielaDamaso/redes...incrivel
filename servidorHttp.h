/******************************************
 * Trabalho de Redes de Computadores      *
 * IFMG - BAMBUÍ 08/2022                  *
 * Alunos:                                *
 * Higor Pereira,                         *
 * Yanky Jhonatha,                        *
 * Gabriela Dâmaso.                       *
 *                                        *
 ******************************************/



#ifndef SERVIDORHTTP_H_INCLUDED
#define SERVIDORHTTP_H_INCLUDED

#include<SocketClass.h>
#include<thread>

class ServidorHttp{
    public:
        ServidorHttp(){};    //1º construtor
        ServidorHttp(int porta , string host, string caminho); //criando socket de conexão
        virtual ~ServidorHttp(){};  //destrutor
        void iniciarServidor();     //inicializador do servidor

    protected:
        string caminho;  //o diretorio que o servidor sera criado
    private:
        SocketClass *servidorSock;     //ponteiro p referenciar o socket do servidor

}


#endif // SERVIDORHTTP_H_INCLUDED
