#ifndef MAIN_H
#define MAIN_H
//no es necesario que los nombres de los guardas sean iguales los nombres a los de la clase sino solamente que sean diferentes...
#include <cstdlib>
#include <iostream>
#include <string>
#include "Simulador.h"

using namespace std;

int main(int argc, char** argv){
    Simulador *elSimulador = new Simulador();//Recuerda que solo cuando no declaras un cnstrct, te quedas con e default, por lo cual puede incializar asi --> Clase nombreInstancia();

    cout<<"\t\t\t-->::MINIMARKET::<--"<<endl;
    cout<<"\t\t\t-Bienvenido-"<<endl<<endl;
    elSimulador->simularMiniMarket();
    return 0;
}

#endif   