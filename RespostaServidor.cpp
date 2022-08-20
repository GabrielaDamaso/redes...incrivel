/******************************************
 * Trabalho de Redes de Computadores      *
 * IFMG - BAMBUÍ 08/2022                  *
 * Alunos:                                *
 * Higor Pereira,                         *
 * Yanky Jhonatha,                        *
 * Gabriela Dâmaso.                       *
 *                                        *
 ******************************************/



#include "RespostaServidor.h"

#define Debug false

void RepostaServidor::getResponse(int thread_id, int clienteSockfd, sockaddr_in endereçoCliente, std::string dir){
    if(Debug){
       std::cout << "ID DO THREAD: " << thread_id << std::endl;
    }
    std::string strRequest = "";
    std::vector<string> difusao;
    std::vector<string> leituraDeLinhas;

    if (clienteSockfd == -1) {
        return;
    }

    char ipstr[INET_ADDRSTRLEN] = {'\0'};
    inet_ntop(endereçoCliente.sin_family, &endereçoCliente.sin_addr, ipstr, sizeof(ipstr));
    if(Debug){
        std::cout << "Conexão iniciada com o cliente " << ipstr << ":" << ntohs(endereçoCliente.sin_port) << std::endl << std::endl;
    }
    databuff datarec = socli.sockrecv(clienteSockfd);
    if(datarec.bufflen > 0){
        strRequest = std::string(datarec.dataChar, 0, datarec.bufflen);
        if(Debug){
            std::cout<< strRequest << std::endl;
        }
        leituraDeLinhas = split(strRequest,'\n');
        leituraDeLinhas = split(leituraDeLinhas[0],' ');
        difusao = split(leituraDeLinhas[1],'.');
        try {
            if(leituraDeLinhas[0] == "GET"){
                if(Debug){
                    std::cout<<"É uma requisição get."<<std::endl;
                    std::cout<<"Pasta Desejada: "<<leituraDeLinhas[1]<<std::endl;
                    std::cout<<"Extensão: "<<difusao[difusao.size()-1]<<std::endl;
                }
                getControl(thread_id,clienteSockfd,endereçoCliente, dir+leituraDeLinhas[1],difusao[difusao.size()-1], dir);
            }
            else {
                throw (leituraDeLinhas[0]);
            }
        } catch(std::string n) {
            int len = 0;
            std::string aux = "", data="";
            aux = "400 BAD REQUEST\n\r";
            len = aux.size();
            data = getStatus(3, len, "html");
            if(Debug){
                std::cout << data << std::endl;
            }
            data += aux;
            socli.socksendk(clienteSockfd, data);
            socli.closesock(clienteSockfd);
        }
    }
    else {
        if(Debug){
            std::cout<<"Tempo limite de requisição atingido!"<<std::endl;
        }
        this->socli.closesock(clienteSockfd);
}
std::vector<string> RespostaServidor::split(std::string str, char delete){

    std::string temp = "";
    std::vector<string> leituraDeStrings;
    for(int i =0; i < (int)str.size(); i++){
    if(str[i] != delete){
            temp += str[i];
        }else{
            leituraDeStrings.push_back(temp);
            temp = "";
        }
    }
    leituraDeStrings.push_back(temp);
    return leituraDeStrings;
}
int RespostaServidor::getControl(int thread_id, int clienteSockfd, sockaddr_in endereçoCliente, std::string raiz,std::string difusao, string dir){
    std::string n, data;
    int len;
    if(Debug){
        std::cout<< "raiz " << raiz << std::endl;
    }
    n = data = "";
    if(fluxoArquivos(raiz, len, n)) {
        data = getStatus(1, len, difusao);
        data += n;
        socli.socksendk(clienteSockfd, data);
        handleRequest(thread_id, clienteSockfd,endereçoCliente, dir);
    } else {
        data = getStatus(2, len, "html");
        data+= n;
        socli.socksendk(clienteSockfd, data);
        socli.closesock(clienteSockfd);
    }
    return 0;
}

bool RespostaServidor::fluxoArquivos(std::string raiz, int &len, std::string &n) {
    fstream arquivo;
    arquivo.open(raiz, fstream::in |fstream::out | fstream::binary);

    if(arquivo.is_open()){
        arquivo.seekg(0, ios::end);
        len = arquivo.tellg();
        leituraArquivo(arquivo, n, len);
        return true;
    }
    else {
        arquivo.open("arquivos/404.html", fstream::in |fstream::out | fstream::binary);
        if(arquivo.is_open()) {
            arquivo.seekg(0, ios::end);
            len = arquivo.tellg();
            leituraArquivo(arquivo, n, len);
        } else {
            n = "404 NOT FOUND\n\r";
            len = n.size();
        }
        return false;
    }
}

void RespostaServidor::leituraArquivo(fstream &arquivo, std::string &n, int len) {
    char *aux =  new char[len];
    arquivo.clear();
    arquivo.seekg(0, ios::beg);
    arquivo.read(aux, len);
    for(int i = 0; i < len; i++){
        n += aux[i];
    }
    arquivo.close();
    delete[] aux;
    aux = nullptr;
}

std::string RespostaServidor::getStatus(int resp, int len, std::string difusao) {
    std::string text;
    mimetype mim;
    char buff[256];
    time_t rawtime;
    struct tm * timeinfo;
    time (&rawtime);
    timeinfo = gmtime (&rawtime);
    strftime(buff, sizeof(buff), "%a, %d %b %Y %H:%M:%S GMT\r\n", timeinfo);

    if(resp == 1) {
        text = "HTTP/1.1 200 OK\r\n"
               "Date: " + std::string(buff) +
               "Content-Length: " + to_string(len) + "\r\n"
               "Keep-Alive: timeout=5, max=100\r\n"
               "Connection: Keep-Alive\r\n"
               "Content-type: " + mim.getType(difusao) + "; charset=UTF-8\r\n\r\n";
    }
    else if(resp == 2){
        text = "HTTP/1.1 404 NOT FOUND\r\n"
                "Date: " + std::string(buff) +
                "Content-Length: " + to_string(len) + "\r\n"
                "Connection: Close\r\n"
                "Content-type: " + mim.getType(difusao) + "; charset=UTF-8\r\n\r\n";
    } else {
        text = "HTTP/1.1 400 BAD REQUEST\r\n"
                "Date: " + std::string(buff) +
                "Content-Length: " + to_string(len) + "\r\n"
                "Connection: Close\r\n"
                "Content-type: " + mim.getType(difusao) + "; charset=UTF-8\r\n\r\n";
    }
    return text;
}
