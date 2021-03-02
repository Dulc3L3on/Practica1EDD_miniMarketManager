#include <cstdlib>
#include <iostream>
#include <string>
#include "Cliente.h"

class Caja{
    private:
        int id;//Que en realidad es el numero de caja
        int tiempoServicio;//en turnos [turnos]
        int turnosFaltantes;
        bool estaDesocupada;
        Cliente clienteActual;

    public: 
        Caja(int, int);//puesto que cuando se asigne el tiempo, se crerpá a la caja, con el fin de reducir trabajo...
        void agregarCliente(Cliente);//se add el cliente y se hace la asignacion en la var turnosFaltantes para permitir regresar el carrito a su pila..        
        int darCodigo();
        int darTiempoServicio();
        void decrementarTiempoRestante();
        int darTurnosFaltantes();
        void desocuparCaja();
        bool estaLibre();
        Cliente darCliente();
};