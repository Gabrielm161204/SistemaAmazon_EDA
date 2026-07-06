#pragma once
#include "Producto.h"
#include <iostream>
#include <string>
using namespace std;

/*
 Clase: ItemPedido
 Representa un item dentro de un pedido o carrito de compras.
 Contiene un puntero al producto, la cantidad solicitada
 y el precio unitario al momento de agregarlo.
*/
class ItemPedido {
public:
  Producto *producto;    // Puntero al producto asociado a este item
  int cantidad;          // Cantidad de unidades del producto en este item
  double precioUnitario; // Precio unitario del producto al momento de agregar
                         // al carrito

  /*
   Constructor por defecto.
   Inicializa el item sin producto y con valores en cero.
  */
  ItemPedido() : producto(nullptr), cantidad(0), precioUnitario(0) {}

  /*
   Constructor con parametros.
   Recibe un puntero al producto y la cantidad deseada.
   El precio unitario se toma directamente del producto.
  */
  ItemPedido(Producto *prod, int cant)
      : producto(prod), cantidad(cant), precioUnitario(prod->precio) {}

  // Destructor por defecto
  ~ItemPedido() {}

  // Calcula y retorna el subtotal (cantidad * precioUnitario)
  double getSubtotal() { return cantidad * precioUnitario; }

  // Actualiza la cantidad del item
  void setCantidad(int n) { cantidad = n; }

  // Muestra en consola el nombre, cantidad, precio unitario y subtotal del item
  void mostrar() {
    cout << "  " << producto->nombre << " | Cant: " << cantidad
         << " | Precio unit: S/." << precioUnitario << " | Subtotal: S/."
         << getSubtotal() << endl;
  }
};
