#ifndef MOCKPOSTGRESQL_H
#define MOCKPOSTGRESQL_H

#include "IDatabase.h"
#include <string>
#include <iostream>
class mockPostgreSQL : public IDatabase {
public:
    // Implementación de los métodos de la interfaz IDatabase
    void guardarFichaDeAtencion(const std::string& message) override;
     std::string getDatabaseType() const override ;
    void elegirBdDatos(const std::string& base);
};

#endif
