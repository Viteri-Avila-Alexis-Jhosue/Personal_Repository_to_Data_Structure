#include "../include/Graficador.h"
#include <fstream>
#include <iostream>
#include <cstdlib>
#include <map>
#include <math.h>
#include <iomanip> // Para formatear la hora
#include <sstream>
#include <set>
#include <utility> // Para std::pair
#include <string>  // Para std::string

Graficador::Graficador() {}

void Graficador::abrirPlanoEnNavegador(const std::string &archivoHTML)
{
    std::string comando = "start " + archivoHTML;
    system(comando.c_str());
}

void Graficador::generarPlanoInteractivo(const std::string &archivoHTML, const std::vector<Ubication> &ubicaciones, const std::vector<Route> &rutas, const std::string &imagenFondo)
{
    std::ofstream htmlFile(archivoHTML);

    if (htmlFile.is_open())
    {
        // Configuración del plano
        int ancho = 1600; // Ancho del plano (aumentado para más espacio)
        int alto = 900;   // Alto del plano (aumentado para más espacio)
        int margen = 100; // Margen para que las ubicaciones no queden pegadas a los bordes

        // Escalar las coordenadas para que quepan en el plano
        double minX = ubicaciones[0].getX();
        double maxX = ubicaciones[0].getX();
        double minY = ubicaciones[0].getY();
        double maxY = ubicaciones[0].getY();

        for (const auto &ubicacion : ubicaciones)
        {
            if (ubicacion.getX() < minX)
                minX = ubicacion.getX();
            if (ubicacion.getX() > maxX)
                maxX = ubicacion.getX();
            if (ubicacion.getY() < minY)
                minY = ubicacion.getY();
            if (ubicacion.getY() > maxY)
                maxY = ubicacion.getY();
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
        htmlFile << "    <title>Mapa ciudad imaginaria</title>" << std::endl;
        htmlFile << "    <style>" << std::endl;
        htmlFile << "        body { margin: 0; padding: 0; background-color: black; }" << std::endl; // Fondo negro
        htmlFile << "        #plano { width: " << ancho << "px; height: " << alto << "px; border: 1px solid black; position: relative; background-image: url('" << imagenFondo << "'); background-size: cover; }" << std::endl;
        htmlFile << "        #capa-oscura { position: absolute; top: 0; left: 0; width: 100%; height: 100%; background-color: rgba(0, 0, 0, 0.5); }" << std::endl;                                                                  // Capa semitransparente oscura
        htmlFile << "        .punto { position: absolute; width: 10px; height: 10px; border-radius: 50%; cursor: pointer; z-index: 2; }" << std::endl;                                                                              // Asegurar que los puntos estén sobre la capa
        htmlFile << "        .coordenada { position: absolute; font-size: 12px; color: white; z-index: 2; }" << std::endl;                                                                                                          // Texto blanco
        htmlFile << "        .linea { position: absolute; height: 2px; background-color: #808080; transform-origin: 0 0; z-index: 1; cursor: pointer; }" << std::endl;                                                              // Líneas grises y un poco más anchas (2px)
        htmlFile << "        #panel { position: fixed; top: 20px; right: 20px; width: 300px; padding: 10px; background: rgba(255, 255, 255, 0.8); border: 1px solid #ccc; display: none; color: black; z-index: 3; }" << std::endl; // Panel semitransparente
        htmlFile << "        #cerrarPanel { position: absolute; top: 5px; right: 5px; cursor: pointer; font-size: 16px; }" << std::endl;                                                                                            // Botón de cierre
        htmlFile << "    </style>" << std::endl;
        htmlFile << "</head>" << std::endl;
        htmlFile << "<body>" << std::endl;
        htmlFile << "    <div id=\"plano\">" << std::endl;
        htmlFile << "        <div id=\"capa-oscura\"></div>" << std::endl; // Capa semitransparente oscura

        // Dibujar las rutas (tramos)
        for (size_t i = 0; i < rutas.size(); ++i)
        {
            const Route &ruta = rutas[i];
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

            htmlFile << "        <div class=\"linea\" id=\"linea" << i << "\" style=\"left: " << x1 << "px; top: " << y1 << "px; width: " << longitud << "px; transform: rotate(" << angulo << "deg);\""
                     << " onclick=\"mostrarInfoRuta('" << "Ruta:  " << ruta.getName() << "')\"></div>" << std::endl;
        }

        // Dibujar las ubicaciones como puntos
        for (size_t i = 0; i < ubicaciones.size(); ++i)
        {
            int x = margen + static_cast<int>((ubicaciones[i].getX() - minX) * escalaX);
            int y = alto - margen - static_cast<int>((ubicaciones[i].getY() - minY) * escalaY); // Invertir Y

            // Asignar un color único a cada punto
            std::string nombreUbicacion = ubicaciones[i].getName();
            if (coloresPuntos.find(nombreUbicacion) == coloresPuntos.end())
            {
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
        htmlFile << "        function mostrarInfoRuta(nombreRuta) {" << std::endl;
        htmlFile << "            document.getElementById('nombre').innerText = nombreRuta;" << std::endl;
        htmlFile << "            document.getElementById('descripcion').innerText = '';" << std::endl;
        htmlFile << "            document.getElementById('panel').style.display = 'block';" << std::endl;
        htmlFile << "        }" << std::endl;
        htmlFile << "        function cerrarPanel() {" << std::endl;
        htmlFile << "            document.getElementById('panel').style.display = 'none';" << std::endl;
        htmlFile << "        }" << std::endl;
        htmlFile << "    </script>" << std::endl;
        htmlFile << "</body>" << std::endl;
        htmlFile << "</html>" << std::endl;

        htmlFile.close();
    }
    else
    {
        std::cerr << "Error: No se pudo abrir el archivo HTML para escritura." << std::endl;
    }
}

// Función para convertir una hora en formato hh:mm:ss a segundos
int convertirHoraASegundos(const std::string &hora)
{
    int hh, mm, ss;
    char sep;
    std::istringstream iss(hora);
    iss >> hh >> sep >> mm >> sep >> ss;
    return hh * 3600 + mm * 60 + ss;
}

void Graficador::generarPlanoInteractivo_trafico(const std::string &archivoHTML, const std::vector<Ubication> &ubicaciones, const std::vector<Route> &rutas, const std::string &imagenFondo, const std::string &hora)
{
    std::ofstream htmlFile(archivoHTML);

    if (htmlFile.is_open())
    {
        // Configuración del plano
        int ancho = 1600; // Ancho del plano (aumentado para más espacio)
        int alto = 900;   // Alto del plano (aumentado para más espacio)
        int margen = 100; // Margen para que las ubicaciones no queden pegadas a los bordes

        // Escalar las coordenadas para que quepan en el plano
        double minX = ubicaciones[0].getX();
        double maxX = ubicaciones[0].getX();
        double minY = ubicaciones[0].getY();
        double maxY = ubicaciones[0].getY();

        for (const auto &ubicacion : ubicaciones)
        {
            if (ubicacion.getX() < minX)
                minX = ubicacion.getX();
            if (ubicacion.getX() > maxX)
                maxX = ubicacion.getX();
            if (ubicacion.getY() < minY)
                minY = ubicacion.getY();
            if (ubicacion.getY() > maxY)
                maxY = ubicacion.getY();
        }

        double escalaX = (ancho - 2 * margen) / (maxX - minX);
        double escalaY = (alto - 2 * margen) / (maxY - minY);

        // Mapa de colores para los puntos
        std::map<std::string, std::string> coloresPuntos;
        std::string colores[] = {"#FF0000", "#00FF00", "#0000FF", "#FF00FF", "#00FFFF", "#FFFF00", "#FFA500", "#800080"};
        int colorIndex = 0;

        // Convertir la hora de entrada a segundos
        int horaEnSegundos = convertirHoraASegundos(hora);

        // Escribir el contenido del archivo HTML
        htmlFile << "<!DOCTYPE html>" << std::endl;
        htmlFile << "<html>" << std::endl;
        htmlFile << "<head>" << std::endl;
        htmlFile << "    <title>Mapa ciudad imaginaria</title>" << std::endl;
        htmlFile << "    <style>" << std::endl;
        htmlFile << "        body { margin: 0; padding: 0; background-color: black; }" << std::endl; // Fondo negro
        htmlFile << "        #plano { width: " << ancho << "px; height: " << alto << "px; border: 1px solid black; position: relative; background-image: url('" << imagenFondo << "'); background-size: cover; }" << std::endl;
        htmlFile << "        #capa-oscura { position: absolute; top: 0; left: 0; width: 100%; height: 100%; background-color: rgba(0, 0, 0, 0.5); }" << std::endl;                                                                  // Capa semitransparente oscura
        htmlFile << "        .punto { position: absolute; width: 10px; height: 10px; border-radius: 50%; cursor: pointer; z-index: 2; }" << std::endl;                                                                              // Asegurar que los puntos estén sobre la capa
        htmlFile << "        .coordenada { position: absolute; font-size: 12px; color: white; z-index: 2; }" << std::endl;                                                                                                          // Texto blanco
        htmlFile << "        .linea { position: absolute; height: 2px; background-color: #808080; transform-origin: 0 0; z-index: 1; cursor: pointer; }" << std::endl;                                                              // Líneas grises y un poco más anchas (2px)
        htmlFile << "        #panel { position: fixed; top: 20px; right: 20px; width: 300px; padding: 10px; background: rgba(255, 255, 255, 0.8); border: 1px solid #ccc; display: none; color: black; z-index: 3; }" << std::endl; // Panel semitransparente
        htmlFile << "        #cerrarPanel { position: absolute; top: 5px; right: 5px; cursor: pointer; font-size: 16px; }" << std::endl;                                                                                            // Botón de cierre
        htmlFile << "        #leyenda { position: fixed; bottom: 20px; left: 20px; background: rgba(255, 255, 255, 0.8); padding: 10px; border: 1px solid #ccc; z-index: 3; }" << std::endl;                                        // Leyenda
        htmlFile << "        #cerrarLeyenda { position: absolute; top: 5px; right: 5px; cursor: pointer; font-size: 16px; color: black; }" << std::endl;                                                                           // Botón de cierre de la leyenda
        htmlFile << "        .color-box { display: inline-block; width: 20px; height: 20px; margin-right: 5px; }" << std::endl;                                                                                                     // Caja de color para la leyenda
        htmlFile << "    </style>" << std::endl;
        htmlFile << "</head>" << std::endl;
        htmlFile << "<body>" << std::endl;
        htmlFile << "    <div id=\"plano\">" << std::endl;
        htmlFile << "        <div id=\"capa-oscura\"></div>" << std::endl; // Capa semitransparente oscura

        // Dibujar las rutas (tramos)
        for (size_t i = 0; i < rutas.size(); ++i)
        {
            const Route &ruta = rutas[i];
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

            // Determinar el color basado en el nivel de tráfico más alto dentro del intervalo de hora
            std::string colorLinea = "#808080"; // Gris por defecto
            int maxTrafficLevel = 0;

            for (const auto &trafic : ruta.getTrafics())
            {
                int inicioTrafico = convertirHoraASegundos(trafic.getInitialHour());
                int finTrafico = convertirHoraASegundos(trafic.getLastHour());

                // Verificar si la hora está dentro del intervalo del tráfico
                if (horaEnSegundos >= inicioTrafico && horaEnSegundos <= finTrafico)
                {
                    if (trafic.getLevel() > maxTrafficLevel)
                    {
                        maxTrafficLevel = trafic.getLevel();
                    }
                }
            }

            // Asignar el color según el nivel de tráfico
            if (maxTrafficLevel == 3)
            {
                colorLinea = "#FF0000"; // Rojo para tráfico nivel 3
            }
            else if (maxTrafficLevel == 2)
            {
                colorLinea = "#FFA500"; // Naranja para tráfico nivel 2
            }
            else if (maxTrafficLevel == 1)
            {
                colorLinea = "#0000FF"; // Azul para tráfico nivel 1
            }

            // Dibujar la línea
            htmlFile << "        <div class=\"linea\" id=\"linea" << i << "\" style=\"left: " << x1 << "px; top: " << y1 << "px; width: " << longitud << "px; transform: rotate(" << angulo << "deg); background-color: " << colorLinea << ";\""
                     << " onclick=\"mostrarInfoRuta('" << ruta.getName() << "', " << maxTrafficLevel << ")\"></div>" << std::endl;
        }

        // Dibujar las ubicaciones como puntos
        for (size_t i = 0; i < ubicaciones.size(); ++i)
        {
            int x = margen + static_cast<int>((ubicaciones[i].getX() - minX) * escalaX);
            int y = alto - margen - static_cast<int>((ubicaciones[i].getY() - minY) * escalaY); // Invertir Y

            // Asignar un color único a cada punto
            std::string nombreUbicacion = ubicaciones[i].getName();
            if (coloresPuntos.find(nombreUbicacion) == coloresPuntos.end())
            {
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

        // Leyenda
        htmlFile << "    <div id=\"leyenda\">" << std::endl;
        htmlFile << "        <span id=\"cerrarLeyenda\" onclick=\"cerrarLeyenda()\">×</span>" << std::endl; // Botón de cierre
        htmlFile << "        <h3>Niveles de Tráfico</h3>" << std::endl;
        htmlFile << "        <div><span class=\"color-box\" style=\"background-color: #FF0000;\"></span>Tráfico alto</div>" << std::endl;
        htmlFile << "        <div><span class=\"color-box\" style=\"background-color: #FFA500;\"></span>Tráfico medio</div>" << std::endl;
        htmlFile << "        <div><span class=\"color-box\" style=\"background-color: #0000FF;\"></span>Tráfico bajo</div>" << std::endl;
        htmlFile << "        <div><span class=\"color-box\" style=\"background-color: #808080;\"></span>Sin tráfico</div>" << std::endl;
        htmlFile << "    </div>" << std::endl;

        // Panel de información
        htmlFile << "    <div id=\"panel\">" << std::endl;
        htmlFile << "        <span id=\"cerrarPanel\" onclick=\"cerrarPanel()\">×</span>" << std::endl; // Botón de cierre
        htmlFile << "        <h2 id=\"nombre\"></h2>" << std::endl;
        htmlFile << "        <p id=\"descripcion\"></p>" << std::endl;
        htmlFile << "    </div>" << std::endl;

        // Script para manejar el panel de información y la leyenda
        htmlFile << "    <script>" << std::endl;
        htmlFile << "        function mostrarInfo(nombre, descripcion) {" << std::endl;
        htmlFile << "            document.getElementById('nombre').innerText = nombre;" << std::endl;
        htmlFile << "            document.getElementById('descripcion').innerText = descripcion;" << std::endl;
        htmlFile << "            document.getElementById('panel').style.display = 'block';" << std::endl;
        htmlFile << "        }" << std::endl;
        htmlFile << "        function mostrarInfoRuta(nombreRuta, nivelTrafico) {" << std::endl;
        htmlFile << "            document.getElementById('nombre').innerText = nombreRuta;" << std::endl;
        htmlFile << "            if (nivelTrafico > 0) {" << std::endl;
        htmlFile << "                document.getElementById('descripcion').innerText = 'Nivel de tráfico: ' + nivelTrafico;" << std::endl;
        htmlFile << "            } else {" << std::endl;
        htmlFile << "                document.getElementById('descripcion').innerText = 'Sin tráfico en este tramo.';" << std::endl;
        htmlFile << "            }" << std::endl;
        htmlFile << "            document.getElementById('panel').style.display = 'block';" << std::endl;
        htmlFile << "        }" << std::endl;
        htmlFile << "        function cerrarPanel() {" << std::endl;
        htmlFile << "            document.getElementById('panel').style.display = 'none';" << std::endl;
        htmlFile << "        }" << std::endl;
        htmlFile << "        function cerrarLeyenda() {" << std::endl;
        htmlFile << "            document.getElementById('leyenda').style.display = 'none';" << std::endl;
        htmlFile << "        }" << std::endl;
        htmlFile << "    </script>" << std::endl;
        htmlFile << "</body>" << std::endl;
        htmlFile << "</html>" << std::endl;

        htmlFile.close();
    }
    else
    {
        std::cerr << "Error: No se pudo abrir el archivo HTML para escritura." << std::endl;
    }
}
void Graficador::generarPlanoInteractivo_rutaT(
    const std::string &archivoHTML,
    const std::vector<Ubication> &ubicaciones,
    const std::vector<Route> &rutas,
    const std::string &imagenFondo,
    const std::vector<Route>& rutaOptima)
{
    std::ofstream htmlFile(archivoHTML);

    if (htmlFile.is_open())
    {
        // Configuración del plano
        int ancho = 1600; // Ancho del plano (aumentado para más espacio)
        int alto = 900;   // Alto del plano (aumentado para más espacio)
        int margen = 100; // Margen para que las ubicaciones no queden pegadas a los bordes

        // Escalar las coordenadas para que quepan en el plano
        double minX = ubicaciones[0].getX();
        double maxX = ubicaciones[0].getX();
        double minY = ubicaciones[0].getY();
        double maxY = ubicaciones[0].getY();

        for (const auto &ubicacion : ubicaciones)
        {
            if (ubicacion.getX() < minX)
                minX = ubicacion.getX();
            if (ubicacion.getX() > maxX)
                maxX = ubicacion.getX();
            if (ubicacion.getY() < minY)
                minY = ubicacion.getY();
            if (ubicacion.getY() > maxY)
                maxY = ubicacion.getY();
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
        htmlFile << "    <title>Mapa ciudad imaginaria</title>" << std::endl;
        htmlFile << "    <style>" << std::endl;
        htmlFile << "        body { margin: 0; padding: 0; background-color: black; }" << std::endl; // Fondo negro
        htmlFile << "        #plano { width: " << ancho << "px; height: " << alto << "px; border: 1px solid black; position: relative; background-image: url('" << imagenFondo << "'); background-size: cover; }" << std::endl;
        htmlFile << "        #capa-oscura { position: absolute; top: 0; left: 0; width: 100%; height: 100%; background-color: rgba(0, 0, 0, 0.5); }" << std::endl;                                                                  // Capa semitransparente oscura
        htmlFile << "        .punto { position: absolute; width: 10px; height: 10px; border-radius: 50%; cursor: pointer; z-index: 2; }" << std::endl;                                                                              // Asegurar que los puntos estén sobre la capa
        htmlFile << "        .coordenada { position: absolute; font-size: 12px; color: white; z-index: 2; }" << std::endl;                                                                                                          // Texto blanco
        htmlFile << "        .linea { position: absolute; height: 2px; background-color: #808080; transform-origin: 0 0; z-index: 1; cursor: pointer; }" << std::endl;                                                              // Líneas grises y un poco más anchas (2px)
        htmlFile << "        .linea-optima { position: absolute; height: 2px; background-color:rgb(255, 87, 255); transform-origin: 0 0; z-index: 1; cursor: pointer; }" << std::endl;                                                       // Líneas púrpuras para la ruta óptima
        htmlFile << "        #panel { position: fixed; top: 20px; right: 20px; width: 300px; padding: 10px; background: rgba(255, 255, 255, 0.8); border: 1px solid #ccc; display: none; color: black; z-index: 3; }" << std::endl; // Panel semitransparente
        htmlFile << "        #cerrarPanel { position: absolute; top: 5px; right: 5px; cursor: pointer; font-size: 16px; }" << std::endl;                                                                                            // Botón de cierre
        htmlFile << "    </style>" << std::endl;
        htmlFile << "</head>" << std::endl;
        htmlFile << "<body>" << std::endl;
        htmlFile << "    <div id=\"plano\">" << std::endl;
        htmlFile << "        <div id=\"capa-oscura\"></div>" << std::endl; // Capa semitransparente oscura

        // Dibujar las rutas (tramos)
        for (size_t i = 0; i < rutas.size(); ++i)
        {
            const Route &ruta = rutas[i];
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

            // Verificar si esta ruta es parte de la ruta óptima
            bool esOptima = false;
            for (const auto& rutaOpt : rutaOptima) {
                if (rutaOpt.getInitialUbication().getName() == inicio.getName() &&
                    rutaOpt.getLastUbication().getName() == fin.getName()) {
                    esOptima = true;
                    break;
                }
            }

            // Desplazamiento perpendicular para rutas bidireccionales
            double desplazamiento = 0.30; // Desplazamiento reducido a 2 píxeles
            double anguloRadianes = angulo * M_PI / 180.0;
            double dxDesplazamiento = -desplazamiento * sin(anguloRadianes);
            double dyDesplazamiento = desplazamiento * cos(anguloRadianes);

            // Dibujar la línea con el color correspondiente
            htmlFile << "        <div class=\"" << (esOptima ? "linea-optima" : "linea") << "\" id=\"linea" << i << "\" style=\"left: " << x1 + dxDesplazamiento << "px; top: " << y1 + dyDesplazamiento << "px; width: " << longitud << "px; transform: rotate(" << angulo << "deg);\""
                     << " onclick=\"mostrarInfoRuta('" << "Ruta:  " << ruta.getName() << "')\"></div>" << std::endl;
        }

        // Dibujar las ubicaciones como puntos
        for (size_t i = 0; i < ubicaciones.size(); ++i)
        {
            int x = margen + static_cast<int>((ubicaciones[i].getX() - minX) * escalaX);
            int y = alto - margen - static_cast<int>((ubicaciones[i].getY() - minY) * escalaY); // Invertir Y

            // Asignar un color único a cada punto
            std::string nombreUbicacion = ubicaciones[i].getName();
            if (coloresPuntos.find(nombreUbicacion) == coloresPuntos.end())
            {
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
        htmlFile << "        function mostrarInfoRuta(nombreRuta) {" << std::endl;
        htmlFile << "            document.getElementById('nombre').innerText = nombreRuta;" << std::endl;
        htmlFile << "            document.getElementById('descripcion').innerText = '';" << std::endl;
        htmlFile << "            document.getElementById('panel').style.display = 'block';" << std::endl;
        htmlFile << "        }" << std::endl;
        htmlFile << "        function cerrarPanel() {" << std::endl;
        htmlFile << "            document.getElementById('panel').style.display = 'none';" << std::endl;
        htmlFile << "        }" << std::endl;
        htmlFile << "    </script>" << std::endl;
        htmlFile << "</body>" << std::endl;
        htmlFile << "</html>" << std::endl;

        htmlFile.close();
    }
    else
    {
        std::cerr << "Error: No se pudo abrir el archivo HTML para escritura." << std::endl;
    }
}