#include <cstdlib>
#include <iostream>
#include <string>

class Cliente{
    private:
        int id;//que en realidad es el # de persona que ha sido creada...
        int carretaAsignada;

    public:
        Cliente(int);
        void recogerCarritoCompras(int);
        int darIdentificacion();
        int darNumeroCarretaCompras();
};