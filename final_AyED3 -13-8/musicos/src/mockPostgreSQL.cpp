#include "mockPostgreSQL.h"
#include <iostream>

void mockPostgreSQL::guardarFichaDeAtencion(const std::string& message) {
    std::cout << "Guardando ficha de atención en PostgreSQL: " << message << std::endl;
}

std::string mockPostgreSQL::getDatabaseType() const {
    return "PostgreSQL";
}
