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
        T inspeccionarUltimoElemento();  
        T desapilarUltimoElemento();
        bool estaVacia();
        int darCapacidad();
        int darNumeroElementosActuales();
        int estaLlena();
};

    template <class T>
    Pila<T>::Pila(){
        posicionUltimoElemento = -1;
        capacidadMaxima = 0;
    }

    template <class T>
    Pila<T>::Pila(int laCapacidadMaxima){
        capacidadMaxima = laCapacidadMaxima;
        posicionUltimoElemento=-1;//para que así no hayan errores por tener a este índice 1 más alla de la posición en la que en realidad se encuenrta el último...
        elementosPila = new T[capacidadMaxima];                       
    }

    template <class T>
    void Pila<T>::apilar(T elementoNuevo){//para así recibir la posición del número... si no da, entonces lo que se hará es que al devolver el ID de los carritos, se devuelva la dirección de estos vals... y con eso problema resoluto xD, es decir que se recibirán en esta clase valores normales y se devolverán las direcciones de esos valores...       
        if(posicionUltimoElemento<(capacidadMaxima-1)){//puesto que las ubicaciones de los arr empiezan en 0 y el entra como -1 al add el primer elemento, para que así al entrar como el antepenúltimo, antes de asignar s evuelva el antepenúltimo, lo cual es equivalente al ultimo en el arr xD
            posicionUltimoElemento++;  
//A            cout<<"\telemento add: "<<elementoNuevo<<endl;
            elementosPila[posicionUltimoElemento] = elementoNuevo;//a mi parecer solo debe ser el valor y no & porque el arreglo es de tipo normal, pero a él apunta u puntero...              
        }
    }

    template <class T>
    T Pila<T>::inspeccionarUltimoElemento(){        
        return elementosPila[posicionUltimoElemento];//si fuera falso quiere decir que la pila se encuentra llena...                   
    }

    template <class T>
    T Pila<T>::desapilarUltimoElemento(){        
        posicionUltimoElemento--;
//A        cout<<"\telemento desapilado: "<<elementosPila[posicionUltimoElemento+1]<<endl;
        return elementosPila[posicionUltimoElemento+1];//para que así pueda recibir el valor el puntero...
        /*delete &elementosPila[posicionUltimoElemento];*///con respecto a esto, lo que se me ocurre, es que reemplaces lo valores, cuando toque apilar nuevos elementos, en este caso como sé que serán valores int, entonces no habrá problema con hacer esto, pero con cualquier otro valor que no sea primitivo, sí daría problema, pues estarías dejando "basura" en la memoria, puesto que eso que quedó en ese espacio ya no es nec luego de finalizada la exe del programa en cuestión...
    }

    template <class T>
    bool Pila<T>::estaVacia(){
        if(posicionUltimoElemento==-1){
            return true;
        }
        return false;
    }

    template <class T>
    int Pila<T>::darCapacidad(){
        return capacidadMaxima;//esto lo hice porque no sé si el sizeof sirve para esto, aunque leí que sí xD
    }

    template <class T>
    int Pila<T>::darNumeroElementosActuales(){//OJO, dice número, NO POSICÓN!
        return (posicionUltimoElemento+1);
    }

    template <class T>
    int Pila<T>::estaLlena(){
        if(posicionUltimoElemento == (capacidadMaxima-1)){
            return true;
        }
        return false;
    }

    template <class T>
    Pila<T>::~Pila(){
        delete [] elementosPila;//para borrar el arreglo completo...
        posicionUltimoElemento=-1;
        capacidadMaxima = 0;
    }

#endif