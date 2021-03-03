#include <cstdlib>
#include <iostream>
#include <string>
#include "Simulador.h"

using namespace std;  
    Simulador::Simulador(){
        manager = new Manager();
        totalClientesCreados=0;
        listadoCajas = new ListaDoblementeEnlazada<Caja>();//creo qeu por haber colocado el cnstrct sin paráms, C++ se encarga de llamarlo para realizar la construcción...
        clientesComprando = new ListaCircular<Cliente>();
        //pilaCarretas = new Pila<int>();
        colaEsperaCarretas = new Cola<Cliente>();
        colaPago = new Cola<Cliente>();
        clientesEnCadaEstacion = new int[3];//1 para los que estén en caja, 2 para los que estén en cola de pagos y 3 para los que estén escogiendo productos...
        //si mal no recuerdo, los cnstrc sin argumentos, la sobreescripción de los default, son activados por el compi C++ al nada más crear una instancia 
    }

    void Simulador::solicitarDatosInmutables(void){//Es decir el numero de carretas [que app para cada pila] y el numero de cajas, que será útil para el método en el que solicita el tiempo de las cajas...
        cout<<endl<<"Ingrese #carretas disponibles: ";
        cin>>numeroCarretas;//yo creo que si mal no estoy, este hace la conversión por si solo...
        cout<<endl<<"Ingrese #cajas de cobro: ";
        cin>>numeroCajas;
    }       

    void Simulador::solicitarTiempoCajas(void){        
        duracionAtencion = new int[numeroCajas];

        for (int numeroCaja = 1; numeroCaja <= numeroCajas; numeroCaja++)
        {
            cout<<endl<<"Ingrese tunos por cliente caja #"<<numeroCaja<<": ";
            scanf("%d", &duracionAtencion[numeroCaja-1]);        
        }               
    }   

    void Simulador::solicitarClientesEnCadaEstacion(void){//supondremos que el # de carretas siempre será > 0, lo que si no supodremos es que sea > al # de cajas de cobro, por si acaso xD, aunque sí debería ser así... :v xD
        cout<<endl<<"Cuantos clientes de 0 a "<<((numeroCarretas>=numeroCajas)?numeroCajas:numeroCarretas)<<" estan pagando? "<<endl;
        scanf("%d", &clientesEnCadaEstacion[0]);
        if((numeroCarretas-clientesEnCadaEstacion[0])>0){
            cout<<endl<<"Cuantos clientes de 0 a "<<(numeroCarretas-clientesEnCadaEstacion[0])<<" estan en cola de pagos? "<<endl;
            scanf("%d", &clientesEnCadaEstacion[1]);
            if((numeroCarretas-clientesEnCadaEstacion[0]-clientesEnCadaEstacion[1])>0){
                cout<<endl<<"Cuantos clientes de 0 a "<<(numeroCarretas-clientesEnCadaEstacion[0]-clientesEnCadaEstacion[1])<<" escogen productos? "<<endl;
                scanf("%d", &clientesEnCadaEstacion[2]);
            }
        }
        asignarClientesEnCadaEstacion();
    }

    void Simulador::prepararCajas(void){//INSIDE "asignarClientesEnCadaEstacion"                
        for (int cajaActual = 0; cajaActual < numeroCajas; cajaActual++)
        {
            listadoCajas->anadirAlFinal(new Caja((cajaActual+1), duracionAtencion[cajaActual]));//hice esto, pues cualquiera de las listas tienen como contenido un ptro del tipo correspondeinte que decidieron alamacenar en la lista...
            
            if(cajaActual< clientesEnCadaEstacion[0]){//para clientes en caja, pongo asi la condición porque supongo que si ingresaron lo que esperaba es decir un #>0 y <= al #de cajas...
                int idCorrespondiente = cajaActual+1;//Debe crearse cada vez la var, sino lo que se estaría haciendo es cb cada vez el valor, puesto que se almacenaría cada valor nuevo en la misma dirección...
                listadoCajas->darUltimoElemento()->agregarCliente(new Cliente(idCorrespondiente));//puesto que los primeros clientes se tomarán como los primeros en llegar a la caja, por lo tanto estos tienen el mismo id que el de las cajas...
                listadoCajas->darUltimoElemento()->darCliente()->recogerCarritoCompras(&idCorrespondiente);//puesto que son las primeras carretas, por lo cual tiene los primeros id's xD
            }
        }        
    } 

    void Simulador::asignarClientesEnCadaEstacion(void){//INSIDE "solicitarClientesEnCadaEstacion"
        prepararCajas();//aquí se asginan los códigos a las cajas, además del tiempo que tardan en liberar un cliente y al cliente xD

        for (int clienteCreadoEnEstacion =1;  clienteCreadoEnEstacion <= (manager->max(clientesEnCadaEstacion[1],clientesEnCadaEstacion[2])); clienteCreadoEnEstacion++)//comencé en 1 puesto que es más común comenzar un conteo a partir de ese valor... y además así será más fácil colocar el id del cliente, que sería = (#clientesACrearEnEstacion(es)Anterior(es)+#ClientesCreadosEstacionActual)
        {            
            if(clienteCreadoEnEstacion <= clientesEnCadaEstacion[1]){//para clientes en cola de pagos
                int idCorrespondiente = clientesEnCadaEstacion[0]+clienteCreadoEnEstacion;
                colaPago->encolar(new Cliente(idCorrespondiente));//pues así se puede lograr el id acumulado
                colaPago->inspeccionarPrimerElemento()->recogerCarritoCompras(&idCorrespondiente);//aunque si mal no recuerdo, estos métodos de los punteros, no son utiles para asignar sino solo para dar, a pesar de que el obj que almacena, posea el setter respectivo...
            }
            if(clienteCreadoEnEstacion<= clientesEnCadaEstacion[2]){//para clientes escogiendo productos
                 int idCorrespondiente = clientesEnCadaEstacion[0]+clientesEnCadaEstacion[1]+clienteCreadoEnEstacion;
                 clientesComprando->anadirAlFinal(new Cliente(idCorrespondiente));
                 clientesComprando->darUltimoElemento()->recogerCarritoCompras(&idCorrespondiente);
            }
        }        
    }

    int Simulador::solicitarNumeroClientes(void){//INSIDE "agregarClientes"... xD
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
                colaEsperaCarretas->encolar(new Cliente((++totalClientesCreados)));//esto hará que antes de que sea enviada la variable, esta sea incrementada... que es justo lo que quiero... xD, por esa razón es que en el for, se inciia por el valor 1, porque de primero se envia la var y luego se le hace el incremento, por ello cuando llega a la siguiente ronda, llegará con 1 valor más alla [si el incre fue simple...], a diferencia si se colocara ++var, así como ahorita xD
            }                                                                                    
            return true;//quiere decir que ingreso un número que indica que sí desea continuar xD  
        }                                                                                             
        return false;
    }

    void Simulador::simularMiniMarket(){
        solicitarDatosInmutables();        
        solicitarTiempoCajas();
        solicitarClientesEnCadaEstacion();

        pilaCarretas = manager->prepararCarretas(numeroCarretas, (numeroCarretas-clientesEnCadaEstacion[0]-clientesEnCadaEstacion[1]-clientesEnCadaEstacion[2]));

        while(agregarClientes(solicitarNumeroClientes())){//Aquí es donde se pide cada vez a los clientes, pero aún no sé que tipo de var sería a la que se le revisaría el valor para saber si hay que contienuar o no... pues si es bool, tendría que hacer una pregunta a parte, en caambio si es un int podría colocar un -1 para saber que ya no quiere seguir viendo...si mejor eso xD, porque aunque no ingresen cientes, tendría que mostrar "no entraron cleintes", "nadie comprando", "sin cola de pagos", dependiendo en qué puntos la estructura que almacena los clientes esté vaía xD
            manager->asignarCarritoCompras(colaEsperaCarretas, pilaCarretas, clientesComprando);//ahi revisas si solo era de asignar esto o había que hacer algo más...
            manager->enviarColaPago(clientesComprando, colaPago);
            manager->realizarProcesoPago(listadoCajas, colaPago, pilaCarretas);        
        }
    }