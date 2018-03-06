/*
 * File:   main.cpp
 * Author: angel
 *
 * Created on March 2, 2018, 10:16 AM
 */

#include <iostream>
#include <cstdlib>
#include <unistd.h>
#include <fstream>
#include <stdio.h>
#include <string.h>

using namespace std;

struct act {
    int codigo;
    string descripcion;
    int horaInicio, minutoInicio, HoraFin, MinutoFin;
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
    void crearDia(int, int, int, int, int, string, int, int, int, int);
    void recorrerDias(void);
    dia buscarDiaPorFecha(int, int, int);
    bool existeDiaConFecha(int, int, int);
    void imprimirDia(dia);
    void agregarActividadDia(dia, int, string, int, int, int, int);
    void recorrerActividades(dia);
    void imprimirActividad(Actividad);
    void desColarActividad(dia);
    void desApilarActividad(dia);
    void eliminarActividadDeLaLista(dia);
    void modificarActividadDeLaLista(dia);
    void graphviz(void);
    bool intervaloHorasCorrecto(int, int, int, int);
    bool validacionSimpleFecha(int, int, int);
    Actividad buscarActividad(dia, int);
    void ordenarActividades(dia);
    string obtenerTipoManejoActividades(int);

private:
    dia beginCal;
    dia endCal;
};

agenda::agenda(void) {
    beginCal = NULL;
    endCal = NULL;
}

void agenda::crearDia(int diaIn, int mesIn, int anioIn, int tipoEstIn, int codigoIn, string descripcionIn, int horaIn, int minutoIn, int horaOut, int minutoOut) {

    if (!existeDiaConFecha(diaIn, mesIn, anioIn)) {
        Actividad aux;
        aux = new(struct act);
        aux->codigo = codigoIn;
        aux->descripcion = descripcionIn;
        aux->horaInicio = horaIn;
        aux->minutoInicio = minutoIn;
        aux->HoraFin = horaOut;
        aux->MinutoFin = minutoOut;
        aux->sigAct = NULL;
        aux->antAct = NULL;

        dia myDia;
        myDia = new(struct day);
        myDia->dias = diaIn;
        myDia->mes = mesIn;
        myDia->anio = anioIn;
        myDia->tipEstructura = tipoEstIn;

        myDia->actBegin = aux;
        myDia->actBegin->sigAct = NULL;
        myDia->actBegin->antAct = NULL;
        myDia->actEnd = myDia->actBegin;

        myDia->ant = NULL;
        myDia->sig = NULL;

        if (beginCal == NULL) {
            beginCal = myDia;
            beginCal->sig = beginCal;
            beginCal->ant = beginCal;
            endCal = beginCal;
        } else {
            endCal->sig = myDia;
            myDia->sig = beginCal;
            myDia->ant = endCal;
            endCal = myDia;
            beginCal->ant = endCal;
        }
    } else {
        cout << "YA EXISTE ESTA FECHA EN LA AGENDA" << endl;
    }
}

void agenda::recorrerDias(void) {
    dia auxR;
    auxR = beginCal;
    if (auxR != NULL) {
        do {
            imprimirDia(auxR);
            if (auxR->actBegin != NULL) {
                cout << "Existe una acitividad" << endl;
            }
            auxR = auxR->sig;
        } while (auxR != beginCal);
    } else {
        cout << "Agenda vacia" << endl;
    }
}

dia agenda::buscarDiaPorFecha(int diaBF, int mesBF, int anioBF) {
    dia auxR;
    auxR = beginCal;
    if (auxR != NULL) {
        do {
            if ((auxR->dias == diaBF) && (auxR->mes == mesBF) && (auxR->anio == anioBF)) {
                return auxR;
            }
            auxR = auxR->sig;
        } while (auxR != beginCal);
        return NULL;
    } else {
        return NULL;
    }
}

bool agenda::existeDiaConFecha(int diaBF, int mesBF, int anioBF) {
    dia auxR;
    auxR = beginCal;
    if (auxR != NULL) {
        do {
            if ((auxR->dias == diaBF) && (auxR->mes == mesBF) && (auxR->anio == anioBF)) {
                return true;
            }
            auxR = auxR->sig;
        } while (auxR != beginCal);
    } else {
        return false;
    }
}

void agenda::imprimirDia(dia resultado) {
    if (resultado != NULL) {
        cout << "\nEncotrado:\nFecha: " << resultado->dias << "/" << resultado->mes << "/" << resultado->anio << "\nTipo de estructura: " << obtenerTipoManejoActividades(resultado->tipEstructura) << endl;
    } else {
        cout << "No hay elementos por imprimir" << endl;
    }
}

void agenda::agregarActividadDia(dia resultado, int codigoIn, string descripcionIn, int horaIn, int minutoIn, int horaOut, int minutoOut) {

    Actividad aux;
    aux = new(struct act);
    aux->codigo = codigoIn;
    aux->descripcion = descripcionIn;
    aux->horaInicio = horaIn;
    aux->minutoInicio = minutoIn;
    aux->HoraFin = horaOut;
    aux->MinutoFin = minutoOut;
    aux->sigAct = NULL;
    aux->antAct = NULL;

    if (resultado->actBegin != NULL) {
        resultado->actEnd->sigAct = aux;
        aux->antAct = resultado->actEnd;
        resultado->actEnd = aux;
    } else {
        resultado->actBegin = aux;
        resultado->actBegin->sigAct = NULL;
        resultado->actBegin->antAct = NULL;
        resultado->actEnd = resultado->actBegin;
    }
}

void agenda::recorrerActividades(dia resultado) {
    Actividad auxR;
    auxR = new(struct act);
    auxR = resultado->actBegin;
    if (resultado->actBegin != NULL) {
        while (auxR != NULL) {
            imprimirActividad(auxR);
            auxR = auxR->sigAct;
        }
    } else {
        cout << "La lista de actividades esta vacia" << endl;
    }

}

Actividad agenda::buscarActividad(dia resultado, int codigoIn) {
    Actividad auxR;
    auxR = new(struct act);
    auxR = resultado->actBegin;
    if (resultado->actBegin != NULL) {
        while (auxR != NULL) {
            if (auxR->codigo == codigoIn) {
                return auxR;
            }
            auxR = auxR->sigAct;
        }
    } else {
        cout << "La lista de actividades esta vacia" << endl;
        return NULL;
    }

}

void agenda::imprimirActividad(Actividad aux) {
    if (aux != NULL) {
        cout << "\nDatos de la Actividad";
        cout << "\nCodigo: " << aux->codigo << "\nDescripcion: " << aux->descripcion << endl;
        cout << "Hora inicio: " << aux->horaInicio << ":" << aux->minutoInicio << " Hora final: " << aux->HoraFin << ":" << aux->MinutoFin << endl;
        cout << "^|^.^|^.^|^.^|^.^|^.^|^.^|^.^|^.^|^.^|^.^|^.^|^.^|^.^|^.^|^.^|^.^|^.^|^.^|^.^|^.^|^.^|^." << endl;
    } else {
        cout << "No existe actividad" << endl;
    }
}

void agenda::desColarActividad(dia resultado) {
    if (resultado->actBegin != NULL) {
        Actividad aux;
        aux = new(struct act);

        aux = resultado->actBegin;
        cout << "SE HA ELIMINADO LA ACTIVIDAD->" << endl;
        imprimirActividad(aux);
        resultado->actBegin = resultado->actBegin->sigAct;
        resultado->actBegin->antAct = NULL;

        delete(aux);
    } else {
        cout << "La lista de actividad esta Vacia" << endl;
    }
}

void agenda::desApilarActividad(dia resultado) {
    if (resultado-> actBegin != NULL) {

        Actividad aux;
        aux = new(struct act);
        cout << "SE HA ELIMINADO LA ACTIVIDAD->" << endl;
        imprimirActividad(aux);
        aux = resultado->actEnd;
        resultado->actEnd = resultado->actEnd->antAct;
        resultado->actEnd->sigAct = NULL;

        delete(aux);
    } else {
        cout << "La lista de actividad esta Vacia" << endl;
    }
}

void agenda::eliminarActividadDeLaLista(dia resultado) {
    int respuesta = 0;
    Actividad auxR;
    auxR = new(struct act);
    Actividad aux;
    aux = new(struct act);
    auxR = resultado->actBegin;
    if (resultado->actBegin != NULL) {
        while (auxR != NULL && ((respuesta != 4) && (respuesta != 2))) {
            do {
                imprimirActividad(auxR);
                cout << "1.Actividad anterior\n2.Eliminar actividad \n3.Siguiente actividad\n 4.Salir" << endl;
                cout << "Que desea realizar? ";
                cin>>respuesta;
                switch (respuesta) {
                    case 1:
                        auxR = auxR->antAct;
                        break;

                    case 2:
                        if (auxR == resultado->actBegin) {
                            auxR = resultado->actBegin;
                            resultado->actBegin = resultado->actBegin->sigAct;
                            resultado->actBegin->antAct = NULL;
                            delete(auxR);
                        } else if (auxR == resultado->actEnd) {
                            auxR = resultado->actEnd;
                            resultado->actEnd = resultado->actEnd->antAct;
                            resultado->actEnd->sigAct = NULL;
                            delete(auxR);
                        } else {
                            aux = auxR->antAct;
                            aux->sigAct = auxR->sigAct;
                            auxR->sigAct->antAct = aux;
                            delete(auxR);
                        }
                        break;

                    case 3:
                        auxR = auxR->sigAct;
                        break;

                    case 4: cout << "Terminar eliminacion" << endl;
                        auxR == NULL;
                        break;

                    default:
                        cout << "opcion Incorrecta, intentelo nuevamente" << endl;
                }
            } while ((respuesta != 4) && (respuesta != 2));
        }
    } else {
        cout << "La lista de actividades esta vacia" << endl;
    }
}

void agenda::modificarActividadDeLaLista(dia resultado) {
    int respuesta = 0;
    Actividad auxR;
    auxR = new(struct act);
    auxR = resultado->actBegin;

    int codigoM;
    string descripcionM;
    int horaM;
    int minutoM;
    int HoraM;
    int MinutoM;

    if (resultado->actBegin != NULL) {
        while ((auxR != NULL) && (respuesta != 4) && (respuesta != 2)) {

            do {
                imprimirActividad(auxR);
                cout << "1.Actividad anterior\n2.Modificar actividad \n3.Siguiente actividad\n 4.Salir" << endl;
                cout << "Que desea realizar? ";
                cin>>respuesta;
                switch (respuesta) {
                    case 1:
                        auxR = auxR->antAct;
                        break;

                    case 2:
                        cout << "\n\tDATOS DE LA ACTIVIDAD A REALIZAR" << endl;
                        cout << "Ingrese el codigo de identificacion de la actividad: \t";
                        cin >> codigoM;
                        cout << "Ingrese una breve descripcion de la actividad: \t" << endl;
                        cin >> descripcionM;
                        cout << "Ingrese la Hora(hh) de inicio: \t";
                        cin >> horaM;
                        cout << "Ingrese los Minutos(mm) de inicio: \t";
                        cin >> minutoM;
                        cout << "Ingrese la Hora(hh) de fin: \t";
                        cin >> HoraM;
                        cout << "Ingrese los Minutos(mm) de fin: \t";
                        cin >> MinutoM;

                        if (intervaloHorasCorrecto(horaM, minutoM, HoraM, MinutoM)) {
                            auxR->codigo = codigoM;
                            auxR->descripcion = descripcionM;
                            auxR->horaInicio = horaM;
                            auxR->minutoInicio = minutoM;
                            auxR->HoraFin = HoraM;
                            auxR->MinutoFin = MinutoM;
                            cout << "Modificacion realizada\n\n" << endl;
                        } else {
                            cout << "Intervalo de tiempo incorrecto" << endl;
                        }
                        break;

                    case 3:
                        auxR = auxR->sigAct;
                        break;

                    case 4: cout << "Terminar Modificacion" << endl;
                        auxR == NULL;
                        break;

                    default:
                        cout << "opcion Incorrecta, intentelo nuevamente" << endl;
                }
            } while ((respuesta != 4) && (respuesta != 2));
        }
    } else {
        cout << "La lista de actividades esta vacia" << endl;
    }
}

void agenda::graphviz(void) {
    ofstream salidagraph("grafica.dot");
    dia auxR;
    auxR = beginCal;
    Actividad aux;
    aux = new(struct act);

    salidagraph << "digraph G { " << endl << "node [shape = record,height=.1];" << endl;
    if (auxR != NULL) {
        do {
            salidagraph << "node" << auxR->dias << auxR->mes << auxR->anio << "[label = \"<f0> Fecha" << auxR->dias << "/" << auxR->mes << "/" << auxR->anio << " |<f1> Tipo: " << obtenerTipoManejoActividades(auxR->tipEstructura) << " \"];" << endl;

            salidagraph << "\"node" << auxR->dias << auxR->mes << auxR->anio << "\":f0 ->\"node" << auxR->sig->dias << auxR->sig->mes << auxR->sig->anio << "\":f0;" << endl;
            salidagraph << "\"node" << auxR->sig->dias << auxR->sig->mes << auxR->sig->anio << "\":f1 ->\"node" << auxR->dias << auxR->mes << auxR->anio << "\":f1;" << endl;
            aux = auxR->actBegin;
            salidagraph << "\"node" << auxR->dias << auxR->mes << auxR->anio << "\":f0 ->\"node" << aux->codigo << auxR->dias << auxR->mes << auxR->anio << "\":f0;" << endl;

            if (auxR->actBegin != NULL) {
                while (aux != NULL) {
                    if ((aux->horaInicio == 0) && (aux->minutoInicio == 0) && (aux->HoraFin == 0) && (aux->MinutoFin == 0)){
                        salidagraph << "node" << aux->codigo << auxR->dias << auxR->mes << auxR->anio << "[label = \"<f0> Codigo: " << aux->codigo << " |<f1> Descripcion: " << aux->descripcion << " \"];" << endl;
                    }else{
                        salidagraph << "node" << aux->codigo << auxR->dias << auxR->mes << auxR->anio << "[label = \"<f0> Codigo: " << aux->codigo << " |<f1> Descripcion: " << aux->descripcion << " |<f2> Hora inicio: " << aux->horaInicio << ":" << aux->minutoInicio << " |<f3> Hora fin: " << aux->HoraFin << ":" << aux->MinutoFin << "\"];" << endl;
                    }

                    if (aux->sigAct != NULL) {
                        salidagraph << "\"node" << aux->codigo << auxR->dias << auxR->mes << auxR->anio << "\":f0 ->\"node" << aux->sigAct->codigo << auxR->dias << auxR->mes << auxR->anio << "\":f0;" << endl;
                        salidagraph << "\"node" << aux->sigAct->codigo << auxR->dias << auxR->mes << auxR->anio << "\":f0 ->\"node" << aux->codigo << auxR->dias << auxR->mes << auxR->anio << "\":f0;" << endl;
                    }
                    aux = aux->sigAct;
                }
            }

            auxR = auxR->sig;
        } while (auxR != beginCal);
    } else {
        cout << "Agenda vacia" << endl;
    }

    salidagraph << endl << "}" << endl;

    salidagraph.close();


    system("dot -Tpng grafica.dot -o grafica.png");
    system("nohup display grafica.png &");
}

bool agenda::intervaloHorasCorrecto(int horaIn, int minutoIn, int horaOut, int minutoOut) {
    if ((horaIn >= 0 && horaIn < 24) && (minutoIn >= 0 && minutoIn < 60) && (horaOut >= 0 && horaOut < 24) && (minutoOut >= 0 && minutoOut < 60)) {
        return (((horaIn * 60) + minutoIn) < ((horaOut * 60) + minutoOut));
    } else {
        cout << "Formato de minuto u hora incorrecto" << endl;
        return false;
    }
}

bool agenda::validacionSimpleFecha(int dia, int mes, int anio) {
    return ((dia > 0 && dia < 32) && (mes > 0 && mes < 13) && (anio >= 2000));
}

void agenda::ordenarActividades(dia resultado) {
    Actividad actual, siguiente;
    actual = new(struct act);
    siguiente = new(struct act);

    int cod, hrIn, minIn, hrFn, minFn;
    string desc;

    actual = resultado->actBegin;

    while (actual->sigAct != NULL) {
        siguiente = actual->sigAct;

        while (siguiente != NULL) {
            if (((actual->horaInicio * 60) + actual->minutoInicio) > ((siguiente->horaInicio * 60) + siguiente->minutoInicio)) {

                cod = siguiente->codigo;
                siguiente->codigo = actual->codigo;
                actual->codigo = cod;

                desc = siguiente->descripcion;
                siguiente->descripcion = actual->descripcion;
                actual->descripcion = desc;

                hrIn = siguiente->horaInicio;
                siguiente->horaInicio = actual->horaInicio;
                actual->horaInicio = hrIn;

                minIn = siguiente->minutoInicio;
                siguiente->minutoInicio = actual->minutoInicio;
                actual->minutoInicio = minIn;

                hrFn = siguiente->HoraFin;
                siguiente->HoraFin = actual->HoraFin;
                actual->HoraFin = hrFn;

                minFn = siguiente->MinutoFin;
                siguiente->MinutoFin = actual->MinutoFin;
                actual->MinutoFin = minFn;
            }
            siguiente = siguiente->sigAct;
        }
        actual = actual->sigAct;
        siguiente = actual->sigAct;
    }
}

string agenda::obtenerTipoManejoActividades(int tipoManejoAct){
    if (tipoManejoAct == 1){
        return "Pila";
    } else if (tipoManejoAct == 2){
        return "Cola";
    } else if (tipoManejoAct == 3){
        return "Lista";
    } else {
        return "";
    }
}

int menu(void) {
    cout << "\n\n\t -------------------------------------------\n";
    cout << "\t|            AGENDA DE ACTIVIDADES          |\n";
    cout << "\t|-------------------------------------------|\n";
    cout << " \t|                                           |" << endl;
    cout << " \t|  1. AGREGAR DIA                           |" << endl;
    cout << " \t|  2. VER LOS DIAS                          |" << endl;
    cout << " \t|  3. BUSCAR UN DIA                         |" << endl;
    cout << " \t|  4. VER ACTIVIDADES DE UNA FECHA          |" << endl;
    cout << " \t|  5. AGREGAR ACTIVIDADES A UNA FECHA       |" << endl;
    cout << " \t|  6. MODIFICAR ACTIVIDADES DE UNA FECHA    |" << endl;
    cout << " \t|  7. ELIMINAR ACTIVIDADES DE UNA FECHA     |" << endl;
    cout << " \t|  8. GENERAR GRAPHVIZ                      |" << endl;
    cout << " \t|  9. SALIR                                 |" << endl;
    cout << " \t|                                           |" << endl;
    cout << "\t -------------------------------------------\n";
    cout << "\t Ingrese opcion: ";
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
    int HoraM;
    int MinutoM;
    int op;

    //generar dias y actividades por defecto
    myAgenda.crearDia(10, 2, 2018, 1, 123, "Ir con el dentista", 0, 0, 0, 0);
    myAgenda.agregarActividadDia(myAgenda.buscarDiaPorFecha(10, 2, 2018), 124, "Lavar el auto", 0, 0, 0, 0);
    myAgenda.agregarActividadDia(myAgenda.buscarDiaPorFecha(10, 2, 2018), 125, "Llevar el auto al CarWash", 0, 0, 0, 0);
    myAgenda.agregarActividadDia(myAgenda.buscarDiaPorFecha(10, 2, 2018), 126, "Sacar el auto de casa", 0, 0, 0, 0);
    myAgenda.crearDia(12, 2, 2018, 2, 123, "Reunion de negocios", 0, 0, 0, 0);
    myAgenda.agregarActividadDia(myAgenda.buscarDiaPorFecha(12, 2, 2018), 124, "Almorza en casa con Mama", 0, 0, 0, 0);
    myAgenda.agregarActividadDia(myAgenda.buscarDiaPorFecha(12, 2, 2018), 125, "Depositar en el banco", 0, 0, 0, 0);
    myAgenda.agregarActividadDia(myAgenda.buscarDiaPorFecha(12, 2, 2018), 126, "Cenar con amigos", 0, 0, 0, 0);
    myAgenda.crearDia(14, 2, 2018, 3, 456, "Bañar al perro", 8, 15, 8, 50);
    myAgenda.agregarActividadDia(myAgenda.buscarDiaPorFecha(14, 2, 2018), 124, "Clase de boxeo", 9, 10, 11, 30);
    myAgenda.agregarActividadDia(myAgenda.buscarDiaPorFecha(14, 2, 2018), 125, "Papeleo en la U", 12, 10, 1, 30);
    myAgenda.agregarActividadDia(myAgenda.buscarDiaPorFecha(14, 2, 2018), 126, "Clase en la U", 14, 30, 20, 20);
    myAgenda.crearDia(16, 2, 2018, 1, 789, "Cena con el Jefe", 0, 0, 0, 0);
    myAgenda.agregarActividadDia(myAgenda.buscarDiaPorFecha(16, 2, 2018), 124, "Terminar informe", 0, 0, 0, 0);
    myAgenda.agregarActividadDia(myAgenda.buscarDiaPorFecha(16, 2, 2018), 125, "Odenar datos para el informe", 0, 0, 0, 0);
    myAgenda.agregarActividadDia(myAgenda.buscarDiaPorFecha(16, 2, 2018), 126, "Almorzar con amigos del trabajo", 0, 0, 0, 0);
    myAgenda.crearDia(18, 2, 2018, 2, 654, "Clase de cocina", 0, 0, 0, 0);
    myAgenda.agregarActividadDia(myAgenda.buscarDiaPorFecha(18, 2, 2018), 124, "Almuerzo en Albamar", 0, 0, 0, 0);
    myAgenda.agregarActividadDia(myAgenda.buscarDiaPorFecha(18, 2, 2018), 125, "Comprar una mesa", 0, 0, 0, 0);
    myAgenda.agregarActividadDia(myAgenda.buscarDiaPorFecha(18, 2, 2018), 126, "Colocar mesa nueva en la cocina", 0, 0, 0, 0);

    system("clear");

    do {
        sleep(1);
        menu();
        cin>> op;
        system("clear");

        switch (op) {
            case 1: cout << "\n\t INGRESE LOS DATOS DEL DIA A AGREGAR " << endl;
                cout << "Ingrese el dia: ";
                cin>>diaM;
                cout << "Ingrese el mes: ";
                cin>>mesM;
                cout << "Ingrese el año: ";
                cin>>anioM;
                if (myAgenda.existeDiaConFecha(diaM, mesM, anioM)){
                    cout << "ERROR! YA EXISTE ESA FECHA" << endl;
                    break;
                }
                if (!myAgenda.validacionSimpleFecha(diaM, mesM, anioM)) {
                    cout << "ERROR! fecha invalida" << endl;
                    break;
                }
                cout << "Ingrese el numero respecto del tipo de manejo de la agenda del dia" << endl;
                cout << "1. Pila, 2. Cola, 3.Lista: ";
                cin>>tipoEstM;
                cout << "\n\tDATOS DE LA PRIMER ACTIVIDAD A REALIZAR" << endl;
                cout << "Ingrese el codigo de identificacion de la actividad: \t";
                cin>>codigoM;
                cout << "Ingrese una breve descripcion de la actividad:\t " << endl;
                //cin>>descripcionM;
                getline (cin, descripcionM);
                if (codigoM == 3) {
                    cout << "Ingrese la Hora(hh) de inicio: \t";
                    cin>>horaM;
                    cout << "Ingrese los Minutos(mm) de inicio:\t ";
                    cin>>minutoM;
                    cout << "Ingrese la Hora(hh) de fin: \t";
                    cin>>HoraM;
                    cout << "Ingrese los Minutos(mm) de fin: \t";
                    cin>>MinutoM;
                    if (myAgenda.intervaloHorasCorrecto(horaM, minutoM, HoraM, MinutoM)) {
                        myAgenda.crearDia(diaM, mesM, anioM, tipoEstM, codigoM, descripcionM, horaM, minutoM, HoraM, MinutoM);
                        cout << "Dia creado exitosamente" << endl;
                    } else {
                        cout << "Error! Intervalo de hora incorrecto" << endl;
                    }
                } else if ((codigoM == 2) || (codigoM == 1)) {
                    myAgenda.crearDia(diaM, mesM, anioM, tipoEstM, codigoM, descripcionM, 0, 0, 0, 0);
                    cout << "Dia creado exitosamente" << endl;
                } else {
                    cout << "Manejo seleccionado invalido" << endl;
                }

                break;

            case 2: cout << "\n\n\tVER DIAS" << endl;
                myAgenda.recorrerDias();
                break;

            case 3: cout << "\n\n\tIngrese la fecha: " << endl;
                cout << "Ingrese el dia: ";
                cin>>diaM;
                cout << "Ingrese el mes: ";
                cin>>mesM;
                cout << "Ingrese el año: ";
                cin>>anioM;
                if (!myAgenda.validacionSimpleFecha(diaM, mesM, anioM)) {
                    cout << "ERROR! fecha invalida" << endl;
                    break;
                }
                myAgenda.imprimirDia(myAgenda.buscarDiaPorFecha(diaM, mesM, anioM));
                break;

            case 4: cout << "\n\n\tVER ACTIVIDADES DE UNA FECHA" << endl;
                cout << "Ingrese la fecha del dia: \n";
                cout << "Ingrese el dia: ";
                cin>>diaM;
                cout << "Ingrese el mes: ";
                cin>>mesM;
                cout << "Ingrese en año: ";
                cin>>anioM;
                if (!myAgenda.validacionSimpleFecha(diaM, mesM, anioM)) {
                    cout << "ERROR! fecha invalida" << endl;
                    break;
                }
                if (myAgenda.existeDiaConFecha(diaM, mesM, anioM)) {
                    myAgenda.recorrerActividades(myAgenda.buscarDiaPorFecha(diaM, mesM, anioM));
                } else {
                    cout << "\n\nNO EXISTE LA FECHA INDICADA" << endl;
                }
                break;

            case 5: cout << "\n\n\tAGREGAR UNA ACTIVIDAD A UNA FECHA" << endl;
                cout << "Ingrese la fecha del dia: \n";
                cout << "Ingrese el dia: ";
                cin>>diaM;
                cout << "Ingrese el mes: ";
                cin>>mesM;
                cout << "Ingrese en año: ";
                cin>>anioM;
                if (!myAgenda.validacionSimpleFecha(diaM, mesM, anioM)) {
                    cout << "ERROR! fecha invalida" << endl;
                    break;
                }
                if (myAgenda.existeDiaConFecha(diaM, mesM, anioM)) {

                    cout << "\n\tDATOS DE LA ACTIVIDAD A REALIZAR" << endl;
                    cout << "Ingrese el codigo de identificacion de la actividad: \t";
                    cin>>codigoM;
                    if (myAgenda.buscarActividad(myAgenda.buscarDiaPorFecha(diaM, mesM, anioM), codigoM) != NULL) {
                        cout << "ERROR! ya existe una actividad con ese codigo" << endl;
                        break;
                    }
                    cout << "Ingrese una breve descripcion de la actividad: \t";
                    cin>>descripcionM;
                    if (myAgenda.buscarDiaPorFecha(diaM, mesM, anioM)->tipEstructura == 3) {
                        cout << "Ingrese la Hora(hh) de inicio: \t";
                        cin>>horaM;
                        cout << "Ingrese los Minutos(mm) de inicio: \t";
                        cin>>minutoM;
                        cout << "Ingrese la Hora(hh) de fin: \t";
                        cin>>HoraM;
                        cout << "Ingrese los Minutos(mm) de fin: \t";
                        cin>>MinutoM;
                        if (myAgenda.intervaloHorasCorrecto(horaM, minutoM, HoraM, MinutoM)) {
                            myAgenda.agregarActividadDia(myAgenda.buscarDiaPorFecha(diaM, mesM, anioM), codigoM, descripcionM, horaM, minutoM, HoraM, MinutoM);
                            myAgenda.ordenarActividades(myAgenda.buscarDiaPorFecha(diaM, mesM, anioM));
                            cout << "Actividad creada exitosamente" << endl;
                        } else {
                            cout << "Error! Intervalo de hora incorrecto" << endl;
                        }
                    } else if ((myAgenda.buscarDiaPorFecha(diaM, mesM, anioM)->tipEstructura == 1) || (myAgenda.buscarDiaPorFecha(diaM, mesM, anioM)->tipEstructura == 2)) {
                        myAgenda.agregarActividadDia(myAgenda.buscarDiaPorFecha(diaM, mesM, anioM), codigoM, descripcionM, 0, 0, 0, 0);
                        cout << "Actividad creada exitosamente" << endl;
                    }
                } else {
                    cout << "\n\nNO EXISTE LA FECHA INDICADA" << endl;
                }
                break;

            case 6: cout << "\n\n\tMODIFICAR ACTIVIDAD EN UNA FECHA" << endl;
                cout << "Ingrese la fecha del dia: \n";
                cout << "Ingrese el dia: ";
                cin>>diaM;
                cout << "Ingrese el mes: ";
                cin>>mesM;
                cout << "Ingrese en año: ";
                cin>>anioM;
                if (!myAgenda.validacionSimpleFecha(diaM, mesM, anioM)) {
                    cout << "ERROR! fecha invalida" << endl;
                    break;
                }
                if (myAgenda.existeDiaConFecha(diaM, mesM, anioM)) {
                    myAgenda.modificarActividadDeLaLista(myAgenda.buscarDiaPorFecha(diaM, mesM, anioM));
                } else {
                    cout << "\n\nNO EXISTE LA FECHA INDICADA" << endl;
                }
                break;

            case 7: cout << "\n\n\tELIMINAR ACTIVIDAD EN UNA FECHA" << endl;
                cout << "Ingrese la fecha del dia: \n";
                cout << "Ingrese el dia: ";
                cin>>diaM;
                cout << "Ingrese el mes: ";
                cin>>mesM;
                cout << "Ingrese en año: ";
                cin>>anioM;
                
                if (!myAgenda.validacionSimpleFecha(diaM, mesM, anioM)) {
                    cout << "ERROR! fecha invalida" << endl;
                    break;
                }
                if (myAgenda.existeDiaConFecha(diaM, mesM, anioM)) {
                    if (myAgenda.buscarDiaPorFecha(diaM, mesM, anioM)->tipEstructura == 1) {
                        myAgenda.desApilarActividad(myAgenda.buscarDiaPorFecha(diaM, mesM, anioM));
                    } else if (myAgenda.buscarDiaPorFecha(diaM, mesM, anioM)->tipEstructura == 2) {
                        myAgenda.desColarActividad(myAgenda.buscarDiaPorFecha(diaM, mesM, anioM));
                    } else if (myAgenda.buscarDiaPorFecha(diaM, mesM, anioM)->tipEstructura == 3) {
                        myAgenda.eliminarActividadDeLaLista(myAgenda.buscarDiaPorFecha(diaM, mesM, anioM));
                    } else {
                        cout << "\n\nNO EXISTE LA FECHA INDICADA" << endl;
                    }
                }
                break;

            case 8:
                myAgenda.graphviz();
                break;

            case 9: cout << "Bye baby!" << endl;
                break;
            default: cout << "\n\tIngrese una Opcion Valida....!!";
        }

        cout << endl << endl;

    } while (op != 9);

    return 0;
}