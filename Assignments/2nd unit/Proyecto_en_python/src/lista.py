from nodo import Nodo
from datetime import datetime
import json
import os
from src.propietario import Propietario  # Importar la clase Propietario
from src.coche import Coche  # Importar la clase Coche

class ListaCircularDoble:
    def __init__(self):
        self.primero = None
        self.ultimo = None

    def get_primero(self):
        return self.primero

    def insertar(self, dato, nombre_archivo):
        nuevo_carro = Nodo(dato)

        if self.primero is None:
            self.primero = nuevo_carro
            self.primero.set_siguiente(self.primero)
            self.primero.set_anterior(self.primero)
            self.ultimo = self.primero
        else:
            self.ultimo.set_siguiente(nuevo_carro)
            nuevo_carro.set_anterior(self.ultimo)
            self.ultimo = nuevo_carro
            self.ultimo.set_siguiente(self.primero)
            self.primero.set_anterior(self.ultimo)

        self.guardar_archivo(nombre_archivo)

    def buscar_por_placa(self, placa):
        if self.primero is None:
            print("La lista está vacía.")
            return

        aux = self.primero
        while True:
            if aux.get_dato().get_placa() == placa:
                print("========================================")
                print("   AUTOMOVIL REGISTRADO")
                print("========================================")
                print(aux.get_dato())
                return
            aux = aux.get_siguiente()
            if aux == self.primero:
                break

        print(f"El coche con la placa {placa} no está en el parqueadero.")

    def mostrar(self, primero):
        if primero is None:
            print("La lista está vacía.")
            return

        aux = primero
        print("AUTOMOVIL REGISTRADO")
        print("========================================")
        print(aux.get_dato())

        aux = aux.get_siguiente()
        while aux != primero:
            print(aux.get_dato())
            aux = aux.get_siguiente()

    def eliminar_por_placa(self, placa):
        if self.primero is None:
            print("La lista está vacía.")
            return

        aux = self.primero
        anterior = None

        if self.primero == self.ultimo and self.primero.get_dato().get_placa() == placa:
            self.primero = None
            self.ultimo = None
            print(f"El coche con la placa {placa} ha sido eliminado.")
            self.guardar_archivo("output/autos.txt")
            return

        while True:
            if aux.get_dato().get_placa() == placa:
                if aux == self.primero:
                    self.primero = self.primero.get_siguiente()
                    self.primero.set_anterior(self.ultimo)
                    self.ultimo.set_siguiente(self.primero)
                elif aux == self.ultimo:
                    self.ultimo = self.ultimo.get_anterior()
                    self.ultimo.set_siguiente(self.primero)
                    self.primero.set_anterior(self.ultimo)
                else:
                    anterior = aux.get_anterior()
                    anterior.set_siguiente(aux.get_siguiente())
                    aux.get_siguiente().set_anterior(anterior)

                print(f"El coche con la placa {placa} ha sido eliminado.")
                self.guardar_archivo("output/autos.txt")
                return

            aux = aux.get_siguiente()
            if aux == self.primero:
                break

        print(f"El coche con la placa {placa} no se encontró en el parqueadero.")

    def busqueda_avanzada(self, criterio, valor_inicio, valor_fin):
        if self.primero is None:
            print("La lista está vacía.")
            return

        aux = self.primero
        encontrado = False

        while True:
            if criterio == "marca" and aux.get_dato().get_marca().lower() == valor_inicio.lower():
                print("========================================")
                print("   AUTOMOVIL REGISTRADO POR MARCA")
                print("========================================")
                print(aux.get_dato())
                encontrado = True
            elif criterio == "modelo" and aux.get_dato().get_modelo().lower() == valor_inicio.lower():
                print("========================================")
                print("   AUTOMOVIL REGISTRADO POR MODELO")
                print("========================================")
                print(aux.get_dato())
                encontrado = True
            elif criterio == "color" and aux.get_dato().get_color().lower() == valor_inicio.lower():
                print("========================================")
                print("   AUTOMOVIL REGISTRADO POR COLOR")
                print("========================================")
                print(aux.get_dato())
                encontrado = True
            elif criterio == "hora":
                hora_ingreso = aux.get_dato().get_hora()
                hora_actual = hora_ingreso.strftime("%H:%M:%S")
                if valor_inicio <= hora_actual <= valor_fin:
                    print("========================================")
                    print("   AUTOMOVIL REGISTRADO POR HORA")
                    print("========================================")
                    print(aux.get_dato())
                    encontrado = True

            aux = aux.get_siguiente()
            if aux == self.primero:
                break

        if not encontrado:
            print(f"No se encontró ningún automóvil con el criterio de búsqueda: {criterio}")

    def cargar_archivo(self, nombre_archivo):
        if not os.path.exists(nombre_archivo):
            print(f"Error: No se pudo abrir el archivo {nombre_archivo}. Creando archivo vacío...")
            with open(nombre_archivo, 'w') as nuevo_archivo:
                pass
            return

        with open(nombre_archivo, 'r') as archivo:
            for linea in archivo:
                datos = linea.strip().split(',')
                if len(datos) != 6:
                    print(f"Error: Formato de línea inválido: {linea}")
                    continue

                placa, modelo, color, marca, fecha_ingreso, hora_salida = datos
                placa = self.descifrar_texto(placa)

                hora_ingreso = datetime.strptime(fecha_ingreso, "%a %b %d %H:%M:%S %Y")
                hora_salida = datetime.strptime(hora_salida, "%a %b %d %H:%M:%S %Y") if hora_salida != "N/A" else None

                propietario = Propietario("Desconocido", "Desconocido", "0000000000", "desconocido@correo.com")
                coche = Coche(placa, modelo, color, marca, hora_ingreso, hora_salida, propietario)

                self.insertar(coche, nombre_archivo)

    def guardar_archivo(self, nombre_archivo):
        with open(nombre_archivo, 'w') as archivo:
            if self.primero is None:
                return

            actual = self.primero
            while True:
                coche = actual.get_dato()
                placa_cifrada = self.cifrar_texto(coche.get_placa())
                hora_ingreso = coche.get_hora().strftime("%a %b %d %H:%M:%S %Y")
                hora_salida = coche.get_hora_salida().strftime("%a %b %d %H:%M:%S %Y") if coche.get_hora_salida() else "N/A"

                archivo.write(f"{placa_cifrada},{coche.get_modelo()},{coche.get_color()},{coche.get_marca()},{hora_ingreso},{hora_salida}\n")

                actual = actual.get_siguiente()
                if actual == self.primero:
                    break

    @staticmethod
    def cifrar_texto(texto):
        texto_cifrado = ""
        for c in texto:
            if c.isdigit():
                texto_cifrado += chr((ord(c) - ord('0') + 2) % 10 + ord('0'))
            elif c.isalpha():
                if c.isupper():
                    texto_cifrado += chr((ord(c) - ord('A') + 2) % 26 + ord('A'))
                else:
                    texto_cifrado += chr((ord(c) - ord('a') + 2) % 26 + ord('a'))
            else:
                texto_cifrado += c
        return texto_cifrado

    @staticmethod
    def descifrar_texto(texto):
        texto_descifrado = ""
        for c in texto:
            if c.isdigit():
                texto_descifrado += chr((ord(c) - ord('0') - 2 + 10) % 10 + ord('0'))
            elif c.isalpha():
                if c.isupper():
                    texto_descifrado += chr((ord(c) - ord('A') - 2 + 26) % 26 + ord('A'))
                else:
                    texto_descifrado += chr((ord(c) - ord('a') - 2 + 26) % 26 + ord('a'))
            else:
                texto_descifrado += c
        return texto_descifrado

    def salir_del_parqueadero(self, placa):
        actual = self.primero
        encontrado = False

        while True:
            coche = actual.get_dato()
            if coche.get_placa() == placa:
                if coche.get_hora_salida() is not None:
                    actual = actual.get_siguiente()
                    continue

                coche.set_hora_salida(datetime.now())
                actual.set_dato(coche)
                print(f"El coche con placa {placa} ha salido del parqueadero.")
                encontrado = True

            actual = actual.get_siguiente()
            if actual == self.primero:
                break

        if encontrado:
            self.guardar_archivo("output/autos_historial.txt")
        else:
            print(f"Coche con placa {placa} no encontrado en el parqueadero.")