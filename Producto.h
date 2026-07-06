#pragma once

#include <iostream>
#include <string>
using namespace std;


/*
 Clase: Producto
 Representa un producto disponible en el marketplace.
 Contiene informacion basica como nombre, stock, categoria,
 precio y estado de disponibilidad.
*/
class Producto {
public:
    string nombre;      // Nombre del producto
    int stock;          // Cantidad de unidades disponibles en inventario
    string categoria;   // Categoria a la que pertenece el producto
    double precio;      // Precio unitario en soles (S/.)
    bool estado;        // true = disponible, false = no disponible

    /*
     Constructor por defecto.
     Inicializa el producto con valores vacios/cero y estado disponible.
    */
    Producto() : nombre(""), stock(0), categoria(""), precio(0.0), estado(true) {}

    /*
     Constructor con parametros.
     Recibe el nombre, stock, categoria, precio y estado del producto.
     El estado es true (disponible) por defecto si no se especifica.
    */
    Producto(string nom, int st, string cat, double prec, bool est = true)
        : nombre(nom), stock(st), categoria(cat), precio(prec), estado(est) {
    }

    /*
     Muestra en consola la informacion completa del producto:
     nombre, stock, categoria, precio y estado.
     El estado se muestra como "Disponible" o "Agotado" segun
     si el estado es true y el stock es mayor a cero.
    */
    void mostrarInfo() {
        cout << "Nombre   : " << nombre << endl;
        cout << "Stock    : " << stock << " und." << endl;
        cout << "Categoria: " << categoria << endl;
        cout << "Precio   : S/. " << precio << endl;
        cout << "Estado   : " << (estado && stock > 0 ? "Disponible" : "Agotado") << endl;
    }

    /*
     Verifica si el producto puede ser vendido.
     Retorna true solo si el estado es true y el stock es mayor a cero.
     Retorna false en caso contrario.
    */
    bool estaDisponible() {
        return estado && stock > 0;
    }
};
