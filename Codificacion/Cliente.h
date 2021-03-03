#ifndef CLIENTE_H
#define CLIENTE_H
#include <cstdlib>
#include <iostream>
#include <string>

using namespace std;  

class Cliente{
    private:
        int id;//que en realidad es el # de persona que ha sido creada...
        int *carretaAsignada;

    public:
        Cliente();
        Cliente(int);
        void recogerCarritoCompras(int*);
        int darIdentificacion();
        int* darNumeroCarretaCompras();
};
#endif