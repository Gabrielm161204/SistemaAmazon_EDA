#pragma once
#include "Categoria.h"
#include "Cola.h"
#include "GestorInventario.h"
#include "Ordenamiento.h"
#include <iostream>
#include <string>

/*
 Clase: Marketplace
 Representa la tienda virtual del sistema.
 Gestiona las categorias disponibles, accede al inventario
 y provee funciones para mostrar productos (con orden aleatorio,
 por categoria o por precio). Usa una cola para gestionar
 los IDs de pedidos pendientes de procesar.
*/
class Marketplace {
public:
  string nombre;                // Nombre del marketplace
  GestorInventario *gestor;     // Puntero al inventario global de productos
  vector<Categoria> categorias; // Lista de categorias disponibles
  Cola<int> colaPedidos;        // Cola de IDs de pedidos pendientes de procesar
  Ordenamiento
      ordenamientos; // Instancia de la clase de algoritmos de ordenamiento

  // Constructor por defecto
  Marketplace() : nombre(""), gestor(nullptr) {}

  // Constructor con nombre del marketplace y puntero al inventario
  Marketplace(string nom, GestorInventario *g) : nombre(nom), gestor(g) {}

  // Agrega una nueva categoria al marketplace
  void agregarCategoria(Categoria cat) { categorias.push_back(cat); }

  /*
   Muestra todos los productos disponibles en orden aleatorio.
   Aplica el algoritmo Fisher-Yates para mezclar los productos
   antes de mostrarlos en consola en formato de cuadricula.
   Si no hay productos disponibles, muestra un mensaje informativo.
  */
  void mostrarMercado() {
    vector<Producto *> productos = gestor->getProductosDisponibles();
    if (productos.empty()) {
      cout << "\n  ===== " << nombre << " =====" << endl;
      cout << "  No hay productos disponibles." << endl;
      return;
    }

    ordenamientos.fisherYates(productos);

    const int columnas = 3;

    cout << "  ===== " << nombre << " =====" << endl;
    cout << "  Mostrando " << productos.size()
         << " productos (orden aleatorio):" << endl;

    for (int i = 0; i < (int)productos.size(); i++) {
      if (i % columnas == 0 && i != 0)
        cout << endl;
      cout << "[" << i + 1 << "]";
      productos[i]->mostrarInfo();
    }
  }

  /*
   Muestra los productos disponibles que pertenecen a una categoria especifica.
   Usa una funcion lambda para filtrar los productos por categoria.
   Si no se encuentran productos en la categoria, muestra un mensaje
   informativo.
  */
  void mostrarPorCategoria(string &catBuscada) {
    vector<Producto *> todos = gestor->getProductosDisponibles();

    // Lambda: filtra productos cuya categoria coincida con la buscada
    auto esDeLaCategoria = [&catBuscada](Producto *p) {
      return p->categoria == catBuscada;
    };

    cout << " === Productos de categoria: " << endl
         << catBuscada << " ===" << endl;
    bool encontro = false;
    for (int i = 0; i < (int)todos.size(); i++) {
      if (esDeLaCategoria(todos[i])) {
        todos[i]->mostrarInfo();
        cout << endl;
        encontro = true;
      }
    }
    if (!encontro)
      cout << "  No hay productos en esa categoria." << endl;
  }

  // Muestra en consola todas las categorias registradas en el marketplace
  void mostrarCategorias() {
    cout << "\n  === Categorias ===" << endl;
    for (int i = 0; i < (int)categorias.size(); i++) {
      categorias[i].mostrar();
    }
  }

  /*
   Muestra los productos disponibles ordenados por precio de menor a mayor.
   Aplica Insertion Sort sobre los punteros usando el precio como criterio.
   Si no hay productos, muestra un mensaje informativo.
  */
  void mostrarOrdenadosPorPrecio() {
    vector<Producto *> productos = gestor->getProductosDisponibles();
    if (productos.empty()) {
      cout << "  Sin productos." << endl;
      return;
    }

    // Insertion Sort sobre punteros usando precio como criterio
    int n = productos.size();
    for (int i = 1; i < n; i++) {
      Producto *key = productos[i];
      int j = i - 1;
      while (j >= 0 && productos[j]->precio > key->precio) {
        productos[j + 1] = productos[j];
        j--;
      }
      productos[j + 1] = key;
    }

    cout << "\n  === Productos ordenados por precio (menor a mayor) ==="
         << endl;
    for (int i = 0; i < (int)productos.size(); i++) {
      cout << "  [" << i + 1 << "] " << productos[i]->nombre << " - S/."
           << productos[i]->precio << endl;
    }
  }
};
