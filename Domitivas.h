#include <Iostream>
struct Ficha{
    int Dato1;
    int Dato2;
    Ficha *prox;
};

Ficha* CrearFicha(int Valor1,int Valor2){
    Ficha *nuevo = new Ficha;
    nuevo->Dato1 = Valor1;
    nuevo->Dato2 = Valor2;
    nuevo->prox = NULL;
    return nuevo;
}

bool FichaVacia(Ficha *inicio){
    return inicio==NULL;
}

void mostrarFichas(Ficha *inicio){
    Ficha *mover;

    if (!FichaVacia(inicio))
    {
        mover = inicio;
        while (mover != NULL)
        {
            std::cout<<"|"<<mover->Dato1<<"|"<<mover->Dato2;
            mover = mover->prox;
        }
    }
    else
    std::cout<<"El jugador no tiene fichas";
}

void insertarUltimoTabla(Ficha **inicio, int valor1,int valor2){
    Ficha *nuevo = CrearFicha(valor1,valor2);
 
   if (FichaVacia(*inicio)) {
       *inicio = nuevo;
    } 
    else {
       Ficha *auxiliar = *inicio;
       while (auxiliar->prox != NULL) {
           auxiliar = auxiliar->prox;
       }
        auxiliar->prox = nuevo;
  }
   
} 

void insertarPrimeroTabla(Ficha **inicio, int valor1,int valor2) {
  Ficha *nuevo = CrearFicha(valor1,valor2);
  nuevo->prox = *inicio;
  *inicio = nuevo;
}