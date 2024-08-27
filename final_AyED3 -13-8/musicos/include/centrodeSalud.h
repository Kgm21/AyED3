#ifndef CENTRODEALUD_H
#define CENTRODEALUD_H

#include <string>
#include <vector>
#include <queue>
#include "Paciente.h"
#include "IDatabase.h"
#include <iostream>
#include <algorithm>

class CentroDeSalud {
public:
    CentroDeSalud(IDatabase* database);
    ~CentroDeSalud();

    void crearPaciente();
    void cargarYCrearFicha();
    void mostrarColaDePacientes();
    void verificarPacientePorDocumento(const std::string& numeroDocumento);
    void mostrarAtencionesDePaciente(); 
    
    void seleccionarBaseDeDatos(const std::string& tipo);

private:
    IDatabase* bd; //Permite que CentroDeSalud interactúe con la base de datos.
    std::vector<Paciente*> pacientes;
    std::queue<FichaDeAtencion*> colaDeAtencion;
};

#endif
