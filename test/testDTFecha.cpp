using namespace std;

#include <iostream>
#include <string>

#include "../include/DTFecha.h"


void imprimirFecha(DTFecha f){
    cout << f.getDia() << "/" << f.getMes() << "/" << f.getAnio() << " " << f.getHora() << " hs\n";
}

DTFecha fechaNula=DTFecha();
DTFecha * CrearFechaPorConsola(DTFecha cotaInferior){
     DTFecha* nueva;
     int d,m,a,h;
     bool cota = false;
     //while (nueva <= &cotaInferior){
     while ( !cota ){
          cout << "Ingrese el día: ";
          cin >> d;
          cout << "Ingrese el mes: ";
          cin >> m;
          cout << "Ingrese el año: ";
          cin >> a;
          cout << "Ingrese la hora: ";
          cin >> h;
          nueva = new DTFecha(d,m,a,h);
          
            imprimirFecha(*nueva);

          if (*nueva <= cotaInferior)
               throw invalid_argument("La fecha ingresada no es correcta o supera la cota fijada");
          else
               cota = true;
     }
     return nueva;
}

  
int main () {
    DTFecha *f1=NULL;
    DTFecha *f2=NULL;
    int a;
    do {
        cout << "\n1. Crear f1 \n";
        cout << "2. Crear f2 \n";
        cout << "3. Comparar\n";
        cout << "4. Ver fecha nula\n";
        cout << "5. \n";
        cout << "6. \n";
        cout << "7. \n";
        cout << "8. \n";
        cout << "9. Salir \n \n";

        cout << "Por favor elija una opción: ";
        cin >> a;

        //acá se puede hacer un chequeo de typos con typeid, porque si se manda como input otra cosa que no sea un int el programa se rompe
        
        switch (a) {
            case 1: 
                //cout << "Ingrese día mes y año (separados por espacios): ";
                //cin >> dia;
                //cin >> mes;
                //cin >> anio;
                //cin >> hora;
                try{ 
                    //f1=DTFecha(dia,mes,anio,hora); 
                    delete f1;
                    f1=CrearFechaPorConsola(fechaNula);
                }
                catch(const exception& e){
                    cout << e.what() << '\n';}
                break;

            case 2: 
                //cout << "Ingrese día mes y año (separados por espacios): ";
                //cin >> dia;
                //cin >> mes;
                //cin >> anio;
                //cin >> hora;
                try{ 
                    //f2=DTFecha(dia,mes,anio,hora); 
                    delete f2;
                    f2=CrearFechaPorConsola(fechaNula);
                }
                catch(const exception& e){
                    cout << e.what() << '\n';}
                break;

            case 3: 
                cout << ">>>RESULTADO: \n";
                if (f1==f2) cout << "f1 IGUAL A f2\n";
                if (f1!=f2) cout << "f1 DISTINTO A f2\n";
                if (f1<f2) cout << "f1 MENOR A f2\n";
                if (f1>f2) cout << "f1 MAYOR A f2\n";
                if (f1<=f2) cout << "f1 MENOR O IGUAL A f2\n";
                if (f1>=f2) cout << "f1 MAYOR O IGUAL A f2\n-----------------\n";
                    

                break;
            case 4: 
                if (f1>f2)
                    imprimirFecha(fechaNula);

                break;
  
            case 5: 
                if (f1!=f2)
                    cout << ">>>RESULTADO: ";
                    //cout << f1.toString();
                    cout << " DISTINTO A ";
                    //cout << f2.toString();"\n";

            
                break;
            case 6: 
                if (f1<=f2)
                    cout << ">>>RESULTADO: ";
                    //cout << f1.toString();
                    cout << " MENOR O IGUAL A ";
                    //cout << f2.toString();"\n";


                break;  
            case 7: 
                if (f1>=f2)
                    cout << ">>>RESULTADO: ";
                    cout << " MAYOR O IGUAL A ";
                    //cout << f2.toString();"\n";


                break;  
            case 8: 
                if (f1==f2)
                    cout << ">>>RESULTADO: ";
                    //cout << f1.toString();
                    cout << " IGUAL A ";
                    //cout << f2.toString();"\n";


                break;             
            case 9: cout << "Salida exitosa. \n";

                break;
            default: cout << "Por favor elija una opcion entre las disponibles: \n";

                break;
        };

    } while (a != 9);


    return 0;
};







