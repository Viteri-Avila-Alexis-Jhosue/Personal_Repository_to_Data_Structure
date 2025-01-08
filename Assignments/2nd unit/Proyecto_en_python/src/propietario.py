class Propietario:
    def __init__(self, nombre="", apellido="", cedula="", correo=""):
        self.nombre = nombre
        self.apellido = apellido
        self.cedula = cedula
        self.correo = correo
        self.placas = []

    def set_nombre(self, nombre):
        self.nombre = nombre

    def set_apellido(self, apellido):
        self.apellido = apellido

    def set_cedula(self, cedula):
        self.cedula = cedula

    def set_correo(self, correo):
        self.correo = correo

    def eliminar_placa(self, placa):
        if placa in self.placas:
            self.placas.remove(placa)
            print("Placa eliminada exitosamente.")
        else:
            print("Placa no encontrada.")

    def get_nombre(self):
        return self.nombre

    def get_apellido(self):
        return self.apellido

    def get_cedula(self):
        return self.cedula

    def get_correo(self):
        return self.correo

    def agregar_placa(self, placa):
        self.placas.append(placa)

    def get_placas(self):
        return self.placas

    def __str__(self):
        result = f"Nombre: {self.nombre}, Apellido: {self.apellido}, Cedula: {self.cedula}, Correo: {self.correo}, Placas: {' '.join(self.placas)}"
        return result

def agregar_propietario(lista_propietarios):
    from validaciones import Validaciones
    validaciones = Validaciones()
    nombre = validaciones.ingresar_string("Ingrese el nombre del propietario: ")
    apellido = validaciones.ingresar_string("Ingrese el apellido del propietario: ")
    cedula = ""
    while True:
        cedula = validaciones.ingresar_cedula("Ingrese la cedula del propietario: ")
        if validaciones.validar_cedula(cedula):
            break
        print("Cedula invalida. Intente de nuevo.")
    
    correo = ""
    while True:
        correo = validaciones.ingresar_correo("Ingrese el correo electronico del propietario: ")
        if validaciones.validar_correo(correo):
            break
        print("Correo invalido. Intente de nuevo.")

    nuevo_propietario = Propietario(nombre, apellido, cedula, correo)
    lista_propietarios.agregar_propietario(nuevo_propietario)
    print("Propietario agregado exitosamente.")

def eliminar_placa_propietario(lista_propietarios):
    from validacion_placa import Placa
    from validaciones import Validaciones
    validaciones = Validaciones()
    validador = Placa()
    cedula = validaciones.ingresar_cedula("Ingrese la cedula del propietario: ")
    propietario = lista_propietarios.buscar_propietario_por_cedula(cedula)
    if propietario:
        placa = validador.ingresar_placa(None)
        propietario.eliminar_placa(placa)
    else:
        print("Propietario no encontrado.")