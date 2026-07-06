#pragma once

/*
 Clase: NodoPila
 Nodo generico utilizado internamente por la clase Pila.
 Almacena un dato de tipo T y un puntero al siguiente nodo.
*/
template <typename T>
class NodoPila {
public:
    T dato;                   // Dato almacenado en el nodo
    NodoPila<T>* siguiente;   // Puntero al siguiente nodo hacia el fondo de la pila
};

/*
 Clase: Pila
 Implementacion generica de la estructura de datos Pila (LIFO).
 Los elementos se insertan y extraen por el tope.
 Utiliza nodos enlazados dinamicamente.
*/
template <typename T>
class Pila {
private:
    NodoPila<T>* tope;   // Puntero al nodo en el tope de la pila
    int tamano;          // Cantidad de elementos en la pila

public:

    /*
     Constructor por defecto.
     Inicializa la pila vacia con tope en nullptr.
    */
    Pila() {
        tope = nullptr;
        tamano = 0;
    }

    /*
     Destructor.
     Libera la memoria de todos los nodos al destruir la pila.
    */
    ~Pila() {
        while (!estaVacia()) pop();
    }

    /*
     Inserta un elemento en el tope de la pila.
     El nuevo nodo apunta al anterior tope y pasa a ser el nuevo tope.
    */
    void push(T dato) {
        NodoPila<T>* nuevo = new NodoPila<T>;
        nuevo->dato = dato;
        nuevo->siguiente = tope;
        tope = nuevo;
        tamano++;
    }

    /*
     Extrae y retorna el elemento del tope de la pila.
     Si la pila esta vacia, muestra un mensaje de error y retorna un valor por defecto.
    */
    T pop() {
        if (estaVacia()) {
            cout << "[Pila] ERROR: la pila esta vacia." << endl;
            return T();
        }
        T dato = tope->dato;
        NodoPila<T>* temp = tope;
        tope = tope->siguiente;
        delete temp;
        tamano--;
        return dato;
    }

    /*
     Retorna el elemento del tope sin extraerlo.
     Si la pila esta vacia, muestra un mensaje de error y retorna un valor por defecto.
    */
    T peek() {
        if (estaVacia()) {
            cout << "[Pila] ERROR: la pila esta vacia." << endl;
            return T();
        }
        return tope->dato;
    }

    // Retorna true si la pila no tiene elementos
    bool estaVacia() { return tope == nullptr; }

    // Retorna la cantidad de elementos en la pila
    int getTamano() { return tamano; }

    // Muestra en consola todos los elementos de la pila desde el tope hasta el fondo
    void mostrar() {
        NodoPila<T>* actual = tope;
        cout << "  [Tope] -> ";
        while (actual != nullptr) {
            cout << actual->dato;
            if (actual->siguiente) cout << " -> ";
            actual = actual->siguiente;
        }
        cout << " [Fondo]" << endl;
    }
};
