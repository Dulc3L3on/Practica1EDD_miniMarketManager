#include <cstdlib>
#include <iostream>
#include <string>
#include "ManejadorGraphviz.h"

ManejadorGraphviz::ManejadorGraphviz(){
    escritor = new Escritor();
}

void ManejadorGraphviz::crearArchivosDot(listaEnlazada<Cliente> *listadoEnEsperaCarreta, listaEnlazada<Cliente> *listadoEnEsperaPago, listaEnlazada<Pila<int>> *pilaCarretas, ListaCircular<Cliente> *listaCompras, ListaDoblementeEnlazada<Caja> *listaCajas){
    escritor->escribirColaEspera(listadoEnEsperaCarreta, "ListaEnlazada_ColaEspera");
    escritor->escribirPilaCarretas(pilaCarretas->darPrimerElemento()->darElementosPila(), pilaCarretas->darPrimerElemento()->darNumeroElementosActuales(), "pilaCarretas1");
    escritor->escribirPilaCarretas(pilaCarretas->darUltimoElemento()->darElementosPila(), pilaCarretas->darUltimoElemento()->darNumeroElementosActuales(), "pilaCarretas2");
    escritor->escribirListaCircularCompras(listaCompras);
    escritor->escribirColaEspera(listadoEnEsperaPago, "ListaEnlazada_ColaPago");
    escritor->escribirListaDoblementeEnlazadaCajas(listaCajas);//Recuerda que aquí esta el cierre del bloque del grafo contenedor...
    guardarRepresentacion();
}

void ManejadorGraphviz::guardarRepresentacion(){//INSIDE "crearArchivosDot"
    system("dot -Tpng grafoMiniMarket.dot -o representacionMinimarket.png");    
}

void ManejadorGraphviz::mostrarGrafico(){
    system("nohup display /home/phily/Documentos/Carpeta_estudios/2021/5toSemestre/EstructuraDeDatos/LabEstructura/pra_proys/practica1/Practica1EDD_miniMarketManager/Codificacion/representacionMinimarket.png &");//sino funciona, pureba con el path rel y si no funciona, haz que se guarde en una carpeta del escritorio...
}