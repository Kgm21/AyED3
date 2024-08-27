#ifndef MOCKMYSQL_H
#define MOCKMYSQL_H

#include "IDatabase.h"
#include <string>
#include <iostream>

class mockMySQL : public IDatabase {
public:
    // Implementación de los métodos de la interfaz IDatabase
    void guardarFichaDeAtencion(const std::string& message) override;
    std::string getDatabaseType() const override ;
    void elegirBdDatos(const std::string& base);
};

#endif
