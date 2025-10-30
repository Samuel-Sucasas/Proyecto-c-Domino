//Librerias o Bibliotecas a usar 
#include <iostream>
#include "Domitivas.h"
using namespace std;


int main(){
    //Declarar variables a usar 
    int players;
    cout<<" ||    Bienvenido al Domino doble 6    ||"<<endl;
    cout<<"Cuantos jugadores Desean jugar: "<<endl;cin>>players;
    return 0;
    if (players<2 and players>4) //Jugadores de 2 a 4
    {
        cout<<"Usted ha colocado un numero de jugadores que no está disponible de momento, en el futuro actualizaremos....";
    }
    else
    {
        cout<<"Usted decidió jugar de:" <<players<<" personas ";
    }
    
    
}