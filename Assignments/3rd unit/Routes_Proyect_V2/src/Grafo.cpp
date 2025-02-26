#include "../include/Grafo.h"
#include <unordered_set>
#include <iomanip>
#include <sstream>
#include <algorithm>
#include <climits>

Grafo::Grafo(const KD_Tree<Ubication> &kdTreeUbicaciones, const KD_Tree<Route> &kdTreeRutas)
    : kdTreeUbicaciones(kdTreeUbicaciones), kdTreeRutas(kdTreeRutas)
{
    construirGrafo(); // Construcción automática al crear el grafo
}

Grafo::~Grafo()
{
    for (auto &par : nodos)
    {
        delete par.second;
    }
}

void Grafo::construirGrafo()
{
    std::vector<Ubication> ubicaciones = kdTreeUbicaciones.obtenerTodasLasUbicaciones();
    for (const auto &ubicacion : ubicaciones)
    {
        agregarNodo(ubicacion);
    }

    std::vector<Route> rutas = kdTreeRutas.obtenerTodasLasRutas();
    for (const auto &ruta : rutas)
    {
        double tiempo = calcularTiempo(ruta.getDistance(), ruta.getTrafics(), "00:00", ruta.getSpeed());
        agregarArista(ruta.getInitialUbication().getName(), ruta.getLastUbication().getName(), tiempo, ruta.getTrafics());
    }
}

void Grafo::agregarNodo(const Ubication &ubicacion)
{
    if (nodos.find(ubicacion.getName()) == nodos.end())
    {
        nodos[ubicacion.getName()] = new Ubication(ubicacion);
    }
}

void Grafo::agregarArista(const std::string &nombreOrigen, const std::string &nombreDestino, double distancia, const std::vector<Trafic> &traficos)
{
    if (nodos.find(nombreOrigen) != nodos.end() && nodos.find(nombreDestino) != nodos.end())
    {
        adyacencias[nombreOrigen].push_back({nombreDestino, distancia});
        adyacencias[nombreDestino].push_back({nombreOrigen, distancia}); // Grafo bidireccional
    }
}

double Grafo::calcularTiempo(double distancia, const std::vector<Trafic> &traficos, const std::string &horaActual, double velocidadRuta) const
{
    double velocidad = velocidadRuta; // Usar la velocidad específica de la ruta

    // Verificar si hay tráfico en la hora actual
    for (const auto &trafico : traficos)
    {
        if (horaActual >= trafico.getInitialHour() && horaActual <= trafico.getLastHour())
        {
            switch (trafico.getLevel())
            {
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
    return distancia / velocidad; // Tiempo en horas
}

std::string Grafo::sumarHoras(const std::string &horaActual, double horas) const
{
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

std::vector<Trafic> Grafo::obtenerTraficos(const std::string &origen, const std::string &destino) const
{
    std::vector<Trafic> traficos;

    // Recorrer todas las rutas en el KD_Tree de rutas
    for (const auto &ruta : kdTreeRutas.obtenerTodasLasRutas())
    {
        // Verificar si la ruta conecta las ubicaciones de origen y destino
        if (ruta.getInitialUbication().getName() == origen && ruta.getLastUbication().getName() == destino)
        {
            // Obtener los traficos de la ruta
            traficos = ruta.getTrafics();
            break; // Salir del bucle una vez encontrada la ruta
        }
    }

    return traficos; // Devolver los traficos (puede estar vacío si no hay traficos)
}

std::vector<Route> Grafo::dijkstraTiempo(const std::string &origen, const std::string &destino, const std::string &horaSalida) const
{
    std::map<std::string, double> distancias;
    std::map<std::string, std::string> previos;
    std::map<std::string, std::string> horaLLegada;
    std::priority_queue<std::pair<double, std::string>, std::vector<std::pair<double, std::string>>, std::greater<>> cola;

    for (const auto &par : nodos)
    {
        distancias[par.first] = std::numeric_limits<double>::infinity();
    }
    distancias[origen] = 0.0;
    horaLLegada[origen] = horaSalida;
    cola.push(std::make_pair(0.0, origen));

    while (!cola.empty())
    {
        std::string actual = cola.top().second;
        cola.pop();

        if (actual == destino)
        {
            break;
        }

        auto it = adyacencias.find(actual);
        if (it == adyacencias.end())
        {
            std::cerr << "Error: El nodo " << actual << " no tiene adyacencias registradas.\n";
            continue;
        }

        for (const auto &adyacente : it->second)
        {
            std::string vecino = adyacente.first;
            double distancia = adyacente.second;

            std::vector<Trafic> traficos;
            try
            {
                traficos = obtenerTraficos(actual, vecino);
            }
            catch (const std::out_of_range &e)
            {
                std::cerr << "Error: No se encontraron datos de tráfico entre " << actual << " y " << vecino << ".\n";
                continue;
            }

            double velocidadRuta = 0.0;
            Route rutaActual;
            for (const auto &ruta : kdTreeRutas.obtenerTodasLasRutas())
            {
                if (ruta.getInitialUbication().getName() == actual && ruta.getLastUbication().getName() == vecino)
                {
                    velocidadRuta = ruta.getSpeed();
                    rutaActual = ruta;
                    break;
                }
            }

            double tiempo = calcularTiempo(distancia, traficos, horaLLegada[actual], velocidadRuta);
            std::string horaLLegadaVecino = sumarHoras(horaLLegada[actual], tiempo);

            if (distancias[vecino] > distancias[actual] + tiempo)
            {
                distancias[vecino] = distancias[actual] + tiempo;
                previos[vecino] = actual;
                horaLLegada[vecino] = horaLLegadaVecino;
                cola.push(std::make_pair(distancias[vecino], vecino));
            }
        }
    }

    if (previos.find(destino) == previos.end())
    {
        std::cout << "No se encontró una ruta entre " << origen << " y " << destino << ".\n";
        return {};
    }

    std::vector<Route> rutaOptima;
    for (std::string at = destino; at != origen; at = previos[at])
    {
        std::string anterior = previos[at];

        for (const auto &ruta : kdTreeRutas.obtenerTodasLasRutas())
        {
            if (ruta.getInitialUbication().getName() == anterior && ruta.getLastUbication().getName() == at)
            {
                rutaOptima.push_back(ruta);
                break;
            }
        }
    }
    std::reverse(rutaOptima.begin(), rutaOptima.end());

    if (!rutaOptima.empty())
    {
        std::cout << "La ruta óptima para llegar desde " << origen << " hasta " << destino << " es:\n";
        std::string horaActual = horaSalida;
        double tiempoTotal = 0.0;

        for (const auto &ruta : rutaOptima)
        {
            std::string nodoActual = ruta.getInitialUbication().getName();
            std::string nodoSiguiente = ruta.getLastUbication().getName();
            double distancia = ruta.getDistance();
            double velocidadRuta = ruta.getSpeed();

            std::vector<Trafic> traficos = obtenerTraficos(nodoActual, nodoSiguiente);

            double tiempo = calcularTiempo(distancia, traficos, horaActual, velocidadRuta);

            std::cout << "Desde  " << nodoActual << ", seguir por " << ruta.getName()
                      << " durante " << distancia << " km hasta " << nodoSiguiente << ".\n";

            horaActual = sumarHoras(horaActual, tiempo);
            tiempoTotal += tiempo;
        }
        int horas = static_cast<int>(tiempoTotal);
        int minutos = static_cast<int>((tiempoTotal - horas) * 60);
        std::cout << "Tiempo total de viaje: " << horas << " horas, " << minutos << " minutos.\n";
    }
    else
    {
        std::cout << "No se encontró una ruta entre " << origen << " y " << destino << ".\n";
    }

    return rutaOptima;
}

std::vector<Route> Grafo::dijkstraD(const std::string &origen, const std::string &destino) const
{
    std::map<std::string, double> distancias;   // Almacena la distancia mínima a cada nodo
    std::map<std::string, std::string> previos; // Almacena el nodo anterior en la ruta óptima
    std::priority_queue<std::pair<double, std::string>, std::vector<std::pair<double, std::string>>, std::greater<>> cola;

    // Inicializar distancias con infinito, excepto el nodo de origen
    for (const auto &par : nodos)
    {
        distancias[par.first] = std::numeric_limits<double>::infinity();
    }
    distancias[origen] = 0.0;
    cola.push(std::make_pair(0.0, origen));

    while (!cola.empty())
    {
        std::string actual = cola.top().second;
        cola.pop();

        // Si llegamos al destino, terminar
        if (actual == destino)
        {
            break;
        }

        // Verificar si el nodo actual tiene adyacencias
        auto it = adyacencias.find(actual);
        if (it == adyacencias.end())
        {
            std::cerr << "Advertencia: El nodo " << actual << " no tiene adyacencias registradas.\n";
            continue; // Saltar este nodo si no tiene adyacencias
        }

        // Explorar los nodos adyacentes
        for (const auto &adyacente : it->second)
        {
            std::string vecino = adyacente.first;
            double distancia = adyacente.second; // Usar la distancia directamente como peso

            // Si encontramos un camino más corto, actualizar distancias y previos
            if (distancias[vecino] > distancias[actual] + distancia)
            {
                distancias[vecino] = distancias[actual] + distancia;
                previos[vecino] = actual;
                cola.push(std::make_pair(distancias[vecino], vecino));
            }
        }
    }

    // Verificar si se encontró una ruta al destino
    if (previos.find(destino) == previos.end())
    {
        std::cout << "No se encontró una ruta entre " << origen << " y " << destino << ".\n";
        return {}; // Retornar un vector vacío si no hay ruta
    }

    // Reconstruir la ruta óptima como un vector de Route
    std::vector<Route> rutaOptima;
    for (std::string at = destino; at != origen; at = previos[at])
    {
        std::string anterior = previos[at];

        // Buscar la ruta entre 'anterior' y 'at' en el grafo
        bool rutaEncontrada = false;
        for (const auto &ruta : kdTreeRutas.obtenerTodasLasRutas())
        {
            if (ruta.getInitialUbication().getName() == anterior && ruta.getLastUbication().getName() == at)
            {
                rutaOptima.push_back(ruta); // Agregar la ruta al vector
                rutaEncontrada = true;
                break;
            }
        }

        // Si no se encuentra la ruta, mostrar un mensaje de advertencia
        if (!rutaEncontrada)
        {
            std::cerr << "Advertencia: No se encontró una ruta registrada entre " << anterior << " y " << at << ".\n";
        }
    }
    std::reverse(rutaOptima.begin(), rutaOptima.end());

    // Imprimir la ruta en el formato deseado
    if (!rutaOptima.empty())
    {
        std::cout << "La ruta más corta (por distancia) desde " << origen << " hasta " << destino << " es:\n";
        double distanciaTotal = 0.0;

        for (const auto &ruta : rutaOptima)
        {
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
    }
    else
    {
        std::cout << "No se encontró una ruta entre " << origen << " y " << destino << ".\n";
    }

    return rutaOptima;
}

std::vector<Route> Grafo::calcularRutaOptimaVariosPuntosDistancia(const std::vector<std::string> &puntos) const
{
    if (puntos.size() < 2)
    {
        std::cerr << "Error: Se necesitan al menos dos puntos para calcular una ruta.\n";
        return {};
    }

    auto calcularDistanciaYRuta = [&](const std::string &origen, const std::string &destino)
        -> std::pair<double, std::vector<Route>>
    {
        std::map<std::string, double> distancias;
        std::priority_queue<std::pair<double, std::string>, std::vector<std::pair<double, std::string>>, std::greater<>> cola;
        std::map<std::string, std::string> previos;

        // Inicializar distancias con infinito, excepto el nodo de origen
        for (const auto &par : nodos)
        {
            distancias[par.first] = std::numeric_limits<double>::infinity();
        }
        distancias[origen] = 0.0;
        cola.push(std::make_pair(0.0, origen));

        while (!cola.empty())
        {
            std::string actual = cola.top().second;
            cola.pop();

            if (actual == destino)
            {
                break;
            }

            // Explorar los nodos adyacentes
            for (const auto &adyacente : adyacencias.at(actual))
            {
                std::string vecino = adyacente.first;
                double distancia = adyacente.second;

                // Si encontramos un camino más corto, actualizar distancias
                if (distancias[vecino] > distancias[actual] + distancia)
                {
                    distancias[vecino] = distancias[actual] + distancia;
                    previos[vecino] = actual;
                    cola.push(std::make_pair(distancias[vecino], vecino));
                }
            }
        }

        // Reconstruir la ruta detallada como un vector de Route
        std::vector<Route> rutaDetallada;
        for (std::string at = destino; at != origen; at = previos[at])
        {
            std::string anterior = previos[at];

            bool rutaEncontrada = false;
            for (const auto &ruta : kdTreeRutas.obtenerTodasLasRutas())
            {
                if (ruta.getInitialUbication().getName() == anterior && ruta.getLastUbication().getName() == at)
                {
                    rutaDetallada.push_back(ruta);
                    rutaEncontrada = true;
                    break;
                }
            }

            if (!rutaEncontrada)
            {
                std::cerr << "Advertencia: No se encontró una ruta registrada entre " << anterior << " y " << at << ".\n";
            }
        }
        std::reverse(rutaDetallada.begin(), rutaDetallada.end());

        // Devolver la distancia total y la ruta detallada
        return {distancias[destino], rutaDetallada};
    };

    // Inicializar variables
    std::vector<Route> rutaOptima;
    std::unordered_set<std::string> visitados;
    double distanciaTotal = 0.0; // Variable para sumar la distancia total

    // Comenzar desde el primer punto
    std::string puntoActual = puntos[0];
    visitados.insert(puntoActual);

    std::cout << "Iniciando recorrido desde: " << puntoActual << "\n";

    // Construir la ruta usando el algoritmo del vecino más cercano
    while (visitados.size() < puntos.size())
    {
        double minimaDistancia = std::numeric_limits<double>::infinity();
        std::string siguientePunto;
        std::vector<Route> rutaDetallada;

        // Buscar el punto no visitado más cercano en términos de distancia
        for (const auto &punto : puntos)
        {
            if (visitados.find(punto) == visitados.end())
            {
                auto [distancia, ruta] = calcularDistanciaYRuta(puntoActual, punto);
                if (distancia < minimaDistancia)
                {
                    minimaDistancia = distancia;
                    siguientePunto = punto;
                    rutaDetallada = ruta;
                }
            }
        }

        if (minimaDistancia == std::numeric_limits<double>::infinity())
        {
            std::cerr << "Error: No se puede conectar todos los puntos con las rutas existentes.\n";
            return {};
        }

        // Imprimir los tramos de la ruta detallada y sumar la distancia
        for (const auto &ruta : rutaDetallada)
        {
            std::cout << "Desde " << ruta.getInitialUbication().getName() << " hasta " << ruta.getLastUbication().getName()
                      << " | Distancia: " << ruta.getDistance() << " km\n";
            distanciaTotal += ruta.getDistance(); // Sumar la distancia del tramo
        }

        rutaOptima.insert(rutaOptima.end(), rutaDetallada.begin(), rutaDetallada.end());
        visitados.insert(siguientePunto);
        puntoActual = siguientePunto;
    }

    // Regresar al punto de inicio para completar el ciclo (opcional)
    auto [distanciaRegreso, rutaRegreso] = calcularDistanciaYRuta(puntoActual, puntos[0]);
    for (const auto &ruta : rutaRegreso)
    {
        std::cout << "Desde " << ruta.getInitialUbication().getName() << " hasta " << ruta.getLastUbication().getName()
                  << " | Distancia: " << ruta.getDistance() << " km\n";
        distanciaTotal += ruta.getDistance(); // Sumar la distancia del tramo de regreso
    }
    rutaOptima.insert(rutaOptima.end(), rutaRegreso.begin(), rutaRegreso.end());

    // Mostrar la distancia total recorrida
    std::cout << "\nDistancia total recorrida: " << distanciaTotal << " km\n";

    return rutaOptima;
}

std::vector<Route> Grafo::calcularRutaOptimaVariosPuntos(const std::vector<std::string> &puntos, const std::string &horaSalida) const
{
    if (puntos.size() < 2)
    {
        std::cerr << "Error: Se necesitan al menos dos puntos para calcular una ruta.\n";
        return {};
    }

    auto calcularTiempoYRuta = [&](const std::string &origen, const std::string &destino, const std::string &horaInicio)
        -> std::pair<double, std::vector<Route>>
    {
        std::map<std::string, double> distancias;
        std::priority_queue<std::pair<double, std::string>, std::vector<std::pair<double, std::string>>, std::greater<>> cola;
        std::map<std::string, std::string> previos;
        std::map<std::string, std::string> horaLLegada;

        // Inicializar distancias con infinito, excepto el nodo de origen
        for (const auto &par : nodos)
        {
            distancias[par.first] = std::numeric_limits<double>::infinity();
        }
        distancias[origen] = 0.0;
        horaLLegada[origen] = horaInicio;
        cola.push(std::make_pair(0.0, origen));

        while (!cola.empty())
        {
            std::string actual = cola.top().second;
            cola.pop();

            if (actual == destino)
            {
                break;
            }

            // Explorar los nodos adyacentes
            for (const auto &adyacente : adyacencias.at(actual))
            {
                std::string vecino = adyacente.first;
                double distancia = adyacente.second;

                // Obtener los traficos de la ruta entre actual y vecino
                std::vector<Trafic> traficos = obtenerTraficos(actual, vecino);

                // Obtener la velocidad de la ruta
                double velocidadRuta = 0.0;
                for (const auto &ruta : kdTreeRutas.obtenerTodasLasRutas())
                {
                    if (ruta.getInitialUbication().getName() == actual && ruta.getLastUbication().getName() == vecino)
                    {
                        velocidadRuta = ruta.getSpeed();
                        break;
                    }
                }

                // Calcular el tiempo de viaje
                double tiempo = calcularTiempo(distancia, traficos, horaLLegada[actual], velocidadRuta);
                std::string horaLLegadaVecino = sumarHoras(horaLLegada[actual], tiempo);

                // Si encontramos un camino más corto, actualizar distancias
                if (distancias[vecino] > distancias[actual] + tiempo)
                {
                    distancias[vecino] = distancias[actual] + tiempo;
                    previos[vecino] = actual;
                    horaLLegada[vecino] = horaLLegadaVecino;
                    cola.push(std::make_pair(distancias[vecino], vecino));
                }
            }
        }

        // Reconstruir la ruta detallada como un vector de Route
        std::vector<Route> rutaDetallada;
        for (std::string at = destino; at != origen; at = previos[at])
        {
            std::string anterior = previos[at];

            bool rutaEncontrada = false;
            for (const auto &ruta : kdTreeRutas.obtenerTodasLasRutas())
            {
                if (ruta.getInitialUbication().getName() == anterior && ruta.getLastUbication().getName() == at)
                {
                    rutaDetallada.push_back(ruta);
                    rutaEncontrada = true;
                    break;
                }
            }

            if (!rutaEncontrada)
            {
                std::cerr << "Advertencia: No se encontró una ruta registrada entre " << anterior << " y " << at << ".\n";
            }
        }
        std::reverse(rutaDetallada.begin(), rutaDetallada.end());

        // Devolver el tiempo total y la ruta detallada
        return {distancias[destino], rutaDetallada};
    };

    // Inicializar variables
    std::vector<Route> rutaOptima;
    std::unordered_set<std::string> visitados;
    double tiempoTotal = 0.0; // Variable para sumar el tiempo total en horas
    double distanciaTotal = 0.0; // Variable para sumar la distancia total en km
    std::string horaActual = horaSalida;

    // Comenzar desde el primer punto
    std::string puntoActual = puntos[0];
    visitados.insert(puntoActual);

    std::cout << "Iniciando recorrido desde: " << puntoActual << " a las " << horaActual << "\n";

    // Construir la ruta usando el algoritmo del vecino más cercano
    while (visitados.size() < puntos.size())
    {
        double minimoTiempo = std::numeric_limits<double>::infinity();
        std::string siguientePunto;
        std::vector<Route> rutaDetallada;

        // Buscar el punto no visitado más cercano en términos de tiempo
        for (const auto &punto : puntos)
        {
            if (visitados.find(punto) == visitados.end())
            {
                auto [tiempo, ruta] = calcularTiempoYRuta(puntoActual, punto, horaActual);
                if (tiempo < minimoTiempo)
                {
                    minimoTiempo = tiempo;
                    siguientePunto = punto;
                    rutaDetallada = ruta;
                }
            }
        }

        if (minimoTiempo == std::numeric_limits<double>::infinity())
        {
            std::cerr << "Error: No se puede conectar todos los puntos con las rutas existentes.\n";
            return {};
        }

        // Imprimir los tramos de la ruta detallada y sumar el tiempo
        for (const auto &ruta : rutaDetallada)
        {
            // Obtener los traficos de la ruta
            std::vector<Trafic> traficos = obtenerTraficos(ruta.getInitialUbication().getName(), ruta.getLastUbication().getName());

            // Obtener la velocidad de la ruta
            double velocidadRuta = 0.0;
            for (const auto &rutaCompleta : kdTreeRutas.obtenerTodasLasRutas())
            {
                if (rutaCompleta.getInitialUbication().getName() == ruta.getInitialUbication().getName() &&
                    rutaCompleta.getLastUbication().getName() == ruta.getLastUbication().getName())
                {
                    velocidadRuta = rutaCompleta.getSpeed();
                    break;
                }
            }

            // Calcular el tiempo de viaje para este tramo
            double tiempoTramo = calcularTiempo(ruta.getDistance(), traficos, horaActual, velocidadRuta);

            // Imprimir el tramo con su tiempo específico
            std::cout << "Desde " << ruta.getInitialUbication().getName() << " hasta " << ruta.getLastUbication().getName()
                      << " | Distancia: " << ruta.getDistance() << " km"
                      << " | Tiempo: " << tiempoTramo << " horas\n";

            // Sumar el tiempo del tramo al tiempo total
            tiempoTotal += tiempoTramo;
            distanciaTotal += ruta.getDistance();
        }

        rutaOptima.insert(rutaOptima.end(), rutaDetallada.begin(), rutaDetallada.end());
        visitados.insert(siguientePunto);
        horaActual = sumarHoras(horaActual, minimoTiempo);
        puntoActual = siguientePunto;
    }

    // Regresar al punto de inicio para completar el ciclo (opcional)
    auto [tiempoRegreso, rutaRegreso] = calcularTiempoYRuta(puntoActual, puntos[0], horaActual);
    for (const auto &ruta : rutaRegreso)
    {
        // Obtener los traficos de la ruta
        std::vector<Trafic> traficos = obtenerTraficos(ruta.getInitialUbication().getName(), ruta.getLastUbication().getName());

        // Obtener la velocidad de la ruta
        double velocidadRuta = 0.0;
        for (const auto &rutaCompleta : kdTreeRutas.obtenerTodasLasRutas())
        {
            if (rutaCompleta.getInitialUbication().getName() == ruta.getInitialUbication().getName() &&
                rutaCompleta.getLastUbication().getName() == ruta.getLastUbication().getName())
            {
                velocidadRuta = rutaCompleta.getSpeed();
                break;
            }
        }

        // Calcular el tiempo de viaje para este tramo
        double tiempoTramo = calcularTiempo(ruta.getDistance(), traficos, horaActual, velocidadRuta);

        // Imprimir el tramo con su tiempo específico
        std::cout << "Desde " << ruta.getInitialUbication().getName() << " hasta " << ruta.getLastUbication().getName()
                  << " | Distancia: " << ruta.getDistance() << " km"
                  << " | Tiempo: " << tiempoTramo << " horas\n";

        // Sumar el tiempo del tramo al tiempo total
        tiempoTotal += tiempoTramo;
        distanciaTotal += ruta.getDistance();
    }
    rutaOptima.insert(rutaOptima.end(), rutaRegreso.begin(), rutaRegreso.end());

    // Convertir el tiempo total a horas y minutos
    int horasTotales = static_cast<int>(tiempoTotal);
    int minutosTotales = static_cast<int>((tiempoTotal - horasTotales) * 60);

    // Mostrar el tiempo total recorrido
    std::cout << "\nTiempo total recorrido: " << horasTotales << " horas y " << minutosTotales << " minutos\n";
    std::cout << "\nDistancia total recorrida: " << distanciaTotal << " km\n";
    return rutaOptima;
}