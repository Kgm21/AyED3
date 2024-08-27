#ifndef IDATABASE_H
#define IDATABASE_H

#pragma once
#include <string>

class IDatabase {
public:
    virtual void guardarFichaDeAtencion(const std::string& message) = 0;
    virtual std::string getDatabaseType() const = 0; // Método puro para obtener el tipo de base de datos
    virtual ~IDatabase() = default;
};

#endif // IDATABASE_H

    