#ifndef LISTAENLAZADA_H
#define LISTAENLAZADA_H
//header de la clase listaEnlazada, en el cual se colocan los prototipos 
//de los métodos variables y constct a emplear...
#include <cstdlib>
#include <iostream>
#include <string>
#include "Nodo.cpp"

using namespace std;

template <class T>
class listaEnlazada
{
    private:
         Nodo<T> *primerNodo;
         Nodo<T> *ultimoNodo;
         int tamanio;

    public://Se declaran los prototipos de las funciones, que tiene como función indicar al compi con que tipo de valores se estará trabajando...
        listaEnlazada();
        ~listaEnlazada();        
        void anadirAlPrincipio(T*);//será útil para la Pila, puesto que sobre el primer elemento caen los demás...
        void anadirAlFinal(T*);//Este será útil para todas las listas y para la cola...
        T* darPrimerElemento();
        T* darUltimoElemento();
        T* darYEliminarPrimerElemento();
        T* darYEliminarUltimoElemento();
        void limpiarLista();
        int darTamanio();
        bool estaVacia();
        Nodo<T>* darPrimerNodo();
        Nodo<T>* darUltimoNodo();
        //no veo necesario tener que colocar un insertar en por el hecho de que el recorrido de la lista, especificacmente para el caso de la listaDoblementeEnlazada de cajas, puede hacerse en el método mismo en el que se haga la inserción ó en la clase de la lista 2blementeEnlazada xD
};

    template <class T>
    //Se implementan los métodos declarados en el header [arch.h]... tuvo que colocarse aquí por el hecho de ger clase genérica...
    listaEnlazada<T>::listaEnlazada()
    {
        limpiarLista();
    }

    template <class T>
    void listaEnlazada<T>::anadirAlPrincipio(T *elemento){//para la pila...
        Nodo<T> *nuevoNodo = new Nodo<T>(elemento, primerNodo);//recuerda que en el caso de C++, el new se emplea para cuando se quiere asignar una referencia de un OBJ  a un puntero
        //Nodo<T> nuevoNodo(elemento, primerNodo);//lo hago así por el hecho de que este es un nodo "contenido" no es en sí con el que se estará navegando,por lo cual no requiere de ser un puntero, sino un nodo normal...       
        primerNodo = nuevoNodo;
        tamanio++;
    }

    template <class T>
    void listaEnlazada<T>::anadirAlFinal(T *elemento){//para la cola...
        if(estaVacia()){
            primerNodo = new Nodo<T>(elemento);
            ultimoNodo = primerNodo;
            tamanio++;
        }else{
            Nodo<T> *nuevoNodo = new Nodo<T>(elemento);            
            /*Nodo<T> *nodoSiguienteAntiguoUltimo = ultimoNodo->obtenerElSiguiente();
            nodoSiguienteAntiguoUltimo = nuevoNodo;*/
        
            ultimoNodo->establecerElSiguiente(nuevoNodo);

            ultimoNodo = nuevoNodo;//para darle seguimiento a la lista...
            tamanio++;
        }
    }

    template <class T>
    T* listaEnlazada<T>::darPrimerElemento(){
        return primerNodo->darContenido();
    }

    template <class T>
    T* listaEnlazada<T>::darUltimoElemento(){
        return ultimoNodo->darContenido();
    }

    template <class T>
    T* listaEnlazada<T>::darYEliminarPrimerElemento(){//esto es para la cola...
        if(tamanio>0){                 
            Nodo<T> *nodoAuxiliar = primerNodo;
            T *elementoAEliminar = nodoAuxiliar->darContenido();
            delete primerNodo;//Aquí se borró el contenido antrior del 1er nodo antes de asignarle el nuevo, a diferencia del método para eliminar el último esto lo digo porque solo se elimina la referncia del nodo temporla auxilar... [aunque no debería hacerse porque desaparee al terminar el contexto del método...], pues se asgina de una vez el nuevo valor en lugar de estar borrado, aunque creo que si hay qie borrar porque sino no se libera la memoria...

            primerNodo = nodoAuxiliar->obtenerElSiguiente();
            delete nodoAuxiliar;            
            tamanio--;
            return elementoAEliminar;//recuerdate que al enviar esto, lo que estás mandando es la dir, por lo cual al querer acceder al contenido deberás colocar el * en la clase que emplee la listaEnlazada...
        }
        return NULL;
    }//por ser el primero y no tener noción del anterior, entonces para este caso, al momneto de eliminar, basta con que se elimine el contenido del "primerNodo", pues es el único por medio del cual puede hacerse referencia a dichp nodo...

    template <class T>
    T* listaEnlazada<T>::darYEliminarUltimoElemento(){//Esto es para la pila...
        if(tamanio>0){            
            T *elementoAEliminar = ultimoNodo->darContenido();
            delete ultimoNodo;//puedo hacer esto sin problemas, porque solo estoy eleiminando uno de lso 2 caminos en los que se hace referencia a este , y por medio del for elimino la otra forma por medio de la cual sigue existiendo, es decir, por el camino de los "siguientes"...

            Nodo<T> *nodoAuxiliar = primerNodo;//Esto es para que se actualice la dirección que almacena el último nodo
            for (int nodoActual = 2; nodoActual < tamanio; nodoActual++)//de tal forma que se quede en el penúltimo nodo...
            {
                nodoAuxiliar = nodoAuxiliar->obtenerElSiguiente();
            }
            delete nodoAuxiliar->obtenerElSiguiente();//liberando ultimo ultimo nodo, puesto que los punteros no pueden hacerse null... creo xD
            ultimoNodo = nodoAuxiliar;
            tamanio--;

            return elementoAEliminar;
        }
        return NULL;
    }

    template <class T>
    void listaEnlazada<T>::limpiarLista(){//por el hecho de que puede haber más de un nodo, al momento de querer limpiarla, entonces mejor se procederá ha hacer un for
        Nodo<T>* nodoAuxiliar = primerNodo;

        for (int nodoActual = 2; nodoActual < tamanio; nodoActual++)
        {
            Nodo<T> *nodoSubAuxiliar = nodoAuxiliar;//con el fin de no perder la referencia, para así limpiarla...
            nodoAuxiliar = nodoAuxiliar->obtenerElSiguiente();
            delete nodoSubAuxiliar;
        }//for por medio del cual liberameos la memoria hasta el penúltimo nodo...                       

        delete nodoAuxiliar;//se libera el espacio del penúltimo Nodo...
        delete ultimoNodo;
        tamanio = 0;
    }

    template <class T>
    int listaEnlazada<T>::darTamanio(){
        return tamanio;
    }

    template <class T>
    bool listaEnlazada<T>::estaVacia(){
        if(tamanio==0){//lo hice así porque no se si al igual que java, detectaría como pregunta una expre entre () directamente en el return...
            return true;
        }
        return false;
    }

    template <class T>
    Nodo<T>* listaEnlazada<T>::darPrimerNodo(){//para la cola...
        return primerNodo;
    }

    template <class T>
    Nodo<T>* listaEnlazada<T>::darUltimoNodo(){//para la pila...
        return ultimoNodo;
    }

    template <class T>
    listaEnlazada<T>::~listaEnlazada(){//el destructor
        limpiarLista();
    }

#endif