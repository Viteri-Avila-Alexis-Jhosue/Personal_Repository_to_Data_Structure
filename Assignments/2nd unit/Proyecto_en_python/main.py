from src.lista_propietarios import ListaPropietarios
from src.lista import ListaCircularDoble
from src.coche import Coche
from src.menu import menu

def main():
    lista_propietarios = ListaPropietarios()
    lista_propietarios.cargar_archivo("output/propietarios.txt")

    lista_coches_historial = ListaCircularDoble()
    lista_coches_historial.cargar_archivo("output/autos_historial.txt")

    lista_coches = ListaCircularDoble()
    lista_coches.cargar_archivo("output/autos.txt")

    input("Presione Enter para continuar...")

    menu(lista_coches, lista_coches_historial, lista_propietarios)

if __name__ == "__main__":
    main()