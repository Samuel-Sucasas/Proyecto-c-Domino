//Librerias o Bibliotecas a usar 
#include "FuncionesJuego.h"

int main(){

    cout<<" ||    Bienvenido al Domino doble 6    ||"<<endl;

    int numero_de_jugadores;
    cout<<"Cuantos jugadores Desean jugar: "<<endl;
    cin>>numero_de_jugadores;
    

    if (numero_de_jugadores < 2 || numero_de_jugadores > 4) //Jugadores de 2 a 4
    {
        cout<<"Usted ha colocado un numero de jugadores que no esta disponible de momento, en el futuro actualizaremos....";
    }
    else
    {
        cout<<"Usted decidió jugar de:" <<numero_de_jugadores<<" personas "; // Puede jugar 



        //Inicializar y apuntar pozo, jugadores y tablero a nulo
        Ficha *pozo =nullptr;
        Jugador *jugadores = nullptr;
        Ficha *tablero=nullptr;

        //Creamos los jugadores
        crear_jugadores(&jugadores, jugadores);

        //Creamos el juego
        crear_juego(&pozo);

        //Dejar para más tarde 
        cout<<"Se creo el juego";
        contar_fichas_en_lista(stock)<<endl;

        //Se reparten las fichas a los jugadores
        repartir_fichas(&pozo,jugadores);
        cout<<"Las fichas se reparieron, preparete para jugar";

        // Se cuentan las fichas restantes
        contar_fichas_en_lista(stock)<<endl;

        //Se muestran las manos ya repartidas
        mostrar_manos(jugadores);

        //Orden jugadores 
        NodoInt *orden=nullptr;
        barajear_turnos(jugadores, &orden); //Se barajean los turnos
        cout<<"Orden de turnos(aleatorio)";
        NodoInt *it=orden;

        while(it){ //Samu cambia esto 
            cout<<"Jugador"<< (it->val+1)<<" ";
            it=it->prox;
            cout<<endl;
        }

        //Comienza el juego
        const int maximo_de_rondas=3;
        bool hay_ganador= false;

        for(int ronda=0; ronda<=maximo_de_rondas && !hay_ganador, ronda++){ //Si llego a 3 rondas o existe un ganador

            cout<<" ------- Ronnda "<< ronda <<" ------- "<<endl;
            it=orden;
            while(it && !hay_ganador){
                int jugador= it->val;
                hay_ganador=ejecutar_turno(jugador, jugadores,&pozo, &tablero);
                it=it->prox;
            }
        }

        if(!hay_ganador){ //Si nadie gana se suman las fichas
            int mejor=-1;
            int mejor_count=int_max;
            int mejor_pips= int_max;
            jugador *aux= jugadores;
            while(aux){
                int c= contar_fichas(aux->mano);
                int s= sumar_pips(auz->mano);
                cout<<"Jugador"<<(aux->id+1);
                fichas="<< c ", pips=" " <<s<<endl;
                if(c< mejor_count || (c== mejor_count&& s<mejor_pips)){
                    mejor=aux->id;
                    mejor_count= c;
                    mejor_pips=s;
                    
                }
            aux=aux->prox;
            }
            if (mejor>=0){
                cout<<"Terminaron las " <<maximo_de_rondas<< "rondas;"
                <<(mejor+1)<< "."<<endl;
            }
            else{
                cout<<"No se pudo determinar un ganador "<<endl;  
            }
        }

        cout<<"El juego ha finalizado"

        //Liberar memoria
        jugador *j=jugadores;
        while(j){
            jugador *jn =j->prox;
            Ficha *f=j->mano;
            while(f){
                Ficha *fn= f->prox;
                delete f;
                f=fn;
            }
            delete f;
            j=jn;
        }

        //Liberar pozo
        while(pozo){
            Ficha *fn=stock->prox;
            delete stock;
            stock=fn;
        }

        //Liberar tablero

         while(tablero){
            Ficha *fn=tablero->prox;
            delete tablero;
            tablero=fn;
        }


        //Liberar orden list
         while(orden){
            NodoInt *nn=orden->prox;
            delete orden;
            orden=nn;
        }


    }
    return 0;
}