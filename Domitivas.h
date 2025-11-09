#include <iostream>
using namespace std;
//Primitivas para las Fichas de domino y los judadores
struct Ficha{
    int Dato1;
    int Dato2;
    Ficha *prox;
};

// Estructuras auxiliares: Jugador (lista de jugadores) y NodoInt (lista int)
struct Jugador {
    int id;        // id 0..N-1
    Ficha *mano;
    Jugador *prox;
};

struct NodoInt {
    int val;
    NodoInt *prox;
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
// Contador de fichas 
int contarFichas(Ficha *inicio){
    int cont = 0;
    Ficha *aux = inicio;
    while(aux){
        cont++;
        aux = aux->prox;
    }
    return cont;
}

// Elimina y devuelve la ficha en el índice. 
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
    return true; //Retorna true si eliminó.
}

// Crear lista de jugadores (ids 0..jugadoresCount-1)
void crearJugadores(Jugador **cabeza, int jugadoresCount){
    *cabeza = NULL;
    Jugador *ultimo = NULL;
    for(int i=0;i<jugadoresCount;i++){
        Jugador *j = new Jugador;
        j->id = i;
        j->mano = NULL;
        j->prox = NULL;
        if (*cabeza == NULL) {
            *cabeza = j;
            ultimo = j;
        } else {
            ultimo->prox = j;
            ultimo = j;
        }
    }
}

Jugador* encontrarJugador(Jugador *cabeza, int id){
    Jugador *aux = cabeza;
    while(aux){
        if (aux->id == id) return aux;
        aux = aux->prox;
    }
    return NULL;
}

int contarJugadores(Jugador *cabeza){
    int c = 0;
    Jugador *aux = cabeza;
    while(aux){ c++; aux = aux->prox; }
    return c;
}

// ------------------------------------------------------------------
// Operaciones NodoInt (listas de enteros)
// ------------------------------------------------------------------
void appendNodoInt(NodoInt **cabeza, int v){
    NodoInt *n = new NodoInt;
    n->val = v;
    n->prox = NULL;
    if (*cabeza == NULL) { *cabeza = n; return; }
    NodoInt *aux = *cabeza;
    while(aux->prox) aux = aux->prox;
    aux->prox = n;
}

int contarNodoInt(NodoInt *cabeza){
    int c = 0;
    NodoInt *aux = cabeza;
    while(aux){ 
        c++; aux = aux->prox;
    }
    return c;
}

// Elimina y devuelve el valor del nodo en índice  de una lista de int
bool eliminarNodoIntPorIndice(NodoInt **cabeza, int indice, int &salidaVal){
    if (*cabeza == NULL) return false;
    NodoInt *actual = *cabeza;
    NodoInt *anterior = NULL;
    int i = 0;
    while(actual && i < indice){
        anterior = actual;
        actual = actual->prox;
        i++;
    }
    if (!actual) return false;
    salidaVal = actual->val;
    if (anterior == NULL) *cabeza = actual->prox;
    else anterior->prox = actual->prox;
    delete actual;
    return true;
}

bool nodoIntContiene(NodoInt *cabeza, int v){
    NodoInt *aux = cabeza;
    while(aux){
        if (aux->val == v) return true;
        aux = aux->prox;
    }
    return false;
}
