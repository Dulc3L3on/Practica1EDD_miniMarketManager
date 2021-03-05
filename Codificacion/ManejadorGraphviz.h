#ifndef MANEJADORGRAPHVIZ_H
#define MANEJADORGRAPHVIZ_H
#include <cstdlib>
#include <iostream>
#include <string>
#include "Escritor.h"
#include "Pila.cpp"

class ManejadorGraphviz{
    private:
        Escritor *escritor;

    public:
        ManejadorGraphviz();
        void crearArchivosDot(listaEnlazada<Cliente>*, listaEnlazada<Cliente>*, listaEnlazada<Pila<int>>*, ListaCircular<Cliente> *, ListaDoblementeEnlazada<Caja> *);
        void guardarRepresentacion();
        void mostrarGrafico();
};

#endif