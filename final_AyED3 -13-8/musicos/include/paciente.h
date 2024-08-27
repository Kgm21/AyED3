#ifndef PACIENTE_H
#define PACIENTE_H

#include <string>
#include <vector>

// Incluye la declaración de la clase FichaDeAtencion
#include "FichaDeAtencion.h"

class Paciente {
public:
    // Constructor
    Paciente(const std::string& nombre, const std::string& apellido, int edad, const std::string& genero, const std::string& numSeguroSocial, const std::string& numDocumento);

    // Getters
    std::string getNombre() const;
    std::string getApellido() const;
    int getEdad() const;
    std::string getGenero() const;
    std::string getNumSeguroSocial() const;
    std::string getNumDocumento() const;

    // Método para agregar una ficha de atención
    void agregarFicha(FichaDeAtencion* ficha);

    // Método para obtener todas las fichas de atención
    const std::vector<FichaDeAtencion*>& getFichas() const;

private:
    std::string nombre;
    std::string apellido;
    int edad;
    std::string genero;
    std::string numSeguroSocial;
    std::string numDocumento;
    std::vector<FichaDeAtencion*> fichas; // Almacena las fichas de atención
};

#endif
