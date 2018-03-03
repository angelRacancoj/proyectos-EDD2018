/*
 * File:   main.cpp
 * Author: angel
 *
 * Created on March 2, 2018, 10:16 AM
 */

#include <iostream>
#include <cstdlib>
#include <unistd.h>

using namespace std;

struct act {
    int codigo;
    string descripcion;
    int hora, minuto;
    struct act *ant;
    struct act *sig;
};

typedef struct act *Actividad;

struct day {
    int dia, mes, anio, tipEstructura;
    struct act *inicio;
    struct day *ant;
    struct day *sig;
};

typedef struct day *dia;

class agenda {
public:
    agenda(void);
    void crearDia(int, int, int, int, int, string, int, int);

private:
    dia beginCal;
    dia endCal;
};

agenda::agenda(void) {
    beginCal = NULL;
    endCal = NULL;
}

void agenda::crearDia(int diaIn, int mesIn, int anioIn, int tipoEstIn, int codigoIn, string descripcionIn, int horaIn, int minutoIn) {
    Actividad aux;
    aux = new(struct act);
    aux->codigo = codigoIn;
    aux->descripcion = descripcionIn;
    aux->hora = horaIn;
    aux->minuto = minutoIn;
    aux->sig = NULL;
    aux->ant = NULL;

    dia myDia;
    myDia = new(struct day);
    myDia->dia = diaIn;
    myDia->mes = mesIn;
    myDia->anio = anioIn;
    myDia->tipEstructura = tipoEstIn;
    myDia->inicio = aux;
    myDia->ant = NULL;
    myDia->sig = NULL;

    if (beginCal = NULL) {

    }
}

int main(int argc, char** argv) {

    return 0;
}

