from datetime import datetime
from src.propietario import Propietario
from datetime import datetime
from src.propietario import Propietario
from src.lista_propietarios import ListaPropietarios
from src.validaciones import Validaciones
from src.validacion_placa import Placa
from src.menu import menu_interactivo  # Importar la función menu_interactivo

class Coche:
    def __init__(self, placa="", modelo="", color="", marca="", anio=0, propietario=None, hora_ingreso=None, hora_salida=None):
        self.placa = placa
        self.modelo = modelo
        self.color = color
        self.marca = marca
        self.anio = anio
        self.propietario = propietario
        self.hora_ingreso = hora_ingreso if hora_ingreso else datetime.now()
        self.hora_salida = hora_salida

    def set_hora_salida(self, hora):
        self.hora_salida = hora

    def set_placa(self, placa):
        self.placa = placa

    def set_modelo(self, modelo):
        self.modelo = modelo

    def set_marca(self, marca):
        self.marca = marca

    def set_color(self, color):
        self.color = color

    def get_hora_salida(self):
        return self.hora_salida

    def get_placa(self):
        return self.placa

    def get_marca(self):
        return self.marca

    def get_modelo(self):
        return self.modelo

    def get_color(self):
        return self.color

    def get_anio(self):
        return self.anio

    def get_hora(self):
        return self.hora_ingreso

    def get_propietario(self):
        return self.propietario

    def insertar_datos(self, lista, lista_historial, lista_propietarios):
        validaciones = Validaciones()
        validador = Placa()

        while True:
            placa = validador.ingresar_placa(lista.get_primero())
            temp = lista.get_primero()
            placa_duplicada = False

            if temp:
                while True:
                    coche_actual = temp.get_dato()
                    if coche_actual.get_placa() == placa and coche_actual.get_hora_salida() is None:
                        print(f"\nEl coche con la placa {placa} ya está en el parqueadero. Ingrese una placa nueva.")
                        placa_duplicada = True
                        break
                    temp = temp.get_siguiente()
                    if temp == lista.get_primero():
                        break

            if not placa_duplicada:
                break

        temp_historial = lista_historial.get_primero()
        if temp_historial:
            while True:
                coche_historial = temp_historial.get_dato()
                if coche_historial.get_placa() == placa:
                    print(f"\nLa placa {placa} fue encontrada en el historial. Recuperando datos...")
                    modelo = coche_historial.get_modelo()
                    color = coche_historial.get_color()
                    marca = coche_historial.get_marca()

                    print(f"Marca: {marca}\nColor: {color}\nModelo: {modelo}\n")

                    opciones = ["Si", "No"]
                    seleccion = menu_interactivo(opciones, "Auto encontrado en el sistema.\n¿Desea sobreescribir los datos del historial?")

                    if seleccion == 0:
                        print("========================================")
                        print("        Datos Recuperados Exitosamente  ")
                        print("========================================")
                        print(f"\nMarca:    {marca}")
                        print(f"Modelo:   {modelo}")
                        print(f"Color:    {color}")
                        print(f"Placa:    {placa}")

                        while True:
                            cedula = validaciones.ingresar_cedula("Ingrese la cédula del propietario: ")
                            propietario = lista_propietarios.buscar_propietario_por_cedula(cedula)
                            if propietario:
                                propietario.agregar_placa(placa)
                                print("Placa asociada exitosamente al propietario.")
                                lista_propietarios.guardar_archivo("output/propietarios.txt")
                                break
                            else:
                                print("Propietario no encontrado. Intente de nuevo.")

                        return Coche(placa, modelo, color, marca, self.anio, propietario)
                    else:
                        print("\nPor favor, ingrese los datos manualmente:")
                        break

                temp_historial = temp_historial.get_siguiente()
                if temp_historial == lista_historial.get_primero():
                    break

        marca = validaciones.ingresar_string("Ingrese la marca: ")
        color = validaciones.ingresar_string("Ingrese el color: ")
        modelo = validaciones.ingresar_string("Ingrese el modelo: ")

        while True:
            cedula = validaciones.ingresar_cedula("Ingrese la cédula del propietario: ")
            propietario = lista_propietarios.buscar_propietario_por_cedula(cedula)
            if propietario:
                propietario.agregar_placa(placa)
                print("Placa asociada exitosamente al propietario.")
                lista_propietarios.guardar_archivo("output/propietarios.txt")
                break
            else:
                print("Propietario no encontrado. Intente de nuevo.")

        return Coche(placa, modelo, color, marca, self.anio, propietario)

    def __str__(self):
        hora_ingreso_str = self.hora_ingreso.strftime("%Y-%m-%d %H:%M:%S")
        hora_salida_str = self.hora_salida.strftime("%Y-%m-%d %H:%M:%S") if self.hora_salida else "N/A"
        return (f"Placa: {self.placa}\nMarca: {self.marca}\nModelo: {self.modelo}\nColor: {self.color}\n"
                f"----------------------------------------\n"
                f"Hora de Ingreso: {hora_ingreso_str}\n"
                f"----------------------------------------\n"
                f"Hora de Salida: {hora_salida_str}\n"
                f"----------------------------------------")