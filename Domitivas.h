#include <iostream>
using namespace std;

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

void mostrarFichaEnlinea(const Ficha *f){
    if (!f) return;
    // Imprimo con anchura aproximada
    cout<<"[";
    if (f->Dato1 < 10) cout<<' ';
    cout<<f->Dato1<<"|";
    if (f->Dato2 < 10) cout<<' ';
    cout<<f->Dato2<<"]";
}

void mostrarFichas(Ficha *inicio){
    Ficha *mover = inicio;
    if (!FichaVacia(inicio)){
        while (mover != NULL){
            mostrarFichaEnlinea(mover);
            cout<<" ";
            mover = mover->prox;
        }
        cout<<endl;
    } else {
        cout<<"[vacío]"<<endl;
    }
}

void insertarUltimoTabla(Ficha **inicio, int valor1,int valor2){
    Ficha *nuevo = CrearFicha(valor1,valor2);
    if (FichaVacia(*inicio)){
        *inicio = nuevo;
    } else {
        Ficha *auxiliar = *inicio;
        while (auxiliar->prox != NULL) auxiliar = auxiliar->prox;
        auxiliar->prox = nuevo;
    }
}

void insertarPrimeroTabla(Ficha **inicio, int valor1,int valor2) {
    Ficha *nuevo = CrearFicha(valor1,valor2);
    nuevo->prox = *inicio;
    *inicio = nuevo;
}

int contarFichas(Ficha *inicio){
    int cont = 0;
    Ficha *aux = inicio;
    while(aux){
        cont++;
        aux = aux->prox;
    }
    return cont;
}

// Elimina y devuelve la ficha en el índice (0-based). Retorna true si eliminó.
bool eliminarFichaPorIndice(Ficha **inicio, int indice, int &salida1, int &salida2){
    if (FichaVacia(*inicio)) return false;
    Ficha *actual = *inicio;
    Ficha *anterior = NULL;
    int i = 0;
    while(actual && i < indice){
        anterior = actual;
        actual = actual->prox;
        i++;
    }
    if (!actual) return false;
    salida1 = actual->Dato1;
    salida2 = actual->Dato2;
    if (anterior == NULL){
        *inicio = actual->prox;
    } else {
        anterior->prox = actual->prox;
    }
    delete actual;
    return true;
}
