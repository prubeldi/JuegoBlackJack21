// miblackjack.cpp : Este archivo contiene la función "main". La ejecución del programa comienza y termina ahí.
//

#include <iostream>
#include <time.h>
#include <ctime>

using namespace std;

class Player {
public:
	int fichas;
	string apuesta;
	string name;
	int puntosTotal;
	int valoresCartas[11];
	string cartasGeneradas[11];
};

void inicioJuego();
void primerTurno(Player);


// barajas y palos
string barajas[3][13] = {
	{"Corazon", "Pica", "Rombo", "Trebol"},
	{"A","2","3","4","5","6","7","8","9","10","J","Q","K"},
	{"-1","2","3","4","5","6","7","8","9","10","10","10","10"}
};

//jugador Croupier
/*string maquina = "Croupier";
int puntosCro = 0;
int apuesta2=apuesta1;
int fichas2=10000;*/


string mensajeInicio(){
	cout << "\n************\tBienvenido al Black Jack 21\t************\n";

/*	cout << "┌────────┐░░░┌─────────┐\n";
	cout << "│▓▓▓▓▓▓▓▓│░░░│6♠░░░░░░░│\n";
	cout << "│▓▓▓▓▓▓┌─────│░░░░░░░░░│\n";
	cout << "│▓▓▓▓▓▓│3♦░░░│░░░░♠░░░░│\n";
	cout << "│▓▓▓▓▓▓│░░░░░│░░░░░░░░░│\n";
	cout << "│▓▓▓▓▓▓│░░░░♦│░░░░░░░░░│\n";
	cout << "│▓▓▓▓▓▓│░░░░░│░░░░░░░♠6│\n";
	cout << "└──────│░░░░░└──..─────┘\n";
	cout << "░░░░░░░│░░░░░░░♦3│\n";
	cout << "░░░░░░░└──..─────┘\n\n\n\n";*/
	cout << "Soy el Crupier a continuacion te indico las reglas del juego\n\n";
	cout << "[1] GANA si...\n";
	cout << "   Alcanza un 21 y el croupier no empata a 21 o se pasa de 21\n";
	cout << "   Alcanza menos de 21 pero la banca se pasa de 21\n\n";
	cout << "[2] EMPATA si...\n";
	cout << "   Alcanza un 21 y el croupier alcanza tambien 21\n\n";
	cout << "[3] PIERDE si...\n";
	cout << "   Se pasa de 21\n";
	cout << "   Tiene una puntuacion menor a 21, pero la banca tiene una puntuacion mayor, sin pasarse de 21.\n\n";
	cout << "Quieres jugar?\n";
	cout << "Si o No\n";
	string option = "";
	cin >> option;
	return option;
}

bool validarCartas(Player &player){
	int contador = 0;
	int ases = 0;

	for(int carta : player.valoresCartas){
		if(carta > -2) {
			cout << "\n\tCarta: " << carta;
			if(carta == -1){
				ases++;
			}else{
				contador += carta;
			}
		}
	}
	if(ases > 0){
		for (int i = 0; i < ases; ++i){
			int valorTmp = contador + 11;
			if(valorTmp > 21){
				valorTmp = contador + 1;
			}
			contador = valorTmp;
		}
	}
	player.puntosTotal = contador;
	return contador <= 21;
}

bool seTiroCarta(string cartaGenerada, Player player){
	for(string carta : player.cartasGeneradas){
		if(cartaGenerada == carta){
			return true;
		}
	}
	return false;
}

Player generarCrupier(Player player) {
	Player crupier;
	crupier.name = "Crupier";
	crupier.fichas = 10000;
	crupier.apuesta = player.apuesta;
	return crupier;
}

void mostrarCartas(Player player){
	cout << "\n\n************\tCARTAS de " << player.name << "\t************\n";
	cout << "\nJugador: " << player.name;
	cout << "\nFichas: " << player.fichas;
	cout << "\nApuesta: " << player.apuesta;

	for (string carta : player.cartasGeneradas) {
		if(!carta.empty()){
			cout << "\nCarta: " << carta;
		}
	}
	cout << "\n";
}

int *generarCarta() {
	int *carta = new int[2];

	int palo = rand() % 4;
	carta[0] = palo;

	int valor = rand() % 12;
	carta[1] = valor;

	return carta;
}
void gameTie() {
	cout << "\n\n************\tEMPATE\t************\n";
	system("Pause");
	inicioJuego();
}
void gameWin() {
	cout << "\n\n************\tHAS GANADO\t************\n";
	system("Pause");
	inicioJuego();
}
void gameOver(){
	cout << "\n\n************\tHAS PERDIDO\t************\n";
	system("Pause");
	inicioJuego();
}

Player pedirCarta(Player crupier, Player player, int turno){
	string palo = "";
	string card = "";
	string cardValue = "";
	do{
		int * carta = generarCarta();
		palo = barajas[0][carta[0]];
		card = barajas[1][carta[1]];
		cardValue = barajas[2][carta[1]];
	}
	while(seTiroCarta(card+palo, player));

	crupier.valoresCartas[turno] = atoi(cardValue.c_str());
	crupier.cartasGeneradas[turno] = card + palo;
	return crupier;
}

bool validarJugadaCrupier(Player crupier, Player player){
	cout << "\nPuntos jugador: " << player.puntosTotal;
	cout << "\nPuntos crupie: " << crupier.puntosTotal;
	bool continuaJugando = false;
	continuaJugando = crupier.puntosTotal <= player.puntosTotal;

	if(player.puntosTotal == 21){
		continuaJugando = true;
	}
	
	cout << "\ncontinuaJugando?: " << continuaJugando;
	return continuaJugando;
}

void jugada(int turno, Player player) {
	cout << "\n\n************\tTU JUGADA\t************\n";
	cout << "A. Pedir carta:\n";
	cout << "B. Plantarse:\n";
	
	string option = "";
	cin >> option;

	if(option == "A" || option == "a"){ //TODO mejorar con toLowerCase
		string palo = "";
		string card = "";
		string cardValue = "";
		do{
			int * carta = generarCarta();
			palo = barajas[0][carta[0]];
			card = barajas[1][carta[1]];
			cardValue = barajas[2][carta[1]];
		}
		while(seTiroCarta(card+palo, player));

		player.valoresCartas[turno+1] = atoi(cardValue.c_str());
		player.cartasGeneradas[turno+1] = card + palo;

		mostrarCartas(player);
		if(validarCartas(player)){
			jugada(turno+1, player);
		}else{
			gameOver();
		}
	}else if(option == "B" || option == "b"){
		cout << "Se planta\n";
		validarCartas(player);
		Player crupier = generarCrupier(player);
		
		int turno = 0;
		crupier = pedirCarta(crupier, player, turno);
		mostrarCartas(crupier);

		cout << "\nPuntos jugador: " << player.puntosTotal;
		cout << "\nCrupier jugando....\n";
		
		do{
			turno += 1;
			cout << "\nCrupie pide una carta\n";
			crupier = pedirCarta(crupier, player, turno);
			system("Pause");
		}while(validarCartas(crupier) && validarJugadaCrupier(crupier, player));


		cout << "\nPuntos crupier: " << crupier.puntosTotal;

		if(player.puntosTotal == 21 && crupier.puntosTotal == 21){
			cout << "\nEmpate....\n";
			gameWin();
			system("Pause");
		}else if(crupier.puntosTotal <= 21 && crupier.puntosTotal > player.puntosTotal){
			gameOver();
		}else{
			cout << "\ntu ganas....\n";
			gameTie();
			system("Pause");
		}
	}
}

void primerTurno(Player player) {
	int * carta0 = generarCarta();

	string palo0 = barajas[0][carta0[0]];
	string cartaToShow = barajas[1][carta0[1]];

	player.valoresCartas[0] = atoi(barajas[2][carta0[1]].c_str());
	player.cartasGeneradas[0] = cartaToShow + palo0;

	int * carta1 = generarCarta();
	string palo1 = barajas[0][carta1[0]];
	string cartaToShow1 = barajas[1][carta1[1]];
	player.valoresCartas[1] = atoi(barajas[2][carta1[1]].c_str());
	player.cartasGeneradas[1] = cartaToShow1 + palo1;
	
	mostrarCartas(player);
	jugada(1, player);
}

void jugar() {
	cout << "\n\n************\tTUS DATOS\t************\n";
	Player player;

	cout << "Insete su nombre para empezar a jugar\n\n";
	cout << "Aqui: ";
	cin >> player.name;

	cout << "Introduza las fichas que desea tener\n";
	cout << "Aqui: ";
	cin >> player.fichas;

	cout << "Introduzca la cantidad a apostar\n";
	cout << "Aqui: ";
	cin >> player.apuesta;
	cout << "\n";

	player.puntosTotal = 0;

	primerTurno(player);

}


void inicioJuego() {
	system("cls");
	string option = mensajeInicio();
	if (option == "si" || option == "Si") {
		jugar();
	}
	system("cls");
}

int main() {
	srand((unsigned) time(NULL));
	inicioJuego();
}