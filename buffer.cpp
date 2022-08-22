#include <buffer.h>

Buffer::Buffer(){
    memset(dadosC, '\0', tamMaxRecv);  //reserva um espaço na memoria
    tamBuffer =0;   //zera o
}

char* Buffer::getDados(){ return dadosC; } //pega os dados

void Buffer::setTamBuffer(){ this->tamBuffer= tamBuffer; } //define tamnho do buffer

int Buffer::getTamMaxRecv(){ return tamMaxRecv;  } //pega o tamanho maximo do buffer

int Buffer::tamBuffer{ return tamBuffer;  } 

