import json
from src.propietario import Propietario
from src.lista import ListaCircularDoble

class ListaPropietarios:
    def __init__(self):
        self.propietarios = []

    def agregar_propietario(self, propietario):
        self.propietarios.append(propietario)

    def buscar_propietario_por_cedula(self, cedula):
        for propietario in self.propietarios:
            if propietario.get_cedula() == cedula:
                return propietario
        return None

    def mostrar_propietarios(self):
        for propietario in self.propietarios:
            print(propietario)

    def esta_vacia(self):
        return len(self.propietarios) == 0

    def cargar_archivo(self, archivo):
        try:
            with open(archivo, 'r') as file:
                for linea in file:
                    datos = linea.strip().split(',')
                    if len(datos) < 4:
                        continue
                    nombre, apellido, cedula, correo = datos[:4]
                    propietario = Propietario(nombre, apellido, cedula, correo)
                    for placa in datos[4:]:
                        propietario.agregar_placa(ListaCircularDoble.descifrar_texto(placa))
                    self.agregar_propietario(propietario)
        except FileNotFoundError:
            print(f"Error: No se pudo abrir el archivo {archivo}. Creando archivo vacío...")
            with open(archivo, 'w') as nuevo_archivo:
                pass

    def guardar_archivo(self, archivo):
        with open(archivo, 'w') as file:
            for propietario in self.propietarios:
                file.write(f"{propietario.get_nombre()},{propietario.get_apellido()},{propietario.get_cedula()},{propietario.get_correo()}")
                for placa in propietario.get_placas():
                    file.write(f",{ListaCircularDoble.cifrar_texto(placa)}")
                file.write("\n")