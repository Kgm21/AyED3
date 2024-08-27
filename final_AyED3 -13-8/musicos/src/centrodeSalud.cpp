#include "../include/mockMySQL.h"
#include "../include/mockPostgreSQL.h"
#include "../include/FichaDeAtencion.h"
#include "../include/centrodeSalud.h"
#include "../include/paciente.h"
#include <limits>

CentroDeSalud::CentroDeSalud(IDatabase* database) : bd(database) {}

CentroDeSalud::~CentroDeSalud() {
    // Liberar la memoria de los pacientes
    for (auto paciente : pacientes) {
        delete paciente;
    }

    // Liberar la memoria de las fichas en la cola de atención
    while (!colaDeAtencion.empty()) {
        delete colaDeAtencion.front();
        colaDeAtencion.pop();
    }
}

void CentroDeSalud::crearPaciente() {
    std::string nombre, apellido, genero, numSeguroSocial, numeroDocumento;
    int edad;

    std::cout << "Ingrese número de documento: ";
    std::cin >> numeroDocumento;
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Limpiar el buffer después de std::cin

    std::cout << "Ingrese nombre: ";
    std::getline(std::cin, nombre);

    std::cout << "Ingrese apellido: ";
    std::getline(std::cin, apellido);

    std::cout << "Ingrese edad: ";
    while (!(std::cin >> edad) || edad < 0) {
        std::cout << "Edad no válida. Ingrese un número positivo: ";
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Limpiar el buffer después de std::cin

    std::cout << "Ingrese genero: ";
    std::getline(std::cin, genero);

    std::cout << "Ingrese numero de seguro social: ";
    std::getline(std::cin, numSeguroSocial);

    pacientes.push_back(new Paciente(nombre, apellido, edad, genero, numSeguroSocial, numeroDocumento));
    std::cout << "Paciente creado con exito.\n";

    std:: string tipo;
    std:: cout <<" selecciona una base de datos: ";
    std:: cout << "1. MySQL o 2. PostgreSQL\n";
    std:: getline(std::cin, tipo);
    seleccionarBaseDeDatos(tipo);
   

   // verificarPacientePorDocumento(numeroDocumento);
}

void CentroDeSalud::cargarYCrearFicha() {
    std::string numeroDocumento;
    std::cout << "Ingrese el numero de documento del paciente: ";
    std::cin >> numeroDocumento;
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Limpiar el buffer

    // Buscar el paciente en el vector
    auto it = std::find_if(pacientes.begin(), pacientes.end(),
        [&numeroDocumento](const Paciente* p) -> bool { return p->getNumDocumento() == numeroDocumento; });

    if (it != pacientes.end()) {
        Paciente* paciente = *it;
        std::cout << "Paciente encontrado:\n";
        std::cout << "Nombre: " << paciente->getNombre() << "\n";
        std::cout << "Apellido: " << paciente->getApellido() << "\n";

        // Crear una nueva ficha de atención para este paciente
        std::string fecha;
        std::string motivo;
        int id;

        std::cout << "Ingrese fecha de la nueva consulta (DD/MM/AAAA): ";
        std::getline(std::cin, fecha);

        std::cout << "Ingrese motivo de consulta: ";
        std::getline(std::cin, motivo);

        std::cout << "Ingrese ID para la ficha: ";
        while (!(std::cin >> id) || id < 0) {
            std::cout << "ID no válido. Ingrese un numero positivo: ";
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Limpiar el buffer después de std::cin

        // Crear la instancia de FichaDeAtencion
        FichaDeAtencion* nuevaFicha = new FichaDeAtencion(fecha, motivo, id, paciente);

        paciente->agregarFicha(nuevaFicha); // Agregar la ficha al paciente

        // Preguntar si se desea agregar a la cola de atención
        char respuesta;
        std::cout << "¿Desea agregar la ficha a la cola de atencion? (s/n): ";
        std::cin >> respuesta;

        if (respuesta == 's' || respuesta == 'S') {
            colaDeAtencion.push(nuevaFicha); // Se agrega a la cola de atención
            std::cout << "Ficha agregada a la cola de atencion.\n";
        } else {
            std::cout << "Ficha creada, pero no agregada a la cola de atencion.\n";
        }

    } else {
        std::cout << "Paciente no encontrado.\n";
    }
}



void CentroDeSalud::mostrarColaDePacientes() {
    std::cout << "Lista de espera de pacientes:\n";
    std::queue<FichaDeAtencion*> tempQueue = colaDeAtencion;

    if (tempQueue.empty()) {
        std::cout << "No hay pacientes en la lista de espera.\n";
    } else {
        while (!tempQueue.empty()) {
            FichaDeAtencion* ficha = tempQueue.front();
            Paciente* paciente = ficha->getPaciente(); // Obtener el paciente asociado
            std::cout << "Nombre: " << paciente->getNombre() << ", Apellido: " << paciente->getApellido() 
                      << ", DNI: " << paciente->getNumDocumento() << ", Fecha: " << ficha->getFecha() 
                      << ", Motivo: " << ficha->getMotivo() << std::endl;
            tempQueue.pop();
        }
    }
}



void CentroDeSalud::mostrarAtencionesDePaciente() {
    std::string numeroDocumento;
    std::cout << "Ingrese el número de documento del paciente: ";
    std::cin >> numeroDocumento;
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Limpiar el buffer

    // Buscar el paciente en el vector
    auto it = std::find_if(pacientes.begin(), pacientes.end(),
        [&numeroDocumento](const Paciente* p) -> bool { return p->getNumDocumento() == numeroDocumento; });

    if (it != pacientes.end()) {
        Paciente* paciente = *it;
        const std::vector<FichaDeAtencion*>& fichas = paciente->getFichas();

        if (fichas.empty()) {
            std::cout << "El paciente no tiene fichas de atención registradas.\n";
        } else {
            std::cout << "Atenciones del paciente " << paciente->getNombre() << " " << paciente->getApellido() << ":\n";
            for (const auto& ficha : fichas) {
                std::cout << "Fecha: " << ficha->getFecha() 
                          << ", Motivo: " << ficha->getMotivo() 
                          << ", ID: " << ficha->getId() << "\n";
            }
        }
    } else {
        std::cout << "Paciente con número de documento " << numeroDocumento << " no encontrado.\n";
    }
}


void CentroDeSalud::seleccionarBaseDeDatos(const std::string& tipo) {
    if (tipo == "1") {
        delete bd;
        bd = new mockMySQL;
    } else if (tipo == "2") {
        delete bd;
        bd = new mockPostgreSQL;
    } else {
        std::cout << "Tipo de base de datos no válido" << std::endl;
        return;
    }

    std::cout << "Base de datos seleccionada: " << bd->getDatabaseType() << std::endl;
}
