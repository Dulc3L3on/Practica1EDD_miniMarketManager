#include <cstdlib>
#include <iostream>
#include <string>
#include "NodoDoble.h"

using namespace std; 

	template <class T>//Recuerda que indicar que es una plantilla, debe colocarse en cada método, sea que solo exista un arch .cpp o que esté separado como este, y esto se hace porque debe indicarse especificamente a quine pertenece y en qué consiste, para que sepa cómo trabajar con él el compilador...
    NodoDoble<T>::NodoDoble(T elContenido, NodoDoble<T> *elNodoSiguiente)//recuerd que en las definiciones de los métodos sí debes colocar la clase a la cual pertenecen, sea que seencuentrene en el mismo archivo de las "declaraciones" o no
    {
        contenido = elContenido;
        nodoSiguiente = elNodoSiguiente;
    }

    template <class T>
    void NodoDoble<T>::establecerNodoAnterior(NodoDoble<T>* elNodoAnterior){
        nodoAnterior = elNodoAnterior;
    }

    template <class T>
    void NodoDoble<T>::establecerNodoSiguiente(NodoDoble<T>* elNodoSiguiente){
        nodoAnterior = elNodoSiguiente;
    }

    template <class T>
    NodoDoble<T> NodoDoble<T>::obtenerElSiguiente(){
        return nodoSiguiente;
    }

    template <class T>
    NodoDoble<T> NodoDoble<T>::obtenerElAnterior(){
        return nodoSiguiente;
    }

    template <class T>
    T NodoDoble<T>::darContenido(){
        return contenido;
    }

    template <class T>
    NodoDoble<T>::~NodoDoble<T>(){//el destructor
        delete nodoSiguiente;
    }
