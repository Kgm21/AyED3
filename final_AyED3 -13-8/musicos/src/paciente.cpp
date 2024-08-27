#include "Paciente.h"
#include "FichaDeAtencion.h" // Asegúrate de incluir esta cabecera para que la clase FichaDeAtencion sea conocida

// Constructor
Paciente::Paciente(const std::string& nombre, const std::string& apellido, int edad, const std::string& genero, const std::string& numSeguroSocial, const std::string& numDocumento)
    : nombre(nombre), apellido(apellido), edad(edad), genero(genero), numSeguroSocial(numSeguroSocial), numDocumento(numDocumento) {}

// Getters
std::string Paciente::getNombre() const {
    return nombre;
}

std::string Paciente::getApellido() const {
    return apellido;
}

int Paciente::getEdad() const {
    return edad;
}

std::string Paciente::getGenero() const {
    return genero;
}

std::string Paciente::getNumSeguroSocial() const {
    return numSeguroSocial;
}

std::string Paciente::getNumDocumento() const {
    return numDocumento;
}

// Método para agregar una ficha de atención
void Paciente::agregarFicha(FichaDeAtencion* ficha) {
    fichas.push_back(ficha);
}

// Método para obtener todas las fichas de atención
const std::vector<FichaDeAtencion*>& Paciente::getFichas() const {
    return fichas;
}
