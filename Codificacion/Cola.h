#include <iostream>
#include <string>
#include "listaEnlazada.h"

using namespace std;

template <class T>
class Cola{
    private:
        listaEnlazada<T> elementosCola;//el aux dijo que todos los obj son punteros, y tiene sentido al hacer la analogía con Java, pero no se si hacerlo así 

    public: 
        Cola();
        ~Cola();
        void encolar(T);
        T inspeccionarPrimerElemento(); 
        T desencolarPrimerElemento();  
        bool estaVacia();
        int darTamanio();
};

//#include "Cola.cpp"//te recuerdas que no tocaste "nada" en el .cpp puesto que al parecer si no se podrá hacer la separación de los headers y de la imple.. :c xD por lo que habí a leido...