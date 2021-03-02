#include <cstdlib>
#include <iostream>
#include <string>
#include "Simulador.h"

using namespace std;  
    Simulador::Simulador(){
        manager = new Manager();
        totalClientesCreados=0;
        //si mal no recuerdo, los cnstrc sin argumentos, la sobreescripción de los default, son activados por el compi C++ al nada más crear una instancia 
    }

    void Simulador::solicitarDatosInmutables(){//Es decir el numero de carretas [que app para cada pila] y el numero de cajas, que será útil para el método en el que solicita el tiempo de las cajas...
        cout<<endl<<"Ingrese #carretas disponibles: ";
        cin>>numeroCarretas;//yo creo que si mal no estoy, este hace la conversión por si solo...
        cout<<endl<<"Ingrese #cajas de cobro: ";
        cin>>numeroCajas;
    }

    int Simulador::solicitarTiempoCajas(int numeroCaja){
        int duracionAtencion;
        cout<<endl<<"Ingrese tunos por cliente caja #"<<numeroCaja<<": ";
        cin>>duracionAtencion;
        return duracionAtencion;
    }


    void Simulador::prepararCajas(){
        for (int cajaActual = 0; cajaActual < numeroCajas; cajaActual++)
        {
            listadoCajas.anadirAlFinal(Caja((cajaActual+1), solicitarTiempoCajas(cajaActual+1)));
        }        
    }

    int Simulador::solicitarNumeroClientes(){
        cout<<endl<<endl<<"........----------RONDA: "<<rondaActual<<"------------........"<<endl<<endl;
        int clientesNuevos;
        cout<<endl<<"Ingrese cantidad clientes nuevos: ";
        cin>>clientesNuevos;
        return clientesNuevos;//El dato que hayan ingresado xD
    }

    bool Simulador::agregarClientes(int numeroClientes){
        if(numeroClientes!=-1){//pues si es este valor, quiere decir que ya no quiere seguir, ni siquiera con los datos que quedaban...
            for (int clienteActual = 0; clienteActual < numeroClientes; clienteActual++)
            {
                cout<<"Cliente #"<<totalClientesCreados+1<<"ingresa a la tienda"<<endl;//Esta suma solo afecará a la var en esta línea...
                colaEsperaCarretas.encolar(Cliente((++totalClientesCreados)));//esto hará que antes de que sea enviada la variable, esta sea incrementada... que es justo lo que quiero... xD, por esa razón es que en el for, se inciia por el valor 1, porque de primero se envia la var y luego se le hace el incremento, por ello cuando llega a la siguiente ronda, llegará con 1 valor más alla [si el incre fue simple...], a diferencia si se colocara ++var, así como ahorita xD
            }                                                                                    
            return true;//quiere decir que ingreso un número que indica que sí desea continuar xD  
        }                                                                                             
        return false;
    }

    void Simulador::simularMiniMarket(){
        solicitarDatosInmutables();
        pilaCarretas = manager->prepararCarretas(numeroCarretas);
        prepararCajas();                

        while(agregarClientes(solicitarNumeroClientes())){//Aquí es donde se pide cada vez a los clientes, pero aún no sé que tipo de var sería a la que se le revisaría el valor para saber si hay que contienuar o no... pues si es bool, tendría que hacer una pregunta a parte, en caambio si es un int podría colocar un -1 para saber que ya no quiere seguir viendo...si mejor eso xD, porque aunque no ingresen cientes, tendría que mostrar "no entraron cleintes", "nadie comprando", "sin cola de pagos", dependiendo en qué puntos la estructura que almacena los clientes esté vaía xD
            manager->asignarCarritoCompras(colaEsperaCarretas, pilaCarretas, clientesComprando);//ahi revisas si solo era de asignar esto o había que hacer algo más...
            manager->enviarColaPago(clientesComprando, colaPago);
            manager->realizarProcesoPago(listadoCajas, colaPago, pilaCarretas);        
        }
    }