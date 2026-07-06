#pragma once

#include <iostream>
using namespace std;

/*
 Clase: NodoCola
 Nodo generico utilizado internamente por la clase Cola.
 Almacena un dato de tipo T y un puntero al siguiente nodo.
*/
template <typename T>
class NodoCola {
public:
    T dato;                    // Dato almacenado en el nodo
    NodoCola<T>* siguiente;    // Puntero al siguiente nodo en la cola
};

/*
 Clase: Cola
 Implementacion generica de la estructura de datos Cola (FIFO).
 Los elementos se insertan por el fin y se extraen por el frente.
 Utiliza nodos enlazados dinamicamente.
*/
template <typename T>
class Cola {
private:
    NodoCola<T>* frente;   // Puntero al primer nodo (se extrae por aqui)
    NodoCola<T>* fin;      // Puntero al ultimo nodo (se inserta por aqui)
    int tamano;            // Cantidad de elementos en la cola

public:

    /*
     Constructor por defecto.
     Inicializa la cola vacia con frente y fin en nullptr.
    */
    Cola() {
        frente = nullptr;
        fin = nullptr;
        tamano = 0;
    }

    /*
     Destructor.
     Libera la memoria de todos los nodos al destruir la cola.
    */
    ~Cola() {
        while (!estaVacia()) desencolar();
    }

    /*
     Inserta un elemento al final de la cola.
     Si la cola esta vacia, el nuevo nodo es frente y fin al mismo tiempo.
    */
    void encolar(T dato) {
        NodoCola<T>* nuevo = new NodoCola<T>;
        nuevo->dato = dato;
        nuevo->siguiente = nullptr;

        if (fin == nullptr) {
            frente = nuevo;
            fin = nuevo;
        }
        else {
            fin->siguiente = nuevo;
            fin = nuevo;
        }
        tamano++;
    }

    /*
     Extrae y retorna el elemento del frente de la cola.
     Si la cola esta vacia, muestra un mensaje de error y retorna un valor por defecto.
    */
    T desencolar() {
        if (estaVacia()) {
            cout << "[Cola] ERROR: la cola esta vacia." << endl;
            return T();
        }
        T dato = frente->dato;
        NodoCola<T>* temp = frente;
        frente = frente->siguiente;
        if (frente == nullptr) fin = nullptr;
        delete temp;
        tamano--;
        return dato;
    }

    /*
     Retorna el elemento del frente sin extraerlo.
     Si la cola esta vacia, muestra un mensaje de error y retorna un valor por defecto.
    */
    T verFrente() {
        if (estaVacia()) {
            cout << "[Cola] ERROR: la cola esta vacia." << endl;
            return T();
        }
        return frente->dato;
    }

    // Retorna true si la cola no tiene elementos
    bool estaVacia() { return frente == nullptr; }

    // Retorna la cantidad de elementos en la cola
    int getTamano() { return tamano; }

    // Muestra en consola todos los elementos de la cola del frente al fin
    void mostrar() {
        NodoCola<T>* actual = frente;
        cout << "  [Frente] -> ";
        while (actual != nullptr) {
            cout << actual->dato;
            if (actual->siguiente) cout << " -> ";
            actual = actual->siguiente;
        }
        cout << " [Fin]" << endl;
    }
};
