#include "../include/DTReservaGrupal.h"

DTReservaGrupal::DTReservaGrupal(int cod, DTFecha* chIn, DTFecha* chOut, EstadoReserva est, float costo, int hab, map<string, DTHuesped> hues) {
     this->codigo = cod;
     this->checkIn = chIn;
     this->checkOut = chOut;
     this->estado = est;
     this->costo =  costo;
     this->habitacion = hab;
     this->huespedes = hues;
};

int DTReservaGrupal::getCodigo() {
     return this->codigo;
};

DTFecha* DTReservaGrupal::getCheckIn() {
     return this->checkIn;
};

DTFecha* DTReservaGrupal::getCheckOut() {
     return this->checkOut;
};

EstadoReserva DTReservaGrupal::getEstado() {
     return this->estado;
};

float DTReservaGrupal::getCosto() {
     return this->costo;
};

int DTReservaGrupal::getHabitacion() {
     return this->habitacion;
};

map<string, DTHuesped> DTReservaGrupal::getHuespedes() {
     return this->huespedes;
};

DTReservaGrupal::~DTReservaGrupal(){
     //Nada dinámico ok
};