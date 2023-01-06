//#include "DTReserva.h"
#include "DTHuesped.h"
#include "DTFecha.h"
#include "EstadoReserva.h"
#include <map>

#ifndef DTRESERVAGRUPAL
#define DTRESERVAGRUPAL

//class DTReservaGrupal : public DTReserva {
class DTReservaGrupal{
     protected:
          int codigo;
          DTFecha* checkIn;
          DTFecha* checkOut;
          EstadoReserva estado;
          float costo;
          int habitacion;
          map<string, DTHuesped> huespedes;

     public:
          DTReservaGrupal(int cod, DTFecha* chIn, DTFecha* chOut, EstadoReserva est, float costo, int hab, map<string, DTHuesped> hues);
          int getCodigo();
          DTFecha* getCheckIn();
          DTFecha* getCheckOut();
          EstadoReserva getEstado();
          float getCosto();
          int getHabitacion();
          map<string, DTHuesped> getHuespedes();
          //ACA la sobrecarga <<
          ~DTReservaGrupal();
}; 

#endif