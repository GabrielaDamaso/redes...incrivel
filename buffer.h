#ifndef BUFFER_H_INCLUDED
#define BUFFER_H_INCLUDED

#include <string.h>
#define tamMaxRecv 4048;   //2mb

class Buffer{
    public:
        Buffer();
        virtual ~Buffer(){};
        char* getDados();
        void setTamBuffer(int tamBuffer);
        int getTamMaxRecv();
    private:
        int tamBuffer;
        char dadosC(tamMaxRecv)

}


#endif // BUFFER_H_INCLUDED
