#include <iostream>
#include <limits>
#include "Grafo.cpp"

void mostrarMenuPrincipal() {
    std::cout << "1. Grafo grande" << std::endl;
    std::cout << "2. Grafo pequeno" << std::endl;
    std::cout << "3. Salir" << std::endl;
}

void mostrarMenuTipoGrafo() {
    std::cout << "1. Dirigido" << std::endl;
    std::cout << "2. No dirigido" << std::endl;
}

void mostrarMenuRepresentacion() {
    std::cout << "1. Representacion Logica" << std::endl;
    std::cout << "2. Representacion Lista de Adyacencia" << std::endl;
    std::cout << "3. Representacion Matriz de Adyacencia" << std::endl;
    std::cout << "4. Regresar al menu principal" << std::endl;
}

int obtenerOpcion() {
    int opcion;
    while (true) {
        std::cin >> opcion;
        if (std::cin.fail() || opcion < 1) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "Entrada invalida. Por favor, ingrese un numero entero positivo: ";
        } else {
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            return opcion;
        }
    }
}

int obtenerVertice(int numNodos) {
    int vertice;
    while (true) {
        std::cin >> vertice;
        if (std::cin.fail() || vertice < 0 || vertice >= numNodos) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "Entrada invalida. Por favor, ingrese un numero entero positivo entre 0 y " << numNodos - 1 << ": ";
        } else {
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            return vertice;
        }
    }
}

int main() {
    Grafo grafo;
    int opcionPrincipal, opcionTipoGrafo, opcionRepresentacion, verticeInicial;

    do {
        mostrarMenuPrincipal();
        std::cout << "Seleccione una opcion: ";
        opcionPrincipal = obtenerOpcion();

        if (opcionPrincipal == 1 || opcionPrincipal == 2) {
            int numNodos = (opcionPrincipal == 1) ? 18 : 8;
            mostrarMenuTipoGrafo();
            std::cout << "Seleccione el tipo de grafo: ";
            opcionTipoGrafo = obtenerOpcion();
            bool dirigido = (opcionTipoGrafo == 1);

            grafo.nuevoGrafo(numNodos, dirigido);
            std::cout << "Nuevo grafo generado." << std::endl;

            do {
                mostrarMenuRepresentacion();
                std::cout << "Seleccione una opcion: ";
                opcionRepresentacion = obtenerOpcion();

                switch (opcionRepresentacion) {
                    case 1:
                        grafo.representacionLogica();
                        grafo.representacionLogicaGrafica();
                        break;
                    case 2:
                        grafo.representacionListaAdyacencia();
                        grafo.representacionListaAdyacenciaGrafica();
                        break;
                    case 3:
                        grafo.representacionMatrizAdyacencia();
                        grafo.representacionMatrizAdyacenciaGrafica();
                        break;
                    case 4:
                        std::cout << "Regresando al menu principal..." << std::endl;
                        break;
                    default:
                        std::cout << "Opcion no valida." << std::endl;
                        break;
                }

                if (opcionRepresentacion >= 1 && opcionRepresentacion <= 3) {
                    std::cout << "Ingrese el vertice inicial para la busqueda por amplitud: ";
                    verticeInicial = obtenerVertice(numNodos);
                    grafo.busquedaAmplitud(verticeInicial);
                }

            } while (opcionRepresentacion != 4);
        } else if (opcionPrincipal == 3) {
            std::cout << "Saliendo..." << std::endl;
        } else {
            std::cout << "Opcion no valida." << std::endl;
        }
    } while (opcionPrincipal != 3);

    return 0;
}