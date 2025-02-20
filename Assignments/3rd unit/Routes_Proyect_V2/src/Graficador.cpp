#include "../include/Graficador.h"
#include <fstream>
#include <iostream>
#include <cstdlib> // Para system()
#include <map>     // Para manejar colores por ruta
#include <math.h>

Graficador::Graficador() {
    // Constructor vacío (por ahora)
}

void Graficador::abrirPlanoEnNavegador(const std::string& archivoHTML) {
    std::string comando = "start " + archivoHTML; // Para Windows
    // std::string comando = "xdg-open " + archivoHTML; // Para Linux
    system(comando.c_str());
}

void Graficador::generarPlanoInteractivo(const std::string& archivoHTML, const std::vector<Ubication>& ubicaciones, const std::vector<Route>& rutas, const std::string& imagenFondo) {
    std::ofstream htmlFile(archivoHTML);

    if (htmlFile.is_open()) {
        // Configuración del plano
        int ancho = 1600;  // Ancho del plano (aumentado para más espacio)
        int alto = 900;     // Alto del plano (aumentado para más espacio)
        int margen = 100;   // Margen para que las ubicaciones no queden pegadas a los bordes

        // Escalar las coordenadas para que quepan en el plano
        double minX = ubicaciones[0].getX();
        double maxX = ubicaciones[0].getX();
        double minY = ubicaciones[0].getY();
        double maxY = ubicaciones[0].getY();

        for (const auto& ubicacion : ubicaciones) {
            if (ubicacion.getX() < minX) minX = ubicacion.getX();
            if (ubicacion.getX() > maxX) maxX = ubicacion.getX();
            if (ubicacion.getY() < minY) minY = ubicacion.getY();
            if (ubicacion.getY() > maxY) maxY = ubicacion.getY();
        }

        double escalaX = (ancho - 2 * margen) / (maxX - minX);
        double escalaY = (alto - 2 * margen) / (maxY - minY);

        // Mapa de colores para los puntos
        std::map<std::string, std::string> coloresPuntos;
        std::string colores[] = {"#FF0000", "#00FF00", "#0000FF", "#FF00FF", "#00FFFF", "#FFFF00", "#FFA500", "#800080"};
        int colorIndex = 0;

        // Escribir el contenido del archivo HTML
        htmlFile << "<!DOCTYPE html>" << std::endl;
        htmlFile << "<html>" << std::endl;
        htmlFile << "<head>" << std::endl;
        htmlFile << "    <title>Plano Interactivo</title>" << std::endl;
        htmlFile << "    <style>" << std::endl;
        htmlFile << "        body { margin: 0; padding: 0; background-color: black; }" << std::endl; // Fondo negro
        htmlFile << "        #plano { width: " << ancho << "px; height: " << alto << "px; border: 1px solid black; position: relative; background-image: url('" << imagenFondo << "'); background-size: cover; }" << std::endl;
        htmlFile << "        #capa-oscura { position: absolute; top: 0; left: 0; width: 100%; height: 100%; background-color: rgba(0, 0, 0, 0.5); }" << std::endl; // Capa semitransparente oscura
        htmlFile << "        .punto { position: absolute; width: 10px; height: 10px; border-radius: 50%; cursor: pointer; z-index: 2; }" << std::endl; // Asegurar que los puntos estén sobre la capa
        htmlFile << "        .coordenada { position: absolute; font-size: 12px; color: white; z-index: 2; }" << std::endl; // Texto blanco
        htmlFile << "        .linea { position: absolute; height: 2px; background-color: #808080; transform-origin: 0 0; z-index: 1; }" << std::endl; // Líneas grises y un poco más anchas (2px)
        htmlFile << "        #panel { position: fixed; top: 20px; right: 20px; width: 300px; padding: 10px; background: rgba(255, 255, 255, 0.8); border: 1px solid #ccc; display: none; color: black; z-index: 3; }" << std::endl; // Panel semitransparente
        htmlFile << "        #cerrarPanel { position: absolute; top: 5px; right: 5px; cursor: pointer; font-size: 16px; }" << std::endl; // Botón de cierre
        htmlFile << "    </style>" << std::endl;
        htmlFile << "</head>" << std::endl;
        htmlFile << "<body>" << std::endl;
        htmlFile << "    <div id=\"plano\">" << std::endl;
        htmlFile << "        <div id=\"capa-oscura\"></div>" << std::endl; // Capa semitransparente oscura

        // Dibujar las rutas (tramos)
        for (const auto& ruta : rutas) {
            Ubication inicio = ruta.getInitialUbication();
            Ubication fin = ruta.getLastUbication();

            int x1 = margen + static_cast<int>((inicio.getX() - minX) * escalaX);
            int y1 = alto - margen - static_cast<int>((inicio.getY() - minY) * escalaY);
            int x2 = margen + static_cast<int>((fin.getX() - minX) * escalaX);
            int y2 = alto - margen - static_cast<int>((fin.getY() - minY) * escalaY);

            // Calcular la longitud y el ángulo de la línea
            double dx = x2 - x1;
            double dy = y2 - y1;
            double longitud = sqrt(dx * dx + dy * dy);
            double angulo = atan2(dy, dx) * 180 / M_PI;

            htmlFile << "        <div class=\"linea\" style=\"left: " << x1 << "px; top: " << y1 << "px; width: " << longitud << "px; transform: rotate(" << angulo << "deg);\"></div>" << std::endl;
        }

        // Dibujar las ubicaciones como puntos
        for (size_t i = 0; i < ubicaciones.size(); ++i) {
            int x = margen + static_cast<int>((ubicaciones[i].getX() - minX) * escalaX);
            int y = alto - margen - static_cast<int>((ubicaciones[i].getY() - minY) * escalaY); // Invertir Y

            // Asignar un color único a cada punto
            std::string nombreUbicacion = ubicaciones[i].getName();
            if (coloresPuntos.find(nombreUbicacion) == coloresPuntos.end()) {
                coloresPuntos[nombreUbicacion] = colores[colorIndex % 8]; // Asignar un color único
                colorIndex++;
            }

            // Punto
            htmlFile << "        <div class=\"punto\" style=\"left: " << x << "px; top: " << y << "px; background-color: " << coloresPuntos[nombreUbicacion] << ";\""
                     << " onclick=\"mostrarInfo('" << ubicaciones[i].getName() << "', '" << ubicaciones[i].getDescription() << "')\"></div>" << std::endl;

            // Coordenada
            htmlFile << "        <div class=\"coordenada\" style=\"left: " << x - 10 << "px; top: " << y - 20 << "px;\">"
                     << "(" << ubicaciones[i].getX() << ", " << ubicaciones[i].getY() << ")</div>" << std::endl;
        }

        htmlFile << "    </div>" << std::endl;
        htmlFile << "    <div id=\"panel\">" << std::endl;
        htmlFile << "        <span id=\"cerrarPanel\" onclick=\"cerrarPanel()\">×</span>" << std::endl; // Botón de cierre
        htmlFile << "        <h2 id=\"nombre\"></h2>" << std::endl;
        htmlFile << "        <p id=\"descripcion\"></p>" << std::endl;
        htmlFile << "    </div>" << std::endl;
        htmlFile << "    <script>" << std::endl;
        htmlFile << "        function mostrarInfo(nombre, descripcion) {" << std::endl;
        htmlFile << "            document.getElementById('nombre').innerText = nombre;" << std::endl;
        htmlFile << "            document.getElementById('descripcion').innerText = descripcion;" << std::endl;
        htmlFile << "            document.getElementById('panel').style.display = 'block';" << std::endl;
        htmlFile << "        }" << std::endl;
        htmlFile << "        function cerrarPanel() {" << std::endl;
        htmlFile << "            document.getElementById('panel').style.display = 'none';" << std::endl;
        htmlFile << "        }" << std::endl;
        htmlFile << "    </script>" << std::endl;
        htmlFile << "</body>" << std::endl;
        htmlFile << "</html>" << std::endl;

        htmlFile.close();
    } else {
        std::cerr << "Error: No se pudo abrir el archivo HTML para escritura." << std::endl;
    }
}