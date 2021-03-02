#include <cstdlib>
#include <iostream>
#include <string>
#include "Simulador.h"


int main(int argc, char** argv){
    Simulador elSimulador = Simulador();//Recuerda que solo cuando no declaras un cnstrct, te quedas con e default, por lo cual puede incializar asi --> Clase nombreInstancia();

    cout<<"\t\t\t-->::MINIMARKET::<--"<<endl;
    cout<<"\t\t\t-Bienvenido-"<<endl<<endl;
    elSimulador.simularMiniMarket();
    return 0;
}



   