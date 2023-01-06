//Funciones de utilidad general

#include <string>

#include "EstadoReserva.h"
#include "DTCargoEmpleado.h"
#include "DTFecha.h"

using namespace std;

int menorEntero(int A, int B);

float mayor(float A, float B);

string estadoReservaString(EstadoReserva e);

string CargoEmpleadoString(DTCargoEmpleado c);

//Recibe una fecha y devuelve en su lugar otra incrementada en un día
DTFecha sumarUnDia(DTFecha f);
