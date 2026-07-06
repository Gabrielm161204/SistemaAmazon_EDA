#pragma once

#include <iostream>
#include <string>
using namespace std;

/*
 Clase: Categoria
 Representa una categoria de productos en el marketplace.
 Contiene un identificador, nombre y descripcion de la categoria.
*/
class Categoria {
public:
    int id;             // Identificador unico de la categoria
    string nombre;      // Nombre de la categoria (ej: "Electronica", "Ropa")
    string descripcion; // Descripcion breve de la categoria

    /*
     Constructor por defecto.
     Inicializa la categoria con id 0 y campos vacios.
    */
    Categoria() {
        id = 0;
        nombre = "";
        descripcion = "";
    }

    /*
     Constructor con parametros.
     Recibe el id, nombre y descripcion de la categoria.
    */
    Categoria(int i, string nom, string desc) {
        id = i;
        nombre = nom;
        descripcion = desc;
    }

	// metodos auxiliares
    // Retorna el nombre de la categoria
    string getNombre() { return nombre; }

    // Muestra en consola el id, nombre y descripcion de la categoria
    void mostrar() {
        cout << "  [" << id << "] " << nombre << " - " << descripcion << endl;
    }
};
