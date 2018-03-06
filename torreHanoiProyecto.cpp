# include <iostream>
# include <time.h>
# include <cstdlib>
# include <unistd.h>

using namespace::std;

int inicio[16];
int medio[16];
int final[16];
int movimientos =0;

int enUsoInicio=0;
int enUsoIntermedio=0;
int enUsoFinal=0;

void dibujarDisco(int torre[], int lim){
	for (int i = (lim-1); i > -1; --i){
		if (torre[i]!= 0){
			int size = torre[i];	
			for (int j = 0; j < size; ++j){
			cout<<"x";
			}
			cout<<"  ";
		}
	}
}

void dibujarTodosLosDiscos(int lim){
	cout<<"Torre 1 --> ";
	dibujarDisco(inicio, lim);
	cout<<"\nTorre 2 --> ";
	dibujarDisco(medio, lim);
	cout<<"\nTorre 3 --> ";
	dibujarDisco(final, lim);
	cout<<"\n--------------------------------------------------------------------------------------------------\n"<< endl;
	usleep(100000);
}

void intecambiarElementos(int envia[], int recibe[], int lim){
	int aux=0;
	bool encontrado = false;
	for (int j = 0; j < lim; ++j){
		if ((envia[j] != 0) && (encontrado == false)){
			cout << envia[j];
			aux = envia[j];
			envia[j] = 0;
			recibe[j] = aux;
			aux=0;
			encontrado = true;
		}
	}
} 

void Mover_Torres(int N, int Origen[], int Intermedio[], int Destino[], int lim, int uno, int dos, int tres){ 
	

	if (N > 0 || N < 16){
		if ( 1 == N ){
			cout << "Mover disco: ";
			intecambiarElementos(Origen, Destino, lim);
			cout << " de torre "<< uno << " a " << tres << endl;
			dibujarTodosLosDiscos(lim);

		} else { 
			Mover_Torres( N - 1, Origen, Destino, Intermedio, lim, uno, tres, dos);
			cout << "Mover disco: ";
			intecambiarElementos(Origen, Destino, lim);
			cout << " de torre "<< uno << " a " << tres << endl;
			dibujarTodosLosDiscos(lim);
			Mover_Torres( N - 1, Intermedio, Origen, Destino, lim, dos, uno, tres);
		} 
	}else {
		cout << "\n Cantidad de discos fuera del Rango"<< endl;
	}
	movimientos++;
}

int main(){ 
	int Discos;
	cout << "\tTorres de Hanoi" << endl;
	cout << "Introduzca el numero de discos: "<< endl;
	cin >> Discos;

	for (int i = 0; i < Discos; ++i){
		inicio[i] = (i+1);
	}

	int limite = (sizeof(inicio)/sizeof(inicio[0]));

	movimientos = 0;
	cout<<"\n\t\tInicio Torre de Hanoi"<<endl;
	dibujarTodosLosDiscos(limite);
	Mover_Torres( Discos, inicio, medio, final, limite, 1, 2, 3);
	cout << "\n\tLa cantidad de movimientos realizados es: "<<movimientos<<endl;
	cout << endl << endl;

	return 0;
}