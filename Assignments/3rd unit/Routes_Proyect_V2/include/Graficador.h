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
    void generarPlanoInteractivo_trafico(const std::string& archivoHTML, const std::vector<Ubication>& ubicaciones, const std::vector<Route>& rutas, const std::string& imagenFondo, const std::string& hora);
    void generarPlanoInteractivo_rutaT(const std::string &archivoHTML, const std::vector<Ubication> &ubicaciones, const std::vector<Route> &rutas, const std::string &imagenFondo, const std::vector<Route>& rutaOptima);

};

#endif // GRAFICADOR_H