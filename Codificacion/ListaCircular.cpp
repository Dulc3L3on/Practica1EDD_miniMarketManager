#ifndef LISTACIRCULAR_H
#define LISTACIRCULAR_H
#include <cstdlib>
#include <iostream>
#include <string>
#include "NodoDoble.cpp"

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
        void anadirAlPrincipio(T*);//será útil para la Pila, puesto que sobre el primer elemento caen los demás...
        void anadirAlFinal(T*);//Este será útil para todas las listas y para la cola...
        T* darPrimerElemento();
        T* darUltimoElemento();
        T* darYEliminarPrimerElemento();
        T* darYEliminarEn(int);
        T* darYEliminarUltimoElemento();
        void limpiarLista();
        int darTamanio();
        bool estaVacia();
        NodoDoble<T>* darPrimerNodo();
        NodoDoble<T>* darUltimoNodo();
};

    template <class T>
    //Se implementan los métodos declarados en el header [arch.h]... tuvo que colocarse aquí por el hecho de ger clase genérica...
    ListaCircular<T>::ListaCircular()
    {
        limpiarLista();
    }

    template <class T>
    void ListaCircular<T>::anadirAlPrincipio(T *elemento){
         NodoDoble<T> *nuevoNodo = new NodoDoble<T>(elemento, primerNodo);//recuerda que en el caso de C++, el new se emplea para cuando se quiere asignar una referencia de un OBJ  a un puntero
        //NodoDoble<T> nuevoNodo(elemento, primerNodo);//lo hago así por el hecho de que este es un nodo "contenido" no es en sí con el que se estará navegando,por lo cual no requiere de ser un puntero, sino un nodo normal...       
        if(tamanio>0){            
            nuevoNodo->obtenerElSiguiente()->establecerNodoAnterior(nuevoNodo);//o en otras palabras, se establece el anterior al que antes era el primer nodo...            

            //esto es para que se de la apariencia de trayectoria circular...
            nuevoNodo->establecerNodoAnterior(ultimoNodo);
            ultimoNodo->establecerNodoSiguiente(nuevoNodo);
        }//así se establece el nodoAnterior xD
        
        primerNodo = nuevoNodo;
        if(tamanio == 0){//pues si no daría error...
            ultimoNodo = primerNodo;//puesto que pasará a ser el último de todos, por el hecho de haber sido el primero en add...
        }
        tamanio++;
    }

    template <class T>
    void ListaCircular<T>::anadirAlFinal(T *elemento){
        if(estaVacia()){
            primerNodo = new NodoDoble<T>(elemento, NULL);
            ultimoNodo = primerNodo;
            tamanio++;
        }else{
            NodoDoble<T> *nuevoNodoAnterior = ultimoNodo;
            cout<<"\t->se guarda ultimo nodo"<<endl;
            NodoDoble<T> *nuevoUltimo =  new NodoDoble<T>(elemento, NULL);
            nuevoUltimo->establecerNodoAnterior(nuevoNodoAnterior);
            cout<<"\tse establece nodo anterior"<<endl;
            nuevoNodoAnterior->establecerNodoSiguiente(nuevoUltimo);            
            cout<<"\tse estalece nodo siguiente"<<endl;
            ultimoNodo = nuevoUltimo;
            cout<<"\tse actualiza ultimo nodo"<<endl;           

         /* NodoDoble<T> *nuevoNodo = new NodoDoble<T>(elemento, NULL);            
            nuevoNodo->establecerNodoAnterior(ultimoNodo);
            nuevoNodo->obtenerElAnterior()->establecerNodoSiguiente(nuevoNodo);*/

            //para formar la trayectoria circular...
            /*nuevoUltimo->establecerNodoSiguiente(primerNodo);
            primerNodo->establecerNodoAnterior(nuevoUltimo);*/

            ultimoNodo->establecerNodoSiguiente(primerNodo);
            primerNodo->establecerNodoAnterior(ultimoNodo);//a mi parecer debe ser así o colocar el bloque simi a este que trab con el nuevoUltimo y hacer l actualización del último hasta abajo...
            cout<<"\tse reestablece trayectoria circular"<<endl;       

            /*ultimoNodo = nuevoNodo;//para que así se pueda dar el seguimiento correcto a la lista... *///yo veo que no importa que esté antes de hacer las asignaciones para que siga con la trayec circular, puesto que solo estoy haciendo que en lugar de que se haga la igualación cuando ya el nuevo nodo al que se iguala el último, posee todo, se le asigna no solo a este nuevo nodo, sino tb al ultimo, de manera "simultanea"
            tamanio++;
        }
    }

    template <class T>
    T* ListaCircular<T>::darPrimerElemento(){
        return primerNodo->darContenido();
    }

    template <class T>
    T* ListaCircular<T>::darUltimoElemento(){
        return ultimoNodo->darContenido();
    }

    template <class T>
    T* ListaCircular<T>::darYEliminarPrimerElemento(){
        if(tamanio>0){            
            NodoDoble<T> *nodoAuxiliar = primerNodo->obtenerElSiguiente();//si debe ser así por el hecho de que puede ser un solo elemento, sino, se provocaría un NULL pointer y otros pasos no tendrían sentido...
            T *elementoAEliminar = primerNodo->darContenido();
            //delete primerNodo;//se elimina el antiguo primer nodo//NO es necesario por el hecho de que este cb el lugar al que refiere y el unico que almacena esto es la var temporal, la cual se encarga de eli el compi de C++

            if(tamanio>1){//para asegurar la trayectoria circular...
                nodoAuxiliar->establecerNodoAnterior(ultimoNodo);                
                primerNodo = nodoAuxiliar;                
                ultimoNodo->establecerNodoSiguiente(primerNodo);      
            }/*else{//es decir es =1
                delete ultimoNodo;//o en otras palabras, es igual a NULL... [no lo igualo al 1er nodo porque ese ya lo borré entonces no se si es me vaya a dar problemas...]
            }*///no debe hacerse pues se caería en una redundancia por el hecho de que ya se ha borrado al hacer la eliminación del nodo axiliar que es el +unico que tien la referencia a lo que refería xD el primer nodo xD

           /* NodoDoble<T> *nodoAuxiliar = primerNodo;//si debe ser así por el hecho de que puede ser un solo elemento, sino, se provocaría un NULL pointer y otros pasos no tendrían sentido...
            T *contenido = primerNodo->darContenido();
            //delete primerNodo;//se elimina el antiguo primer nodo//NO es necesario por el hecho de que este cb el lugar al que refiere y el unico que almacena esto es la var temporal, la cual se encarga de eli el compi de C++

            if(tamanio>1){//para asegurar la trayectoria circular...
                nodoAuxiliar->obtenerElSiguiente()->establecerNodoAnterior(ultimoNodo);                
                primerNodo = nodoAuxiliar->obtenerElSiguiente();                
                ultimoNodo->establecerNodoSiguiente(primerNodo);      
            }else{//es decir es =1
                delete ultimoNodo;//o en otras palabras, es igual a NULL... [no lo igualo al 1er nodo porque ese ya lo borré entonces no se si es me vaya a dar problemas...]
            }*/ 

            //no borro al nodo Auxiliar por el hecho de que es una var local, por lo cual debería morir xD lego de terminar la exe de este método...
            tamanio--;
            cout<<endl<<"primer nodo eliminado de la listaCircular"<<endl;
            return elementoAEliminar;
        }
        return NULL;
    }//NOTA: En realidad no debería de tener el if >1 y el else respectivo, puesto que se encarga de esto el métod que engloba a este y al de eliminar ultimo, pero por el hecho de ser punlico, mejor que se deje eso para asegurar su trabajo individual...

    template <class T>
    T* ListaCircular<T>::darYEliminarEn(int posicion){//iniciando desde 0 xD
        if(tamanio>0){
            T *contenido;

            if(posicion == 1){                
                return darYEliminarPrimerElemento();
            }
            if(posicion == tamanio){
                return darYEliminarUltimoElemento();
            }else if(posicion <= tamanio){//puesto que la 1ra es rep por el 1 y no el 0...
                //si no funciona lo que tendrías que hacer es, crear 2 var temp nuevas, una para el anterior y otra para el siguiente, las cuales son las que se peservarán, y a ellas app los cb lo cual es uan anlaogía a lo que se hizo con la listaEnlazada...
                NodoDoble<T> *nodoAuxiliar = primerNodo;

                for (int nodoActual = 2; nodoActual < tamanio; nodoActual++)//De esta forma ya no habría necesidad de tener que restarle 1 al valor de la posición al momento de revisar si el nodo actual corresponde a aquel del cual se brindó la posición, porque están en armonía, es decir poseen el mismo valor para un mismo caso...
                {//debe ser el pto inicial el 2, porque a ese será al que se llegue en la primera vuelta, y debe ser < a tamaño, porque aquí a lo máximo se podrá llegar al penúltimo, puesto que se cuando es el último, se ejecuta el cuerpo de un método diferente...
                    if(nodoActual == posicion){
                        NodoDoble<T> *nodoDobleAuxiliar = nodoAuxiliar;//este será útil para hacer los enlaces nuevos que se requieren y el auxiliar para mantener los enlaces antiguos y así reformar correctamente la lista circular luego de eliminarsele un elemento...
                        contenido = nodoAuxiliar->darContenido();

                        nodoDobleAuxiliar->obtenerElAnterior()->establecerNodoSiguiente(nodoAuxiliar->obtenerElSiguiente());//puede hacerse esto sin necesidad de revisar condiciones, por el hecho de que se sabe que se está en un caso perfecto, es decir en uno en el que no hace falta ni el anterior ni el siguiente[es decir no son NULL] al nodo que se va a eliminar...xD
                        nodoDobleAuxiliar->obtenerElSiguiente()->establecerNodoAnterior(nodoAuxiliar->obtenerElAnterior());
                        //Las variables LOCALES NO se deben eliminar, pues de eso se encarga el compi de C++, eso quiere decir que si la var con la que se asginó el valor a dicha var local, cambia y la unica referencia que se tiene a lo que contenia dicha var cambiada era la var temporal, el compi de C++ se encargará de hacer el delete :) xD, por lo cual si tu haces el delete de manera manual te lanzará un error por intentar, el compi, eli algo que ya se había eli [por la linea que colocaste]                 

                        tamanio--;
                        cout<<endl<<"nodo "<<nodoActual<< "eliminado de la listaCircular"<<endl;
                        return contenido;
                    }//Es probable que requiera de otras var, pero esto es lo que se debe hacer xD
                    nodoAuxiliar = nodoAuxiliar->obtenerElSiguiente();//para permitir la revisión xD
                }                
            }
        }        
        return NULL;//en esta situación el rcibir NULL indica que la posición no corresponde a ninguno de los índices de los elementos que contiene la lista...
    }//NICE

    template <class T>
    T* ListaCircular<T>::darYEliminarUltimoElemento(){
        if(tamanio>0){         
            NodoDoble<T> *nodoAuxiliar = ultimoNodo->obtenerElAnterior();//todo este cuerpo debe ser así por el hecho de que la lista podría tener 1 solo elemento...
            T *contenido = ultimoNodo->darContenido();
            //delete ultimoNodo;//se eleiminar el antiguo primer nodo//NO se requiere porque se reestablecerá su valor y a lo que refería anteriormente será eliminado al eli la var temporal que referenciaba indirectamente a este contenido...                          

            if(tamanio>1){//esto es para asegurar la trayectoria circular...
                nodoAuxiliar->establecerNodoSiguiente(primerNodo);
                ultimoNodo = nodoAuxiliar;
                primerNodo->establecerNodoAnterior(ultimoNodo);                           
            }/*else{
                delete primerNodo;//para que quede nuevamente vacía...
            }*///aunque ahora que lo pienso no dbe colocarse, puesto que se tendría una redundancia, por el hecho de que al usar delete, no se borra lo que contiene el puntero, es decir la dirección, SINO lo que hay en esa dirección! xD


            /*NodoDoble<T> *nodoAuxiliar = ultimoNodo;//todo este cuerpo debe ser así por el hecho de que la lista podría tener 1 solo elemento...
            T *contenido = ultimoNodo->darContenido();
            delete ultimoNodo;//se eleiminar el antiguo primer nodo                          

            if(tamanio>1){//esto es para asegurar la trayectoria circular...
                nodoAuxiliar->obtenerElAnterior()->establecerNodoSiguiente(primerNodo);
                ultimoNodo = nodoAuxiliar->obtenerElAnterior();
                primerNodo->establecerNodoAnterior(ultimoNodo);                           
            }else{
                delete primerNodo;//para que quede nuevamente vacía...
            }*/            
                        
            tamanio--;
            cout<<endl<<"ultimo nodo eliminado de la listaCircular"<<endl;
            return contenido;
        }
        return NULL;
    }//puesto que este método es "ensamblado" en un método general, que se encarga del caso en el que el solo exista un elemento, entonces no es necesario colocar el if tam >1 y el else correspondiente, pero se dejarán para asegurar su trabajo individual...

    template <class T>
    void ListaCircular<T>::limpiarLista(){//por el hecho de que puede haber más de un nodo, al momento de querer limpiarla, entonces mejor se procederá ha hacer un for
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
    NodoDoble<T>* ListaCircular<T>::darPrimerNodo(){
        return primerNodo;
    }

    template <class T>
    NodoDoble<T>* ListaCircular<T>::darUltimoNodo(){
        return ultimoNodo;
    }

    template <class T>
    ListaCircular<T>::~ListaCircular(){//el destructor
        limpiarLista();
    }

#endif