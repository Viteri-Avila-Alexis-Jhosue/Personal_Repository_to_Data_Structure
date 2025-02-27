#include "../include/Ejercicios.h"
# include <iostream>
# include <windows.h>
# include <string>
# include <vector>
# include <algorithm>
# include <cmath>
# include <iomanip>
# include <sstream>
#include <queue>
#include <utility>
#include <climits>
#include <functional>
using namespace std;
Ejercicios::Ejercicios() {
    // Constructor implementation
}

void Ejercicios::ex_pag6() {
    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);
    cout<<"Ejercicio pag 6"<<endl;
    auto f = [](int n) { return n * n - 3 * n + 1; };
    double c = 0.5;
    int n0 = 6;
    bool cumpleDefinicion = true;
    for (int n = n0; n <= 20; ++n) { 
        if (f(n) < c * n * n) {
            cumpleDefinicion = false;
            break;
        }
    }
    if (cumpleDefinicion) {
        cout << "Se cumple que n^2 - 3n + 1 ∈ Ω(n^2) para c = " << c << " y n0 = " << n0 << "." << endl;
    } else {
        cout << "No se cumple la definición de Ω(n^2)." << endl;
    }
}

void Ejercicios::ex_pag7() {
    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);
    cout << "Ejercicio pag 7" << endl;
    cout << "T(n) = 4T(n-1)-5T(n-2) + 2T(n-3) + 1 + n^2 * 2^n" << endl;
    cout << "T(n)-4T(n-1) + 5T(n-2)-2T(n-3) = (1 + n^2) * 2^n + n^2 * 2^n" << endl;
    cout << "Polinomio característico: (x^3-4x^2 + 5x-2)(x-1)^3 / (x-2)^2" << endl;
    cout << "(x-1)^5 / (x-2)^3" << endl;
    cout << "Orden de complejidad: T(n) ∈ θ(n^2 * 2^n)" << endl;
}

void Ejercicios::ex_pag8() {
    // Configurar la consola para soportar UTF-8
    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);

    cout << "Ejercicio pag 8" << endl;
    cout << "Análisis de complejidad del código con bucles anidados" << endl;
    int n;
    cout << "Ingrese el valor de n: ";
    cin >> n;
    long long T_n = n * n * n + 5 * n * n + 9 * n + 2;
    cout << "El número total de operaciones T(n) es: " << T_n << endl;
    cout << "Complejidad: θ(n^3)" << endl;
}

void Ejercicios::ex_pag10() {
    // Configurar la consola para soportar UTF-8
    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);

    cout << "Ejercicio pag 10" << endl;
    cout << "Resolución de la recurrencia T(n) = 2T(n/2) + n" << endl;

    int n;
    cout << "Ingrese el valor de n (debe ser una potencia de 2, por ejemplo, 2, 4, 8, 16, ...): ";
    cin >> n;

    if ((n & (n - 1)) != 0) {
        cout << "Error: n no es una potencia de 2." << endl;
        return;
    }
    double T_n = n + n * log2(n);

    cout << "El valor de T(n) es: " << T_n << endl;
    cout << "Complejidad: θ(n log n)" << endl;
}


void Ejercicios::ex_pag11() {
    // Configurar la consola para soportar UTF-8
    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);

    cout << "Ejercicio pag 11" << endl;
    cout << "Resolución de la recurrencia T(n) = 2T(n/2) + n" << endl;

    // Solicitar el valor de n (debe ser una potencia de 2)
    int n;
    cout << "Ingrese el valor de n (debe ser una potencia de 2, por ejemplo, 2, 4, 8, 16, ...): ";
    cin >> n;

    // Verificar si n es una potencia de 2
    if ((n & (n - 1)) != 0) {
        cout << "Error: n no es una potencia de 2." << endl;
        return;
    }

    // Calcular T(n) según la expresión no recursiva
    // T(n) = n + n * log2(n)
    double T_n = n + n * log2(n);

    // Mostrar el resultado
    cout << "El valor de T(n) es: " << T_n << endl;
    cout << "Complejidad: θ(n log n)" << endl;
}

void Ejercicios::ex_pag12() {
    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);

    int n;
    cout << "Ingrese el valor de n: ";
    cin >> n;

    double T_n = pow(2, n);

    cout << "El valor de T(n) es: " << T_n << endl;
    cout << "Complejidad: θ(2^n)" << endl;
}

void Ejercicios::ex_pag15() {
    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);

    int n0 = 2; // Base del logaritmo (b = 2)
    double c = 5.0;

    cout << "Demostración de que 5n ∈ O(n log(n)):" << endl;
    cout << "Para n >= " << n0 << ", se cumple que 5n <= " << c << " * n * log(n)" << endl;

    for (int n = n0; n <= 10; n++) {
        double left = 5 * n;
        double right = c * n * log2(n);
        cout << "n = " << n << ": " << left << " <= " << right << " -> " << (left <= right ? "Cumple" : "No cumple") << endl;
    }
}

void Ejercicios::ex_pag16() {
    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);

    int n;
    cout << "Ingrese el valor de n: ";
    cin >> n;

    // Calcular T(n) según la fórmula simplificada
    double T_n = (3.0 / 2.0) * n * n + (17.0 / 2.0) * n + 2;

    cout << "El número total de operaciones T(n) es: " << T_n << endl;
    cout << "Complejidad: θ(n^2)" << endl;
}

void Ejercicios::ex_pag17() {
    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);

    int n;
    cout << "Ingrese el valor de n (debe ser una potencia de 2, por ejemplo, 2, 4, 8, 16, ...): ";
    cin >> n;

    if ((n & (n - 1)) != 0) {
        cout << "Error: n no es una potencia de 2." << endl;
        return;
    }
    double T_n = 2 * n * n - n;

    cout << "El valor de T(n) es: " << T_n << endl;
    cout << "Complejidad: θ(n^2)" << endl;
}

void Ejercicios::ex_pag18() {
    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);
    int n;
        std::cout << "Ingrese el valor de n (debe ser una potencia de 2, por ejemplo, 2, 4, 8, 16, ...): ";
        std::cin >> n;

        // Verificar si n es una potencia de 2
        if ((n & (n - 1)) != 0) {
            std::cout << "Error: n no es una potencia de 2." << std::endl;
            return;
        }

        // Calcular k = log2(n)
        int k = log2(n);

        // Calcular T(n) usando la expresión no recursiva: T(n) = 1 + 0.5 * log2(n) + 0.5 * (log2(n))^2
        double T_n = 1 + 0.5 * k + 0.5 * k * k;

        // Mostrar el resultado
        std::cout << "El valor de T(n) es: " << T_n << std::endl;
        std::cout << "Complejidad: θ((log n)^2)" << std::endl;
}

void Ejercicios::ex_pag20() {
    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);

    // Definir el laberinto como una matriz (0 = camino libre, 1 = pared)
    vector<vector<int>> laberinto = {
        {0, 1, 0, 0, 0},
        {0, 1, 0, 1, 0},
        {0, 0, 0, 1, 0},
        {0, 1, 1, 1, 0},
        {0, 0, 0, 0, 0}
    };

    // Imprimir el laberinto
    imprimirLaberinto(laberinto);

    // Definir las dimensiones del laberinto
    int filas = laberinto.size();
    int columnas = laberinto[0].size();

    // Definir el punto de inicio y el punto de destino
    pair<int, int> inicio = {0, 0}; // Esquina superior izquierda
    pair<int, int> destino = {filas - 1, columnas - 1}; // Esquina inferior derecha

    // Crear una matriz de distancias inicializadas con infinito
    vector<vector<int>> distancias(filas, vector<int>(columnas, INT_MAX));
    distancias[inicio.first][inicio.second] = 0; // La distancia al inicio es 0

    // Definir movimientos posibles (arriba, abajo, izquierda, derecha)
    vector<pair<int, int>> direcciones = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};

    // Cola de prioridad para Dijkstra: (distancia, (fila, columna))
    priority_queue<pair<int, pair<int, int>>, vector<pair<int, pair<int, int>>>, greater<pair<int, pair<int, int>>>> cola;
    cola.push({0, inicio});

    // Algoritmo de Dijkstra
    while (!cola.empty()) {
        auto actual = cola.top();
        cola.pop();
        int dist_actual = actual.first;
        int fila_actual = actual.second.first;
        int col_actual = actual.second.second;

        // Si llegamos al destino, terminar
        if (fila_actual == destino.first && col_actual == destino.second) {
            cout << "La distancia más corta es: " << dist_actual << endl;
            return;
        }

        // Explorar vecinos
        for (auto dir : direcciones) {
            int nueva_fila = fila_actual + dir.first;
            int nueva_col = col_actual + dir.second;

            // Verificar si la nueva posición es válida y no es una pared
            if (nueva_fila >= 0 && nueva_fila < filas && nueva_col >= 0 && nueva_col < columnas && laberinto[nueva_fila][nueva_col] == 0) {
                int nueva_distancia = dist_actual + 1; // Cada movimiento tiene un costo de 1

                // Si encontramos un camino más corto, actualizar la distancia
                if (nueva_distancia < distancias[nueva_fila][nueva_col]) {
                    distancias[nueva_fila][nueva_col] = nueva_distancia;
                    cola.push({nueva_distancia, {nueva_fila, nueva_col}});
                }
            }
        }
    }

    // Si no se encuentra un camino
    cout << "No hay camino válido desde el inicio hasta el destino." << endl;
}

void Ejercicios::imprimirLaberinto(const vector<vector<int>>& laberinto) {
    cout << "Laberinto:" << endl;
    for (const auto& fila : laberinto) {
        for (int celda : fila) {
            if (celda == 0) {
                cout << " "; // Camino libre
            } else if (celda == 1) {
                cout << "#"; // Pared
            }
            cout << " "; // Espacio entre celdas
        }
        cout <<"|"<< endl;
    }
    cout<<"----------"<<endl;
}

void Ejercicios::ex_pag21_2() {
    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);

    int a;
    int x;

    cout << "Ingrese el número a (cuyos dígitos están en orden creciente): ";
    cin >> a;
    cout << "Ingrese el dígito x a insertar: ";
    cin >> x;

    // Verificar que los dígitos de a estén en orden creciente
    int temp = a;
    int ultimoDigito = temp % 10;
    temp /= 10;
    bool esOrdenado = true;
    while (temp > 0) {
        int digitoActual = temp % 10;
        if (digitoActual > ultimoDigito) {
            esOrdenado = false;
            break;
        }
        ultimoDigito = digitoActual;
        temp /= 10;
    }

    if (!esOrdenado) {
        cout << "Error: Los dígitos de a no están en orden creciente." << endl;
        return;
    }

    // Insertar x en a
    int resultado = insertaEnEnteroCreciente(x, a);

    // Mostrar el resultado
    cout << "El número resultante es: " << resultado << endl;
}

int Ejercicios::insertaEnEnteroCreciente(int x, int a) {
    // Caso base: si x es mayor o igual que el último dígito de a, se inserta al final
    if (x >= a % 10) {
        return a * 10 + x;
    }
    // Caso recursivo: se descompone a y se inserta x en la posición correcta
    return (a % 10) + 10 * insertaEnEnteroCreciente(x, a / 10);
}
void Ejercicios::ex_pag21_3() {
    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);

    // Ejemplo de lista ordenada
    vector<int> a = {-10, -5, 0, 3, 7, 9, 12, 17};

    // Llamar a la función para encontrar el índice i tal que a[i] == i
    int resultado = elementoEnPosicion(a, 0, a.size() - 1);

    // Mostrar el resultado
    if (resultado != -1) {
        cout << "Se encontró un índice i tal que a[i] == i: " << resultado << endl;
    } else {
        cout << "No se encontró ningún índice i tal que a[i] == i." << endl;
    }
}

int Ejercicios::elementoEnPosicion(const vector<int>& a, int inf, int sup) {
    if (inf > sup) {
        return -1; // Caso base: no se encontró ningún índice válido
    }

    int mitad = (inf + sup) / 2; // Punto medio

    if (a[mitad] == mitad) {
        return mitad; // Caso base: se encontró un índice válido
    } else if (a[mitad] > mitad) {
        // Buscar en la mitad izquierda
        return elementoEnPosicion(a, inf, mitad - 1);
    } else {
        // Buscar en la mitad derecha
        return elementoEnPosicion(a, mitad + 1, sup);
    }
}

void Ejercicios::imprimirSolucion(const vector<bool>& solucion, const vector<int>& L) {
    cout << "Subconjunto seleccionado: { ";
    for (size_t i = 0; i < solucion.size(); ++i) {
        if (solucion[i]) {
            cout << L[i] << " ";
        }
    }
    cout << "}" << endl;
}

// Función recursiva de backtracking
int Ejercicios::buscaSubconjunto(int i, int suma_parcial, const vector<int>& L, int s,
                     vector<bool>& sol_parcial, vector<bool>& sol_opt,
                     int card_opt, int card) {
    // Si la suma parcial es igual a s, actualizamos la solución óptima
    if (suma_parcial == s) {
        if (card < card_opt) {
            card_opt = card;
            sol_opt = sol_parcial;
        }
        return card_opt;
    }

    // Si hemos recorrido toda la lista o la cardinalidad actual es mayor que la óptima, podamos
    if (i >= L.size() || card >= card_opt) {
        return card_opt;
    }

    // Incluir L[i] en el subconjunto
    if (suma_parcial + L[i] <= s) {
        sol_parcial[i] = true;
        card_opt = buscaSubconjunto(i + 1, suma_parcial + L[i], L, s, sol_parcial, sol_opt, card_opt, card + 1);
        sol_parcial[i] = false; // Backtracking
    }

    // No incluir L[i] en el subconjunto
    card_opt = buscaSubconjunto(i + 1, suma_parcial, L, s, sol_parcial, sol_opt, card_opt, card);

    return card_opt;
}

void Ejercicios::ex_pag22() {
    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);

    // Lista de números enteros no negativos
    vector<int> L = {1, 2, 3, 5, 6, 7, 9, 13};
    int s = 13;

    // Vector de booleanos para la solución parcial y óptima
    vector<bool> sol_parcial(L.size(), false);
    vector<bool> sol_opt(L.size(), false);

    // Llamar a la función de backtracking
    int card_opt = buscaSubconjunto(0, 0, L, s, sol_parcial, sol_opt, INT_MAX, 0);

    // Mostrar la solución
    if (card_opt != INT_MAX) {
        cout << "Cardinalidad mínima: " << card_opt << endl;
        imprimirSolucion(sol_opt, L);
    } else {
        cout << "No se encontró ningún subconjunto que sume " << s << "." << endl;
    }
}

void Ejercicios::ex_pag25_1() {
    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);

    // Mostrar el orden de complejidad de las funciones
    cout << "Orden de complejidad de menor a mayor:" << endl;
    cout << "1. log n^2 = 5 log n" << endl;
    cout << "2. 10n" << endl;
    cout << "3. n log10 n" << endl;
    cout << "4. n^(1+a) (con 0 < a < 1)" << endl;
    cout << "5. n^2" << endl;
    cout << "6. n^2 log n" << endl;
}

int Ejercicios::calcularTMejorCaso(int n) {
    // T(n) = (3n^2 + 11n + 4) / 2
    return (3 * n * n + 11 * n + 4) / 2;
}

// Función para calcular T(n) en el peor caso
int Ejercicios::calcularTPeorCaso(int n) {
    // T(n) = (8n^3 + 27n^2 + 43n + 12) / 6
    return (8 * n * n * n + 27 * n * n + 43 * n + 12) / 6;
}

void Ejercicios::ex_pag25_2() {
    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);

    int n;
    cout << "Ingrese el valor de n: ";
    cin >> n;

    // Calcular T(n) en el mejor caso
    int T_mejor_caso = calcularTMejorCaso(n);
    cout << "Número de operaciones en el mejor caso (T(n)): " << T_mejor_caso << endl;
    cout << "Complejidad en el mejor caso: Θ(n^2)" << endl;

    // Calcular T(n) en el peor caso
    int T_peor_caso = calcularTPeorCaso(n);
    cout << "Número de operaciones en el peor caso (T(n)): " << T_peor_caso << endl;
    cout << "Complejidad en el peor caso: Θ(n^3)" << endl;
}

void Ejercicios::ex_pag27() {
    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);
    
    int n;
    std::cout << "Ingrese el valor de n (debe ser una potencia de 4, por ejemplo, 4, 16, 64, ...): ";
    std::cin >> n;
    
    // Verificar si n es una potencia de 4
    int temp = n;
    while (temp > 1) {
        if (temp % 4 != 0) {
            std::cout << "Error: n no es una potencia de 4." << std::endl;
            return;
        }
        temp /= 4;
    }
    
    // Calcular T(n) usando la solución obtenida
    double T_n = (16.0 / 15.0) * (n * n) - (1.0 / 15.0);
    
    std::cout << "El valor de T(n) es: " << T_n << std::endl;
    std::cout << "Complejidad: θ(n^2)" << std::endl;
}

void Ejercicios::ex_pag28() {
    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);
    
    int n;
    std::cout << "Ingrese el valor de n (debe ser una potencia de 4, por ejemplo, 4, 16, 64, ...): ";
    std::cin >> n;
    
    // Verificar si n es una potencia de 4
    int temp = n;
    while (temp > 1) {
        if (temp % 4 != 0) {
            std::cout << "Error: n no es una potencia de 4." << std::endl;
            return;
        }
        temp /= 4;
    }
    
    // Calcular T(n) usando la solución obtenida por expansión de recurrencias
    double T_n = (16.0 / 15.0) * (n * n) - (1.0 / 15.0);
    
    std::cout << "El valor de T(n) es: " << T_n << std::endl;
    std::cout << "Complejidad: θ(n^2)" << std::endl;
}

void Ejercicios::ex_pag29() {
    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);

    // Función auxiliar para encontrar la suma máxima cruzando la mitad
    auto maxCrossingSum = [](std::vector<int>& arr, int ini, int mitad, int fin) -> int {
        int max_izq = INT_MIN, suma = 0;
        for (int i = mitad; i >= ini; i--) {
            suma += arr[i];
            max_izq = std::max(max_izq, suma);
        }

        int max_dcha = INT_MIN;
        suma = 0;
        for (int i = mitad + 1; i <= fin; i++) {
            suma += arr[i];
            max_dcha = std::max(max_dcha, suma);
        }

        return max_izq + max_dcha;
    };

    // Función recursiva para encontrar la sublista de suma máxima
    std::function<int(std::vector<int>&, int, int)> maxima_suma_sublista = [&](std::vector<int>& arr, int ini, int fin) -> int {
        if (ini == fin) return arr[ini];

        int mitad = (ini + fin) / 2;
        int max_mitad_izq = maxima_suma_sublista(arr, ini, mitad);
        int max_mitad_dcha = maxima_suma_sublista(arr, mitad + 1, fin);
        int max_cruzado = maxCrossingSum(arr, ini, mitad, fin);

        return std::max({max_mitad_izq, max_mitad_dcha, max_cruzado});
    };

    // Entrada del usuario
    int n;
    std::cout << "Ingrese el tamaño de la lista: ";
    std::cin >> n;

    std::vector<int> arr(n);
    std::cout << "Ingrese los elementos de la lista separados por espacios: ";
    for (int i = 0; i < n; i++) {
        std::cin >> arr[i];
    }

    // Llamada a la función recursiva
    int resultado = maxima_suma_sublista(arr, 0, n - 1);

    std::cout << "La suma máxima de la sublista es: " << resultado << std::endl;
}
void Ejercicios::ex_pag32() {
    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);

    int n;
    std::cout << "Ingrese el número de actividades: ";
    std::cin >> n;

    std::vector<int> c(n), f(n);
    std::cout << "Ingrese los tiempos de inicio de las actividades: ";
    for (int i = 0; i < n; i++) std::cin >> c[i];

    std::cout << "Ingrese los tiempos de finalización de las actividades: ";
    for (int i = 0; i < n; i++) std::cin >> f[i];

    // Función para verificar si una actividad es compatible con la selección actual
    auto es_candidato_valido = [&](int i, std::vector<int>& sol) -> bool {
        for (int j = 0; j < i; j++) {
            if (sol[j] == 1 && !(c[i] >= f[j] || c[j] >= f[i])) {
                return false;  // Si hay solapamiento, no es válido
            }
        }
        return true;
    };

    // Backtracking para encontrar el subconjunto de mayor cardinalidad
    std::function<int(int, int, std::vector<int>&, std::vector<int>&, int&)> busca_maxima_cardinalidad;
    busca_maxima_cardinalidad = [&](int i, int card_actual, std::vector<int>& sol, std::vector<int>& opt_sol, int& card_opt) -> int {
        if (i == n) {
            if (card_actual > card_opt) {
                card_opt = card_actual;
                opt_sol = sol;  // Guardamos la mejor solución encontrada
            }
        } else {
            for (int k = 0; k <= 1; k++) {
                if (k == 0 || es_candidato_valido(i, sol)) {
                    sol[i] = k;
                    busca_maxima_cardinalidad(i + 1, card_actual + k, sol, opt_sol, card_opt);
                    sol[i] = 0;  // Backtrack
                }
            }
        }
        return card_opt;
    };

    std::vector<int> sol(n, 0), opt_sol(n, 0);
    int card_opt = -1;
    int max_actividades = busca_maxima_cardinalidad(0, 0, sol, opt_sol, card_opt);

    // Mostrar las actividades seleccionadas
    std::cout << "Actividades seleccionadas (1=incluida, 0=excluida): ";
    for (int i = 0; i < n; i++) {
        std::cout << opt_sol[i] << " ";
    }
    std::cout << "\nMáximo número de actividades seleccionadas: " << max_actividades << std::endl;
}

void Ejercicios::ex_pag37() {
    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);

    std::cout << "Demostración de complejidad asintótica O\n";

    // Parte (a): Verificar si 2^(n+1) está en O(2^n)
    std::cout << "\n(a) ¿2^(n+1) ∈ O(2^n)?\n";
    std::cout << "Demostración:\n";
    std::cout << "Sea f(n) = 2^(n+1) y g(n) = 2^n\n";
    std::cout << "Entonces, f(n) = 2 * 2^n\n";
    std::cout << "Queremos encontrar c > 0 y n0 > 0 tal que:\n";
    std::cout << "2 * 2^n ≤ c * 2^n para todo n ≥ n0\n";
    std::cout << "Escogiendo c = 2 y n0 = 1, la desigualdad se cumple.\n";
    std::cout << "Por lo tanto, 2^(n+1) ∈ O(2^n) ✅\n";

    // Parte (b): Verificar si 2^(2n) está en O(2^n)
    std::cout << "\n(b) ¿2^(2n) ∈ O(2^n)?\n";
    std::cout << "Demostración:\n";
    std::cout << "Sea f(n) = 2^(2n) y g(n) = 2^n\n";
    std::cout << "Entonces, f(n) = (2^n)^2\n";
    std::cout << "Queremos encontrar c > 0 y n0 > 0 tal que:\n";
    std::cout << "2^(2n) ≤ c * 2^n para todo n ≥ n0\n";
    std::cout << "Aplicando logaritmos en base 2:\n";
    std::cout << "2n ≤ log2(c) + n\n";
    std::cout << "Despejando: n ≤ log2(c)\n";
    std::cout << "Esto significa que la desigualdad solo se cumple para valores pequeños de n\n";
    std::cout << "Pero no existe un n0 tal que se cumpla para todo n ≥ n0\n";
    std::cout << "Por lo tanto, 2^(2n) ∉ O(2^n) ❌\n";
}

void Ejercicios::ex_pag38() {
    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);

    std::cout << "Cálculo del número de operaciones (T(n)) para el siguiente código:\n";
    std::cout << "1. int i = 0;\n";
    std::cout << "2. while (i <= n) {\n";
    std::cout << "3.     int j = i;\n";
    std::cout << "4.     while (j <= n) {\n";
    std::cout << "5.         procesa(i, j);  // dos operaciones\n";
    std::cout << "6.         j++;\n";
    std::cout << "7.     }\n";
    std::cout << "8.     i++;\n";
    std::cout << "9. }\n";

    std::cout << "\nDemostración de la cantidad de operaciones (T(n)):\n";
    std::cout << "El código tiene dos bucles anidados, que podemos analizar por separado:\n";

    // Parte (1): Análisis de operaciones
    std::cout << "\nDescomposición de T(n):\n";
    std::cout << "T(n) = 1 + \\sum_{i=0}^{n} (1 + TFor_2 + 1) + 1\n";
    std::cout << "TFor_2 = 1 + \\sum_{j=i}^{n} (1 + 2 + 1) + 1 = 2 + 4(n - i + 1) = 4n + 6 - 4i\n";

    std::cout << "\nSustituyendo TFor_2 en T(n):\n";
    std::cout << "T(n) = 2 + \\sum_{i=0}^{n} (2 + 4n + 6 - 4i)\n";
    std::cout << "T(n) = 2 + \\sum_{i=0}^{n} (4n + 8 - 4i)\n";
    std::cout << "T(n) = 2 + 4n(n + 1) + 8(n + 1) - 4 \\sum_{i=0}^{n} i\n";
    std::cout << "T(n) = 2 + 4n^2 + 4n + 8n + 8 - 4 \\cdot \\frac{n(n + 1)}{2}\n";

    std::cout << "\nFinalmente, el número de operaciones T(n) es:\n";
    std::cout << "T(n) = 2n^2 + 10n + 10 ∈ Θ(n^2)\n";
}

void Ejercicios::ex_pag39() {
    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);

    std::cout << "Resolución de la relación de recurrencia T(n):\n";
    std::cout << "T(n) = (1 si n = 1)\n";
    std::cout << "T(n) = T(n/10) + log10(n^2) si n > 1\n";

    std::cout << "\nPara poder resolver esta recurrencia, primero reescribimos log10(n^2) como 2 log10(n).\n";
    std::cout << "Luego, realizamos el cambio de variable n = 10^k, de modo que k = log10(n).\n";
    
    std::cout << "\nPor lo tanto, la expresión de la recurrencia se reescribe de la siguiente manera:\n";
    std::cout << "T(10^k) = T(10^(k-1)) + 2k\n";
    std::cout << "A continuación, realizamos un cambio de función t(k) = T(10^k), lo que nos da:\n";
    std::cout << "t(k) = t(k-1) + 2k\n";

    std::cout << "\nEl polinomio característico de la recurrencia t(k) = t(k-1) + 2k es (x - 1)^3.\n";
    std::cout << "Por lo tanto, la recurrencia tiene la forma:\n";
    std::cout << "t(k) = C1 + C2k + C3k^2\n";

    std::cout << "\nAhora, tenemos tres casos base para hallar las constantes:\n";
    std::cout << "t(0) = C1 = 1\n";
    std::cout << "t(1) = C1 + C2 + C3 = 3\n";
    std::cout << "t(2) = C1 + 2C2 + 4C3 = 7\n";

    std::cout << "\nEl sistema de ecuaciones a resolver es:\n";
    std::cout << "t(0) = C1 = 1\n";
    std::cout << "t(1) = C1 + C2 + C3 = 3\n";
    std::cout << "t(2) = C1 + 2C2 + 4C3 = 7\n";
    
    std::cout << "\nResolviendo este sistema obtenemos:\n";
    std::cout << "C1 = 1, C2 = 1 y C3 = 1\n";

    std::cout << "\nPor lo tanto, la forma general de t(k) es:\n";
    std::cout << "t(k) = 1 + k + k^2\n";

    std::cout << "\nFinalmente, deshacemos el cambio de variable y función obteniendo:\n";
    std::cout << "T(n) = 1 + log10(n) + [log10(n)]^2\n";

    std::cout << "\nPor lo tanto, T(n) ∈ Θ[(log n)^2].\n";
}

void Ejercicios::ex_pag40() {
    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);

    std::cout << "Resolución de la relación de recurrencia T(n) por el método de expansión de recurrencias:\n";
    std::cout << "T(n) = (1 si n = 1)\n";
    std::cout << "T(n) = T(n/10) + 2 log10(n) si n > 1\n";

    std::cout << "\nPrimero expresamos log10(n^2) como 2 log10(n), quedando la recurrencia como:\n";
    std::cout << "T(n) = T(n/10) + 2 log10(n)\n";

    std::cout << "\nProcedemos a expandir la recurrencia paso a paso:\n";
    std::cout << "T(n) = T(n/10) + 2 log10 n\n";
    std::cout << "T(n/10) = T(n/100) + 2 log10(n/10)\n";
    std::cout << "T(n/100) = T(n/1000) + 2 log10(n/100)\n";

    std::cout << "\nVamos sumando los términos en cada expansión:\n";
    std::cout << "T(n) = T(n/10^i) + 2i log10 n - 2(1 + 2 + 3 + ... + (i-1))\n";

    std::cout << "\nLa expansión continúa hasta llegar al caso base cuando n/10^i = 1, es decir, cuando n = 10^i, o equivalentemente cuando i = log10(n).\n";
    
    std::cout << "\nSustituyendo en la expresión:\n";
    std::cout << "T(n) = T(1) + 2(log10 n)(log10 n) - (log10 n - 1)(log10 n)\n";
    
    std::cout << "\nFinalmente, sabemos que T(1) = 1, entonces la solución es:\n";
    std::cout << "T(n) = 1 + log10(n) + [log10(n)]^2\n";

    std::cout << "\nPor lo tanto, T(n) ∈ Θ[(log n)^2].\n";
}

bool Ejercicios::esta_ordenada_matriz(const std::vector<std::vector<int>>& A, int inicio_fila, int fin_fila, int inicio_col, int fin_col) {
    int n = fin_fila - inicio_fila;
    int m = fin_col - inicio_col;

    // Caso base: si la submatriz tiene un solo elemento
    if (n == 1 && m == 1) {
        return true;
    }

    // Caso base: si una fila o columna está vacía
    if (n == 0 || m == 0) {
        return true;
    }

    int mitad_n = (inicio_fila + fin_fila) / 2;
    int mitad_m = (inicio_col + fin_col) / 2;

    // Verificar los elementos de las filas y columnas centrales
    bool elementos_centrales_ordenados = true;

    // Verificar orden en la fila central
    for (int i = inicio_fila; i < fin_fila && elementos_centrales_ordenados; ++i) {
        if (A[i][mitad_m - 1] > A[i][mitad_m]) {
            elementos_centrales_ordenados = false;
        }
    }

    // Verificar orden en la columna central
    for (int j = inicio_col; j < fin_col && elementos_centrales_ordenados; ++j) {
        if (A[mitad_n - 1][j] > A[mitad_n][j]) {
            elementos_centrales_ordenados = false;
        }
    }

    // Verificar la submatriz y sus partes recursivamente
    return elementos_centrales_ordenados &&
           esta_ordenada_matriz(A, inicio_fila, mitad_n, inicio_col, mitad_m) &&
           esta_ordenada_matriz(A, inicio_fila, mitad_n, mitad_m, fin_col) &&
           esta_ordenada_matriz(A, mitad_n, fin_fila, inicio_col, mitad_m) &&
           esta_ordenada_matriz(A, mitad_n, fin_fila, mitad_m, fin_col);
}

void Ejercicios::ex_pag41() {
    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);

    // Ejemplo de matriz ordenada
    std::vector<std::vector<int>> A = {
        {1, 3, 6, 8, 10},
        {2, 4, 7, 9, 10},
        {4, 8, 11, 14, 14},
        {5, 10, 12, 15, 16}
    };

    // Llamada a la función para comprobar si la matriz está ordenada
    bool resultado = esta_ordenada_matriz(A, 0, A.size(), 0, A[0].size());

    // Imprimir el resultado
    if (resultado) {
        std::cout << "La matriz está ordenada por filas y columnas.\n";
    } else {
        std::cout << "La matriz NO está ordenada por filas y columnas.\n";
    }
}

// Función que verifica si es válido asignar el color k al vértice i
bool Ejercicios::es_candidato_valido(int k, int i, const vector<int>& sol, const vector<vector<int>>& A) {
    // Verificar los vértices adyacentes a i
    for (int j = 0; j < i; j++) {
        if (A[j][i] == 1 && sol[j] == k) {
            return false; // El color k ya está en uno de los vértices adyacentes
        }
    }
    return true;
}

// Función recursiva de backtracking para colorear el grafo
bool Ejercicios::colorear_backtracking(int i, int m, vector<int>& sol, const vector<vector<int>>& A) {
    int n = A.size();

    // Caso base: Si todos los vértices han sido coloreados
    if (i == n) {
        // Opcional: Imprimir la solución
        for (int j = 0; j < n; j++) {
            cout << sol[j] << " ";
        }
        cout << endl;
        return true;
    }

    // Intentar asignar colores a los vértices
    for (int k = 0; k < m; k++) {
        // Verificar si el color k es válido para el vértice i
        if (es_candidato_valido(k, i, sol, A)) {
            sol[i] = k;  // Asignar el color k al vértice i

            // Llamada recursiva para el siguiente vértice
            if (colorear_backtracking(i + 1, m, sol, A)) {
                return true;
            }

            // Si no se puede colorear con este color, deshacer la asignación
            sol[i] = -1;
        }
    }

    // No se pudo colorear el vértice i con ningún color, regresar
    return false;
}

// Función que inicia el proceso de coloreado
bool Ejercicios::puede_colorear(const vector<vector<int>>& A, int m) {
    int n = A.size();
    vector<int> sol(n, -1); // Solución parcial, -1 indica que no se ha asignado un color

    return colorear_backtracking(0, m, sol, A);
}

void Ejercicios::ex_pag42() {
    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);

    // Definir el grafo (matriz de adyacencia)
    vector<vector<int>> A = {
        {0, 1, 1, 1, 1},
        {1, 0, 1, 0, 0},
        {1, 1, 0, 0, 1},
        {1, 0, 0, 0, 0},
        {1, 0, 1, 0, 0}
    };

    // Número de colores que se desean usar
    int m = 3;

    // Verificar si es posible colorear el grafo con m colores
    if (puede_colorear(A, m)) {
        cout << "Es posible colorear el grafo con " << m << " colores." << endl;
    } else {
        cout << "No es posible colorear el grafo con " << m << " colores." << endl;
    }
}

void Ejercicios::ex_pag45() {
    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);

    int n;
    std::cout << "Ingrese un valor de n (n >= 1): ";
    std::cin >> n;

    if (n < 1) {
        std::cout << "Error: n debe ser mayor o igual a 1." << std::endl;
        return;
    }

    // Cálculo de log4(n) y log2(n)
    double log2_n = log2(n);
    double log4_n = log2_n / log2(4); // log4(n) = log2(n) / log2(4) = log2(n) / 2

    // Demostración de la cota inferior (Ω)
    double C1 = 0.25; // C1 = 1/4
    double n1 = 1;
    bool cumple_omega = (0.5 * log2_n >= C1 * log2_n);

    // Demostración de la cota superior (O)
    double C2 = 1; // C2 = 1
    double n2 = 1;
    bool cumple_O = (0.5 * log2_n <= C2 * log2_n);

    // n0 = max(n1, n2)
    double n0 = std::max(n1, n2);

    // Resultado de la demostración
    std::cout << "log4(n) = " << log4_n << std::endl;
    std::cout << "log2(n) = " << log2_n << std::endl;
    
    if (cumple_omega && cumple_O) {
        std::cout << "Se ha demostrado que log4(n) ∈ Θ(log2(n)) con n0 = " << n0 << std::endl;
    } else {
        std::cout << "No se ha podido demostrar la pertenencia a Θ." << std::endl;
    }
}

#include <iostream>
#include <cmath>

void Ejercicios::ex_pag46() {
    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);

    int j, n;
    std::cout << "Ingrese el valor de j: ";
    std::cin >> j;
    std::cout << "Ingrese el valor de n: ";
    std::cin >> n;

    if (j < 1) {
        std::cout << "El valor de j debe ser mayor o igual a 1." << std::endl;
        return;
    }

    // Primer término
    int term1 = j;

    // Segundo término
    int term2 = j * j;

    // Tercer término: -2 * (j(j + 1) / 2)
    int term3 = -2 * (j * (j + 1) / 2);

    // Cuarto término: 6 * (2j + 1) * j(j + 1) / 6
    int term4 = (2 * j + 1) * j * (j + 1) / 6;

    // Quinto término: nj^2
    int term5 = n * j * j;

    // Sexto término: 8n * (j(j + 1) / 2)
    int term6 = 8 * n * (j * (j + 1) / 2);

    // Séptimo término: 3 * (4^(j+1) - 4) / (4 - 1)
    int term7 = 3 * (pow(4, j + 1) - 4) / 3;

    // Resultado final
    int resultado = term1 - term2 + term3 + term4 + term5 + term6 + term7;

    std::cout << "El resultado de la suma es: " << resultado << std::endl;
}

void Ejercicios::ex_pag47() {
    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);

    int n;
    cout << "Ingrese el valor de n: ";
    cin >> n;

    if (n <= 0) {
        cout << "Error: n debe ser un entero positivo." << endl;
        return;
    }

    // Solución 1: Aproximación por integrales
    double cota_inferior_integral = exp(n - 1) - exp(-1); // e^(n-1) - e^(-1)
    double cota_superior_integral = exp(n) - 1;          // e^n - 1

    // Solución 2: Serie geométrica
    double suma_geometrica = (exp(n) - 1) / (exp(1) - 1); // (e^n - 1) / (e - 1)

    // Mostrar resultados
    cout << "Cota inferior (aproximación por integrales): " << cota_inferior_integral << endl;
    cout << "Cota superior (aproximación por integrales): " << cota_superior_integral << endl;
    cout << "Valor exacto (serie geométrica): " << suma_geometrica << endl;
}

void Ejercicios::ex_pag48() {
    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);

    int n;
    cout << "Ingrese el valor de n (debe ser una potencia de 4, por ejemplo, 1, 4, 16, 64, ...): ";
    cin >> n;

    // Verificar si n es una potencia de 4
    if (n <= 0 || (n & (n - 1)) != 0 || (log2(n) / 2) != floor(log2(n) / 2)) {
        cout << "Error: n no es una potencia de 4." << endl;
        return;
    }

    // Cambio de variable: n = 4^k => k = log4(n)
    double k = log2(n) / 2; // log4(n) = log2(n) / 2

    // Calcular T(n) usando la solución de la recurrencia
    double T_n = 5 * sqrt(n) - 4 - 2 * k;

    // Mostrar el resultado
    cout << "El valor de T(n) es: " << T_n << endl;
    cout << "Complejidad: Θ(√n)" << endl;
}

void Ejercicios::ex_pag49() {
    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);

    int n;
    cout << "Ingrese el valor de n (debe ser una potencia de 4, por ejemplo, 1, 4, 16, 64, ...): ";
    cin >> n;

    // Verificar si n es una potencia de 4
    if (n <= 0 || (n & (n - 1)) != 0 || (log2(n) / 2) != floor(log2(n) / 2)) {
        cout << "Error: n no es una potencia de 4." << endl;
        return;
    }

    // Cambio de variable: n = 4^k => k = log4(n)
    double k = log2(n) / 2; // log4(n) = log2(n) / 2

    // Calcular T(n) usando la solución de la recurrencia
    double T_n = sqrt(n) + sqrt(n) * k;

    // Mostrar el resultado
    cout << "El valor de T(n) es: " << T_n << endl;
    cout << "Complejidad: Θ(√n log n)" << endl;
}

pair<vector<double>, vector<double>> Ejercicios::extrae_indices_pares_impares(const vector<double>& a) {
    int n = a.size();

    // Caso base: lista vacía
    if (n == 0) {
        return make_pair(vector<double>(), vector<double>());
    }
    // Caso base: lista con un solo elemento
    else if (n == 1) {
        return make_pair(a, vector<double>());
    }
    // Caso recursivo
    else {
        // Llamada recursiva para la lista sin el último elemento
        auto [lista_pares, lista_impares] = extrae_indices_pares_impares(vector<double>(a.begin(), a.end() - 1));

        // Si la longitud de la lista original es par, el último elemento va a la lista de impares
        if (n % 2 == 0) {
            lista_impares.push_back(a[n - 1]);
        }
        // Si la longitud de la lista original es impar, el último elemento va a la lista de pares
        else {
            lista_pares.push_back(a[n - 1]);
        }

        return make_pair(lista_pares, lista_impares);
    }
}

void Ejercicios::ex_pag51() {
    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);

    // Ejemplo de lista de entrada
    vector<double> a = {3, 6, 5, 7, 0, 9, 2};

    // Llamada a la función recursiva
    auto [apar, aimpar] = extrae_indices_pares_impares(a);

    // Mostrar resultados
    cout << "Lista original: ";
    for (double num : a) {
        cout << num << " ";
    }
    cout << endl;

    cout << "Elementos en índices pares: ";
    for (double num : apar) {
        cout << num << " ";
    }
    cout << endl;

    cout << "Elementos en índices impares: ";
    for (double num : aimpar) {
        cout << num << " ";
    }
    cout << endl;
}

// Función recursiva para evaluar el polinomio usando Divide y Vencerás
double Ejercicios::evalua_polinomio(const vector<double>& c, double x) {
    // Caso base: si el polinomio es una constante
    if (c.size() == 1) {
        return c[0];
    }
    // Caso recursivo: dividir el polinomio en partes pares e impares
    auto [cpares, cimpares] = extrae_indices_pares_impares(c);

    // Evaluar recursivamente Ppares(x^2) y Pimpares(x^2)
    double Ppares = evalua_polinomio(cpares, x * x);
    double Pimpares = evalua_polinomio(cimpares, x * x);

    // Combinar resultados: P(x) = Ppares(x^2) + x * Pimpares(x^2)
    return Ppares + x * Pimpares;
}

void Ejercicios::ex_pag52() {
    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);

    // Ejemplo de coeficientes del polinomio: P(x) = 2x^6 + 9x^5 + 0x^4 + 7x^3 + 5x^2 + 6x + 3
    vector<double> coeficientes = {3, 6, 5, 7, 0, 9, 2};

    // Valor de x para evaluar el polinomio
    double x = 2.0;

    // Evaluar el polinomio
    double resultado = evalua_polinomio(coeficientes, x);

    // Mostrar resultados
    cout << "Coeficientes del polinomio: ";
    for (double coef : coeficientes) {
        cout << coef << " ";
    }
    cout << endl;

    cout << "Valor de x: " << x << endl;
    cout << "Resultado de evaluar el polinomio: " << resultado << endl;
}

int Ejercicios::factorial(int n) {
    if (n <= 1) return 1;
    return n * factorial(n - 1);
}

// Función recursiva para generar permutaciones con repetición
int Ejercicios::genera_permutaciones_repeticion(int i, vector<string>& sol, vector<int>& r, const vector<string>& a) {
    int n = sol.size();
    int m = a.size();

    // Caso base: se ha completado una permutación
    if (i == n) {
        for (int j = 0; j < n; ++j) {
            cout << sol[j] << " ";
        }
        cout << endl;
        return 1; // Se ha generado una permutación válida
    }

    int s = 0; // Contador de permutaciones generadas

    // Generar candidatos (todos los elementos posibles)
    for (int k = 0; k < m; ++k) {
        // Comprobar si el candidato es válido (r[k] > 0)
        if (r[k] > 0) {
            // Incluir el candidato en la solución parcial
            sol[i] = a[k];

            // Decrementar el número de repeticiones del candidato
            r[k]--;

            // Expandir la solución parcial a partir de la posición i+1
            s += genera_permutaciones_repeticion(i + 1, sol, r, a);

            // Incrementar el número de repeticiones del candidato (backtracking)
            r[k]++;
        }
    }

    return s; // Devolver el número de permutaciones generadas
}

void Ejercicios::ex_pag53() {
    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);

    // Ejemplo de entrada
    vector<string> a = {"a", "b", "c"};
    vector<int> r = {1, 2, 1};

    // Calcular el tamaño de la permutación (n = r0 + r1 + ... + rm-1)
    int n = 0;
    for (int rep : r) {
        n += rep;
    }

    // Vector para almacenar la solución parcial
    vector<string> sol(n);

    // Generar permutaciones con repetición
    int nsols = genera_permutaciones_repeticion(0, sol, r, a);

    // Mostrar el número de permutaciones generadas
    cout << "Permutaciones con repetición halladas: " << nsols << endl;

    // Comprobación opcional: calcular el número teórico de permutaciones
    int p = 1;
    for (int rep : r) {
        p *= factorial(rep);
    }
    int permutaciones_teoricas = factorial(n) / p;
    cout << "Permutaciones con repetición correctas: " << permutaciones_teoricas << endl;
}

void Ejercicios::ex_pag56() {
    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);
}

void Ejercicios::ex_pag58() {
    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);
}

void Ejercicios::ex_pag59() {
    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);
}

void Ejercicios::ex_pag62() {
    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);
}

void Ejercicios::ex_pag63() {
    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);
}

void Ejercicios::ex_pag65() {
    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);
}

void Ejercicios::ex_pag68() {
    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);
}

void Ejercicios::ex_pag69() {
    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);
}

void Ejercicios::ex_pag70() {
    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);
}

void Ejercicios::ex_pag71() {
    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);
}

void Ejercicios::ex_pag73() {
    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);
}

void Ejercicios::ex_pag74() {
    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);
}

void Ejercicios::ex_pag76() {
    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);
}

void Ejercicios::ex_pag78() {
    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);
}

void Ejercicios::ex_pag81() {
    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);
}

void Ejercicios::ex_pag82() {
    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);
}

void Ejercicios::ex_pag83() {
    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);
}

void Ejercicios::ex_pag85() {
    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);
}

void Ejercicios::ex_pag89_1() {
    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);
    cout<<"Ejercicio pag 89_1"<<endl;
}

void Ejercicios::ex_pag89_2() {
    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);
    cout<<"Ejercicio pag 89_2"<<endl;
}

void Ejercicios::ex_pag90() {
    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);
}

void Ejercicios::ex_pag92_1() {
    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);
}

void Ejercicios::ex_pag92_2() {
    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);
}

void Ejercicios::ex_pag93_3() {
    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);
}

void Ejercicios::ex_pag93_4() {
    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);
}

void Ejercicios::ex_pag95_1() {
    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);
}

void Ejercicios::ex_pag95_2() {
    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);
}

void Ejercicios::ex_pag95_3() {
    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);
}

void Ejercicios::ex_pag97_1() {
    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);
}

void Ejercicios::ex_pag97_2() {
    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);
}

void Ejercicios::ex_pag97_3() {
    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);
}

void Ejercicios::ex_pag99_1() {
    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);
}

void Ejercicios::ex_pag99_2() {
    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);
}

void Ejercicios::ex_pag99_3() {
    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);
}

void Ejercicios::ex_pag99_4() {
    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);
}

void Ejercicios::ex_pag101_1() {
    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);
}

void Ejercicios::ex_pag101_2() {
    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);
}

void Ejercicios::ex_pag101_3() {
    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);
}

void Ejercicios::ex_pag103_1() {
    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);
}

void Ejercicios::ex_pag103_2() {
    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);
}

void Ejercicios::ex_pag103_3() {
    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);
}

void Ejercicios::ex_pag105_1() {
    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);
}

void Ejercicios::ex_pag105_2() {
    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);
}

void Ejercicios::ex_pag105_3() {
    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);
}

void Ejercicios::ex_pag107() {
    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);
}

void Ejercicios::ex_pag108() {
    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);
}

void Ejercicios::ex_pag110_1() {
    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);
}

void Ejercicios::ex_pag110_2() {
    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);
}

void Ejercicios::ex_pag110_3() {
    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);
}

void Ejercicios::ex_pag110_4() {
    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);
}

void Ejercicios::ex_pag110_5() {
    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);
}

void Ejercicios::ex_pag110_6() {
    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);
}

void Ejercicios::ex_pag110_7() {
    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);
}

void Ejercicios::ex_pag110_8() {
    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);
}

void Ejercicios::ex_pag111_9() {
    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);
}

void Ejercicios::ex_pag111_10() {
    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);
}

void Ejercicios::ex_pag112_11() {
    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);
}

void Ejercicios::ex_pag112_12() {
    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);
}

void Ejercicios::ex_pag112_13() {
    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);
}

void Ejercicios::ex_pag112_14() {
    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);
}

void Ejercicios::ex_pag112_15() {
    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);
}

void Ejercicios::ex_pag113_16() {
    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);
}

void Ejercicios::ex_pag113_17() {
    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);
}

void Ejercicios::ex_pag113_18() {
    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);
}

void Ejercicios::ex_pag114() {
    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);
}

void Ejercicios::ex_pag115() {
    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);
}

void Ejercicios::ex_pag116() {
    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);
}

void Ejercicios::ex_pag117() {
    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);
}

void Ejercicios::ex_pag118() {
    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);
}

void Ejercicios::ex_pag120_6() {
    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);
}

void Ejercicios::ex_pag120_7() {
    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);
}

void Ejercicios::ex_pag121() {
    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);
}

void Ejercicios::ex_pag123() {
    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);
}

void Ejercicios::ex_pag125() {
    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);
}

void Ejercicios::ex_pag127() {
    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);
}

void Ejercicios::ex_pag129() {
    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);
}

void Ejercicios::ex_pag132() {
    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);
}

void Ejercicios::ex_pag136() {
    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);
}

void Ejercicios::ex_pag138() {
    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);
}

void Ejercicios::ex_pag139_1() {
    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);
}

void Ejercicios::ex_pag139_2() {
    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);
}

void Ejercicios::ex_pag139_3() {
    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);
}

void Ejercicios::ex_pag139_4() {
    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);
}

void Ejercicios::ex_pag139_5() {
    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);
}

void Ejercicios::ex_pag139_6() {
    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);
}

void Ejercicios::ex_pag139_7() {
    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);
}

void Ejercicios::ex_pag140() {
    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);
}

void Ejercicios::ex_pag141_9() {
    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);
}

void Ejercicios::ex_pag141_10() {
    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);
}

void Ejercicios::ex_pag141_11() {
    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);
}

void Ejercicios::ex_pag141_12() {
    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);
}

void Ejercicios::ex_pag142_13() {
    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);
}

void Ejercicios::ex_pag142_14() {
    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);
}

void Ejercicios::ex_pag143_15() {
    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);
}

void Ejercicios::ex_pag143_16() {
    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);
}

void Ejercicios::ex_pag144_1() {
    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);
}

void Ejercicios::ex_pag144_2() {
    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);
}

void Ejercicios::ex_pag144_3() {
    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);
}

void Ejercicios::ex_pag144_4() {
    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);
}

void Ejercicios::ex_pag145_5() {
    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);
}

void Ejercicios::ex_pag145_6() {
    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);
}

void Ejercicios::ex_pag145_7() {
    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);
}

void Ejercicios::ex_pag145_8() {
    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);
}

void Ejercicios::ex_pag145_9() {
    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);
}

void Ejercicios::ex_pag145_10() {
    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);
}

void Ejercicios::ex_pag145_11() {
    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);
}

void Ejercicios::ex_pag145_12() {
    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);
}

void Ejercicios::ex_pag146_13() {
    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);
}

void Ejercicios::ex_pag146_14() {
    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);
}

void Ejercicios::ex_pag146_15() {
    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);
}

void Ejercicios::ex_pag146_16() {
    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);
}

void Ejercicios::ex_pag147() {
    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);
}

void Ejercicios::ex_pag148_1() {
    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);
}

void Ejercicios::ex_pag148_2() {
    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);
}

void Ejercicios::ex_pag148_3() {
    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);
}

void Ejercicios::ex_pag148_4() {
    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);
}

void Ejercicios::ex_pag149_5() {
    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);
}

void Ejercicios::ex_pag149_6() {
    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);
}

void Ejercicios::ex_pag149_7() {
    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);
}

void Ejercicios::ex_pag149_8() {
    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);
}

void Ejercicios::ex_pag150() {
    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);
}

void Ejercicios::ex_pag151_1() {
    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);
}

void Ejercicios::ex_pag151_2() {
    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);
}

void Ejercicios::ex_pag151_3() {
    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);
}

void Ejercicios::ex_pag151_4() {
    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);
}

void Ejercicios::ex_pag151_5() {
    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);
}

void Ejercicios::ex_pag151_6() {
    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);
}

void Ejercicios::ex_pag152_7() {
    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);
}

void Ejercicios::ex_pag152_8() {
    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);
}

void Ejercicios::ex_pag153_1() {
    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);
}

void Ejercicios::ex_pag153_2() {
    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);
}

void Ejercicios::ex_pag154_3() {
    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);
}

void Ejercicios::ex_pag154_4() {
    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);
}

void Ejercicios::ex_pag155_5() {
    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);
}

void Ejercicios::ex_pag155_6() {
    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);
}

void Ejercicios::ex_pag156_7() {
    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);
}

void Ejercicios::ex_pag156_8() {
    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);
}

void Ejercicios::ex_pag157_1() {
    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);
}

void Ejercicios::ex_pag157_2() {
    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);
}

void Ejercicios::ex_pag158_3() {
    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);
}

void Ejercicios::ex_pag158_4() {
    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);
}

void Ejercicios::ex_pag159_5() {
    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);
}

void Ejercicios::ex_pag159_6() {
    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);
}

void Ejercicios::ex_pag159_7() {
    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);
}

void Ejercicios::ex_pag159_8() {
    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);
}

void Ejercicios::ex_pag159_9() {
    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);
}

void Ejercicios::ex_pag160_1() {
    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);
}

void Ejercicios::ex_pag160_2() {
    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);
}

void Ejercicios::ex_pag160_3() {
    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);
}

void Ejercicios::ex_pag160_4() {
    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);
}

void Ejercicios::ex_pag161_5() {
    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);
}

void Ejercicios::ex_pag161_6() {
    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);
}

void Ejercicios::ex_pag161_7() {
    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);
}

void Ejercicios::ex_pag161_8() {
    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);
}