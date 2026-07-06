#pragma once

#include "Producto.h"

/*
 Clase: NodoProducto
 Nodo utilizado en la lista enlazada simple del GestorInventario.
 Almacena un objeto Producto y un puntero al siguiente nodo.
*/
class NodoProducto {
public:
    Producto producto;          // Producto almacenado en este nodo
    NodoProducto* siguiente;    // Puntero al siguiente nodo de la lista

    // Constructor por defecto
    NodoProducto() {}

    // Destructor por defecto
    ~NodoProducto() {}
};
