#pragma once

#include "Pedido.h"
#include "iostream"

/*
 Clase: NodoHistorial
 Nodo de la lista doblemente enlazada usada en el Historial.
 Almacena un pedido y punteros al nodo anterior y siguiente.
*/
class NodoHistorial {
public:
    Pedido pedido;               // Pedido almacenado en este nodo
    NodoHistorial* siguiente;    // Puntero al nodo siguiente
    NodoHistorial* anterior;     // Puntero al nodo anterior
};

/*
 Clase: Historial
 Almacena el historial de compras de un cliente usando
 una lista doblemente enlazada de pedidos.
 Permite recorrer los pedidos hacia adelante y hacia atras,
 y calcula el total gastado de forma recursiva.
*/
class Historial {
private:
    NodoHistorial* cabeza;   // Puntero al primer nodo de la lista
    NodoHistorial* cola;     // Puntero al ultimo nodo de la lista

public:
    double totalGastado;     // Suma acumulada del total de todos los pedidos
    int cantidadCompras;     // Cantidad total de pedidos registrados

    /*
     Constructor por defecto.
     Inicializa la lista vacia con totalGastado y cantidadCompras en cero.
    */
    Historial() {
        cabeza = nullptr;
        cola = nullptr;
        totalGastado = 0.0;
        cantidadCompras = 0;
    }

    /*
     Destructor.
     Libera la memoria de todos los nodos de la lista.
    */
    ~Historial() {
        NodoHistorial* actual = cabeza;
        while (actual != nullptr) {
            NodoHistorial* sig = actual->siguiente;
            delete actual;
            actual = sig;
        }
    }

    /*
     Agrega un pedido al final de la lista doblemente enlazada.
     Si la lista esta vacia, el nodo es cabeza y cola al mismo tiempo.
     Actualiza totalGastado y cantidadCompras.
    */
    void agregarPedido(Pedido p) {
        NodoHistorial* nuevo = new NodoHistorial;
        nuevo->pedido = p;
        nuevo->siguiente = nullptr;
        nuevo->anterior = nullptr;

        if (cabeza == nullptr) {
            cabeza = nuevo;
            cola = nuevo;
        }
        else {
            nuevo->anterior = cola;
            cola->siguiente = nuevo;
            cola = nuevo;
        }
        totalGastado += p.total;
        cantidadCompras++;
    }

    /*
     Muestra el historial de compras desde el mas reciente al mas antiguo.
     Recorre la lista desde la cola hacia la cabeza (lista doble).
     Al final muestra el total gastado y la cantidad de pedidos.
    */
    void historialCompras() {
        if (cabeza == nullptr) {
            cout << "  No hay compras en el historial." << endl;
            return;
        }
        cout << "\n  ===== HISTORIAL DE COMPRAS (reciente a antiguo) =====" << endl;
        NodoHistorial* actual = cola;
        while (actual != nullptr) {
            actual->pedido.mostrarResumen();
            cout << endl;
            actual = actual->anterior;
        }
        cout << "  Total gastado  : S/." << totalGastado << endl;
        cout << "  Total de pedidos: " << cantidadCompras << endl;
    }

    /*
     Calcula el total gastado de forma recursiva recorriendo la lista.
     Caso base: nodo es nullptr, retorna 0.0.
     Suma el total del pedido actual con el resultado de la llamada recursiva.
    */
    double calcularTotalRecursivo(NodoHistorial* nodo) {
        if (nodo == nullptr) return 0.0;
        return nodo->pedido.total + calcularTotalRecursivo(nodo->siguiente);
    }

    // Llama a calcularTotalRecursivo desde la cabeza de la lista
    double getTotalRecursivo() {
        return calcularTotalRecursivo(cabeza);
    }

    // Retorna el puntero al primer nodo del historial
    NodoHistorial* getCabeza() { return cabeza; }
};
