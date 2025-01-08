def partition(lista, low, high, comp):
    pivot = lista[high]
    i = low - 1
    for j in range(low, high):
        if comp(lista[j], pivot):
            i += 1
            lista[i], lista[j] = lista[j], lista[i]
    lista[i + 1], lista[high] = lista[high], lista[i + 1]
    return i + 1

def quick_sort(lista, low, high, comp):
    if low < high:
        pi = partition(lista, low, high, comp)
        quick_sort(lista, low, pi - 1, comp)
        quick_sort(lista, pi + 1, high, comp)

def bubble_sort_pass(lista, comp, n):
    if n <= 1:
        return
    for j in range(n - 1):
        if not comp(lista[j], lista[j + 1]):
            lista[j], lista[j + 1] = lista[j + 1], lista[j]

def bubble_sort_recursive(lista, comp, n):
    if n <= 1:
        return
    bubble_sort_pass(lista, comp, n)
    bubble_sort_recursive(lista, comp, n - 1)

def bubble_sort(lista, comp):
    bubble_sort_recursive(lista, comp, len(lista))

def ordenar_lista(lista, comp):
    elementos = []
    aux = lista.get_primero()
    while True:
        elementos.append(aux.get_dato())
        aux = aux.get_siguiente()
        if aux == lista.get_primero():
            break

    quick_sort(elementos, 0, len(elementos) - 1, comp)

    aux = lista.get_primero()
    index = 0
    while True:
        aux.set_dato(elementos[index])
        index += 1
        aux = aux.get_siguiente()
        if aux == lista.get_primero():
            break

    lista.mostrar(lista.get_primero())

def ordenar_lista_bubble_sort(lista, comp):
    elementos = []
    aux = lista.get_primero()
    while True:
        elementos.append(aux.get_dato())
        aux = aux.get_siguiente()
        if aux == lista.get_primero():
            break

    bubble_sort(elementos, comp)

    aux = lista.get_primero()
    index = 0
    while True:
        aux.set_dato(elementos[index])
        index += 1
        aux = aux.get_siguiente()
        if aux == lista.get_primero():
            break

    lista.mostrar(lista.get_primero())

def ordenar_lista_bucket(lista, get_key):
    elementos = []
    aux = lista.get_primero()
    if aux is None:
        print("La lista está vacía.")
        return

    while True:
        elementos.append(aux.get_dato())
        aux = aux.get_siguiente()
        if aux == lista.get_primero():
            break

    bucket_count = 256
    buckets = [[] for _ in range(bucket_count)]

    for item in elementos:
        key = get_key(item)
        if key:
            first_char = key[0].lower()
            bucket_index = ord(first_char)
            buckets[bucket_index].append(item)

    elementos.clear()

    for bucket in buckets:
        bucket.sort(key=get_key)
        elementos.extend(bucket)

    aux = lista.get_primero()
    index = 0
    while True:
        aux.set_dato(elementos[index])
        index += 1
        aux = aux.get_siguiente()
        if aux == lista.get_primero():
            break

    lista.mostrar(lista.get_primero())

def ordenar_lista_shell_sort(lista, comp):
    def contar_elementos():
        n = 0
        aux = lista.get_primero()
        if aux:
            while True:
                n += 1
                aux = aux.get_siguiente()
                if aux == lista.get_primero():
                    break
        return n

    def copiar_lista_a_arreglo(elementos, n):
        aux = lista.get_primero()
        for i in range(n):
            elementos[i] = aux.get_dato()
            aux = aux.get_siguiente()

    def copiar_arreglo_a_lista(elementos, n):
        aux = lista.get_primero()
        for i in range(n):
            aux.set_dato(elementos[i])
            aux = aux.get_siguiente()

    def shell_sort(elementos, n):
        gap = n // 2
        while gap > 0:
            for i in range(gap, n):
                temp = elementos[i]
                j = i
                while j >= gap and comp(temp, elementos[j - gap]):
                    elementos[j] = elementos[j - gap]
                    j -= gap
                elementos[j] = temp
            gap //= 2

    n = contar_elementos()
    elementos = [None] * n
    copiar_lista_a_arreglo(elementos, n)
    shell_sort(elementos, n)
    copiar_arreglo_a_lista(elementos, n)
    lista.mostrar(lista.get_primero())

def radix_sort_by_string(elementos, get_key):
    max_length = max(len(get_key(item)) for item in elementos)
    for i in range(max_length - 1, -1, -1):
        buckets = [[] for _ in range(256)]
        for item in elementos:
            key = get_key(item)
            char_index = len(key) - 1 - i
            char_value = ord(key[char_index]) if char_index >= 0 else 0
            buckets[char_value].append(item)
        elementos.clear()
        for bucket in buckets:
            elementos.extend(bucket)

def radix_sort_by_int(elementos, get_key):
    max_value = max(get_key(item) for item in elementos)
    exp = 1
    while max_value // exp > 0:
        buckets = [[] for _ in range(10)]
        for item in elementos:
            digit = (get_key(item) // exp) % 10
            buckets[digit].append(item)
        elementos.clear()
        for bucket in buckets:
            elementos.extend(bucket)
        exp *= 10

def ordenar_lista_por_radix(lista, get_key):
    elementos = []
    aux = lista.get_primero()
    while True:
        elementos.append(aux.get_dato())
        aux = aux.get_siguiente()
        if aux == lista.get_primero():
            break

    if isinstance(get_key(elementos[0]), str):
        radix_sort_by_string(elementos, get_key)
    elif isinstance(get_key(elementos[0]), int):
        radix_sort_by_int(elementos, get_key)
    else:
        raise TypeError("El tipo de clave no es compatible con Radix Sort")

    aux = lista.get_primero()
    index = 0
    while True:
        aux.set_dato(elementos[index])
        index += 1
        aux = aux.get_siguiente()
        if aux == lista.get_primero():
            break

    lista.mostrar(lista.get_primero())

def ordenar_lista_heap_sort(lista, comp):
    def contar_elementos():
        n = 0
        aux = lista.get_primero()
        if aux:
            while True:
                n += 1
                aux = aux.get_siguiente()
                if aux == lista.get_primero():
                    break
        return n

    def copiar_lista_a_arreglo(elementos, n):
        aux = lista.get_primero()
        for i in range(n):
            elementos[i] = aux.get_dato()
            aux = aux.get_siguiente()

    def copiar_arreglo_a_lista(elementos, n):
        aux = lista.get_primero()
        for i in range(n):
            aux.set_dato(elementos[i])
            aux = aux.get_siguiente()

    def heapify(elementos, n, i):
        largest = i
        left = 2 * i + 1
        right = 2 * i + 2

        if left < n and comp(elementos[left], elementos[largest]):
            largest = left

        if right < n and comp(elementos[right], elementos[largest]):
            largest = right

        if largest != i:
            elementos[i], elementos[largest] = elementos[largest], elementos[i]
            heapify(elementos, n, largest)

    def build_heap(elementos, n):
        for i in range(n // 2 - 1, -1, -1):
            heapify(elementos, n, i)

    def heap_sort(elementos, n):
        build_heap(elementos, n)
        for i in range(n - 1, 0, -1):
            elementos[0], elementos[i] = elementos[i], elementos[0]
            heapify(elementos, i, 0)

    n = contar_elementos()
    if n > 0:
        elementos = [None] * n
        copiar_lista_a_arreglo(elementos, n)
        heap_sort(elementos, n)
        copiar_arreglo_a_lista(elementos, n)
        lista.mostrar(lista.get_primero())