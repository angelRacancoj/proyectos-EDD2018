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
    struct act *antAct;
    struct act *sigAct;
};

typedef struct act *Actividad;

struct day {
    int dias, mes, anio, tipEstructura;
    struct act *inicio;
    struct day *ant;
    struct day *sig;
    Actividad actBegin;
    Actividad actEnd;
};

typedef struct day *dia;

class agenda {
public:
    agenda(void);
    void crearDia(int, int, int, int, int, string, int, int);
    void recorrerDias(void);

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
    aux->sigAct = NULL;
    aux->antAct = NULL;

    dia myDia;
    myDia = new(struct day);
    myDia->dias = diaIn;
    myDia->mes = mesIn;
    myDia->anio = anioIn;
    myDia->tipEstructura = tipoEstIn;
    myDia->inicio = aux;
    myDia->actBegin = aux;
    myDia->actEnd = aux;

    if (beginCal = NULL) {
        myDia->sig = endCal;
        myDia->ant = beginCal;
        beginCal = myDia;
        endCal = myDia;
    }else {
        myDia->ant = endCal;
        myDia->sig = beginCal;
        endCal->sig = myDia;
        beginCal->ant = myDia;
        endCal = myDia;
    }
}

void agenda::recorrerDias(void){
    dia auxR;
    auxR = beginCal;
    if (auxR != NULL){
        do{
            cout<<auxR->dias<<"/"<<auxR->mes<<"/"<<auxR->anio<<" Tipo de estructura: "<<auxR->tipEstructura<<endl;
            if (auxR->actBegin != NULL){
                cout<<"Existe una acitividad"<<endl;
            }
        }while(&beginCal != &endCal);
    }else{
        cout<< "Agenda vacia"<< endl;
    }
}

int menu(void)
{
    cout<<"\n\n\t -------------------------------------------\n";
    cout<<"\t|            AGENDA DE ACTIVIDADES          |\n";
    cout<<"\t|-------------------------------------------|\n";
    cout<<" \t|                                           |"<<endl;
    cout<<" \t|  1. AGREGAR DIA                           |"<<endl;
    cout<<" \t|  2. VER LOS DIAS                          |"<<endl;
    cout<<" \t|  3. MODIFICAR UN DIA*                      |"<<endl;
    cout<<" \t|  4. ELIMINAR DIA*                          |"<<endl;
    cout<<" \t|  5. VER ACTIVIDADES DE UNA FECHA*          |"<<endl;
    cout<<" \t|  6. AGREGAR ACTIVIDADES A UNA FECHA*       |"<<endl;
    cout<<" \t|  7. MODIFICAR ACTIVIDADES DE UNA FECHA*    |"<<endl;
    cout<<" \t|  8. ELIMINAR ACTIVIDADES DE UNA FECHA*     |"<<endl;
    cout<<" \t|  9. SALIR                                 |"<<endl;
    cout<<" \t|                                           |"<<endl;
    cout<<" \t|  *. aun no han sido creados               |"<<endl;
    cout<<"\t -------------------------------------------\n";
    cout<<"\t Ingrese opcion: ";
}

int main(void) {

    agenda myAgenda;
    int diaM;
    int mesM;
    int anioM;
    int tipoEstM;
    int codigoM;
    string descripcionM;
    int horaM;
    int minutoM;
    int op;

    do
    {
        sleep(1); 
        menu();  
        cin>> op;
        system ("clear");

        switch(op)
        {
            case 1: cout<< "\n\t INGRESE LOS DATOS DEL DIA A AGREGAR "<<endl;
                    cout<<"Ingrese el dia: ";                                                           cin>>diaM;
                    cout<<"Ingrese el mes: ";                                                           cin>>mesM;
                    cout<<"Ingrese el año: ";                                                           cin>>anioM;
                    cout<<"Ingrese el numero respecto del tipo de manejo de la agenda del dia"<<endl;
                    cout<<"1. Pila, 2. Cola, 3.Lista: ";                                                cin>>tipoEstM;
                    cout<<"Ingrese el codigo de identificacion del dia: ";                              cin>>codigoM;
                    cout<<"\n\tDATOS DE LA PRIMER ACTIVIDAD A REALIZAR"<< endl;
                    cout<<"Ingrese una breve descripcion de la actividad: "<< endl;                     cin>>descripcionM;
                    cout<<"Ingrese la Hora(hh): ";                                                      cin>>horaM;
                    cout<<"Ingrese los Minutos(mm): ";                                                  cin>>minutoM;
                    myAgenda.crearDia(diaM, mesM, anioM, tipoEstM, codigoM, descripcionM, horaM, minutoM);
                    break;
 
            case 2: cout<<"\n\n\tVER DIAS"<<endl;
                    myAgenda.recorrerDias();
                    break;
 
            default: cout<<"\n\tIngrese una Opcion Valida....!!";
         }
 
        cout<<endl<<endl;
 
    }while(op!=5);

    return 0;
}

