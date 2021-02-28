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
