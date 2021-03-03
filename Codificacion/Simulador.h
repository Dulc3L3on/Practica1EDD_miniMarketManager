#ifndef SIMULADOR_H
#define SIMULADOR_H
//estos son los guardas y su función es que si al incluir más de un aclase en otra, algunas de las incluidas incluyan xD, a una clase o header en común, no exista error por aparecer más de una vez la definición de la clase :3 xD
#include <cstdlib>
#include <iostream>
#include <string>
#include "Manager.h"

using namespace std;
class Simulador{
    private:
        int numeroCajas;        
        int numeroCarretas;
        int totalClientesCreados;
        int rondaActual;
        ListaCircular<Cliente> clientesComprando;
        ListaDoblementeEnlazada<Caja> listadoCajas;
        Pila<int> *pilaCarretas;//Debe ser un puntero, por el hecho de que envío un arreglo de 2 pilas...
        Cola<Cliente> colaEsperaCarretas;
        Cola<Cliente> colaPago;               
        Manager *manager;

    public:
        Simulador();
        void solicitarDatosInmutables();//Es decir numero de cajas y carretas...
        int solicitarTiempoCajas(int);
        void prepararCajas();
        void simularMiniMarket();//Aquí se hace la llamada al método para solicitar el # de clientes entrantes, y los demás métodos de manager que se encarga de realizar los movimientos que sucederían al estar en la tienda...
        int solicitarNumeroClientes();
        bool agregarClientes(int);

};
#endif