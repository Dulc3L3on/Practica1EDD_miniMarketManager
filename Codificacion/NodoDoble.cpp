#ifndef NODODOBLE_H
#define NODODOBLE_H
#include <cstdlib>
#include <iostream>
#include <string>

using namespace std;

template <class T>//forma equivalente de crear una clase genérica a la de Java
class NodoDoble {
    private:
        NodoDoble<T>* nodoSiguiente;//puesto que debe poder hacer referencia a un obj creado almacenado en él...        
        NodoDoble<T>* nodoAnterior;
        T *contenido;

    public://se declaran los prototipos de las funciones, métodos normales y cnstrcs xD        
        NodoDoble(T*, NodoDoble<T>*);
        void establecerNodoAnterior(NodoDoble<T>*);//este lo coloco por el hecho de que la sobrecarga de constrc no es permitida en C++...
        void establecerNodoSiguiente(NodoDoble<T>*);
        NodoDoble<T>* obtenerElSiguiente();
        NodoDoble<T>* obtenerElAnterior();
        T* darContenido();
       ~NodoDoble();//Destructor       
};

    template <class T>//Recuerda que indicar que es una plantilla, debe colocarse en cada método, sea que solo exista un arch .cpp o que esté separado como este, y esto se hace porque debe indicarse especificamente a quine pertenece y en qué consiste, para que sepa cómo trabajar con él el compilador...
    NodoDoble<T>::NodoDoble(T *elContenido, NodoDoble<T> *elNodoSiguiente)//recuerd que en las definiciones de los métodos sí debes colocar la clase a la cual pertenecen, sea que seencuentrene en el mismo archivo de las "declaraciones" o no
    {
        contenido = elContenido;
        nodoSiguiente = elNodoSiguiente;
    }

    template <class T>
    void NodoDoble<T>::establecerNodoAnterior(NodoDoble<T> *elNodoAnterior){
        nodoAnterior = elNodoAnterior;
    }

    template <class T>
    void NodoDoble<T>::establecerNodoSiguiente(NodoDoble<T> *elNodoSiguiente){
        nodoSiguiente = elNodoSiguiente;
    }

    template <class T>
    NodoDoble<T>* NodoDoble<T>::obtenerElSiguiente(){
        return nodoSiguiente;
    }

    template <class T>
    NodoDoble<T>* NodoDoble<T>::obtenerElAnterior(){
        return nodoAnterior;
    }

    template <class T>
    T* NodoDoble<T>::darContenido(){
        return contenido;
    }

    template <class T>
    NodoDoble<T>::~NodoDoble<T>(){//el destructor
        delete nodoSiguiente;
        delete nodoAnterior;//no creo que de problemas si la lista está vacía :v xD
    }

#endif//no se si va aquí [al fianl de todo si es que no existe un archivo h y cpp de una misma "clase"... tal y como sucede aquí...] o al final de la clase...