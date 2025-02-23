#include "../include/Grafo.h"
#include <iomanip>
#include <sstream>

Grafo::Grafo(const KD_Tree<Ubication>& kdTreeUbicaciones, const KD_Tree<Route>& kdTreeRutas) 
    : kdTreeUbicaciones(kdTreeUbicaciones), kdTreeRutas(kdTreeRutas) {
    construirGrafo(); // Construcción automática al crear el grafo
}

Grafo::~Grafo() {
    for (auto& par : nodos) {
        delete par.second;
    }
}

void Grafo::construirGrafo() {
    std::vector<Ubication> ubicaciones = kdTreeUbicaciones.obtenerTodasLasUbicaciones();
    for (const auto& ubicacion : ubicaciones) {
        agregarNodo(ubicacion);
    }

    std::vector<Route> rutas = kdTreeRutas.obtenerTodasLasRutas();
    for (const auto& ruta : rutas) {
        double tiempo = calcularTiempo(ruta.getDistance(), ruta.getTrafics(), "00:00", ruta.getSpeed());
        agregarArista(ruta.getInitialUbication().getName(), ruta.getLastUbication().getName(), tiempo, ruta.getTrafics());
    }
}

void Grafo::agregarNodo(const Ubication& ubicacion) {
    if (nodos.find(ubicacion.getName()) == nodos.end()) {
        nodos[ubicacion.getName()] = new Ubication(ubicacion);
    }
}

void Grafo::agregarArista(const std::string& nombreOrigen, const std::string& nombreDestino, double distancia, const std::vector<Trafic>& traficos) {
    if (nodos.find(nombreOrigen) != nodos.end() && nodos.find(nombreDestino) != nodos.end()) {
        adyacencias[nombreOrigen].push_back({nombreDestino, distancia});
        adyacencias[nombreDestino].push_back({nombreOrigen, distancia}); // Grafo bidireccional
    }
}

double Grafo::calcularTiempo(double distancia, const std::vector<Trafic>& traficos, const std::string& horaActual, double velocidadRuta) const {
    double velocidad = velocidadRuta; // Usar la velocidad específica de la ruta

    // Verificar si hay tráfico en la hora actual
    for (const auto& trafico : traficos) {
        if (horaActual >= trafico.getInitialHour() && horaActual <= trafico.getLastHour()) {
            switch (trafico.getLevel()) {
                case 1:
                    velocidad *= 0.7; // Reducción del 30%
                    break;
                case 2:
                    velocidad *= 0.5; // Reducción del 50%
                    break;
                case 3:
                    velocidad *= 0.15; // Reducción del 85%
                    break;
            }
        }
    }

    // Calcular el tiempo en horas
    return distancia / velocidad; // Tiempo en horas
}


std::string Grafo::sumarHoras(const std::string& horaActual, double horas) const {
    // Convertir la hora actual a horas desde la medianoche
    int h, m;
    char sep;
    std::istringstream iss(horaActual);
    iss >> h >> sep >> m;

    double totalHoras = h + m / 60.0 + horas;

    // Convertir de nuevo a formato HH:MM
    int nuevasHoras = static_cast<int>(totalHoras) % 24;
    int nuevosMinutos = static_cast<int>((totalHoras - nuevasHoras) * 60);

    std::ostringstream oss;
    oss << std::setw(2) << std::setfill('0') << nuevasHoras << ":"
        << std::setw(2) << std::setfill('0') << nuevosMinutos;
    return oss.str();
}

std::vector<Trafic> Grafo::obtenerTraficos(const std::string& origen, const std::string& destino) const {
    std::vector<Trafic> traficos;

    // Recorrer todas las rutas en el KD_Tree de rutas
    for (const auto& ruta : kdTreeRutas.obtenerTodasLasRutas()) {
        // Verificar si la ruta conecta las ubicaciones de origen y destino
        if (ruta.getInitialUbication().getName() == origen && ruta.getLastUbication().getName() == destino) {
            // Obtener los traficos de la ruta
            traficos = ruta.getTrafics();
            break; // Salir del bucle una vez encontrada la ruta
        }
    }

    return traficos; // Devolver los traficos (puede estar vacío si no hay traficos)
}

std::vector<Route> Grafo::dijkstraTiempo(const std::string& origen, const std::string& destino, const std::string& horaSalida) const {
    std::map<std::string, double> distancias; // Almacena la distancia mínima a cada nodo
    std::map<std::string, std::string> previos; // Almacena el nodo anterior en la ruta óptima
    std::map<std::string, std::string> horaLLegada; // Almacena la hora de llegada a cada nodo
    std::priority_queue<std::pair<double, std::string>, std::vector<std::pair<double, std::string>>, std::greater<>> cola;

    // Inicializar distancias con infinito, excepto el nodo de origen
    for (const auto& par : nodos) {
        distancias[par.first] = std::numeric_limits<double>::infinity();
    }
    distancias[origen] = 0.0;
    horaLLegada[origen] = horaSalida;
    cola.push(std::make_pair(0.0, origen));

    while (!cola.empty()) {
        std::string actual = cola.top().second;
        cola.pop();

        // Si llegamos al destino, terminar
        if (actual == destino) {
            break;
        }

        // Explorar los nodos adyacentes
        for (const auto& adyacente : adyacencias.at(actual)) {
            std::string vecino = adyacente.first;
            double distancia = adyacente.second;

            // Obtener los traficos de la ruta entre actual y vecino
            std::vector<Trafic> traficos = obtenerTraficos(actual, vecino);

            // Obtener la velocidad de la ruta
            double velocidadRuta = 0.0;
            Route rutaActual;
            for (const auto& ruta : kdTreeRutas.obtenerTodasLasRutas()) {
                if (ruta.getInitialUbication().getName() == actual && ruta.getLastUbication().getName() == vecino) {
                    velocidadRuta = ruta.getSpeed(); // Usar la velocidad de la ruta
                    rutaActual = ruta; // Guardar la ruta completa
                    break;
                }
            }

            // Calcular el tiempo de viaje en función de la hora de llegada al nodo actual
            double tiempo = calcularTiempo(distancia, traficos, horaLLegada[actual], velocidadRuta);

            // Calcular la hora de llegada al vecino
            std::string horaLLegadaVecino = sumarHoras(horaLLegada[actual], tiempo);

            // Si encontramos un camino más corto, actualizar distancias y previos
            if (distancias[vecino] > distancias[actual] + tiempo) {
                distancias[vecino] = distancias[actual] + tiempo;
                previos[vecino] = actual;
                horaLLegada[vecino] = horaLLegadaVecino;
                cola.push(std::make_pair(distancias[vecino], vecino));
            }
        }
    }

    // Reconstruir la ruta óptima como un vector de Route
    std::vector<Route> rutaOptima;
    for (std::string at = destino; at != origen; at = previos[at]) {
        std::string anterior = previos[at];

        // Buscar la ruta entre 'anterior' y 'at' en el grafo
        for (const auto& ruta : kdTreeRutas.obtenerTodasLasRutas()) {
            if (ruta.getInitialUbication().getName() == anterior && ruta.getLastUbication().getName() == at) {
                rutaOptima.push_back(ruta); // Agregar la ruta al vector
                break;
            }
        }
    }
    std::reverse(rutaOptima.begin(), rutaOptima.end());

    // Imprimir la ruta en el formato deseado
    if (!rutaOptima.empty()) {
        std::cout << "La ruta óptima para llegar desde " << origen << " hasta " << destino << " es:\n";
        std::string horaActual = horaSalida;
        double tiempoTotal = 0.0;

        for (const auto& ruta : rutaOptima) {
            std::string nodoActual = ruta.getInitialUbication().getName();
            std::string nodoSiguiente = ruta.getLastUbication().getName();
            double distancia = ruta.getDistance();
            double velocidadRuta = ruta.getSpeed();

            // Obtener los traficos de la ruta
            std::vector<Trafic> traficos = obtenerTraficos(nodoActual, nodoSiguiente);

            // Calcular el tiempo de viaje
            double tiempo = calcularTiempo(distancia, traficos, horaActual, velocidadRuta);

            // Imprimir el tramo
            std::cout << "Desde  " << nodoActual << ", seguir por " << ruta.getName()
                      << " durante " << distancia << " km hasta " << nodoSiguiente << ".\n";

            // Actualizar la hora actual y el tiempo total
            horaActual = sumarHoras(horaActual, tiempo);
            tiempoTotal += tiempo;
        }
        int horas = static_cast<int>(tiempoTotal); // Parte entera: horas
        int minutos = static_cast<int>((tiempoTotal - horas) * 60); // Parte decimal: minutos
        std::cout << "Tiempo total de viaje: " << horas << " horas, " << minutos << " minutos.\n";
    } else {
        std::cout << "No se encontró una ruta entre " << origen << " y " << destino << ".\n";
    }

    return rutaOptima;
}

std::vector<Route> Grafo::dijkstraD(const std::string& origen, const std::string& destino) const {
    std::map<std::string, double> distancias; // Almacena la distancia mínima a cada nodo
    std::map<std::string, std::string> previos; // Almacena el nodo anterior en la ruta óptima
    std::priority_queue<std::pair<double, std::string>, std::vector<std::pair<double, std::string>>, std::greater<>> cola;

    // Inicializar distancias con infinito, excepto el nodo de origen
    for (const auto& par : nodos) {
        distancias[par.first] = std::numeric_limits<double>::infinity();
    }
    distancias[origen] = 0.0;
    cola.push(std::make_pair(0.0, origen));

    while (!cola.empty()) {
        std::string actual = cola.top().second;
        cola.pop();

        // Si llegamos al destino, terminar
        if (actual == destino) {
            break;
        }

        // Explorar los nodos adyacentes
        for (const auto& adyacente : adyacencias.at(actual)) {
            std::string vecino = adyacente.first;
            double distancia = adyacente.second; // Usar la distancia directamente como peso

            // Si encontramos un camino más corto, actualizar distancias y previos
            if (distancias[vecino] > distancias[actual] + distancia) {
                distancias[vecino] = distancias[actual] + distancia;
                previos[vecino] = actual;
                cola.push(std::make_pair(distancias[vecino], vecino));
            }
        }
    }

    // Reconstruir la ruta óptima como un vector de Route
    std::vector<Route> rutaOptima;
    for (std::string at = destino; at != origen; at = previos[at]) {
        std::string anterior = previos[at];

        // Buscar la ruta entre 'anterior' y 'at' en el grafo
        for (const auto& ruta : kdTreeRutas.obtenerTodasLasRutas()) {
            if (ruta.getInitialUbication().getName() == anterior && ruta.getLastUbication().getName() == at) {
                rutaOptima.push_back(ruta); // Agregar la ruta al vector
                break;
            }
        }
    }
    std::reverse(rutaOptima.begin(), rutaOptima.end());

    // Imprimir la ruta en el formato deseado
    if (!rutaOptima.empty()) {
        std::cout << "La ruta más corta (por distancia) desde " << origen << " hasta " << destino << " es:\n";
        double distanciaTotal = 0.0;

        for (const auto& ruta : rutaOptima) {
            std::string nodoActual = ruta.getInitialUbication().getName();
            std::string nodoSiguiente = ruta.getLastUbication().getName();
            double distancia = ruta.getDistance();

            // Imprimir el tramo
            std::cout << "Desde  " << nodoActual << ", seguir por " << ruta.getName()
                      << " durante " << distancia << " km hasta " << nodoSiguiente << ".\n";

            // Actualizar la distancia total
            distanciaTotal += distancia;
        }

        // Imprimir la distancia total
        std::cout << "Distancia total de viaje: " << distanciaTotal << " km.\n";
    } else {
        std::cout << "No se encontró una ruta entre " << origen << " y " << destino << ".\n";
    }

    return rutaOptima;
}