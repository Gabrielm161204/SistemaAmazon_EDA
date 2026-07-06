#pragma once
#include <iostream>
#include <string>
#include <vector>
using namespace std;
#include "ItemPedido.h"

/*
 Clase: Pedido
 Representa un pedido realizado por un cliente en el marketplace.
 Contiene los detalles de los productos comprados, el total,
 el estado actual del pedido y la fecha de realizacion.
*/
class Pedido {
public:
  int id;                      // Identificador unico del pedido
  string nombreCliente;        // Nombre del cliente que realizo el pedido
  vector<ItemPedido> detalles; // Lista de items incluidos en el pedido
  double total;                // Total calculado del pedido en soles
  string estado; // Estado: "Pendiente", "En proceso", "Entregado", "Cancelado"
  string fechaHora; // Fecha y hora en que se genero el pedido

  // Constructor por defecto. Inicializa el pedido en estado Pendiente con total
  // cero.
  Pedido()
      : id(0), nombreCliente(""), total(0.0), estado("Pendiente"),
        fechaHora("") {}

  // Constructor con parametros. Recibe id, nombre del cliente y fecha del
  // pedido.
  Pedido(int i, string cliente, string fecha)
      : id(i), nombreCliente(cliente), total(0.0), estado("Pendiente"),
        fechaHora(fecha) {}

  /*
   Agrega un item al pedido con el producto y cantidad indicados.
   Crea un ItemPedido y lo inserta en la lista de detalles.
  */
  void agregarDetalle(Producto *prod, int cant) {
    ItemPedido det(prod, cant);
    detalles.push_back(det);
  }

  /*
   Calcula y retorna el total del pedido.
   Suma los subtotales de todos los items en la lista de detalles.
  */
  double calcularTotal() {
    total = 0.0;
    for (int i = 0; i < (int)detalles.size(); i++) {
      total += detalles[i].getSubtotal();
    }
    return total;
  }

  /*
   Muestra en consola el resumen completo del pedido.
   Incluye id, cliente, fecha, estado, lista de items y total.
  */
  void mostrarResumen() {
    cout << "  ===== PEDIDO #" << id << " =====" << endl;
    cout << "  Cliente  : " << nombreCliente << endl;
    cout << "  Fecha    : " << fechaHora << endl;
    cout << "  Estado   : " << estado << endl;
    cout << "  Detalles :" << endl;
    for (int i = 0; i < (int)detalles.size(); i++) {
      detalles[i].mostrar();
    }
    cout << "  Total    : S/." << total << endl;
  }

  /*
   Cambia el estado del pedido al valor indicado.
   Muestra en consola la confirmacion del cambio de estado.
  */
  void cambiarEstado(string nuevoEstado) {
    estado = nuevoEstado;
    cout << "  [OK] Pedido #" << id << " -> Estado: " << estado << endl;
  }

  // Retorna el estado actual del pedido
  string getEstado() { return estado; }

  // Alias de mostrarResumen, usado para compatibilidad con la Cola de pedidos
  void mostrar() { mostrarResumen(); }
};
