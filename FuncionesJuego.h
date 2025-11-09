#include "Domitivas.h"

// Pequeño RNG interno
// inicializarSemilla(0) mezclara la semilla con la dirección de la lista
long semilla_rnd = 123456789;

// inicializarSemilla(0) hara una mezcla.
void inicializarSemilla(int s){
    if (s != 0) semilla_rnd = s;
    else {
        // Usamos la direccion de 's' como un entero. 
        // Convertimos el puntero a 's' a un entero largo.
        long x = (long)&s; 
        
        // Mezclamos la semilla actual con la direccion de memoria y una constante
        semilla_rnd = semilla_rnd ^ (x + 0x9e3779b9);
        
        // Aseguramos que la semilla no sea 0 despues de la mezcla
        if (semilla_rnd == 0) semilla_rnd = 1; 
    }
}
// miRand(lim) devuelve 0..lim-1 (lim>0)
int miRand(int lim){
    if (lim <= 0) return 0;
    // Aplicamos la formula del generador: (a * semilla + c)
    semilla_rnd = semilla_rnd * 1103515245 + 12345;
    // Aseguramos que el resultado sea positivo (si la formula dio negativo)
    if (semilla_rnd < 0) {
        semilla_rnd = semilla_rnd * -1; // O simplemente: semilla_rnd = -semilla_rnd;
    }
    
    // Devolvemos el resultado en el rango (0 a lim-1)
    return (int)((semilla_rnd >> 16) % (long)lim);
}

// ------------------------------------------------------------------
// Creación y reparto de fichas (usa listas de jugadores)
// ------------------------------------------------------------------
void crearJuego(Ficha **pozo){
    for(int i=0;i<=6;i++){
        for(int j=i;j<=6;j++){
            insertarUltimoTabla(pozo,i,j);
        }
    }
}

bool extraerAleatoria(Ficha **pozo, int &v1, int &v2){
    int n = contarFichas(*pozo);
    if (n == 0) return false;
    int idx = miRand(n);
    return eliminarFichaPorIndice(pozo, idx, v1, v2);
}

// Reparte a la lista de jugadores (recorre la lista en orden natural)
void repartirFichas(Ficha **pozo, Jugador *jugadores){
    int jugadoresCount = contarJugadores(jugadores);
    int porJugador = (jugadoresCount == 2) ? 7 : 5;
    for(int r=0;r<porJugador;r++){
        Jugador *p = jugadores;
        while(p){
            int a,b;
            if (extraerAleatoria(pozo,a,b)){
                insertarUltimoTabla(&p->mano, a, b);
            }
            p = p->prox;
        }
    }
}

// ------------------------------------------------------------------
// Barajar turnos: genera una lista NodoInt con ids en orden aleatorio
// ------------------------------------------------------------------
void barajarTurnosJugadores(Jugador *jugadores, NodoInt **ordenHead){
    int n = contarJugadores(jugadores);
    // crear lista inicial de ids 0..n-1
    NodoInt *pool = NULL;
    for(int i=0;i<n;i++) appendNodoInt(&pool, i);
    *ordenHead = NULL;
    while(contarNodoInt(pool) > 0){
        int c = contarNodoInt(pool);
        int idx = miRand(c);
        int val;
        eliminarNodoIntPorIndice(&pool, idx, val);
        appendNodoInt(ordenHead, val);
    }
}

// ------------------------------------------------------------------
// Mostrar manos y tablero (utilizan Ficha listas)
// ------------------------------------------------------------------
void mostrarManoConIndices(Ficha *mano); 

void mostrarManos(Jugador *jugadores){
    Jugador *aux = jugadores;
    while(aux){
        cout<<"Jugador "<<(aux->id+1)<<":\n";
        mostrarManoConIndices(aux->mano);
        aux = aux->prox;
    }
}

int contarFichasEnLista(Ficha *inicio){
    return contarFichas(inicio);
}

// ------------------------------------------------------------------
// Tablero, extremos, indices jugables (las funciones usan listas)
// ------------------------------------------------------------------
void mostrarTablero(Ficha *tablero){
    if (FichaVacia(tablero)){
        cout<<"Tablero: [vacío]"<<endl;
        return;
    }
    cout<<"Tablero: ";
    mostrarFichas(tablero);
}

void obtenerExtremos(Ficha *tablero, int &izq, int &derch){
    if (FichaVacia(tablero)){ izq = -1; derch = -1; return; }
    izq = tablero->Dato1;
    Ficha *aux = tablero;
    while(aux->prox) aux = aux->prox;
    derch = aux->Dato2;
}

// Retorna lista de índices jugables (NodoInt) basados en la mano del jugador
NodoInt* indicesJugables(Ficha *mano, Ficha *tablero){
    NodoInt *cabeza = NULL;
    int izq, derch;
    obtenerExtremos(tablero, izq, derch);
    int idx = 0;
    Ficha *aux = mano;
    while(aux){
        bool jugable = false;
        if (izq == -1 && derch == -1) jugable = true;
        else {
            if (aux->Dato1 == izq || aux->Dato2 == izq || aux->Dato1 == derch || aux->Dato2 == derch) jugable = true;
        }
        if (jugable) appendNodoInt(&cabeza, idx);
        idx++;
        aux = aux->prox;
    }
    return cabeza;
}

int sumarPips(Ficha *mano){
    int s = 0;
    Ficha *aux = mano;
    while(aux){ 
        s += aux->Dato1 + aux->Dato2; 
        aux = aux->prox;
    }
    return s;
}

// Mostrar mano con índices (usa Ficha list)
void mostrarManoConIndices(Ficha *mano){
    if (FichaVacia(mano)){
        cout<<"(vacío)\n";return; 
    }
    // indices simples
    Ficha *aux = mano;
    int idx = 0;
    while(aux){
        cout<<" ["<<idx<<"] ";
        aux = aux->prox; idx++;
    }
    cout<<"\n";
    // representación simple de fichas
    aux = mano;
    while(aux){ 
        cout<<"+---+ "; aux = aux->prox;
    }
    cout<<"\n";
    aux = mano;
    while(aux){ 
        cout<<"|"<<aux->Dato1<<"|"<<aux->Dato2<<"| "; 
        aux = aux->prox; 
    }
    cout<<"\n";
    aux = mano;
    while(aux){ 
        cout<<"+---+ "; 
        aux = aux->prox; 
    }
    cout<<"\n";
}

// Colocar ficha en tablero (izquierda o derecha)
void colocarFichaEnTablero(Ficha **tablero, int p1, int p2, char lado){
    if (FichaVacia(*tablero)){ 
        insertarPrimeroTabla(tablero, p1, p2); return;
    }
    if (lado == 'I') insertarPrimeroTabla(tablero, p1, p2);
    else insertarUltimoTabla(tablero, p1, p2);
}

// Ejecutar turno: usa jugadorId y lista jugadores para acceder a su mano
bool ejecutarTurno(int jugadorId, Jugador *jugadores, Ficha **pozo, Ficha **tablero){
    Jugador *jug = encontrarJugador(jugadores, jugadorId);
    if (!jug) return false;
    cout<<"--- Turno Jugador "<<(jugadorId+1)<<" ---"<<endl;
    mostrarTablero(*tablero);
    cout<<"Tu mano:"<<endl;
    mostrarManoConIndices(jug->mano);

    NodoInt *jugables = indicesJugables(jug->mano, *tablero);
    if (jugables != NULL){
        cout<<"Fichas jugables (indices): ";
        NodoInt *it = jugables;
        while(it){ 
            cout<<it->val<<" "; 
            it = it->prox; 
        }
        cout<<endl;
        int choice = -1;
        while(true){
            cout<<"Elige indice de ficha a colocar: ";
            cin>>choice;
            if (!cin){ 
                cin.clear(); 
                cin.ignore(10000,'\n'); 
                choice = -1; 
            }
            if (nodoIntContiene(jugables, choice)) break;
            cout<<"Indice no válido o no jugable. Intenta de nuevo."<<endl;
        }
        int a,b;
        if (!eliminarFichaPorIndice(&jug->mano, choice, a, b)){
            cout<<"Error al quitar ficha de la mano."<<endl;
            return false;
        }
        int izq,derch;
        obtenerExtremos(*tablero, izq, derch);
        char lado = 'D';
        bool canizq = false, canDerch = false;
        if (izq == -1 && derch == -1) lado = 'D';
        else {
            if (a == izq || b == izq) canizq = true;
            if (a == derch || b == derch) canDerch = true;
            if (canizq && canDerch){
                char s;
                while(true){
                    cout<<"Colocar a la izquierda (I) o derecha (D)? ";
                    cin>>s;
                    if (!cin){ 
                        cin.clear(); 
                        cin.ignore(10000,'\n');
                        continue; 
                    }
                    if (s=='I' || s=='D' || s=='i' || s=='d'){ lado = (s=='i')? 'I' : (s=='d')? 'D' : s; break; }
                }
            } else if (canizq) lado = 'I';
            else if (canDerch) lado = 'D';
            else lado = 'D';
        }
        int p1 = a, p2 = b;
        if (lado == 'I' && izq != -1){
            if (p2 != izq) { 
                int t = p1; 
                p1 = p2; 
                p2 = t; 
            }
        } else if (lado == 'D' && derch != -1){
            if (p1 != derch) {
                int t = p1; 
                p1 = p2; 
                p2 = t; 
            }
        }
        colocarFichaEnTablero(tablero, p1, p2, lado);
        cout<<"Jugador "<<(jugadorId+1)<<" colocó ["<<p1<<"|"<<p2<<"] en "<<(lado=='I'?"izquierda":"derecha")<<endl;
    } else {
        cout<<"No tienes fichas jugables. Robando del pozo..."<<endl;
        int ra, rb;
        if (extraerAleatoria(pozo, ra, rb)){
            cout<<"Robaste ["<<ra<<"|"<<rb<<"]."<<endl;
            int izq,derch;
            obtenerExtremos(*tablero, izq, derch);
            bool canizq = false, canDerch = false;
            if (izq == -1 && derch == -1){
                colocarFichaEnTablero(tablero, ra, rb, 'D');
                cout<<"Se colocó automaticamente la ficha en el tablero (tabla estaba vacía)."<<endl;
            } else {
                if (ra == izq || rb == izq) canizq = true;
                if (ra == derch || rb == derch) canDerch = true;
                if (canDerch || canizq){
                    char lado = canDerch ? 'D' : 'I';
                    int p1 = ra, p2 = rb;
                    if (lado == 'I'){
                        if (p2 != izq) { int t = p1; p1 = p2; p2 = t; }
                    } else {
                        if (p1 != derch) { int t = p1; p1 = p2; p2 = t; }
                    }
                    colocarFichaEnTablero(tablero, p1, p2, lado);
                    cout<<"Se colocó automaticamente la ficha robada ["<<p1<<"|"<<p2<<"] en "<<(lado=='I'?"izquierda":"derecha")<<endl;
                } else {
                    insertarUltimoTabla(&jug->mano, ra, rb);
                    cout<<"La ficha no era jugable y quedó en tu mano."<<endl;
                }
            }
        } else {
            cout<<"No hay fichas en el pozo. No puedes robar. Pasas turno."<<endl;
        }
    }

    // limpiar lista de jugables
    while(jugables){
        NodoInt *tmp = jugables->prox;
        delete jugables;
        jugables = tmp;
    }

    if (contarFichas(jug->mano) == 0){
        cout<<"Jugador "<<(jugadorId+1)<<" se quedó sin fichas y gana el juego!"<<endl;
        return true;
    }
    return false;
}
