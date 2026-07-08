#pragma once
#include <iostream>
#include <string>
#include <vector>
#include "NodoProducto.h"
#include "Ordenamiento.h"
#include "HashTable.h"
#include "BST.h"

/*
 Clase: GestorInventario
 Administra el inventario de productos usando una lista enlazada simple.
 Permite registrar, buscar, actualizar y eliminar productos.
 Usa recursividad para buscar y mostrar, una tabla hash para búsquedas rápidas,
 y un árbol binario de búsqueda (BST) para búsquedas y listado ordenado alfabéticamente.
*/
class GestorInventario {
private:
    NodoProducto* cabeza;                       // Primer nodo de la lista enlazada
    int cantidad;                               // Total de productos registrados
    HashTable<Producto*> indicePorNombre;        // Índice hash para búsqueda rápida por nombre
    ArbolBinarioBusqueda<Producto*> indiceBST;   // Índice BST para búsqueda y ordenación alfabética
    Ordenamiento ordenamientos;                 // Instancia de la clase de algoritmos de ordenamiento

    /*
     Busca un producto por nombre recorriendo la lista de forma recursiva.
     Caso base: llega al final (nullptr) o encuentra el producto.
     Retorna el nodo encontrado o nullptr si no existe.
    */
    NodoProducto* buscarRecursivo(NodoProducto* nodo, string& nombre) {
        if (nodo == nullptr) return nullptr;
        if (nodo->producto.nombre == nombre) return nodo;
        return buscarRecursivo(nodo->siguiente, nombre);
    }

    /*
     Muestra todos los productos de forma recursiva a partir de un nodo.
     Caso base: nodo es nullptr (fin de la lista).
     Cada llamada imprime el producto actual y avanza al siguiente.
    */
    void mostrarRecursivo(NodoProducto* nodo, int num) {
        if (nodo == nullptr) return;
        cout << "[" << num << "]" << endl;
        nodo->producto.mostrarInfo();
        cout << "-----------------------------------" << endl;
        mostrarRecursivo(nodo->siguiente, num + 1);
    }

public:
    GestorInventario() : cabeza(nullptr), cantidad(0), indicePorNombre(211) {}

    /*
     Destructor.
     Libera la memoria de todos los nodos de la lista enlazada.
    */
    ~GestorInventario() {
        NodoProducto* actual = cabeza;
        while (actual != nullptr) {
            NodoProducto* siguiente = actual->siguiente;
            delete actual;
            actual = siguiente;
        }
    }

	NodoProducto* getCabeza() { // retornamos el puntero a la cabeza de la lista
        return cabeza;
    }

	void reconstruirBST() { // logica de reconstruccion del BST para que este siempre actualizado
        indiceBST.limpiar();
        NodoProducto* actual = cabeza;
        while (actual != nullptr) {
            indiceBST.insertar(actual->producto.nombre, &actual->producto);
            actual = actual->siguiente;
        }
    }

    /*
     Registra un nuevo producto solicitando datos por consola.
     El producto se inserta al inicio de la lista.
    */
    void registrarProducto() {
        string nom, cat;
        int st;
        double prec;

        cout << "\n\033[1;36m┌────────────────────────────────────────┐\033[0m" << endl;
        cout << "\033[1;36m│          REGISTRAR PRODUCTO            │\033[0m" << endl;
        cout << "\033[1;36m└────────────────────────────────────────┘\033[0m" << endl;
        cout << " Nombre : "; cin.ignore(); getline(cin, nom);
        cout << " Categoria: "; getline(cin, cat);
        cout << " Stock : "; cin >> st;
        cout << " Precio : "; cin >> prec;

        Producto p(nom, st, cat, prec);

        NodoProducto* nuevo = new NodoProducto;
        nuevo->producto = p;
        nuevo->siguiente = cabeza;
        cabeza = nuevo;
        cantidad++;

        indicePorNombre.insertar(nom, &nuevo->producto);
        indiceBST.insertar(nom, &nuevo->producto);

        cout << "\n\033[1;32m [OK] Producto '" << nom << "' registrado con exito.\033[0m" << endl;
    }

    /*
     Registra un producto directamente con datos ya construidos.
    */
    void registrarProductoDirecto(Producto p) {
        NodoProducto* nuevo = new NodoProducto;
        nuevo->producto = p;
        nuevo->siguiente = cabeza;
        cabeza = nuevo;
        cantidad++;
        indicePorNombre.insertar(p.nombre, &nuevo->producto);
        indiceBST.insertar(p.nombre, &nuevo->producto);
    }

    /*
     Muestra todos los productos del inventario usando recursividad.
    */
    void mostrarProductosRegistrados() {
        if (cabeza == nullptr) {
            cout << "\n\033[1;31m [!] No hay productos registrados.\033[0m" << endl;
            return;
        }
        cout << "\n\033[1;35m========================================\033[0m" << endl;
        cout << "\033[1;35m               INVENTARIO               \033[0m" << endl;
        cout << "\033[1;35m========================================\033[0m" << endl;
        mostrarRecursivo(cabeza, 1);
    }

    /*
     Muestra productos ordenados alfabéticamente usando inorden en el BST.
    */
    void mostrarProductosBST() {
        auto lista = indiceBST.obtenerInorden(); //Izquierda-Raiz-Deerecha
        if (lista.empty()) {
            cout << "\n\033[1;31m [!] No hay productos en el indice BST.\033[0m" << endl;
            return;
        }
        cout << "\n\033[1;34m========================================\033[0m" << endl;
        cout << "\033[1;34m    PRODUCTOS ORDENADOS ALFABETICAMENTE \033[0m" << endl;
        cout << "\033[1;34m               (BST INORDEN)            \033[0m" << endl;
        cout << "\033[1;34m========================================\033[0m" << endl;
        int idx = 1;
        for (auto* p : lista) {
            cout << "[" << idx++ << "]" << endl;
            p->mostrarInfo();
            cout << "-----------------------------------" << endl;
        }
    }

    /*
     Busca producto usando BST.
    */
    void buscarProductoBST() {
        string nombre;
        cout << "\n Ingrese el nombre a buscar (BST): "; cin.ignore(); getline(cin, nombre);
        Producto* p = indiceBST.buscar(nombre);
        if (p != nullptr) {
            cout << "\n\033[1;32m [OK] Producto encontrado en el BST:\033[0m" << endl;
            p->mostrarInfo();
        } else {
            cout << "\n\033[1;31m [!] Producto '" << nombre << "' no encontrado en el BST.\033[0m" << endl;
        }
    }

    /*
     Busca un producto por nombre usando recursividad de la lista.
    */
    void buscarProducto() {
        string nombre;
        cout << "\n Nombre a buscar (Recursivo): "; cin.ignore(); getline(cin, nombre);

        NodoProducto* resultado = buscarRecursivo(cabeza, nombre);
        if (resultado != nullptr) {
            cout << "\n\033[1;32m [OK] Producto encontrado:\033[0m" << endl;
            resultado->producto.mostrarInfo();
        }
        else {
            cout << "\n\033[1;31m [!] Producto '" << nombre << "' no encontrado.\033[0m" << endl;
        }
    }

    /*
     Busca un producto por nombre usando la tabla hash.
    */
    Producto* buscarPorNombre(string& nombre) {
        Producto* ptr = nullptr;
        if (indicePorNombre.encontrado(nombre, ptr)) {
            return ptr;
        }
        return nullptr;
    }

    /*
     Actualiza el stock de un producto existente.
    */
    void actualizarProducto() {
        string nombre;
        cout << "\n Nombre del producto a actualizar: "; cin.ignore(); getline(cin, nombre);
        NodoProducto* nodo = buscarRecursivo(cabeza, nombre);
        if (nodo == nullptr) {
            cout << "\n\033[1;31m [!] Producto no encontrado.\033[0m" << endl;
            return;
        }
        cout << " Stock actual: " << nodo->producto.stock << endl;
        cout << " Nuevo stock : "; cin >> nodo->producto.stock;
        nodo->producto.estado = (nodo->producto.stock > 0);
        reconstruirBST(); // Actualizamos referencias en el BST
        cout << "\n\033[1;32m [OK] Stock actualizado con exito.\033[0m" << endl;
    }

    /*
     Elimina un producto del inventario por nombre.
    */
    void eliminarProducto() {
        string nombre;
        cout << "\n Nombre del producto a eliminar: "; cin.ignore(); getline(cin, nombre);

        if (cabeza == nullptr) {
            cout << "\n\033[1;31m [!] No hay productos en el inventario.\033[0m" << endl;
            return;
        }

        if (cabeza->producto.nombre == nombre) {
            indicePorNombre.borrar(nombre);
            NodoProducto* temp = cabeza;
            cabeza = cabeza->siguiente;
            delete temp;
            cantidad--;
            reconstruirBST();
            cout << "\n\033[1;32m [OK] Producto eliminado con exito.\033[0m" << endl;
            return;
        }

        NodoProducto* anterior = cabeza;
        NodoProducto* actual = cabeza->siguiente;
        while (actual != nullptr) {
            if (actual->producto.nombre == nombre) {
                indicePorNombre.borrar(nombre);
                anterior->siguiente = actual->siguiente;
                delete actual;
                cantidad--;
                reconstruirBST();
                cout << "\n\033[1;32m [OK] Producto eliminado con exito.\033[0m" << endl;
                return;
            }
            anterior = actual;
            actual = actual->siguiente;
        }
        cout << "\n\033[1;31m [!] Producto no encontrado.\033[0m" << endl;
    }

    /*
     Ordena usando insertionSort.
    */
    void ordenarPorPrecio() {
        if (cabeza == nullptr) return;
        vector<double> precios;
        NodoProducto* actual = cabeza;
        while (actual) { precios.push_back(actual->producto.precio); actual = actual->siguiente; }
        ordenamientos.insertionSort(precios);
        cout << "\n Precios ordenados (Insertion Sort): ";
        for (double p : precios) cout << "S/." << p << " ";
        cout << endl;
    }

    /*
     Ordena usando Quick Sort.
    */
    void ordenarQuickSort() {
        if (cabeza == nullptr) return;
        vector<double> precios;
        NodoProducto* actual = cabeza;
        while (actual) { precios.push_back(actual->producto.precio); actual = actual->siguiente; }
        ordenamientos.quickSort(precios, 0, precios.size() - 1);
        cout << "\n Precios ordenados (Quick Sort): ";
        for (double p : precios) cout << "S/." << p << " ";
        cout << endl;
    }

    /*
     Retorna todos los productos disponibles.
    */
    vector<Producto*> getProductosDisponibles() {
        vector<Producto*> lista;
        NodoProducto* actual = cabeza;
        while (actual) {
            if (actual->producto.estaDisponible())
                lista.push_back(&actual->producto);
            actual = actual->siguiente;
        }
        return lista;
    }

    int getCantidad() { return cantidad; }
};
