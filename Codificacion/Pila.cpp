#ifndef PILA_H
#define PILA_H
//recuerda que en el caso de la pila el error que tenías no era
// en esta clase,s ino en la listaEnlazada, porque no hacía el
// desincremento de la var tamanio al dar y eliminar el útlimo xD
#include <cstdlib>
#include <iostream>
#include <string>

using namespace std;

template <class T>
class Pila{
    private://por el hecho de que el tamaño de la pila no crecerá, entonces se empleará un arreglo...
        T *elementosPila;
        int posicionUltimoElemento;
        int capacidadMaxima;

    public:     
        Pila();//lo iba a colocar, pero mejor lo haré solo si me da problemas el no tenerlo...
        Pila(int);
        ~Pila();
        void apilar(T);
        T* inspeccionarUltimoElemento();  
        T* desapilarUltimoElemento();
        bool estaVacia();
        int darCapacidad();
        int darNumeroElementosActuales();
        int estaLlena();
};

    template <class T>
    Pila<T>::Pila(){}

    template <class T>
    Pila<T>::Pila(int laCapacidadMaxima){
        capacidadMaxima = laCapacidadMaxima;
        posicionUltimoElemento=0;
        elementosPila = new T[capacidadMaxima];                       
    }

    template <class T>
    void Pila<T>::apilar(T elementoNuevo){//para así recibir la posición del número... si no da, entonces lo que se hará es que al devolver el ID de los carritos, se devuelva la dirección de estos vals... y con eso problema resoluto xD, es decir que se recibirán en esta clase valores normales y se devolverán las direcciones de esos valores...
        for (int elementoActual = 0; elementoActual < capacidadMaxima; elementoActual++)//En C++ el lenght() además de ser un método, solo es aplicacble a los strings...
        {
            if(elementosPila[elementoActual]> posicionUltimoElemento){//puesto que el número de carretas iniciará a partir de 1 [y estas no será un obj, sino solo un #...], pero esto está mal, porque si no fuera de números sino de chars, el 0 no indicaría vacío... y si fuera de booleans :| xD
                elementosPila[elementoActual] = elementoNuevo;//a mi parecer solo debe ser el valor y no & porque el arreglo es de tipo normal, pero a él apunta u puntero...
                posicionUltimoElemento++;
                break;
            }
        }        
    }

    template <class T>
    T* Pila<T>::inspeccionarUltimoElemento(){
        return &elementosPila[posicionUltimoElemento];            
    }

    template <class T>
    T* Pila<T>::desapilarUltimoElemento(){        
        T *valorAEliminar = &elementosPila[posicionUltimoElemento];//para que así pueda recibir el valor el puntero...
        //elementosPila[posicionUltimoElemento] = 0;//Pero a ligual que en el caso del método para apilar, solo sería correcto hacer esto para valores de tipo numéricos...
        //yo digo que el delete funciona para cualquier tipo de dato... y de ser así, entonces se ha garantizado que este método podra app a sin importar que tipo de valor sea el que almacene la pila...
        delete &elementosPila[posicionUltimoElemento];

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
    int Pila<T>::estaLlena(){
        if(posicionUltimoElemento == capacidadMaxima){
            return true;
        }
        return false;
    }

    template <class T>
    Pila<T>::~Pila(){
        delete [] elementosPila;//para borrar el arreglo completo...
        posicionUltimoElemento=0;
        capacidadMaxima = 0;
    }

#endif