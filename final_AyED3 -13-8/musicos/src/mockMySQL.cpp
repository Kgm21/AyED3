#include "mockMySQL.h"
#include <iostream>

void mockMySQL::guardarFichaDeAtencion(const std::string& message) {
    std::cout << "Guardando ficha de atención en MySQL: " << message << std::endl;
}

std::string mockMySQL::getDatabaseType() const {
    return "MySQL";
}
