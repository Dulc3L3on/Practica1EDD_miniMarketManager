#include <cstdlib>
#include <iostream>
#include <string>
#include "Pila.h"
#include "ListaCircular.cpp"
#include "ListaDoblementeEnlazada.cpp"
#include "Caja.h"
#include "Cola.h"
#include "Cliente.h"

class Manager{
    private:
        void retornarCarritoCompras();//Aqui se revisa se genera el numero aleatorio entre 1 y 2 para poner a disponibilidad la carreta

    public:
        Manager();
        Pila<int>* prepararCarretas(int numeroCarretas);//no olvides que cuando quieras devolver un arreglo, lo que debes hacer es devolver su puntero, puesto que este en realidad es uno de estos :0 xD
        //ya no se hará este aquí puesto que olo sería de retornar un nuevooj caja :v, entonces mejor de una vez se add al método que se encarga de solicitar los datos y llamar los métodos que corresponden...        
        /*ListaDoblementeEnlazada<Caja> prepararCajas(int tiempoEnTurnos);*///Esto se hará al repetir el bucle, que se encargue de solicitar los datos, una cdad de veces = al número de cajas solicitado... el numero de repetición actual, corresponderá a la caja que se debe obtener...
        //o en lugar de crear un metodo para buscar en la lista2blemente enlazada, es obtener el primer nodod en este método y conforme vayas dando las vueltas, irias obteniendo la caja en cuestión, de tal forma que no se tenga cada vez empezar el l primera, hasta llegar a la que corresponde... 
        //para ese caso, mejor se va a ir creando cada caja conforme se vaya recibiendo el tiempo, es decir que el #cajas recibido se guardará en la var que servirá coo límite para exe este método, así no hay necesidad de buscar las cajas, puesto que así creo que crearía más trabajo...         
        // Cola<Cliente> agregarClientes(int numeroClientesNuevos);//Se crea el numero de clientes especificado y se add a la cola global de clientes        
            //Este método no se hará aquí, por el hecho de que puede que la ronda pasada no todos los clientes alcanzaran carrito, por lo cual tendría que recibir la cola antigua y a ella hacer la add, pero para eso, mejor hago el método en el simulador :v xD
        void asignarCarritoCompras(Cola<Cliente>, Pila<int>[], ListaCircular<Cliente>);//este es para dar las carretas a los clientes, no para colocar el # de carretas solicitadas en la pila...
        //no, este método para enviar al area de compras no debe existir, porque nada más tendría la llamada al método de la lista circular global [que se encuentra en la calse main, pues ahí se desenlza todo el proceso... a menos que crees otra clase en la que tengas la línea de vida respectiva en un solo método y así solo debas llamar ese método en el main y ahorrarte el crear vars en el main...]
        //void enviarAAreaCompras();
        void enviarColaPago(ListaCircular<Cliente>, Cola<Cliente>);//aquí se generará la cdad aleatoria de intentos a realizar para add clientes a la cola de pago [la cual es una var global...]
        void realizarProcesoPago(ListaDoblementeEnlazada<Caja>, Cola<Cliente>);//aquí se hará la revisión de si hay clientes en espera de realizar pago, para así asignarlos a la caja que se encuentre vacía al momento de revisar el listado 2blemente enlazado de cajas y tb se hace el proceso para liberación de las cajas, si es que cumple con una de las 2 condic para este proceso, es decir que aquí se usa el método para retornar el carrito de compras...
        void retornarCarritoCompras();
        

        int generarNumeroAleatorio(int);//Quizá sería mejor colocarlo en una clase llamada herramientas...
};

//Creo que aparte vamos a crear una clase creadora, una de herramientas y otra para las gráficas [quiza la de herramientas solo tenga 1 método, entonces solo se crearía la clase para las gráficas...]