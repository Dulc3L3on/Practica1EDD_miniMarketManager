#include <cstdlib>
#include <iostream>
#include <string>
#include "Cliente.h"  

using namespace std;  

    Cliente::Cliente(){
     //pensaba colocar el id como -1, pero no debería ser así pues lo que en realidad debería hacer es que todas las instancias a objetos, 
     //sean punteros, esto específicamente en los contenidos de los Nodos, de tal manera que pueda devolver algo null
     //eso sí, todas las instancias que reciban los valores de estas listas tb deberían ser null
    }

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