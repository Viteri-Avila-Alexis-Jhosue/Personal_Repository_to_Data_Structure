import re

class Placa:
    def ingresar_placa(self, aux):
        provincias_validas = {
            "A", "B", "C", "E", "G", "H", "I", "J", "K", "L", "M", "N", "O", "P", "Q", "R", "S", "T", "U", "V", "W", "X", "Y", "Z"
        }

        while True:
            placa = input("Ingrese la placa: ").strip().upper()

            if len(placa) != 7:
                print("\nLa placa debe tener exactamente 7 caracteres. Intente de nuevo.")
                continue

            if placa[0] not in provincias_validas:
                print("\nInicial de provincia no válida. Intente de nuevo.")
                continue

            if not re.match(r"^[A-Z]{1,3}[0-9]{4}$", placa):
                print("\nFormato de placa incorrecto. Intente de nuevo.")
                continue

            break

        return placa