// FichaDeAtencion.cpp

#include "FichaDeAtencion.h"
#include "paciente.h"

FichaDeAtencion::FichaDeAtencion(const std::string& fecha, const std::string& motivo, int id, Paciente* paciente)
    : fecha(fecha), motivo(motivo), id(id), paciente(paciente) {}

std::string FichaDeAtencion::getFecha() const {
    return fecha;
}

std::string FichaDeAtencion::getMotivo() const {
    return motivo;
}

int FichaDeAtencion::getId() const {
    return id;
}

Paciente* FichaDeAtencion::getPaciente() const {
    return paciente;
}
