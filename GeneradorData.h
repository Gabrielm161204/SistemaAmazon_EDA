#pragma once
#include "GestorInventario.h"
#include "Marketplace.h"
#include <iostream>
#include <string>

/*
 Clase: GeneradorData
 Clase encargada de precargar datos de ejemplo
 en el inventario y el marketplace. Genera categorias y
 productos predefinidos para facilitar las pruebas del sistema.
*/
class GeneradorData {
private:
  GestorInventario *inventario; // Puntero al gestor de inventario
  Marketplace *market;          // Puntero al marketplace

public:
  GeneradorData() {}
  ~GeneradorData() {}

  /*
   Carga datos de ejemplo en el inventario y marketplace.
   Primero genera las categorias y luego los productos predefinidos.
  */
  void CargarDatosEjemplo(GestorInventario &inventario, Marketplace &market) {
    generarCategorias(market);
    generarProductos(inventario);
  }

  /*
   Carga una cantidad especificada de productos generados aleatoriamente.
   Cada producto tiene nombre "Producto_N", stock aleatorio entre 1 y 100,
   categoria ciclica (Electronica, Ropa, Accesorios) y precio aleatorio.
  */
  void CargarCantidadProductos(GestorInventario &inventario, int cantidad) {
    for (int i = 1; i <= cantidad; i++) {
      string nombre = "Producto_" + to_string(i);
      int stock = rand() % 100 + 1;
      string categoria = (i % 3 == 0)   ? "Electronica" : (i % 3 == 1) ? "Ropa": "Accesorios";
      double precio = (rand() % 200 + 10) * 1.5;
      inventario.registrarProductoDirecto(
          Producto(nombre, stock, categoria, precio));
    }
  }

  /*
   Agrega las categorias predefinidas al marketplace:
   Electronica, Ropa y Accesorios.
  */
  void generarCategorias(Marketplace &market) {
    market.agregarCategoria(Categoria(1, "Electronica", "Dispositivos electronicos y accesorios"));
    market.agregarCategoria(Categoria(2, "Ropa", "Ropa y calzado para toda la familia"));
    market.agregarCategoria(Categoria(3, "Accesorios", "Mochilas, bolsos y accesorios varios"));
  }

  /*
   Agrega un conjunto de productos predefinidos al inventario.
   Incluye productos de las categorias Electronica, Ropa y Accesorios.
  */
  void generarProductos(GestorInventario &inventario) {
    inventario.registrarProductoDirecto(Producto("Laptop HP", 15, "Electronica", 2500.00));
    inventario.registrarProductoDirecto(Producto("Mouse Gamer", 40, "Electronica", 85.00));
    inventario.registrarProductoDirecto(Producto("Teclado USB", 30, "Electronica", 60.00));
    inventario.registrarProductoDirecto(Producto("Polo Casual", 50, "Ropa", 35.00));
    inventario.registrarProductoDirecto(Producto("Zapatillas", 25, "Ropa", 180.00));
    inventario.registrarProductoDirecto(Producto("Mochila", 20, "Accesorios", 75.00));
    inventario.registrarProductoDirecto(Producto("Auriculares", 18, "Electronica", 120.00));
    inventario.registrarProductoDirecto(Producto("Camisa Formal", 35, "Ropa", 45.00));
  }
};
