#ifndef GRAFICADOR_H
#define GRAFICADOR_H

#include <string>
#include <vector>
#include "Ubication.h"
#include "Route.h"

class Graficador {
public:
    Graficador();
    void generarPlanoInteractivo(const std::string& archivoHTML, const std::vector<Ubication>& ubicaciones, const std::vector<Route>& rutas, const std::string& imagenFondo);
    void abrirPlanoEnNavegador(const std::string& archivoHTML);
};

#endif // GRAFICADOR_H