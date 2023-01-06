#include "../include/FechaSistema.h"
#include "../include/ControladorReservas.h"
#include "../include/ControladorHostal.h"
#include "../include/ControladorUsuarios.h"
#include "../include/ReservaIndividual.h"
#include "../include/ReservaGrupal.h"
#include "../include/Utils.h"
#include <iostream> //para testing

// CONSTRUCTOR
ControladorReservas * ControladorReservas::instancia = NULL;

ControladorReservas::ControladorReservas(){
     maxCodEstadiaExistente=0;
     maxCodReservaExistente=0;
};

ControladorReservas * ControladorReservas::getInstancia(){
     if( instancia == NULL )
          instancia = new ControladorReservas();
     return instancia;
};

// FUNCIONES

bool ControladorReservas::existeEstadia(int identificador){
     if(!this->estadias.empty()){
          if(this->estadias.find(identificador) != this->estadias.end()){
               return true;    
          } else return false;   
     } else return false;
} 


map<int, DTEstadia> ControladorReservas::estadiaActivaHuesped(string email, string nombreHostal) {

     map<int, DTEstadia> DTestadiasActivas;
     if(!this->estadias.empty()){
          map<int, Estadia*>::iterator iter = estadias.begin();
          while(iter != estadias.end()){
               if((iter->second->getHues()->getEmail() == email) && (iter->second->getRes()->getHabitacion()->getHostal()->getNombre() == nombreHostal) && (iter->second->getCheckOutEstadia() == NULL)){
               DTestadiasActivas.insert(map<int, DTEstadia>::value_type(iter->first, iter->second->getDatosEstadia()));
               }
               ++iter;
          }
     }
     return DTestadiasActivas;
}





void ControladorReservas::finalizarEstadiaActiva(int identificador, DTFecha *out) {

     Estadia* estAFinalizar = this->estadias.find(identificador)->second;
     estAFinalizar->setCheckOut(out);

}


Estadia* ControladorReservas::getEstadia(int identificador){
     return this->estadias.find(identificador)->second;
}

void ControladorReservas::elegirEstadia(int identificador){
     if(existeEstadia(identificador)){
          this->IdEstadia = identificador;    
     }
}

int ControladorReservas::getIdEstadia(){
     return this->IdEstadia;
}

map<int, DTEstadia> ControladorReservas::listarEstadiasHuesped(string email, string nombre){
     map<int, DTEstadia> DTestadias;
     if(!this->estadias.empty()){
          map<int, Estadia*>::iterator iter = estadias.begin();
          while(iter != estadias.end()){
               if((iter->second->getHues()->getEmail() != email) && (iter->second->getRes()->getHabitacion()->getHostal()->getNombre() != nombre) && (iter->second->getCheckOutEstadia() == NULL)){
                    ++iter;
               } else {
                    DTestadias.insert(map<int, DTEstadia>::value_type(iter->first, iter->second->getDatosEstadia()));
                    ++iter;
               }
          }
     }
     return DTestadias;
}

map<int, DTEstadia> ControladorReservas::listarEstadiasHostal(string nombre) {
     map<int, DTEstadia> ret;
     if (!this->estadias.empty()) {
          for (map<int, Estadia*>::iterator t = estadias.begin(); t != estadias.end(); ++t) {
               Estadia* actual = t->second;
               if (actual->getRes()->getHabitacion()->getHostal()->getNombre() == nombre) {
                    if (actual->getCal() ==  nullptr) {
                         cout << "NULL" << endl;
                    } else {
                         cout << actual->getCal()->getPuntuacion() << endl;
                    }
                    ret.insert(map<int, DTEstadia>::value_type(t->first, actual->getDatosEstadia()));
               }
          }
     }
     return ret;
};

DTEstadia ControladorReservas::mostrarDatosEstadia(int seleccion) {
     map<int, Estadia*>::iterator t = estadias.find(seleccion);
     DTEstadia ret = t->second->getDatosEstadia();
     return ret;
};

DTCalificacion ControladorReservas::verCalificaion(int seleccion, string &resp) {
     map<int, Estadia*>::iterator t = estadias.find(seleccion);
     if (t->second->getCal() == nullptr) {
          DTCalificacion ret(0, 0, nullptr, " ");
          return ret;
     } else {
          DTCalificacion ret = t->second->getCalificacion();
          resp = t->second->getCal()->getComentario();
          return ret;
     }
}

DTReserva ControladorReservas::reservaAsociada(int seleccion) {
     map<int, Estadia*>::iterator t = estadias.find(seleccion);
     DTReserva ret = t->second->getRes()->getDatosReserva();
     return ret;
};

map<int,Reserva*> ControladorReservas::getReservas(){
     return reservas;
};

int ControladorReservas::getCodReservaNuevo(){
     return maxCodReservaExistente++;
};

int ControladorReservas::getCodEstadiaNuevo(){
     return maxCodEstadiaExistente++;
};

int ControladorReservas::CamasDispEnHab(string nombreHostal,int numHab,DTFecha in, DTFecha out){
     ControladorHostal *ich=ControladorHostal::getInstancia();
     Habitacion* hab=ich->obtenerHabitacion(nombreHostal,numHab);
     //almacena las reservas de esa habitación
     map<int,Reserva*> resHabit;
     for (map<int,Reserva*>::iterator it=reservas.begin(); it!=reservas.end(); ++it)
          if (it->first==numHab)
               resHabit.insert(make_pair(it->second->getCodigo(),it->second));

     //va guardando el peor caso de camas disponibles
     int camasDisponibles=hab->getCapacidad();

     //Recorrer días desde in hasta out
     for (DTFecha x=in;x>&out;x=sumarUnDia(x)){
          //listar reservas en esa fecha
          map<int,Reserva*> reservasX;
          for (map<int,Reserva*>::iterator it=resHabit.begin(); it!=resHabit.end(); ++it)
               if (it->second->getCheckin()<=&in && it->second->getCheckOut()>=&out)
                    reservasX.insert(make_pair(it->second->getCodigo(),it->second));
          
          //recorrer lista y restar a capacidad para ese día las camas no disponibles
          int capacidadEseDia=camasDisponibles;
          for (map<int,Reserva*>::iterator it=reservasX.begin(); it!=reservasX.end(); ++it)
               capacidadEseDia = capacidadEseDia - it->second->cantidadDeEstadias();
          
          //elige el peor caso
          camasDisponibles=menorEntero(camasDisponibles,capacidadEseDia);
     }
          
     return camasDisponibles;
};

bool ControladorReservas::existeReserva(int c){
     return reservas.find(c)!=reservas.end();
};


void ControladorReservas::altaEstadia(int codReserva,string huespedQueReserva){
     //El último throw antes de saber que todo está en orden
     if (reservas.find(codReserva)==reservas.end())
          throw invalid_argument("El código de la reserva no es correcto");
     
     //Se sigue el diagrama de comunicación
     //1:
     FechaSistema* ifs=FechaSistema::getInstancia();
     //2:
     DTFecha fecha=ifs->getFechaSistema();
     //3:
     ControladorUsuarios* icu=ControladorUsuarios::getInstancia();
     Reserva* r=reservas.find(codReserva)->second;
     Huesped* h=icu->obtenerHuesped(huespedQueReserva);
     Estadia* e=new Estadia(r, h);
     //4:
     e->setReserva(r);
     e->setHuesped(h);
     estadias.insert(make_pair(e->getCodigo(),e));
     //5: cerrar reserva
     r->cerrarReserva();
};


void ControladorReservas::confirmarReservaIndividual(string nombreHostal, int numHab,string huespedQueReserva, DTFecha* checkin, DTFecha* checkout){
     //Se sigue el diagrama de comunicación del caso de uso Realizar Reserva
     //1:
     ControladorHostal *ich=ControladorHostal::getInstancia();
     if (!ich->existeHostal(nombreHostal))
          throw invalid_argument("El hostal no existe");
     //2:
     if (!ich->existeHabitacion(numHab,nombreHostal))
          throw invalid_argument("El habitacion no es correcta");
     //3:
     ControladorUsuarios* icu=ControladorUsuarios::getInstancia();
     if (!icu->existeHuesped(huespedQueReserva))
          throw invalid_argument("El huésped no es correcto");
     //4:
     maxCodReservaExistente++;
     Huesped* hues=icu->obtenerHuesped(huespedQueReserva);
     Habitacion* hab=ich->obtenerHabitacion(nombreHostal,numHab);
     
     int aux = getCodReservaNuevo();

     Reserva* r=new ReservaIndividual(aux,checkin,checkout,hues,hab);
     //5:
     icu->vincularReserva(r,huespedQueReserva);
     //6::
     reinterpret_cast<ReservaIndividual*>(r)->vincularReservaIndividual(hab,huespedQueReserva);

     this->reservas.insert(map<int,Reserva*>::value_type(aux, r));

     LiberarMemoria();
};

void ControladorReservas::confirmarReservaGrupal(string nombreHostal, int numHab,string huespedQueReserva, DTFecha* checkin, DTFecha* checkout,map<string,DTHuesped> conjuntoHuesp){
     //Se sigue el diagrama de comunicación del caso de uso Realizar Reserva
     //1:
     ControladorHostal *ich=ControladorHostal::getInstancia();
     if (!ich->existeHostal(nombreHostal))
          throw invalid_argument("El hostal no existe");
     //2:
     if (!ich->existeHabitacion(numHab,nombreHostal))
          throw invalid_argument("El habitacion no es correcta");
     //3:
     ControladorUsuarios* icu=ControladorUsuarios::getInstancia();
     if (!icu->existeHuesped(huespedQueReserva))
          throw invalid_argument("El huésped no es correcto");
     //4:
     maxCodReservaExistente++;
     Huesped* hues=icu->obtenerHuesped(huespedQueReserva);
     Habitacion* hab=ich->obtenerHabitacion(nombreHostal,numHab);
     //5:
     map<string,Huesped*> conjPunterosAHsp;
     for (map<string,DTHuesped>::iterator it=conjuntoHuesp.begin();it!=conjuntoHuesp.end();++it)
          conjPunterosAHsp.insert( make_pair(it->first,icu->obtenerHuesped(it->first)) );
     
     
     int aux = getCodReservaNuevo();
     
     Reserva* r=new ReservaGrupal(aux,checkin,checkout,hues,hab,conjPunterosAHsp);
     //6::
     reinterpret_cast<ReservaGrupal*>(r)->vincularReservaGrupal(hab,huespedQueReserva,conjPunterosAHsp);
     

     this->reservas.insert(map<int,Reserva*>::value_type(aux, r));

     LiberarMemoria();
};

void ControladorReservas::LiberarMemoria(){
     //SE REEMPLAZA MEMORIA DEL SISTEMA POR MEMORIA LOCAL EN MAIN PASAJE POR PARÁMETROS
     //memoriaReservas.checkin = memoriaReservas.checkout = NULL; //No se borra la instancia
     //memoriaReservas.huespedQueReserva="";
     //memoriaReservas.nombreHostal="";
     //memoriaReservas.numHabitacion=0;
     //memoriaReservas.habitacionElegida=0;
     //memoriaReservas.codReserva=0;
     //memoriaReservas.huespedDeLaReserva="";
};


//map<int,DTReserva> ControladorReservas::listarReservasHostal(string nombreHostal){
//     map<int,DTReserva> salida;
//
//     //Hay que discriminar que sean reservas del hostal nombreHostal
//     //for (map<int,Reserva*>::iterator it=reservas.begin(); it!=reservas.end(); ++it)
//     //     salida.insert(make_pair(it->first,it->second->getDatosReserva()));
//     
//     return salida;
//};

map<int,DTReserva> ControladorReservas::listarReservasHostalSeleccionado(string nombre){
     map<int,DTReserva> dr;
     for(map<int, Reserva*>::iterator iter = reservas.begin(); iter != reservas.end(); ++iter){
          if(iter->second->getHabitacion()->getHostal()->getNombre() == nombre)
               dr.insert(map<int, DTReserva>::value_type(iter->first, iter->second->getDatosReserva()));
     }
     return dr;
};

map<int,DTReserva> ControladorReservas::listarReservasHostalIndividual(string nombre){
     map<int,DTReserva> dr;
     for(map<int, Reserva*>::iterator iter = reservas.begin(); iter != reservas.end(); ++iter){
          if( iter->second->getHabitacion()->getHostal()->getNombre() == nombre ){
               if(ReservaIndividual* ri = dynamic_cast<ReservaIndividual*>(iter->second)){
                    dr.insert(map<int, DTReserva>::value_type(iter->first, ri->getDatosReserva()));
               }
          }
     }
     return dr;
};

map<int,DTReservaGrupal> ControladorReservas::listarReservasHostalGrupal(string nombre){
     map<int,DTReservaGrupal> dr;
     for(map<int, Reserva*>::iterator iter = reservas.begin(); iter != reservas.end(); ++iter){
          if(iter->second->getHabitacion()->getHostal()->getNombre() == nombre){
               if(ReservaGrupal* rg = dynamic_cast<ReservaGrupal*>(iter->second)){
                    dr.insert(map<int, DTReservaGrupal>::value_type(iter->first, rg->getDatosReservaGrupal()));
               }
          }
     }    
     return dr;
};

map<int,DTReserva> ControladorReservas::listarReservasNoCanceladasDelHuesped(string h){
     map<int,DTReserva> resultado;
     ControladorUsuarios* CUsu=ControladorUsuarios::getInstancia();
     map<int, Reserva *> todas=CUsu->obtenerHuesped(h)->getReservas();
     for (map<int, Reserva *>::iterator it=todas.begin();it!=todas.end();++it)
          if (it->second->getEstado()!=Cancelada)
               resultado.insert(make_pair(it->first,it->second->getDatosReserva()));
     return resultado;
};

void ControladorReservas::eliminarReserva(int codReserva){
     if (existeReserva(codReserva)){
          Reserva* r=reservas.find(codReserva)->second;
          r->eliminarEstadias();
          delete r;
     } else
          throw ("La reserva no existe");
};

void ControladorReservas::cancelarCreacionReserva(){
};


Estadia* ControladorReservas::DPRegistrarEstadia(Reserva* r,string emailHuesped,DTFecha *checkin){
//Se parece mucho alta estadia     
     //3:
     ControladorUsuarios* icu=ControladorUsuarios::getInstancia();
     Huesped* h=icu->obtenerHuesped(emailHuesped);
     Estadia* e=new Estadia(r, h,checkin);
     //4:
     e->setReserva(r);
     e->setHuesped(h);
     estadias.insert(make_pair(e->getCodigo(),e));
     //5: cerrar reserva
     if (r->getEstado() == 0) {
          r->cerrarReserva();
     }
     return e;
};


// DESTRUCTOR
ControladorReservas::~ControladorReservas(){}