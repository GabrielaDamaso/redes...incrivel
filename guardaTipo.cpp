#include "guardaTipo.h"
guardaTipo::guardaTipo(){} //Construtor padrão
string guardaTipo::getTipo(string tipo){
    for (int i=0; i<13;i++) { 
        if(tipo == tipos[i][0]){
            return tipos[i][1];                  
        }
    }
    return "Aplicação/"+tipo;                         
}
