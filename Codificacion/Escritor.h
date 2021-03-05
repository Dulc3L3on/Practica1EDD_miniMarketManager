#ifndef ESCRITOR_H
#define ESCRITOR_H
#include <cstdlib>
#include <iostream>
#include <string>
#include <fstream>//permite escribir y leer archivos
#include "listaEnlazada.cpp"
#include "Cliente.cpp"
#include "ListaCircular.cpp"
#include "ListaDoblementeEnlazada.cpp"
#include "Caja.h"

using namespace std;

class Escritor{
    private:    
        fstream manejadorArchivo;    

    public:
        Escritor();
        void escribirColaEspera(listaEnlazada<Cliente>*, string);//puesto que en realidad lo que me interesa es la lista como tal, este me será útil para la cola de espera y pago...
        void escribirPilaCarretas(int*, int, string);//Se empelará 2 veces 1 para la 1er pila y la otra para la 2da xD :v XD
        void escribirListaCircularCompras(ListaCircular<Cliente>*);        
        void escribirListaDoblementeEnlazadaCajas(ListaDoblementeEnlazada<Caja>*);        
};

#endif