class Nodo:
    def __init__(self, dato):
        self.dato = dato
        self.siguiente = None
        self.anterior = None

    def get_dato(self):
        return self.dato

    def set_dato(self, dato):
        self.dato = dato

    def set_siguiente(self, siguiente):
        self.siguiente = siguiente

    def get_siguiente(self):
        return self.siguiente

    def set_anterior(self, anterior):
        self.anterior = anterior

    def get_anterior(self):
        return self.anterior