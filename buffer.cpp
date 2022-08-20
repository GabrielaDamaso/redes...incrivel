#include <buffer.h>

Buffer::Buffer(){
    memset(dadosC, '\0', tamMaxRecv);  //reserva um espaço na memoria
    tamBuffer =0;   //zera o
}

char* Buffer::getDados(){ return dadosC; }

void Buffer::setTamBuffer(){ this->tamBuffer= tamBuffer; }

int Buffer::getTamMaxRecv(){ return tamMaxRecv;  }

int Buffer::tamBuffer{ return tamBuffer;  }

