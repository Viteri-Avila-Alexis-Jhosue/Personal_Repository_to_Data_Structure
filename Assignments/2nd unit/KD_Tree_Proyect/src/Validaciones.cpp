
#include "../include/Validaciones.h"  
#include <iostream>
#include <conio.h>
#include <regex>

string Validaciones::ingresarString(const string &msj)
{
    string input;
    char c;

    cout << msj;

    while (true)
    {
        c = getch();  

        if (isalpha(c))
        {
            input += c;
            cout << c;
        }
        else if (c == '\b' && !input.empty())  
        {
            input.pop_back();
            cout << "\b \b";
        }
        else if (c == '\r')  
        {
            if (!input.empty())  
            {
                break;
            }
            else
            {
                cout << "\a";  
            }
        }
        else
        {
            cout << "\a";  
        }
    }

    cout << endl;
    return input;
}

string Validaciones::ingresarCedula(const string &msj)
{
    string cedula;
    char c;

    cout << msj;

    while (true)
    {
        c = _getch();  

        if (isdigit(c))
        {
            cedula += c;
            cout << c;
        }
        else if (c == '\b' && !cedula.empty())  
        {
            cedula.pop_back();
            cout << "\b \b";
        }
        else if (c == '\r')  
        {
            if (!cedula.empty())  
            {
                break;
            }
            else
            {
                cout << "\a";  
            }
        }
        else
        {
            cout << "\a";  
        }
    }

    cout << endl;
    return cedula;
}

string Validaciones::ingresarCorreo(const string &msj)
{
    string correo;
    cout << msj;
    cin >> correo;
    return correo;
}

bool Validaciones::validarCedula(const string &cedula)
{
    if (cedula.length() != 10)
    {
        return false;
    }

    int suma = 0;
    for (int i = 0; i < 9; i++)
    {
        int digito = cedula[i] - '0';
        if (i % 2 == 0)
        {
            digito *= 2;
            if (digito > 9)
            {
                digito -= 9;
            }
        }
        suma += digito;
    }

    int ultimoDigito = cedula[9] - '0';
    int digitoVerificador = (10 - (suma % 10)) % 10;

    return ultimoDigito == digitoVerificador;
}

bool Validaciones::validarCorreo(const string &correo)
{
    const regex pattern(R"((\w+)(\.{1}\w+)*@(\w+)(\.{1}\w+)+)");
    return regex_match(correo, pattern);
}

string Validaciones::ingresarPlaca(const string &msj)
{
    string placa;
    char c;
    const regex pattern(R"([A-Z]{3}\d{4})"); // Formato: tres letras mayúsculas y cuatro dígitos

    cout << msj;

    while (true)
    {
        c = _getch(); // Captura el carácter sin mostrar el eco en consola

        if (isalpha(c) && placa.length() < 3) // Letras (solo las tres primeras posiciones)
        {
            c = toupper(c); // Convierte a mayúscula
            placa += c;
            cout << c; // Muestra la letra en mayúscula
        }
        else if (isdigit(c) && placa.length() >= 3 && placa.length() < 7) // Dígitos (siguientes cuatro posiciones)
        {
            placa += c;
            cout << c; // Muestra el dígito
        }
        else if (c == '\b' && !placa.empty()) // Retroceso para borrar
        {
            placa.pop_back();
            cout << "\b \b"; // Borra el carácter de la consola
        }
        else if (c == '\r') // Enter para confirmar
        {
            if (placa.length() == 7 && regex_match(placa, pattern)) // Validación final
            {
                break;
            }
            else
            {
                cout << "\nFormato inválido. Ingrese nuevamente: ";
                placa.clear();
            }
        }
        else // Cualquier otro símbolo no permitido
        {
            cout << "\a"; // Sonido de alerta para caracteres no válidos
        }
    }

    cout << endl;
    return placa;
}
string Validaciones::ingresarPlacaMoto(const string &msj){
    string placa;
    char c;
    const regex pattern(R"([A-Z]{2}\d{3}[A-Z])"); // Formato: dos letras, tres dígitos, una letra

    cout << msj;

    while (true)
    {
        c = _getch(); // Captura el carácter sin mostrar el eco en consola

        if (isalpha(c) && placa.length() < 2) // Letras (las dos primeras posiciones)
        {
            c = toupper(c); // Convierte a mayúscula
            placa += c;
            cout << c; // Muestra la letra en mayúscula
        }
        else if (isdigit(c) && placa.length() >= 2 && placa.length() < 5) // Dígitos (tres siguientes posiciones)
        {
            placa += c;
            cout << c; // Muestra el dígito
        }
        else if (isalpha(c) && placa.length() == 5) // Última posición, letra
        {
            c = toupper(c); // Convierte a mayúscula
            placa += c;
            cout << c; // Muestra la letra
        }
        else if (c == '\b' && !placa.empty()) // Retroceso para borrar
        {
            placa.pop_back();
            cout << "\b \b"; // Borra el carácter de la consola
        }
        else if (c == '\r') // Enter para confirmar
        {
            if (placa.length() == 6 && regex_match(placa, pattern)) // Validación final
            {
                break;
            }
            else
            {
                cout << "\nFormato inválido. Ingrese nuevamente: ";
                placa.clear();
            }
        }
        else // Cualquier otro símbolo no permitido
        {
            cout << "\a"; // Sonido de alerta para caracteres no válidos
        }
    }

    cout << endl;
    return placa;
}

string Validaciones::ingresarFecha(const string &msj)
{
    string fecha;
    char c;
    const regex pattern(R"(\d{2}/\d{2}/\d{4})"); // Formato: dd/mm/aaaa

    cout << msj;

    while (true)
    {
        c = _getch(); // Captura el carácter sin mostrar el eco en consola

        if (isdigit(c) && fecha.length() < 10) // Dígitos (solo las diez posiciones)
        {
            fecha += c;
            cout << c; // Muestra el dígito

            // Agrega automáticamente las barras después de 2 y 4 dígitos
            if (fecha.length() == 2 || fecha.length() == 5)
            {
                fecha += '/';
                cout << '/'; // Muestra la barra
            }
        }
        else if (c == '\b' && !fecha.empty()) // Retroceso para borrar
        {
            if (fecha.back() == '/') // Evitar borrar la barra
            {
                fecha.pop_back();
                cout << "\b \b"; // Borra la barra de la consola
            }
            else
            {
                fecha.pop_back();
                cout << "\b \b"; // Borra el carácter de la consola
            }
        }
        else if (c == '\r') // Enter para confirmar
        {
            if (fecha.length() == 10 && regex_match(fecha, pattern)) // Validación final
            {
                break;
            }
            else
            {
                cout << "\nFormato inválido. Ingrese nuevamente: ";
                fecha.clear();
                cout << msj;
            }
        }
        else // Cualquier otro símbolo no permitido
        {
            cout << "\a"; // Sonido de alerta para caracteres no válidos
        }
    }

    cout << endl;
    return fecha;
}

string Validaciones::ingresarHora(const string &msj)
{
    string hora;
    char c;
    const regex pattern(R"(\d{2}:\d{2}:\d{2})"); // Formato: hh:mm:ss

    cout << msj;

    while (true)
    {
        c = _getch(); // Captura el carácter sin mostrar el eco en consola

        if (isdigit(c) && hora.length() < 8) // Dígitos (solo las ocho posiciones)
        {
            hora += c;
            cout << c; // Muestra el dígito

            // Agrega automáticamente los dos puntos después de 2 y 5 dígitos
            if (hora.length() == 2 || hora.length() == 5)
            {
                hora += ':';
                cout << ':'; // Muestra el colon
            }
        }
        else if (c == '\b' && !hora.empty()) // Retroceso para borrar
        {
            if (hora.back() == ':') // Evitar borrar los dos puntos
            {
                hora.pop_back();
                cout << "\b \b"; // Borra el dos puntos de la consola
            }
            else
            {
                hora.pop_back();
                cout << "\b \b"; // Borra el carácter de la consola
            }
        }
        else if (c == '\r') // Enter para confirmar
        {
            if (hora.length() == 8 && regex_match(hora, pattern)) // Validación final
            {
                break;
            }
            else
            {
                cout << "\nFormato inválido. Ingrese nuevamente: ";
                hora.clear();
                cout << msj;
            }
        }
        else // Cualquier otro símbolo no permitido
        {
            cout << "\a"; // Sonido de alerta para caracteres no válidos
        }
    }

    cout << endl;
    return hora;
}