#pragma once

#include "ItemPedido.h"

/*
 Clase: Carrito
 Representa el carrito de compras de un cliente en el marketplace.
 Almacena una lista de items (productos con cantidad) y calcula
 el total de la compra. Utiliza funciones lambda para operaciones
 de suma y validacion de stock.
*/
class Carrito {
private:
	string nombreCliente;       // Nombre del cliente dueño del carrito que se 
    //como parametro de la clase Cliente
    vector<ItemPedido> items;   // Lista de productos agregados al carrito
    double total;               // Total acumulado de la compra en soles

public:

    /*
     Constructor por defecto.
     Inicializa el carrito sin cliente y con total igual a 0.
    */
    Carrito() {
        nombreCliente = "";
        total = 0.0;
    }

    /*
     Constructor con nombre de cliente.
     Asigna el nombre del cliente al carrito y total en cero.
    */
    Carrito(string cliente) {
        nombreCliente = cliente;
        total = 0.0;
    }

    /*
     Agrega un producto al carrito con la cantidad indicada.
     Si el producto no esta disponible o no hay stock suficiente, muestra un mensaje de error.
     Si el producto ya existe en el carrito solo actualiza su cantidad.
     Al finalizar, recalcula el total con el metodo calcularTotal().
    */
    void agregarProducto(Producto* prod, int cantidad) {
        if (!prod->estaDisponible()) {
            cout << "  [!] El producto '" << prod->nombre << "' no esta disponible." << endl;
            return;
        }
        if (cantidad > prod->stock) {
            cout << "  [!] Stock insuficiente. Disponible: " << prod->stock << endl;
            return;
        }
        // Verificar si ya existe en el carrito
        for (int i = 0; i < (int)items.size(); i++) {
            if (items[i].producto->nombre == prod->nombre) {
                items[i].setCantidad(items[i].cantidad + cantidad);
                cout << "  [OK] Cantidad actualizada para '" << prod->nombre << "'." << endl;
                calcularTotal();
                return;
            }
        }
        ItemPedido item(prod, cantidad);
        items.push_back(item);
        calcularTotal();
        cout << "  [OK] '" << prod->nombre << "' agregado al carrito." << endl;
    }

    /*
     Muestra en consola el contenido del carrito.
     Lista cada item con su numero, nombre y subtotal. 
     Al final muestra el total acumulado en soles.
     Si el carrito esta vacio se muestra "El carrito esta vacio.".
    */
    void mostrarCarrito() {
        if (items.empty()) {
            cout << "  El carrito esta vacio." << endl;
            return;
        }
        cout << "  ===== CARRITO DE " << nombreCliente << " =====" << endl << endl;
        for (int i = 0; i < (int)items.size(); i++) {
            cout << "  [" << i + 1 << "] ";
            items[i].mostrar();
        }
        cout << "  --------------------------------" << endl;
        cout << "  TOTAL: S/." << total << endl;
    }

    /*
     Calcula el total del carrito sumando los subtotales de cada item.
     Utiliza una funcion lambda anonima para acumular los subtotales.
    */
    void calcularTotal() {
        // Lambda: encargada de ir acumulando los subtotales
        auto sumarSubtotales = [&]() {
            double suma = 0.0;
            for (int i = 0; i < (int)items.size(); i++) {
                suma += items[i].getSubtotal();
            }
            return suma;
        };
        total = sumarSubtotales();
    }

    /*
     Valida que todos los items del carrito tengan stock suficiente.
     Usa una lambda para verificar cada item individualmente.
     Retorna true si todos los items tienen stock, false si alguno no lo tiene.
    */
    bool validarStock() {
        // LAMBDA: verifica si algun item supera el stock disponible
        auto tieneStockSuficiente = [](ItemPedido& item) {
            return item.cantidad <= item.producto->stock;
        };

        for (int i = 0; i < (int)items.size(); i++) {
            if (!tieneStockSuficiente(items[i])) {
                cout << "  [!] Stock insuficiente para: " << items[i].producto->nombre << endl;
                return false;
            }
        }
        return true;
    }

    /*
     Descuenta el stock de cada producto al confirmar la compra.
     Si el stock llega a cero, el producto se marca como no disponible.
    */
    void descontarStock() {
        for (int i = 0; i < (int)items.size(); i++) {
            items[i].producto->stock -= items[i].cantidad;
            if (items[i].producto->stock == 0)
                items[i].producto->estado = false;
        }
    }

	// metodos auxiliares
    // Vacia el carrito y reinicia el total a cero
    void vaciar() { items.clear(); total = 0.0; }

    // Retorna true si el carrito no tiene ningun item
    bool estaVacio() { return items.empty(); }

    // Retorna el total acumulado del carrito
    double getTotal() { return total; }

    // Retorna la lista de items del carrito por referencia
    vector<ItemPedido>& getItems() { return items; }

    // Retorna el nombre del cliente dueno del carrito
    string getNombreCliente() { return nombreCliente; }
};
