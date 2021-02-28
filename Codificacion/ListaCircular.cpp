#include <cstdlib>
#include <iostream>
#include <string>
#include "NodoDoble.h"

using namespace std;

template <class T>
class ListaCircular{//lista xD creo jajaja xD, BIEN YA xD
    private:
         NodoDoble<T> *primerNodo;
         NodoDoble<T> *ultimoNodo;
         int tamanio;

    public:    
        ListaCircular();
        ~ListaCircular();        
        void anadirAlPrincipio(T);//será útil para la Pila, puesto que sobre el primer elemento caen los demás...
        void anadirAlFinal(T);//Este será útil para todas las listas y para la cola...
        T darPrimerElemento();
        T darUltimoElemento();
        T darYEliminarPrimerElemento();
        T darYEliminarEn(int);
        T darYEliminarUltimoElemento();
        void limpiarLista();
        int darTamanio();
        bool estaVacia();
        NodoDoble<T> darPrimerNodo();
        NodoDoble<T> darUltimoNodo();
};


    template <class T>
    //Se implementan los métodos declarados en el header [arch.h]... tuvo que colocarse aquí por el hecho de ger clase genérica...
    ListaCircular<T>::ListaCircular()
    {
        limpiarLista();
    }

    template <class T>
    void ListaCircular<T>::anadirAlPrincipio(T elemento){
         Nodo<T> *nuevoNodo = new Nodo<T>(elemento, primerNodo);//recuerda que en el caso de C++, el new se emplea para cuando se quiere asignar una referencia de un OBJ  a un puntero
        //NodoDoble<T> nuevoNodo(elemento, primerNodo);//lo hago así por el hecho de que este es un nodo "contenido" no es en sí con el que se estará navegando,por lo cual no requiere de ser un puntero, sino un nodo normal...       
        if(tamanio>0){            
            nuevoNodo.obtenerElSiguiente().establecerNodoAnterior(nuevoNodo);//o en otras palabras, se establece el anterior al que antes era el primer nodo...            

            //esto es para que se de la apariencia de trayectoria circular...
            nuevoNodo.establecerNodoAnterior(ultimoNodo);
            ultimoNodo->establecerNodoSiguiente(nuevoNodo);
        }//así se establece el nodoAnterior xD
        
        primerNodo = nuevoNodo;
        if(tamanio == 0){//pues si no daría error...
            ultimoNodo = primerNodo;//puesto que pasará a ser el último de todos, por el hecho de haber sido el primero en add...
        }
        tamanio++;
    }

    template <class T>
    void ListaCircular<T>::anadirAlFinal(T elemento){
        if(estaVacia()){
            primerNodo = new NodoDoble<T>(elemento, NULL);
            ultimoNodo = primerNodo;
            tamanio++;
        }else{
            NodoDoble<T> *nuevoNodo = new NodoDoble<T>(elemento);            
            nuevoNodo->establecerNodoAnterior(ultimoNodo);
            nuevoNodo->obtenerElAnterior().establecerNodoSiguiente(nuevoNodo);            

            //para formar la trayectoria circular...
            nuevoNodo->establecerNodoSiguiente(primerNodo);
            primerNodo->establecerNodoAnterior(nuevoNodo);

            ultimoNodo = nuevoNodo;//para que así se pueda dar el seguimiento correcto a la lista...
            tamanio++;
        }
    }

    template <class T>
    T ListaCircular<T>::darPrimerElemento(){
        return primerNodo->darContenido();
    }

    template <class T>
    T ListaCircular<T>::darUltimoElemento(){
        return ultimoNodo->darContenido();
    }

    template <class T>
    T ListaCircular<T>::darYEliminarPrimerElemento(){
        if(tamanio>0){            
            NodoDoble<T> *nodoAuxiliar = primerNodo;//si debe ser así por el hecho de que puede ser un solo elemento, sino, se provocaría un NULL pointer y otros pasos no tendrían sentido...
            T contenido = primerNodo.darContenido();
            delete primerNodo;//se eleiminar el antiguo primer nodo                         

            if(tamanio>1){//para asegurar la trayectoria circular...
                nodoAuxiliar.obtenerElSiguiente()->establecerNodoAnterior(ultimoNodo);                
                primerNodo = nodoAuxiliar.obtenerElSiguiente();                
                ultimoNodo->establecerNodoSiguiente(primerNodo);      
            }else{//es decir es =1
                delete ultimoNodo;//o en otras palabras, es igual a NULL... [no lo igualo al 1er nodo porque ese ya lo borré entonces no se si es me vaya a dar problemas...]
            } 

            //no borro al nodo Auxiliar por el hecho de que es una var local, por lo cual debería morir xD lego de terminar la exe de este método...
            tamanio--;
            return contenido;
        }
        return NULL;
    }//NOTA: En realidad no debería de tener el if >1 y el else respectivo, puesto que se encarga de esto el métod que engloba a este y al de eliminar ultimo, pero por el hecho de ser punlico, mejor que se deje eso para asegurar su trabajo individual...

    template <class T>
    T ListaCircular<T>::darYEliminarEn(int posicion){//iniciando desde 0 xD
        if(tamanio>0){
            T contenido;

            /*if(tamanio == 1){
                contenido = primerNodo->darContenido();
                delete primerNodo;
                delete ultimoNodo;
                tamanio =0;
                return contenido;
            }*///esto no debe ir porque sin importar que posición se haya ingresadom si solo tiene 1 elemento, devolverá al unico que está ahi cuando en realidad no se haya solicitado a ese...
              // eso tb quiere decir que SÍ, los métodos que se llaman en este mpetidi es decir el que elimina el 1ro y último, tendrán que ser capaces de controlar el hecho en el que la lista solo tenga 1 elemento...
            if(posicion == 1){
                return darYEliminarPrimerElemento();
            }
            if(posicion == tamanio){
                return darYEliminarUltimoElemento();
            }else if(posicion <= tamanio){//puesto que la 1ra es rep por el 1 y no el 0...
                NodoDoble<T> nodoAuxiliar = primerNodo;

                for (int nodoActual = 2; nodoActual < tamanio; nodoActual++)//De esta forma ya no habría necesidad de tener que restarle 1 al valor de la posición al momento de revisar si el nodo actual corresponde a aquel del cual se brindó la posición, porque están en armonía, es decir poseen el mismo valor para un mismo caso...
                {//debe ser el pto inicial el 2, porque a ese será al que se llegue en la primera vuelta, y debe ser < a tamaño, porque aquí a lo máximo se podrá llegar al penúltimo, puesto que se cuando es el último, se ejecuta el cuerpo de un método diferente...
                    if(nodoActual == (posicion){
                        NodoDoble<T> nodoDobleAuxiliar = nodoAuxiliar;//este será útil para hacer los enlaces nuevos que se requieren y el auxiliar para mantener los enlaces antiguos y así reformar correctamente la lista circular luego de eliminarsele un elemento...
                        contenido = nodoAuxiliar.darContenido();

                        nodoDobleAuxiliar.obtenerElAnterior().establecerNodoSiguiente(nodoAuxiliar.obtenerElSiguiente());//puede hacerse esto sin necesidad de revisar condiciones, por el hecho de que se sabe que se está en un caso perfecto, es decir en uno en el que no hace falta ni el anterior ni el siguiente[es decir no son NULL] al nodo que se va a eliminar...xD
                        nodoDobleAuxiliar.obtenerElSiguiente().establecerNodoAnterior(nodoAuxiliar.obtenerElAnterior());
                        delete nodoAuxiliar;                        

                        tamanio--;
                        return contenido;
                    }//Es probable que requiera de otras var, pero esto es lo que se debe hacer xD
                }                
            }
        }        
        return NULL;//en esta situación el rcibir NULL indica que la posición no corresponde a ninguno de los índices de los elementos que contiene la lista...
    }//NICE

    template <class T>
    T ListaCircular<T>::darYEliminarUltimoElemento(){
        if(tamanio>0){         
            NodoDoble<T> nodoAuxiliar = ultimoNodo;//todo este cuerpo debe ser así por el hecho de que la lista podría tener 1 solo elemento...
            T contenido contenido = ultimoNodo.darContenido();
            delete ultimoNodo;//se eleiminar el antiguo primer nodo                          

            if(tamanio>1){//esto es para asegurar la trayectoria circular...
                nodoAuxiliar.obtenerElAnterior().establecerNodoSiguiente(primerNodo);
                ultimoNodo = nodoAuxiliar.obtenerElAnterior();
                primerNodo->establecerNodoAnterior(ultimoNodo);                           
            }else{
                delete primerNodo;//para que quede nuevamente vacía...
            }            
                        
            tamanio--;
            return contenido;
        }
        return NULL;
    }//puesto que este método es "ensamblado" en un método general, que se encarga del caso en el que el solo exista un elemento, entonces no es necesario colocar el if tam >1 y el else correspondiente, pero se dejarán para asegurar su trabajo individual...

    template <class T>
    void ListaCircular<T>::limpiarLista(){//por el hecho de que puede haber más de un nodo, al momento de querer limpiarla, entonces mejor se procederá ha hacer un for
        NodoDoble* nodoAuxiliar = primerNodo;

        for (int nodoActual = 2; nodoActual < tamanio; nodoActual++)
        {
            NodoDoble<T> *nodoSubAuxiliar = nodoAuxiliar;//con el fin de no perder la referencia, para así limpiarla...
            nodoAuxiliar = nodoAuxiliar.obtenerElSiguiente();
            delete nodoSubAuxiliar;
        }//for por medio del cual liberameos la memoria hasta el penúltimo nodo...                       

        delete nodoAuxiliar;//se libera el espacio del penúltimo Nodo...
        delete ultimoNodo;
        tamanio = 0;
    }

    template <class T>
    int ListaCircular<T>::darTamanio(){
        return tamanio;
    }

    template <class T>
    bool ListaCircular<T>::estaVacia(){
        if(tamanio==0){//lo hice así porque no se si al igual que java, detectaría como pregunta una expre entre () directamente en el return...
            return true;
        }
        return false;
    }

    template <class T>
    NodoDoble<T> ListaCircular<T>::darPrimerNodo(){
        return primerNodo;
    }

    template <class T>
    NodoDoble<T> ListaCircular<T>::darUltimoNodo(){
        return ultimoNodo;
    }

    template <class T>
    ListaCircular<T>::~ListaCircular(){//el destructor
        limpiarLista();
    }

