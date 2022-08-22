#include "guardaTipo.h"
guardaTipo::guardaTipo(){} //Construtor padrão
string guardaTipo::getTipo(string tipo){ //declara a string tipo
    for (int i=0; i<13;i++) {      //criando um for 
        if(tipo == tipos[i][0]){   
            return tipos[i][1];                  
        }
    }
    return "Aplicação/"+tipo;                         
}
