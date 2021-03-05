#ifndef MANEJADORGRAPHVIZ_H
#define MANEJADORGRAPHVIZ_H

#include <cstdlib>
#include <iostream>
#include <string>
#include <fstream>//permite escribir y leer archivos
#include "Escritor.h"
#include "listaEnlazada.cpp"
#include "Pila.cpp"
#include "Cliente.cpp"
#include "ListaCircular.cpp"
#include "ListaDoblementeEnlazada.cpp"
#include "Caja.h"

class manejadorGraphviz{
    private:
        Escritor *escritor;

    public:
        manejadorGraphviz();
        void crearArchivosDot(listaEnlazada<Cliente>*, listaEnlazada<Cliente>*, listaEnlazada<Pila<int>>*, ListaCircular<Cliente> *, ListaDoblementeEnlazada<Caja> *);
        void mostrarGrafico();
};

#endif