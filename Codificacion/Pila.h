#include <cstdlib>
#include <iostream>
#include <string>

using namespace std;

template <class T>
class Pila{
    private://por el hecho de que el tamaño de la pila no crecerá, entonces se empleará un arreglo...
        T elementosPila[];
        int posicionUltimoElemento;
        int capacidadMaxima;

    public:        
        Pila(int);
        ~Pila();
        void apilar(T);
        T inspeccionarUltimoElemento();  
        T desapilarUltimoElemento();
        bool estaVacia();
        int darCapacidad();
        int darNumeroElementosActuales();
};