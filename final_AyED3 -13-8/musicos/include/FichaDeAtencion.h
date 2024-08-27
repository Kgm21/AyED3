#ifndef FICHADEATENCION_H
#define FICHADEATENCION_H

#include <string>

// Declaración adelantada de la clase Paciente
class Paciente;

class FichaDeAtencion {
public:
    FichaDeAtencion(const std::string& fecha, const std::string& motivo, int id, Paciente* paciente);

    std::string getFecha() const;
    std::string getMotivo() const;
    int getId() const;
    Paciente* getPaciente() const;

private:
    std::string fecha;
    std::string motivo;
    int id;
    Paciente* paciente;
};

#endif
