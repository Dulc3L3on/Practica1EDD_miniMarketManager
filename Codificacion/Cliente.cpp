#include <cstdlib>
#include <iostream>
#include <string>
#include "Cliente.h"  

    Cliente::Cliente(int elCodigo){
        id = elCodigo;
    }
  
    void Cliente::recogerCarritoCompras(int codigoCarreta){
        carretaAsignada = codigoCarreta;
    }

    int Cliente::darIdentificacion(){
        return id;
    }

    int Cliente::darNumeroCarretaCompras(){
        return carretaAsignada;
    }