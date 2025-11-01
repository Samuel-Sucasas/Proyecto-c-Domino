#include <Iostream>
#include "FuncionesJuego.h"
using namespace std;

int main(){
    int players=0,valor=5,valor2=2,i=0;
    Ficha *Tabla=nullptr;
    cout<<"Bienvenido al Domino doble 6"<<endl;
    cout<<"Cuantos jugadores Desean jugar: "<<endl;cin>>players;
    while (i != 4)
    {
        i++;
        insertarUltimoTabla(&Tabla,valor,valor2);
    }
    mostrarFichas(Tabla);
    return 0;
}