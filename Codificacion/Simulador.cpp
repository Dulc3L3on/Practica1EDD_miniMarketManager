#include <cstdlib>
#include <iostream>
#include <string>
#include "Simulador.h"

using namespace std;  
    Simulador::Simulador(){
        rondaActual=1;
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
        cout<<endl<<"Ingrese #carretas/pila disponibles: ";//por pila
        cin>>numeroCarretas;//yo creo que si mal no estoy, este hace la conversión por si solo...
        cout<<endl<<"Ingrese #cajas de cobro: ";
        cin>>numeroCajas;
    }       

    void Simulador::solicitarTiempoCajas(void){        
        duracionAtencion = new int[numeroCajas];

        for (int numeroCaja = 1; numeroCaja <= numeroCajas; numeroCaja++)
        {
            cout<<endl<<"Ingrese turnos/cliente caja #"<<numeroCaja<<": ";
            scanf("%d", &duracionAtencion[numeroCaja-1]);        
        }               
    }   

    void Simulador::solicitarClientesEnCadaEstacion(void){//supondremos que el # de carretas siempre será > 0, lo que si no supodremos es que sea > al # de cajas de cobro, por si acaso xD, aunque sí debería ser así... :v xD
        cout<<endl<<"Cuantos clientes de 0 a "<<(((numeroCarretas*2)>=numeroCajas)?numeroCajas:(numeroCarretas*2))<<" estan pagando? ";
        scanf("%d", &clientesEnCadaEstacion[0]);
        if(((numeroCarretas*2)-clientesEnCadaEstacion[0])>0){
            cout<<endl<<"Cuantos clientes de 0 a "<<((numeroCarretas*2)-clientesEnCadaEstacion[0])<<" estan en cola de pagos? ";
            scanf("%d", &clientesEnCadaEstacion[1]);
            if(((numeroCarretas*2)-clientesEnCadaEstacion[0]-clientesEnCadaEstacion[1])>0){
                cout<<endl<<"Cuantos clientes de 0 a "<<((numeroCarretas*2)-clientesEnCadaEstacion[0]-clientesEnCadaEstacion[1])<<" escogen productos? ";
                scanf("%d", &clientesEnCadaEstacion[2]);
            }
        }
//        asignarClientesEnCadaEstacion();
    }

    void Simulador::prepararCajas(void){//INSIDE "asignarClientesEnCadaEstacion"                
        for (int cajaActual = 0; cajaActual < numeroCajas; cajaActual++)
        {
            cout<<endl<<"intenta añadir al final la caja"<<endl;
            listadoCajas->anadirAlFinal(new Caja((cajaActual+1), duracionAtencion[cajaActual]));//hice esto, pues cualquiera de las listas tienen como contenido un ptro del tipo correspondeinte que decidieron alamacenar en la lista...
            
            if(cajaActual< clientesEnCadaEstacion[0]){//para clientes en caja, pongo asi la condición porque supongo que si ingresaron lo que esperaba es decir un #>0 y <= al #de cajas...
                int idCorrespondiente = cajaActual+1;//Debe crearse cada vez la var, sino lo que se estaría haciendo es cb cada vez el valor, puesto que se almacenaría cada valor nuevo en la misma dirección...
                listadoCajas->darUltimoElemento()->agregarCliente(new Cliente(idCorrespondiente));//puesto que los primeros clientes se tomarán como los primeros en llegar a la caja, por lo tanto estos tienen el mismo id que el de las cajas...                
                listadoCajas->darUltimoElemento()->darCliente()->recogerCarritoCompras(manager->darCarritoDeCompras(pilaCarretas));//puesto que son las primeras carretas, por lo cual tiene los primeros id's xD
            }
        }   
        cout<<endl<<"se añadieron todas las cajas"<<endl;     
    } 

    void Simulador::asignarClientesEnCadaEstacion(void){//INSIDE "solicitarClientesEnCadaEstacion", antes, ahora está afuera...xD
        prepararCajas();//aquí se asginan los códigos a las cajas, además del tiempo que tardan en liberar un cliente y al cliente xD

        for (int clienteCreadoEnEstacion =1;  clienteCreadoEnEstacion <= (manager->max(clientesEnCadaEstacion[1],clientesEnCadaEstacion[2])); clienteCreadoEnEstacion++)//comencé en 1 puesto que es más común comenzar un conteo a partir de ese valor... y además así será más fácil colocar el id del cliente, que sería = (#clientesACrearEnEstacion(es)Anterior(es)+#ClientesCreadosEstacionActual)
        {            
            if(clienteCreadoEnEstacion <= clientesEnCadaEstacion[1]){//para clientes en cola de pagos
                int idCorrespondiente = clientesEnCadaEstacion[0]+clienteCreadoEnEstacion;
                colaPago->encolar(new Cliente(idCorrespondiente));//pues así se puede lograr el id acumulado
                colaPago->inspeccionarPrimerElemento()->recogerCarritoCompras(manager->darCarritoDeCompras(pilaCarretas));//aunque si mal no recuerdo, estos métodos de los punteros, no son utiles para asignar sino solo para dar, a pesar de que el obj que almacena, posea el setter respectivo...
                cout<<endl<<"se encolo a "<<idCorrespondiente<<" en cola de pagos"<<endl;
            }
            if(clienteCreadoEnEstacion<= clientesEnCadaEstacion[2]){//para clientes escogiendo productos
                int idCorrespondiente = clientesEnCadaEstacion[0]+clientesEnCadaEstacion[1]+clienteCreadoEnEstacion;
                clientesComprando->anadirAlFinal(new Cliente(idCorrespondiente));
                clientesComprando->darUltimoElemento()->recogerCarritoCompras(manager->darCarritoDeCompras(pilaCarretas));
                cout<<endl<<idCorrespondiente<<" procede a escoger sus productos"<<endl;
            }
        }        
        cout<<"se terminaron de añadir a los clientes en cada estación"<<endl;
    }

    int Simulador::solicitarNumeroClientes(void){
        cout<<endl<<endl<<"........---------- RONDA: "<<(rondaActual++)<<" ------------........"<<endl<<endl;//coloco después el ++ porque así se manda el valor que tiene la var en ese momento y luego se incre...
        int clientesNuevos;
        cout<<endl<<"Ingrese cantidad clientes nuevos: ";
        cin>>clientesNuevos;
        return clientesNuevos;//El dato que hayan ingresado xD
    }

    bool Simulador::agregarClientes(int numeroClientes){
        if(numeroClientes!=-1){//pues si es este valor, quiere decir que ya no quiere seguir, ni siquiera con los datos que quedaban...
            totalClientesCreados = (clientesEnCadaEstacion[0] +clientesEnCadaEstacion[1] + clientesEnCadaEstacion[2]);

            for (int clienteActual = 0; clienteActual < numeroClientes; clienteActual++)
            {
                cout<<endl<<"Cliente #"<<++totalClientesCreados<<" ingresa a la tienda"<<endl;//al hacer la suma así, ya no será necesario hacer el incre en la siguiente... recuerda, que la posicion del ++ [o el duplicado corresp xD, creo que tb se puede con * y /] indica si se hará antes la operación, en este caso un incremento, o se enviará el valor que tenía la variable antes de app la operación... por ello es que al colocar en el for un var++, empezará en el valor ini, pej 0 y a la sig ronda, esta var tendrá el valor dep del incremento...
                colaEsperaCarretas->encolar(new Cliente((totalClientesCreados)));
            }                                                                                    
            return true;//quiere decir que ingreso un número que indica que sí desea continuar xD  
        }                                                                                             
        return false;
    }

    void Simulador::simularMiniMarket(){
        solicitarDatosInmutables();        
        solicitarTiempoCajas();
        pilaCarretas = (manager->prepararCarretas(numeroCarretas));//se toma como suposicón que los clientes que se encuentran en las otras partes de la tienda, NO sobrepasan el # de carretas existentes...
        cout<<endl<<"se apilaron las carretas"<<endl;
        //cout<<"asignacion"<<pilaCarretas;//tb sirvio para comprobar que era el mismo obj referido
        solicitarClientesEnCadaEstacion();
        asignarClientesEnCadaEstacion();      
        
        int numeroClientes = solicitarNumeroClientes();

        while(numeroClientes>-1){//con el >-1 justo se hace lo que deseo, es decir que pueda ingresar cualquier numero de clientes menos aquello valores irracionales [<0...], esto porque aunque no ingresen cientes, tendría que mostrar "no entraron cleintes", "nadie comprando", "sin cola de pagos", dependiendo de que estructura que almacena los clientes esté vacía xD
            agregarClientes(numeroClientes);
            cout<<endl<<"fin de la add de clientes nuevos"<<endl;
            manager->asignarCarritoCompras(colaEsperaCarretas, pilaCarretas, clientesComprando);//ahi revisas si solo era de asignar esto o había que hacer algo más...
            cout<<endl<<"fin asignacion carritos de compras"<<endl;
            manager->enviarColaPago(clientesComprando, colaPago);
            cout<<endl<<"fin add a cola de pago"<<endl;
            manager->realizarProcesoPago(listadoCajas, colaPago, pilaCarretas);        
            cout<<endl<<"fin proceso de cobro"<<endl;
            numeroClientes = solicitarNumeroClientes();
        }
    }