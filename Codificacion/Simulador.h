#include <cstdlib>
#include <iostream>
#include <string>
#include "Pila.h"
#include "ListaCircular.cpp"
#include "ListaDoblementeEnlazada.cpp"
#include "Caja.h"
#include "Cola.h"
#include "Cliente.h"
#include "Manager.h"

class Simulador{
    private:
        int numeroCajas;        
        int numeroCarretas;
        int totalClientesCreados;
        ListaCircular<Cliente> clientesComprando;
        ListaDoblementeEnlazada<Caja> listadoCajas;
        Pila<int> *pilaCarretas;//Debe ser un puntero, por el hecho de que envío un arreglo de 2 pilas...
        Cola<Cliente> colaEsperaCarretas;
        Cola<Cliente> colaPago;               
        Manager *manager;

    public:
        Simulador();
        void solicitarDatosInmutables();//Es decir numero de cajas y carretas...
        int solicitarTiempoCajas();
        void prepararCajas();
        void simularMiniMarket();//Aquí se hace la llamada al método para solicitar el # de clientes entrantes, y los demás métodos de manager que se encarga de realizar los movimientos que sucederían al estar en la tienda...
        int solicitarNumeroClientes();
        bool agregarClientes(int);

};