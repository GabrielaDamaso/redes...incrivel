/******************************************
 * Trabalho de Redes de Computadores      *
 * IFMG - BAMBUÍ 08/2022                  *
 * Alunos:                                *
 * Higor Pereira,                         *
 * Yanky Jhonatha,                        *
 * Gabriela Dâmaso.                       *
 *                                        *
 ******************************************/



#include "RespostaServidor.h" //inclui o aqruivo .h

#define Debug false

//criando metodo resposta servidor:
void RepostaServidor::getResponse(int thread_id, int clienteSockfd, sockaddr_in endereçoCliente, std::string caminho){
    if(Debug){
       std::cout << "ID DO THREAD: " << thread_id << std::endl;
    }
    //declarando variavel e vetores:
    std::string solicitarString = ""; 
    std::vector<string> difusao;
    std::vector<string> leituraDeLinhas;

    if (clienteSockfd == -1) {
        return;
    }

    char ipString[INET_ADDRSTRLEN] = {'\0'};
    inet_ntop(endereçoCliente.sin_family, &endereçoCliente.sin_addr, ipString, sizeof(ipString));
    if(Debug){
        //exibe status: 
        std::cout << "Conexão iniciada com o cliente " << ipString << ":" << ntohs(endereçoCliente.sin_port) << std::endl << std::endl;
    }
    databuff datarec = cleanSock.sockrecv(clienteSockfd);
    if(datarec.bufftamanho > 0){
        solicitarString = std::string(datarec.dataChar, 0, datarec.bufftamanho); 
        if(Debug){
            std::cout<< solicitarString << std::endl; //exibe mensagem ao usuário
        }
        leituraDeLinhas = split(solicitarString,'\n'); 
        leituraDeLinhas = split(leituraDeLinhas[0],' ');
        difusao = split(leituraDeLinhas[1],'.');
        try {
            if(leituraDeLinhas[0] == "GET"){
                if(Debug){ //caso a condição seja atendida verá as seguintes mensagens na tela:
                    std::cout<<"É uma requisição get."<<std::endl;
                    std::cout<<"Pasta escolhida: "<<leituraDeLinhas[1]<<std::endl;
                    std::cout<<"Extensão: "<<difusao[difusao.size()-1]<<std::endl;
                }
                getControl(thread_id,clienteSockfd,endereçoCliente, caminho+leituraDeLinhas[1],difusao[difusao.size()-1], caminho);
            }
            else {
                throw (leituraDeLinhas[0]);
            }
        } catch(std::string n) { //declara a variavel n
            int tamanho = 0; //define a variavel tamanho com valor 0
            std::string aux = "", data="";
            aux = "400 BAD REQUEST\n\r"; 
            tamanho = aux.size();
            data = getStatus(3, tamanho, "Html"); //atribui o valor de getStatus na variavél data
            if(Debug){
                std::cout << data << std::endl;  
            }
            data += aux;
            cleanSock.socksendk(clienteSockfd, data);
            cleanSock.closesock(clienteSockfd);
        }
    }
    else {
        if(Debug){
            std::cout<<"Tempo limite do requerimento atingido!"<<std::endl; //exibe mensagem de erro
        }
        this->cleanSock.closesock(clienteSockfd); 
}
std::vector<string> RespostaServidor::split(std::string stringAux, char delete){

    std::string temp = ""; //declara a variavél temp e atribui um espaço em branco como seu valor
    std::vector<string> leituraDeStrings; 
    for(int i =0; i < (int)str.size(); i++){
    if(stringAux[i] != delete){
            temp += stringAux[i];
        }else{
            leituraDeStrings.push_back(temp);
            temp = "";
        }
    }
    leituraDeStrings.push_back(temp);
    return leituraDeStrings; //retorna o valor da variavel leituraDeStrings
}
int RespostaServidor::getControl(int thread_id, int clienteSockfd, sockaddr_in endereçoCliente, std::string raiz,std::string difusao, string caminho){
    std::string n, data; //declara as variaveis n e data
    int tamanho; //declara a variavel tamanho
    if(Debug){
        std::cout<< "raiz " << raiz << std::endl;
    }
    n = data = "";
    if(fluxoArquivos(raiz, tamanho, n)) {
        data = getStatus(1, tamanho, difusao);
        data += n;
        cleanSock.socksendk(clienteSockfd, data);
        handleRequest(thread_id, clienteSockfd,endereçoCliente, caminho);
    } else {
        data = getStatus(2, tamanho, "Html");
        data+= n;
        cleanSock.socksendk(clienteSockfd, data);
        cleanSock.closesock(clienteSockfd);
    }
    return 0;
}

bool RespostaServidor::fluxoArquivos(std::string raiz, int &tamanho, std::string &n) {
    fstream arquivo; // para ler e escrever no arquivo
    arquivo.open(raiz, fstream::in |fstream::out | fstream::binary);

    if(arquivo.is_open()){
        arquivo.seekg(0, ios::end);
        tamanho = arquivo.tellg();
        leituraArquivo(arquivo, n, tamanho);
        return true;
    }
    else {
        arquivo.open("Arquivos/404.html", fstream::in |fstream::out | fstream::binary); //abre o arquivo e depois fecha
        if(arquivo.is_open()) {
            arquivo.seekg(0, ios::end);
            tamanho = arquivo.tellg();
            leituraArquivo(arquivo, n, tamanho);
        } else {
            n = "404 NOT FOUND\n\r"; //atribui a mensagem como valor da variavel n
            tamanho = n.size();
        }
        return false;
    }
}

void RespostaServidor::leituraArquivo(fstream &arquivo, std::string &n, int tamanho) {
    char *aux =  new char[tamanho];
    arquivo.clear();
    arquivo.seekg(0, ios::beg);
    arquivo.read(aux, tamanho);
    for(int i = 0; i < tamanho; i++){
        n += aux[i];
    }
    arquivo.close();
    delete[] aux;
    aux = nullptr;
}

std::string RespostaServidor::getStatus(int resp, int tamanho, std::string difusao) {
    std::string text;
    guardaTipo gt;
    char buff[256];
    time_t tempoTotal;
    struct tm * infoTempo;
    time (&tempoTotal);
    infoTempo = gmtime (&tempoTotal);
    strftime(buff, sizeof(buff), "%a, %d %b %Y %H:%M:%S GMT\r\n", infoTempo);

    if(resp == 1) {
        //caso a res seja =1 a seguinte mensagem será atribuida na variavel text:
        text = "HTTP/1.1 200 OK\r\n" // 200 ok significa que foi bem sucedida  
               "Data: " + std::string(buff) +
               "Tamanho do Conteúdo: " + to_string(tamanho) + "\r\n"
               "Keep-Alive: timeout=5, max=100\r\n"
               "Conexão: Keep-Alive\r\n"
               "Tipo de Conteúdo: " + gt.getTipo(difusao) + "; charset=UTF-8\r\n\r\n";
    }
    else if(resp == 2){
        //caso a resp=2 o seguinte texto sera atribuido na variavel text:
        text = "HTTP/1.1 404 NOT FOUND\r\n" //404 NOT FOUND significa que a pagina solicitada não foi encontrada
                "Data: " + std::string(buff) +
                "Tamanho do Conteúdo: " + to_string(tamanho) + "\r\n"
                "Conexão: Close\r\n"
                "Tipo de Conteúdo: " + gt.getTipo(difusao) + "; charset=UTF-8\r\n\r\n";
    } else { //caso resp não seja igal a 1 ou a 2 o seguinte texto será atribuido a variavel text
        text = "HTTP/1.1 400 BAD REQUEST\r\n" //indica que a solicitação enviada pelo navegador do usuário ao servidor web do site é inválida ou está corrompida
                "Data: " + std::string(buff) +
                "Tamanho do Conteúdo: " + to_string(tamanho) + "\r\n"
                "Conexão: Close\r\n"
                "Tipo de Conteúdo: " + gt.getTipo(difusao) + "; charset=UTF-8\r\n\r\n";
    }
    return text; //exibe o valor atribuido na variavel text
}
