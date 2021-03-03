#ifndef MANAGER_H
#define MANAGER_H
#include <cstdlib>
#include <iostream>
#include <string>
#include "Pila.cpp"
#include "ListaCircular.cpp"
#include "ListaDoblementeEnlazada.cpp"
#include "Caja.h"
#include "Cola.cpp"

using namespace std;  

class Manager{
    private:
        void retornarCarritoCompras(Pila<int>*, int);//Aqui se revisa se genera el numero aleatorio entre 1 y 2 para poner a disponibilidad la carreta

    public:
        Manager();
        Pila<int>* prepararCarretas(int, int);//no olvides que cuando quieras devolver un arreglo, lo que debes hacer es devolver su puntero, puesto que este en realidad es uno de estos :0 xD        
        void asignarCarritoCompras(Cola<Cliente>*, Pila<int>[], ListaCircular<Cliente>*);//este es para dar las carretas a los clientes, no para colocar el # de carretas solicitadas en la pila...      
        void enviarColaPago(ListaCircular<Cliente>*, Cola<Cliente>*);//aquí se generará la cdad aleatoria de intentos a realizar para add clientes a la cola de pago [la cual es una var global...]
        void realizarProcesoPago(ListaDoblementeEnlazada<Caja>*, Cola<Cliente>*, Pila<int>*);//aquí se hará la revisión de si hay clientes en espera de realizar pago, para así asignarlos a la caja que se encuentre vacía al momento de revisar el listado 2blemente enlazado de cajas y tb se hace el proceso para liberación de las cajas, si es que cumple con una de las 2 condic para este proceso, es decir que aquí se usa el método para retornar el carrito de compras...        

        int max(int, int);//es una herramienta, por eso lo puse aquí xD
};
//Creo que aparte vamos a crear una clase creadora, una de herramientas y otra para las gráficas [quiza la de herramientas solo tenga 1 método, entonces solo se crearía la clase para las gráficas...]

#endif