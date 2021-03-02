#include <iostream>
#include <string>
#include "Cola.h"

using namespace std;//esta clase la coloqué tal y como se hace con el resto de clases, es decir las no genéricas...


//en esta clase solo se requiere emplear los métodos de la lista enlazada, puesto que esta se encarga de hacer los movimientos, las reservaciones de memoria y los respectivos free... aunque en el caso de C++, este ya se encarga de hacer las reservaciones de memoria, a diferencia de su padre C xD
    template <class T>
    Cola<T>::Cola(){
        elementosCola();//para inicializar la lista... no creo que de error xD auqnue ahora que lo pienso, creo que es innecesario, porque al final de cuentas al crear una var de esta lista, en compi de C++ exe automáticamente el constructor...
    }//no, no va a dar null porque si tengo un cnstrc vacío :v xD

    template <class T>
    void Cola<T>::encolar(T elemento){
        if(elemento!=NULL){
            elementosCola.anadirAlFinal(elemento);
        }
        cout<<"El elemento no debe ser NULO"<<endl;
    }

    template <class T>
    T Cola<T>:: inspeccionarPrimerElemento(){
        return elementosCola.darPrimerElemento();
    }

    template <class T>
    T Cola<T>:: desencolarPrimerElemento(){
        return elementosCola.darYEliminarPrimerElemento();
    }

    template <class T>
    bool Cola<T>::estaVacia(){
        return elementosCola.estaVacia();
    }

    template <class T>
    int Cola<T>::darTamanio(){
        return elementosCola.darTamanio();
    }
    //puesto que las colas, en este programa, no tienen espacios "vacios" es decir que cada vez que se elimine un elemento, se reduce su tamaño, entonces no será necesario add una var para saber el tamño actual de la cola

    template <class T>
    Cola<T>::~Cola<T>(){
        elementosCola.limpiarLista();//esto es para la cola, por si acaso había quedado algo en ella...
    }
