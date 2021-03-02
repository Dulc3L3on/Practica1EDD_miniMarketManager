#include <cstdlib>
#include <iostream>
#include <string>

using namespace std;

template <class T>//forma equivalente de crear una clase genérica a la de Java
class Nodo {
    private:
        Nodo<T> *nodoSiguiente;//puesto que debe poder hacer referencia a un obj creado almacenado en él...        
        T contenido;

    public://se declaran los prototipos de las funciones, métodos normales y cnstrcs xD
        Nodo(T);//A ver si no te da problemas este, busca sobre la sobrecarga de cnstrcs... si no se puede entonces solo envía NULL en los lugares en los que lo usabas xD.. al parecer si se puede xD no decían que no xD, solo para los desructores...
        Nodo(T , Nodo<T>*);
        void establecerElSiguiente(Nodo<T>*);
        Nodo<T> obtenerElSiguiente();       
        T darContenido();
       ~Nodo();//Destructor       
};

    template <class T>//al parecer aunque el header posea esta especificación, en el archivo del código fuente del encabezado habrá que colocarlo de nuevo...
    Nodo<T>::Nodo(T elemento):Nodo<T> (elemento, NULL)
    {
        //esta sintaxis es simi a como se hizo en C#, para invocar a un 
        //vrs de cnstrct diferente... [mejro dicho C# realizó una
        //sintaxis simi a la delegación de cnstrc de C++ xD]
    }

	template <class T>    
    Nodo<T>::Nodo(T elContenido, Nodo<T> *elNodoSiguiente)//recuerd que en las definiciones de los métodos sí debes colocar la clase a la cual pertenecen, sea que seencuentrene en el mismo archivo de las "declaraciones" o no
    {
        contenido = elContenido;
        nodoSiguiente = elNodoSiguiente;
    }

    template <class T>    
    void  Nodo<T>::establecerElSiguiente(Nodo<T> *elSiguiente){
        nodoSiguiente = elSiguiente;
    }

    template <class T>
    Nodo<T> Nodo<T>::obtenerElSiguiente(){
        return nodoSiguiente;
    }

    template <class T>
    T Nodo<T>::darContenido(){
        return contenido;
    }

    template <class T>
    Nodo<T>::~Nodo<T>(){//el destructor
        delete nodoSiguiente;;
    }