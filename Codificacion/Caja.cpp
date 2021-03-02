#include <cstdlib>
#include <iostream>
#include <string>
#include "Caja.h"  
  
    Caja::Caja(int elId, int elTiempoServicio){
        id = elId;
        tiempoServicio = elTiempoServicio;      
    }//puesto que cuando se asigne el tiempo, se crerpá a la caja, con el fin de reducir trabajo...
    
    void Caja::agregarCliente(Cliente elCliente){
        clienteActual = elCliente;
        estaDesocupada = false;
        turnosFaltantes = tiempoServicio;
    }//se add el cliente y se hace la asignacion en la var turnosFaltantes para permitir regresar el carrito a su pila..        
        
    int Caja::darCodigo(){
        return id;
    }

    int Caja::darTiempoServicio(){
        return tiempoServicio;
    }

    void Caja::decrementarTiempoRestante(){
        turnosFaltantes--;
    }
        
    int Caja::darTurnosFaltantes(){
        return turnosFaltantes;
    }
        
    void Caja::desocuparCaja(){
        delete &clienteActual;//ya que no es un puntero, entonces mando a dirección, pues eso es lo que devuelve un ptr por default xD
        estaDesocupada = true;//PUESTO que los turnos faltantes ya eseta en 0, solo faltaba hacer esto xD
    }//así ya no 

    bool Caja::estaLibre(){
        return estaDesocupada;
    }

    Cliente Caja::darCliente(){
        return clienteActual;
    }