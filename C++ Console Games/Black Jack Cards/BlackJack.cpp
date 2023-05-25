#include<iostream>
#include<fstream>
#include<cstring>
#include<cstdlib>
#include<ctime>

using namespace std;

// tamano máximo de la cubierta
#define mazo_tamano 40
#define MAX_JUGADORS 50

// Cartas type
struct Cartas{
    int numeroDeCartas;
    int cartas[mazo_tamano];

    Cartas()
    {
        numeroDeCartas = 0;
        for(int i=0; i<mazo_tamano; i++)
            cartas[i] = 0;
    }
};

typedef struct Jugador{
    string nick;
    int numeroDeGanadas;
    int numeroDePerdidas;
    int saldo;
}Jugador;

typedef struct DatosPartida{
    int numeroDeJugadors;
    Jugador jugadors[MAX_JUGADORS];
}DatosPartida;

int menu();
void muestraReglas();
void juegoBlackjack(DatosPartida &d, Jugador &j);
int juegaHumano(Cartas & mazo, Cartas & cartasJugador);
int juegaCrupier(Cartas & mazo, Cartas & cartasCrupier);
int ganador(int puntosJugador, int puntosCrupier, int numCartasJugador, int numCartasCrupier);
void inicializaMazo(Cartas& mazo);
void barajar(Cartas& mazo);
void annadeCarta(Cartas & mano, int carta);
void muestraMazo(Cartas cartas);
int sacarCartaMazo(Cartas & mazo);
int calculaPuntos(Cartas mano);

void cargaDatos(DatosPartida &d);
int buscaJugador(DatosPartida &d, string nick);
void guardaDatos(DatosPartida &d);
Jugador iniciarSesin(DatosPartida &d, string nick);
void actualizaJugador(DatosPartida &d, Jugador &j);
void guardaJugador(DatosPartida &d, Jugador &j);
void gestionSaldo(DatosPartida &d, Jugador &j);
void infoJugadores(DatosPartida &d);
void muestraInfo(DatosPartida &d,string nick);

int main()
{
    int opcion;
    DatosPartida d;
    string nick;
    Jugador p;

    cargaDatos(d);
    cout << "Introduce to nick: ";
    getline(cin, nick, '\n');
    p = iniciarSesin(d, nick);
    cout << "Bienvenido " << p.nick << '\n';
    do{
        opcion = menu();
        if(opcion == 0)
            cout << "\nHasta la proxima\n¡Hasta pronto!\n";
        else if(opcion == 1)
        {
            if(p.saldo == 0)
            {
                cout << "No dispones de saldo.\n";
                cout << "Para jugar, realiza una recarga.\n\n";
            }
            else 
                juegoBlackjack(d, p);
        }
        else if(opcion == 2)
            infoJugadores(d);
        else if(opcion == 3){
            muestraInfo(d, p.nick);
            cout << '\n';
        }
        else if(opcion == 4)
            gestionSaldo(d, p);
        else if(opcion == 5)
            muestraReglas();
    }while(opcion != 0);
    
    guardaDatos(d);

    return 0;
}

int menu()
{
    srand(time(0));
    int opcion;
    do{
        cout << "---------------------------------\n";
        cout << "BIENVENIDO A LA MESA DE BLACKJACK\n";
        cout << "---------------------------------\n";
        cout << "1 - Jugar\n";
        cout << "2 - Ver información de todos los jugadores\n";
        cout << "3 - ver información jugador\n";
        cout << "4 - Saldo\n";
        cout << "5 - Reglas de juego\n";
        cout << "0 - Salir\n";
        cout << "Elige una opcion: ";
        cin >> opcion;
        if(opcion < 0 || opcion > 5)
            cout << "\nSeleccion invalida!\n\n";
    }while(opcion < 0 || opcion > 5);
    return opcion;
}

void muestraReglas()
{
    cout << "\nAntes de comenzar la partida, has de hacer tu apuesta.\n";
    cout << "Si no tienes suficiente saldo, puedes recargarlo antes e jugar eligiendo la opcion 4 del menu.\n";
    cout << "Al principio, los dos jugadores obtienen dos Cartas\n";
    cout << "En tu turno, elegirás si quieres una carta más o si quieres plantarte.\n";
    cout << "El ganador de la partida será el que se acerque más a 21 sin pasarse.\n";
    cout << "Las cartas númericas suman su valor, las figuras suman 10 y el As vale 11 o 1.\n";
    cout << "La mejor jugada es el Blackjack: consigue 21 con solo dos Cartas, un as más un 10.\n";
    cout << "Un Blackjack gana sobre un 21 logrado con más de dos Cartas.\n";
    cout << "Volviendo al menú...\n\n";
}

void juegoBlackjack(DatosPartida &d, Jugador &j)
{
    Cartas mazo, cartasJugador, cartasCrupier;
    int puntosJugador, puntosCrupier, victoria, apuesta;

    do{
        cout << "¿Cuánto quieres apostar? Tienes " << j.saldo << " Euros: ";
        cin >> apuesta;
        if(apuesta > j.saldo)
            cout << "No tienes saldo suficiente.\n";
    }while(apuesta > j.saldo);
    cout << "Empieza al juego. Apuestas " << apuesta << " euros.\n";
    j.saldo -= apuesta;
    actualizaJugador(d, j);
    inicializaMazo(mazo);
    barajar(mazo);
    annadeCarta(cartasCrupier, sacarCartaMazo(mazo));
    annadeCarta(cartasCrupier, sacarCartaMazo(mazo));
    annadeCarta(cartasJugador, sacarCartaMazo(mazo));
    annadeCarta(cartasJugador, sacarCartaMazo(mazo));
    cout << "\nSe ha repartido\n";
    cout << "La primera carta del crupier es un " << cartasCrupier.cartas[0] << "\n\n";
    puntosJugador = juegaHumano(mazo, cartasJugador);
    if(puntosJugador > 21)
    {
        cout << "Te pasas de 21. ¡Pierdes!\n";
        cout << "¡Gana el crupier!\n";
        return;
    }
    puntosCrupier = juegaCrupier(mazo, cartasCrupier);
    if(puntosCrupier > 21)
    {
        cout << "El crupier tiene más de 21 anos. ¡El crupier pierde!\n";
        cout << "¡Ganas!\n";
        return;
    }
    victoria = ganador(puntosJugador, puntosCrupier, cartasJugador.numeroDeCartas, cartasCrupier.numeroDeCartas);
    cout << "\n--------------\n";
    cout << "Puntuacion Final\n";
    cout << "\n--------------\n";
    cout << "Crupier: " << puntosCrupier << "\tJugador: " << puntosJugador << '\n';
    if(victoria == 1)
    {
        cout << "¡Ganas!\n";
        j.saldo += (2*apuesta);
        j.numeroDeGanadas++;
    }
    else if(victoria == 2)
    {
        cout << "¡Gana el crupier!\n";
        j.numeroDePerdidas++;
    }
    else    
        cout << "¡Este juego es un empate!\n";

    actualizaJugador(d, j);
}

int juegaHumano(Cartas & mazo, Cartas & cartasJugador)
{
    char eleccion;
    int puntos = calculaPuntos(cartasJugador);
    cout << "Turno del jugador\n";
    cout << "------------------------\n\n";
    do{
        cout << "Tus cartas: ";
        muestraMazo(cartasJugador);
        cout << "\t\tPuntos: " << puntos << '\n';
        cout << "Quieres plantarte? (S/N): ";
        cin >> eleccion;
        eleccion |= 32;
        if(eleccion == 's')
            return puntos;
        else if(eleccion == 'n')
            annadeCarta(cartasJugador, sacarCartaMazo(mazo));
        else 
            cout << "\nSeleccion invalida!\n\n";

        puntos = calculaPuntos(cartasJugador);
        if(puntos > 21){
            cout << "Tus cartas: ";
            muestraMazo(cartasJugador);
            cout << "\t\tPuntos: " << puntos << '\n';
            return puntos;
        }
    }while(eleccion != 'y');
    return puntos;
}

int juegaCrupier(Cartas & mazo, Cartas & cartasCrupier)
{
    int puntos;
    cout << "Turno del crupier\n";
    cout << "------------------------\n\n";
    puntos = calculaPuntos(cartasCrupier);
    cout << "Cartas crupier: ";
    muestraMazo(cartasCrupier);
    cout << "\t\tPuntos: " << puntos << '\n';
    while(puntos < 17)
    {
        cout << "El crupier saca otra carta\n";      
        annadeCarta(cartasCrupier, sacarCartaMazo(mazo));
        puntos = calculaPuntos(cartasCrupier);
        cout << "Cartas crupier: ";
        muestraMazo(cartasCrupier);
        cout << "\t\tPuntos: " << puntos << '\n';
    }
    return puntos;
}

int ganador(int puntosJugador, int puntosCrupier, int numCartasJugador, int numCartasCrupier)
{
    if(puntosJugador > puntosCrupier)
        return 1;
    else if(puntosCrupier > puntosJugador)
        return 2;
    else if(numCartasJugador > numCartasCrupier)
        return 1;
    else if(numCartasCrupier > numCartasJugador)
        return 2;

    return 0;
}

void inicializaMazo(Cartas& mazo)
{
    mazo.numeroDeCartas = mazo_tamano;
    int cartas[] = {1, 2, 3, 4, 5, 6, 7, 10, 11, 12}, i, j;
    for(i = 0, j = 0; i < mazo_tamano; i++)
    {
        mazo.cartas[i] = cartas[j];
        j = (j+1) % 10;
    }
}

void barajar(Cartas& mazo)
{
    int i, n1, n2, temporario;
    for(i=0; i<mazo_tamano*10; i++)
    {
        n1 = rand() % mazo.numeroDeCartas;
        n2 = rand() % mazo.numeroDeCartas;
        if(n1 == n2)    
            n2 = rand() % mazo.numeroDeCartas;

        temporario = mazo.cartas[n1];
        mazo.cartas[n1] = mazo.cartas[n2];
        mazo.cartas[n2] = temporario;
    }
}

void annadeCarta(Cartas & mano, int carta)
{
    if(mano.numeroDeCartas < mazo_tamano)
    {
        mano.cartas[mano.numeroDeCartas] = carta;
        mano.numeroDeCartas++;
    }
}

void muestraMazo(Cartas cartas)
{
    for(int i=0; i<cartas.numeroDeCartas; i++)
        cout << cartas.cartas[i] << ' ';
}

int sacarCartaMazo(Cartas & mazo)
{
    mazo.numeroDeCartas--;
    return mazo.cartas[mazo.numeroDeCartas];
}

int calculaPuntos(Cartas mano)
{
    int puntos = 0;
    for(int i=0; i<mano.numeroDeCartas; i++)
    {
        if(mano.cartas[i] >= 10)
            puntos += 10;
        else if( mano.cartas[i] == 1 && mano.cartas[i] + puntos < 21)
        {
            mano.cartas[i] = 11;
            puntos += 11;
        }
        else 
            puntos += mano.cartas[i];
    }
    return puntos;
}

void cargaDatos(DatosPartida &d)
{
    string nick;
    int ganadas, perdidas, saldo;
    fstream archivo;
    archivo.open("jugadores.txt", ios::in);

    if(archivo.fail())
    {
        d.numeroDeJugadors = 0;
        return;
    }

    archivo >> d.numeroDeJugadors;
    archivo.ignore();

    for(int i=0; i<d.numeroDeJugadors; i++)
    {
        getline(archivo, nick, '\n');
        archivo >> ganadas >> perdidas >> saldo;
        archivo.ignore();
        if(i < MAX_JUGADORS)
        {
            d.jugadors[i].nick = nick;
            d.jugadors[i].numeroDeGanadas = ganadas;
            d.jugadors[i].numeroDePerdidas = perdidas;
            d.jugadors[i].saldo = saldo;
        }
    }

    archivo.close();
}

void guardaDatos(DatosPartida &d)
{
    int i;
    fstream archivo;

    archivo.open("jugadores.txt", ios::out);

    archivo << d.numeroDeJugadors << '\n';

    for(i=0; i<d.numeroDeJugadors; i++)
    {
        archivo << d.jugadors[i].nick << '\n';
        archivo << d.jugadors[i].numeroDeGanadas << '\n';
        archivo << d.jugadors[i].numeroDePerdidas << '\n';
        archivo << d.jugadors[i].saldo << '\n';
    }

    archivo.close();
}

int buscaJugador(DatosPartida &d, string nick)
{
    int i;
    for(i=0; i<d.numeroDeJugadors; i++)
        if(d.jugadors[i].nick == nick)
            return i;
        
    return -1;
}

Jugador iniciarSesin(DatosPartida &d, string nick)
{
    Jugador p;
    p.nick = "";
    int index = buscaJugador(d, nick);

    if(index != -1){
        p.nick = d.jugadors[index].nick;
        p.numeroDeGanadas = d.jugadors[index].numeroDeGanadas;
        p.numeroDePerdidas = d.jugadors[index].numeroDePerdidas;
        p.saldo = d.jugadors[index].saldo;
    }
    else {
        p.nick = nick;
        p.numeroDeGanadas = 0;
        p.numeroDePerdidas = 0;
        p.saldo = 100;
        cout << "El jugador no está en nuestra base de datos\n";
        cout << "Creando un nuevo usuario...\n";
        guardaJugador(d, p);
    }

    return p;
}

void guardaJugador(DatosPartida &d, Jugador &j)
{
    if(d.numeroDeJugadors == MAX_JUGADORS)
    {
        cout << "Max jugadors limit reached\n\n";
        return;
    }

    d.jugadors[d.numeroDeJugadors].nick = j.nick;
    d.jugadors[d.numeroDeJugadors].numeroDeGanadas = j.numeroDeGanadas;
    d.jugadors[d.numeroDeJugadors].numeroDePerdidas = j.numeroDePerdidas;
    d.jugadors[d.numeroDeJugadors].saldo = j.saldo;

    d.numeroDeJugadors++;
}

void actualizaJugador(DatosPartida &d, Jugador &j)
{
    int index = buscaJugador(d, j.nick);

    if(index == -1)
        guardaJugador(d, j);
    else 
    {
        d.jugadors[index].nick = j.nick;
        d.jugadors[index].numeroDeGanadas = j.numeroDeGanadas;
        d.jugadors[index].numeroDePerdidas = j.numeroDePerdidas;
        d.jugadors[index].saldo = j.saldo;
    }
}

void gestionSaldo(DatosPartida &d, Jugador &j)
{
    int opcion;
    cout << '\n';
    do{
        cout << "----------------\n";
        cout << "GESTIÓN DE SALDO\n";
        cout << "----------------\n";
        cout << "1 - Consulta saldo disponible\n";
        cout << "2 - Recarga\n";
        cout << "0 - Salir\n";
        cout << "Elige una opcion: ";
        cin >> opcion;
        if(opcion < 0 || opcion > 2)
            cout << "\nSeleccion invalida!\n\n";
    }while(opcion < 0 || opcion > 2);

    if(opcion == 1)
        cout << "The saldo disponible es: " << j.saldo << "\n\n";
    else if(opcion == 2)
    {
        j.saldo += 100;
        actualizaJugador(d, j);
        cout << "Se recarga saldo 100 euros.\n\n";
    }
}

void muestraInfo(DatosPartida &d,string nick)
{
    Jugador p = iniciarSesin(d, nick);

    cout << "\nLos datos almacenados del jugador " << p.nick << " son:\n";
    cout << "Número de partidas ganados: " << p.numeroDeGanadas << '\n';
    cout << "Número de partidas perdidas: " << p.numeroDePerdidas << '\n';
    cout << "Saldo disponible: " << p.saldo << '\n';
}

void infoJugadores(DatosPartida &d)
{
    int i;
    for(i=0; i<d.numeroDeJugadors; i++)
    {
        muestraInfo(d, d.jugadors[i].nick);
    }
    cout << '\n';
}