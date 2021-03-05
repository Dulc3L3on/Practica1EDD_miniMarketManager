#include <cstdlib>
#include <iostream>
#include <fstream>
#include <string>
#include "Escritor.h"

using namespace std;

    Escritor::Escritor(){
        manejadorArchivo.open("grafoMiniMarket.dot");
        manejadorArchivo<<"digraph G {\n";
    }

    void Escritor::escribirColaEspera(listaEnlazada<Cliente> *listadoClientes, string nombreArchivo){        
        manejadorArchivo<<"subgraph "+nombreArchivo+" {\n";

        Nodo<Cliente> *nodoAuxiliar = listadoClientes->darPrimerNodo();//aunque en realidad no es neesario que estas listas sean un puntero porque no voy a modificarles nada, sino que solamente voy a leerlas
        for (int nodoActual = 0; nodoActual < (listadoClientes->darTamanio()-1); nodoActual++)
        {   
            manejadorArchivo<<"Cliente"+to_string(nodoAuxiliar->darContenido()->darIdentificacion())+"shape= box];\n";
            manejadorArchivo<<"Cliente"+to_string(nodoAuxiliar->obtenerElSiguiente()->darContenido()->darIdentificacion())+"[shape= box];\n";         
            manejadorArchivo<<"Cliente"+to_string(nodoAuxiliar->darContenido()->darIdentificacion())+" -> Cliente"+to_string(nodoAuxiliar->obtenerElSiguiente()->darContenido()->darIdentificacion())+";\n";//no hbará problema con estar trabajando con el siguiente, puesto que el ciclo para en la penultima posición, lo cual hace que no se exceda el limite de la lista xD :3

            nodoAuxiliar = nodoAuxiliar->obtenerElSiguiente();
        }        
        manejadorArchivo<<"}\n";        
    }

    void Escritor::escribirPilaCarretas(int *pilaDeCarretas, int limite,string nombreArchivo){       
        manejadorArchivo<<"subgraph "+nombreArchivo+" {\n";
        
        for (int elementoActual = 0; elementoActual < (limite); elementoActual++)//si no se tuviera que manejar el siguiente, debería ser <= puesto que esta var contiene el valor de la ultima posición "que tiene dato" lo digo así porque en realidad las posteriores a esta tienen dato, pero se hace como si se hubiera eliminado, pues es una clase genérica la apila y solo se puede app delete a punteros reales xD, no a los flasificados xD jajaja &nobreVarTipoPrim [o tipo no puntero xD] xD 
        {   
            manejadorArchivo<<"Carreta"+to_string(pilaDeCarretas[elementoActual])+"[shape= box];\n";
            manejadorArchivo<<"Carreta"+to_string(pilaDeCarretas[elementoActual+1])+"[shape= box];\n";         
            manejadorArchivo<<"Carreta"+to_string(pilaDeCarretas[elementoActual])+" -> Carreta"+to_string(pilaDeCarretas[elementoActual+1])+";\n";
        }        
        manejadorArchivo<<"}\n";        
    }

    void Escritor::escribirListaCircularCompras(ListaCircular<Cliente> *listadoClientes){        
        manejadorArchivo<<"subgraph listaCircularCompras {\n";
        
        NodoDoble<Cliente> *nodoAuxiliar = listadoClientes->darPrimerNodo();
        for (int elementoActual = 0; elementoActual < (listadoClientes->darTamanio()-1); elementoActual++)//si no se tuviera que manejar el siguiente, debería ser <= puesto que esta var contiene el valor de la ultima posición "que tiene dato" lo digo así porque en realidad las posteriores a esta tienen dato, pero se hace como si se hubiera eliminado, pues es una clase genérica la apila y solo se puede app delete a punteros reales xD, no a los flasificados xD jajaja &nobreVarTipoPrim [o tipo no puntero xD] xD 
        {   
            manejadorArchivo<<"Cliente"+to_string(nodoAuxiliar->darContenido()->darIdentificacion())+"[label = \"Cliente"+to_string(nodoAuxiliar->darContenido()->darIdentificacion())+"\nCarreta: "+to_string(nodoAuxiliar->darContenido()->darNumeroCarretaCompras())+"\", shape= box];\n";
            manejadorArchivo<<"Cliente"+to_string(nodoAuxiliar->obtenerElSiguiente()->darContenido()->darIdentificacion())+"[label= \"Cliente"+to_string(nodoAuxiliar->obtenerElSiguiente()->darContenido()->darIdentificacion())+"\nCarreta: "+to_string(nodoAuxiliar->obtenerElSiguiente()->darContenido()->darNumeroCarretaCompras())+"\", shape= box];\n";         
            manejadorArchivo<<"Cliente"+to_string(nodoAuxiliar->darContenido()->darIdentificacion())+" -> Cliente"+to_string(nodoAuxiliar->obtenerElSiguiente()->darContenido()->darIdentificacion())+";\n";
            nodoAuxiliar = nodoAuxiliar->obtenerElSiguiente();
        }        
        manejadorArchivo<<"}\n";        
    }

    void Escritor::escribirListaDoblementeEnlazadaCajas(ListaDoblementeEnlazada<Caja> *listadoCajas){        
        manejadorArchivo<<"subgraph listadoCajas {\n";
        
        NodoDoble<Caja> *nodoAuxiliar = listadoCajas->darPrimerNodo();
        for (int elementoActual = 0; elementoActual < (listadoCajas->darTamanio()-1); elementoActual++)//si no se tuviera que manejar el siguiente, debería ser <= puesto que esta var contiene el valor de la ultima posición "que tiene dato" lo digo así porque en realidad las posteriores a esta tienen dato, pero se hace como si se hubiera eliminado, pues es una clase genérica la apila y solo se puede app delete a punteros reales xD, no a los flasificados xD jajaja &nobreVarTipoPrim [o tipo no puntero xD] xD 
        {   
            manejadorArchivo<<"Caja"+to_string(nodoAuxiliar->darContenido()->darCodigo())+"[label = \"Caja#"+to_string(nodoAuxiliar->darContenido()->darCodigo())+"\nDuracion: "+to_string(nodoAuxiliar->darContenido()->darTiempoServicio())+"\nOcupada? "+to_string(!nodoAuxiliar->darContenido()->estaLibre())+"\", shape = box];\n";
            manejadorArchivo<<"Caja"+to_string(nodoAuxiliar->obtenerElSiguiente()->darContenido()->darCodigo())+"[label = \"Caja#"+to_string(nodoAuxiliar->obtenerElSiguiente()->darContenido()->darCodigo())+"\nDuracion: "+to_string(nodoAuxiliar->obtenerElSiguiente()->darContenido()->darTiempoServicio())+"\nOcupada? "+to_string(nodoAuxiliar->obtenerElSiguiente()->darContenido()->estaLibre())+"\", shape = box];\n";         
            manejadorArchivo<<"Caja"+to_string(nodoAuxiliar->darContenido()->darCodigo())+" -> Caja"+to_string(nodoAuxiliar->obtenerElSiguiente()->darContenido()->darCodigo())+";\n";
            nodoAuxiliar = nodoAuxiliar->obtenerElSiguiente();
        }        
        manejadorArchivo<<"}\n";
        manejadorArchivo<<"}\n";//el cierre del grafo englobador...
        manejadorArchivo.close();
    }