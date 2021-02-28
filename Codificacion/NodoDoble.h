#include <cstdlib>
#include <iostream>
#include <string>

using namespace std;

template <class T>//forma equivalente de crear una clase genérica a la de Java
class NodoDoble {
    private:
        NodoDoble<T> *nodoSiguiente;//puesto que debe poder hacer referencia a un obj creado almacenado en él...        
        NodoDoble<T> *nodoAnterior;
        T contenido;

    public://se declaran los prototipos de las funciones, métodos normales y cnstrcs xD        
        NodoDoble(T, NodoDoble<T>*);
        void establecerNodoAnterior(NodoDoble<T>*);//este lo coloco por el hecho de que la sobrecarga de constrc no es permitida en C++...
        void establecerNodoSiguiente(NodoDoble<T>*);
        NodoDoble<T> obtenerElSiguiente();
        NodoDoble<T> obtenerElAnterior();
        T darContenido();
       ~NodoDoble();//Destructor       
};