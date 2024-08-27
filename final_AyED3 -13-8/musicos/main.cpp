#include <iostream>
#include "./include/centrodeSalud.h"
#include "./include/mockMySQL.h"
#include "./include/mockPostgreSQL.h"
#include "./include/FichaDeAtencion.h"
#include "./include/paciente.h"

int main() {
    IDatabase* db = new mockPostgreSQL();
    CentroDeSalud centro(db);
    
    int opcion;
    do {
        std::cout << "\nMenu Centro de Salud:\n";
        std::cout << "1. Crear paciente\n";
        std::cout << "2. Crear ficha de atencion  y cargar paciente a la cola de espera\n";
        std::cout << "3. Mostrar cola de pacientes\n";
        std::cout <<"4. Mostrar lista de atenciones de un paciente\n" ;
        std::cout << "0. Salir\n";
        std::cout << "Elija una opcion: ";
        std::cin >> opcion;
         

        switch(opcion) {
            case 1:
                centro.crearPaciente();
                break;
            case 2:
                centro.cargarYCrearFicha();
                break;
                
            case 3:
                centro.mostrarColaDePacientes();
                break;
             case 4:
                
                centro.mostrarAtencionesDePaciente();
                break;
            case 0:
            std::cout << "Saliendo del programa.\n";
                break;
            default:
                std::cout << "Opcion no valida. Intente de nuevo.\n";
        }
    } while (opcion != 0);
    
    delete db;
    return 0;
}
