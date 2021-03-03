#ifndef LISTADOBLEMENTEENLAZADA_H
#define LISTADOBLEMENTEENLAZADA_H
#include <cstdlib>
#include <iostream>
#include <string>
#include "NodoDoble.cpp"

using namespace std;

template <class T>
class ListaDoblementeEnlazada{//lista xD creo jajaja xD, BIEN YA xD
    private:
         NodoDoble<T> *primerNodo;
         NodoDoble<T> *ultimoNodo;
         int tamanio;

    public:    
        ListaDoblementeEnlazada();
        ~ListaDoblementeEnlazada();        
        void anadirAlPrincipio(T*);//será útil para la Pila, puesto que sobre el primer elemento caen los demás...
        void anadirAlFinal(T*);//Este será útil para todas las listas y para la cola...
        T* darPrimerElemento();
        T* darUltimoElemento();
        T* darYEliminarPrimerElemento();
        T* darYEliminarUltimoElemento();
        void limpiarLista();
        int darTamanio();
        bool estaVacia();
        NodoDoble<T>* darPrimerNodo();//debe devolver PUNTEROS! xD
        NodoDoble<T>* darUltimoNodo();
};

    template <class T>
    //Se implementan los métodos declarados en el header [arch.h]... tuvo que colocarse aquí por el hecho de ger clase genérica...
    ListaDoblementeEnlazada<T>::ListaDoblementeEnlazada()
    {
        limpiarLista();
    }

    template <class T>
    void ListaDoblementeEnlazada<T>::anadirAlPrincipio(T *elemento){
         NodoDoble<T> *nuevoNodo = new NodoDoble<T>(elemento, primerNodo);//recuerda que en el caso de C++, el new se emplea para cuando se quiere asignar una referencia de un OBJ  a un puntero
        //NodoDoble<T> nuevoNodo(elemento, primerNodo);//lo hago así por el hecho de que este es un nodo "contenido" no es en sí con el que se estará navegando,por lo cual no requiere de ser un puntero, sino un nodo normal...       
        if(tamanio>0){
            
            nuevoNodo->obtenerElSiguiente()->establecerNodoAnterior(nuevoNodo);//Esto por el error que tuve que corregir en el ejercicio de la listaEnlazada de C++ que dejó el Aux Valiente...         
            //o en otras palabras, se establece el anterior al que antes era el primer nodo...            
        }//así se establece el nodoAnterior xD
        
        primerNodo = nuevoNodo;
        if(tamanio==0){
            ultimoNodo = primerNodo;//puesto que pasa a ser el último de todos... y debe hacerse en la primera creación, es decir, por la misma razón por lo cual lo cb en la lista circular...
        }
        tamanio++;
    }

    template <class T>
    void ListaDoblementeEnlazada<T>::anadirAlFinal(T *elemento){
        if(estaVacia()){
            primerNodo = new NodoDoble<T>(elemento, NULL);
            ultimoNodo = primerNodo;
            tamanio++;
        }else{
            NodoDoble<T> *nuevoNodo = new NodoDoble<T>(elemento, NULL);            
            nuevoNodo->establecerNodoAnterior(ultimoNodo);
            nuevoNodo->obtenerElAnterior()->establecerNodoSiguiente(nuevoNodo);//como el nodo anterior, tb es un puntero, por eso coloqué a ->          

            ultimoNodo = nuevoNodo;//para que así se pueda dar el seguimiento correcto a la lista...
            tamanio++;
        }
    }

    template <class T>
    T* ListaDoblementeEnlazada<T>::darPrimerElemento(){
        return primerNodo->darContenido();
    }

    template <class T>
    T* ListaDoblementeEnlazada<T>::darUltimoElemento(){
        return ultimoNodo->darContenido();
    }

    template <class T>
    T* ListaDoblementeEnlazada<T>::darYEliminarPrimerElemento(){
        if(tamanio>0){
            NodoDoble<T> *nodoAuxiliar = primerNodo;//Debe ser así por el hecho de que la lista puede llegar a tener un solo elemento...
            T *elementoAEliminar = nodoAuxiliar->darContenido();
            delete primerNodo;//Aquí se borró el contenido antrior del 1er nodo antes de asignarle el nuevo, a diferencia del método para eliminar el último esto lo digo porque solo se elimina la referncia del nodo temporla auxilar... [aunque no debería hacerse porque desaparee al terminar el contexto del método...], pues se asgina de una vez el nuevo valor en lugar de estar borrado, aunque creo que si hay qie borrar porque sino no se libera la memoria...

            if(tamanio>1){
                nodoAuxiliar->obtenerElSiguiente()->establecerNodoAnterior(NULL);//puesto que pasa a ser el primero..
                primerNodo = nodoAuxiliar->obtenerElSiguiente();//pues no tiene sentido hacerlo si el siguiente es nulo :v
            }else{
                delete ultimoNodo;//pues solo tenía un elemento, entonces alusar esto la lista se quedó vacía...
            }
          
            delete nodoAuxiliar;                        
            tamanio--;
            return elementoAEliminar;
        }
        return NULL;
    }//NICE...

    template <class T>
    T* ListaDoblementeEnlazada<T>::darYEliminarUltimoElemento(){//Debe ser así por el hecho de que la lista puede llegar a tener un solo elemento...
        if(tamanio>0){
            /*NodoDoble<T> *nodoAEliminar = ultimoNodo;
            T elementoAEliminar = nodoAEliminar.darContenido();
            delete nodoAEliminar;*/
            T *elementoAEliminar = ultimoNodo->darContenido();//no se por qué había creado la var de arriba :v xD, pues se puede obtener directamente el contenido, sin necesidad de tener que crear otra var...

            if(tamanio>1){
                NodoDoble<T> *nodoAuxiliar = primerNodo;//Esto es para que se actualice la dirección que almacena el último nodo
                for (int nodoActual = 2; nodoActual < tamanio; nodoActual++)//de tal forma que se quede en el penúltimo nodo...
                {
                    nodoAuxiliar = nodoAuxiliar->obtenerElSiguiente();
                }
                //Hice esto por el hecho de que se borró la copia de la dirección que almacenaba el "últimoNodo" mas no al al verdadero último nodo, es decir al que se encuentra en la lista...
            
                delete nodoAuxiliar->obtenerElSiguiente();//liberando ultimo ultimo nodo, puesto que los punteros no pueden hacerse null... creo xD                
                nodoAuxiliar->establecerNodoSiguiente(NULL);//puesto que pasa a ser el ultimo...
                ultimoNodo = nodoAuxiliar;
            }else{
                delete ultimoNodo;
                delete primerNodo;                
            }
            
            tamanio--;
            return elementoAEliminar;
        }
        return NULL;
    }//creo que si tengo que colocar el delete ultimoNodo después de eliminar lo que el siguiente del nodoAuxiliar posee... pues al no hacerlo, no se liberará la memoria, porque solo estás perdiendo la refernecia a lo creado y no eliminandolo de la memoria...

    template <class T>
    void ListaDoblementeEnlazada<T>::limpiarLista(){//por el hecho de que puede haber más de un nodo, al momento de querer limpiarla, entonces mejor se procederá ha hacer un for
        NodoDoble<T> *nodoAuxiliar = primerNodo;

        for (int nodoActual = 2; nodoActual < tamanio; nodoActual++)
        {
            NodoDoble<T> *nodoSubAuxiliar = nodoAuxiliar;//con el fin de no perder la referencia, para así limpiarla...
            nodoAuxiliar = nodoAuxiliar->obtenerElSiguiente();
            delete nodoSubAuxiliar;
        }//for por medio del cual liberameos la memoria hasta el penúltimo nodo...                       

        delete nodoAuxiliar;//se libera el espacio del penúltimo Nodo...
        delete ultimoNodo;
        tamanio = 0;
    }

    template <class T>
    int ListaDoblementeEnlazada<T>::darTamanio(){
        return tamanio;
    }

    template <class T>
    bool ListaDoblementeEnlazada<T>::estaVacia(){
        if(tamanio==0){//lo hice así porque no se si al igual que java, detectaría como pregunta una expre entre () directamente en el return...
            return true;
        }
        return false;
    }

    template <class T>
    NodoDoble<T>* ListaDoblementeEnlazada<T>::darPrimerNodo(){
        return primerNodo;
    }

    template <class T>
    NodoDoble<T>* ListaDoblementeEnlazada<T>::darUltimoNodo(){
        return ultimoNodo;
    }

    template <class T>
    ListaDoblementeEnlazada<T>::~ListaDoblementeEnlazada(){//el destructor
        limpiarLista();
    }

#endif