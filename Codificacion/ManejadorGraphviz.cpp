#include <cstdlib>
#include <iostream>
#include <string>
#include "ManejadorGraphviz.h"

manejadorGraphviz::manejadorGraphviz(){
    escritor = new Escritor();
}

void manejadorGraphviz::crearArchivosDot(listaEnlazada<Cliente> *listadoEnEsperaCarreta, listaEnlazada<Cliente> *listadoEnEsperaPago, listaEnlazada<Pila<int>> *pilaCarretas, ListaCircular<Cliente> *listaCompras, ListaDoblementeEnlazada<Caja> *listaCajas){
    escritor->escribirColaEspera(listadoEnEsperaCarreta, "ListaEnlazada_ColaEspera");
    escritor->escribirPilaCarretas(pilaCarretas->darPrimerElemento()->darElementosPila(), pilaCarretas->darPrimerElemento()->darNumeroElementosActuales(), "pilaCarretas1");
    escritor->escribirPilaCarretas(pilaCarretas->darUltimoElemento()->darElementosPila(), pilaCarretas->darUltimoElemento()->darNumeroElementosActuales(), "pilaCarretas2");
    escritor->escribirListaCircularCompras(listaCompras);
    escritor->escribirColaEspera(listadoEnEsperaPago, "ListaEnlazada_ColaPago");
    escritor->escribirListaDoblementeEnlazadaCajas(listaCajas);
}

void manejadorGraphviz::mostrarGrafico(){
    //system("");
}