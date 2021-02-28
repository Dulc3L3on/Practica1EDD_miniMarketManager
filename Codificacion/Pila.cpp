//recuerda que en el caso de la pila el error que tenías no era
// en esta clase,s ino en la listaEnlazada, porque no hacía el
// desincremento de la var tamanio al dar y eliminar el útlimo xD
#include <cstdlib>
#include <iostream>
#include <string>
#include "Pila.h"

using namespace std;    

    template <class T>
    Pila<T>::Pila(int laCapacidadMaxima){

        elementosPila[laCapacidadMaxima];//hay que ver cómo se le da el tamanio a un arr en C++...
        posicionUltimoElemento=0;
        capacidadMaxima = laCapacidadMaxima;
    }

    template <class T>
    void Pila<T>::apilar(T elementoNuevo){
        for (int elementoActual = 0; elementoActual < capacidadMaxima; elementoActual++)//En C++ el lenght() además de ser un método, solo es aplicacble a los strings...
        {
            if(elementosPila[elementoActual]==0){//puesto que el número de carretas iniciará a partir de 1 [y estas no será un obj, sino solo un #...], pero esto está mal, porque si no fuera de números sino de chars, el 0 no indicaría vacío... y si fuera de booleans :| xD
                elementosPila[elementoActual] = elementoNuevo;
                posicionUltimoElemento++;
                break;
            }
        }        
    }

    template <class T>
    T Pila<T>::inspeccionarUltimoElemento(){
        return elementosPila[posicionUltimoElemento];            
    }

    template <class T>
    T Pila<T>::desapilarUltimoElemento(){        
        T valorAEliminar = elementosPila[posicionUltimoElemento];
        elementosPila[posicionUltimoElemento] = 0;//Pero a ligual que en el caso del método para apilar, solo sería correcto hacer esto para valores de tipo numéricos...
        posicionUltimoElemento--;
        return valorAEliminar;
    }

    template <class T>
    bool Pila<T>::estaVacia(){
        if(posicionUltimoElemento==0){
            return true;
        }
        return false;
    }

    template <class T>
    int Pila<T>::darCapacidad(){
        return capacidadMaxima;//esto lo hice porque no sé si el sizeof sirve para esto, aunque leí que sí xD
    }

    template <class T>
    int Pila<T>::darNumeroElementosActuales(){
        return posicionUltimoElemento;
    }


    template <class T>
    Pila<T>::~Pila(){
        delete elementosPila;
        posicionUltimoElemento=0;
        capacidadMaxima = 0;
    }
