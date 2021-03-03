#include <cstdlib>
#include <iostream>
#include <string>
#include "Manager.h"

using namespace std;  

    Manager::Manager(){}
  
    Pila<int>* Manager::prepararCarretas(int numeroCarretas, int numeroCarretasSinUso){
        Pila<int> *pilaCarretas = new Pila<int>[2]();
        //vamos a seguir con esta forma, y si la pila de carretas te presenta errores, entonces lo que harás es declarar una var global privada de tipo puntero y en este método hacer el new Pila<int>[2] y en una linea, incializar el espacio con Pila<int> [puesto que recibe valores normales, puesto que en realidad así es como funcionan los arreglo] y en otra linea la otra ini xD y así devolverás el ptro gobal al arr de las 2 pilas... [recuerda que la sintaxis y forma de "tratamiento" es simi a como lo hiciste en la pila xD, para colocar el arr que almacena sus datos]
        pilaCarretas[0] = Pila<int>(numeroCarretas);
        pilaCarretas[1] = Pila<int>(numeroCarretas);

        for (int carretaActual = 0; carretaActual < numeroCarretasSinUso; carretaActual++)
        {            
            if(numeroCarretasSinUso <= numeroCarretas){
                pilaCarretas[0].apilar(carretaActual);//puesto que requiero enviar un puntero, y un puntero es practicamente una direción, entonces... mando la dirección xD                
            }else{
                pilaCarretas[1].apilar(carretaActual);
            }           
        }   
        return pilaCarretas;
    }//no olvides que cuando quieras devolver un arreglo, lo que debes hacer es devolver su puntero, puesto que este en realidad es uno de estos :0 xD

   //La asignación de cajas se hará al repetir el bucle, que se encargue de solicitar los datos, una cdad de veces = al número de cajas solicitado... el numero de repetición actual, corresponderá a la caja que se debe obtener...
        //o en lugar de crear un metodo para buscar en la lista2blemente enlazada, es obtener el primer nodod en este método y conforme vayas dando las vueltas, irias obteniendo la caja en cuestión, de tal forma que no se tenga cada vez empezar el l primera, hasta llegar a la que corresponde... 
        //para ese caso, mejor se va a ir creando cada caja conforme se vaya recibiendo el tiempo, es decir que el #cajas recibido se guardará en la var que servirá coo límite para exe este método, así no hay necesidad de buscar las cajas, puesto que así creo que crearía más trabajo...         
       
    void Manager::asignarCarritoCompras(Cola<Cliente> *colaEsperaCarretas, Pila<int> *pilaCarretas, ListaCircular<Cliente> *clientesEnCompras){//recuerda que enviaste un puntero, porque se envia un arreglo, por ello se requiere la dirección del primer elemento...
        while(!colaEsperaCarretas->estaVacia() && (!pilaCarretas[0].estaVacia() || !pilaCarretas[1].estaVacia())){//pues se requiere que al menos 1 de las dos tengan carretas...

            if(!pilaCarretas[0].estaVacia() && !pilaCarretas[1].estaVacia()){//puesto que recibir un puntero es recibir la cabeza de un arreglo xD                
                colaEsperaCarretas->inspeccionarPrimerElemento()->recogerCarritoCompras(pilaCarretas[rand()%(2)+1].desapilarUltimoElemento());//para que se agarre cualquira de las carretas... xD                 
            }else if(!pilaCarretas[0].estaVacia()){
                colaEsperaCarretas->inspeccionarPrimerElemento()->recogerCarritoCompras(pilaCarretas[0].desapilarUltimoElemento());
            }else{//Es decir que la 1 está llena [está asegurado este hecho por la condición del while... xD]
                colaEsperaCarretas->inspeccionarPrimerElemento()->recogerCarritoCompras(pilaCarretas[1].desapilarUltimoElemento());//si la var que recibía esto hubiera sido un int norma y no un int ptro, hubieras tenido que colocar el * puesto que el contenido de la pila es un ptro y se requieria un valor, y este * permite realizar la conversión...
            }            
            
            cout<<"El cliente "<<colaEsperaCarretas->inspeccionarPrimerElemento()->darIdentificacion()<<" escoge carreta # "<<colaEsperaCarretas->inspeccionarPrimerElemento()->darNumeroCarretaCompras()<<endl;//creo que aquí lo que voy a estar mostando será la dirección y no el contendio, lo cual es lo que deseo... pero su recuerdas, cuando en C hiciste esto, tb pensaste que termianrías obteniendo el valor, pero no fue así, y terminaste concluyendo que era porque por default devuelve el valor y si se coloca el & devuelve la dirección, entonces quiere decir que sabe que tipo de evolución debe ahcer según el contexto...
            clientesEnCompras->anadirAlFinal(colaEsperaCarretas->desencolarPrimerElemento());//y así se agrega a la tienda a cliente par que pueda escoger sus productos xD            
        }

        if(colaEsperaCarretas->estaVacia() && pilaCarretas[0].estaVacia() && pilaCarretas[1].estaVacia()){//si llegamos aquí es porque, o se acabaron las carretas, los clientes o ambas
            cout<<"Todos los clientes en espera de carreta obtuvieron una"<<endl;
        }else if(colaEsperaCarretas->estaVacia()){//si se llego aquí es porque solo una de las 2 estaban vacías o la cola o las pilas...
            cout<<"Sin clientes en espera de carretas"<<endl;
        }
        if(pilaCarretas[0].estaVacia() && pilaCarretas[1].estaVacia()){
            cout<<"Clientes en espera de carretas"<<endl;
        }        
    }//este es para dar las carretas a los clientes, no para colocar el # de carretas solicitadas en la pila...
      
    void Manager::enviarColaPago(ListaCircular<Cliente> *clientesEnCompras, Cola<Cliente> *colaDePagos){
        int numero = rand()%(clientesEnCompras->darTamanio())+1;//De tal forma que tenga oportunidad de sair todos los clientes en una misma ronda, se escoge una cantidad de clientes existentes a sacar... si no hay de todos modos no harbá problema porque tengo una revisión de si ese valor es <= al tamaño...
        int ubicacionCliente = 0;

        for (int clienteCandidatoActual = 1; clienteCandidatoActual <= numero; clienteCandidatoActual++)
        {
            ubicacionCliente = (rand()%(100)+1);//en realidad debería ser un número desde 0 hasta el tam [pero en las indicaciones 1 a 100], pues sino, no todos tendrán oportunidad de salir en el primer intento
            if(ubicacionCliente <= clientesEnCompras->darTamanio()){//puesto que tengo que mostrar un msje...
                Cliente *cliente = clientesEnCompras->darYEliminarEn(ubicacionCliente);//puesto que lo que devuelve es un puntero...
                cout<<"Cliente #"<<cliente->darIdentificacion()<<"procede a pagar la compra"<<endl;
                colaDePagos->encolar(cliente);//De esta forma se da el cliente que fue escogido por medio del "azar"
            }
        }        
    }//aquí se generará la cdad aleatoria de intentos a realizar para add clientes a la cola de pago [la cual es una var global...]

    void Manager::realizarProcesoPago(ListaDoblementeEnlazada<Caja> *cajas, Cola<Cliente> *colaPagos, Pila<int> *pilaCarritosCompras){
        for (int cajaActual = 0; cajaActual < cajas->darTamanio(); cajaActual++)
        {
            NodoDoble<Caja> *nodoAuxiliar = cajas->darPrimerNodo();//por eso el método debe devolver punteros xD
            if(!nodoAuxiliar->darContenido()->estaLibre() && nodoAuxiliar->darContenido()->darTurnosFaltantes()==0){
                cout<<"Cliente # "<<nodoAuxiliar->darContenido()->darCliente()->darIdentificacion()<<"sale de la tienda y devuelve carreta #"<<nodoAuxiliar->darContenido()->darCliente()->darNumeroCarretaCompras()<<endl;
                retornarCarritoCompras(pilaCarritosCompras, *nodoAuxiliar->darContenido()->darCliente()->darNumeroCarretaCompras());//puesto que al desocupar la caja, se va el cliente y el carrito xD
                nodoAuxiliar->darContenido()->desocuparCaja();                
            }
            if(!nodoAuxiliar->darContenido()->estaLibre() && nodoAuxiliar->darContenido()->darTurnosFaltantes()>0){
                nodoAuxiliar->darContenido()->decrementarTiempoRestante();
            }if(nodoAuxiliar->darContenido()->estaLibre() && !colaPagos->estaVacia()){
                nodoAuxiliar->darContenido()->agregarCliente(colaPagos->desencolarPrimerElemento());//Se elimina al primer cliente en espera de la cola de pagos y se le asigna en una caja...
            }    
        }               
    }

    void Manager::retornarCarritoCompras(Pila<int> *pilaCarritosCompras, int codigoCarritoCompras){
        if(!pilaCarritosCompras[0].estaLlena() && !pilaCarritosCompras[1].estaLlena()){
            pilaCarritosCompras[rand()%(2)+1].apilar(codigoCarritoCompras);
        }if(!pilaCarritosCompras[0].estaLlena()){
            pilaCarritosCompras[0].apilar(codigoCarritoCompras);
        }if(!pilaCarritosCompras[1].estaLlena()){
            pilaCarritosCompras[1].apilar(codigoCarritoCompras);
        }
    }//Aqui se revisa se genera el numero aleatorio entre 1 y 2 para poner a disponibilidad la carreta    


    int Manager::max(int numero1, int numero2){
        if(numero1>numero2){
            return numero1;
        }
        return numero2;
    }
    