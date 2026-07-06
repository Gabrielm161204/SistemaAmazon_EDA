#pragma once
#include "Cliente.h"
#include <vector>
#include "GestorInventario.h"
#include "Pedido.h"
#include <fstream>
#include <sstream>

using namespace std;

/*
 Clase: ManejadorArchivos
 Se encarga de la lectura y escritura de datos del sistema en archivos
 de texto. Guarda y carga productos, historial de pedidos y las
 credenciales del administrador. También registra un log de acciones.
 Todos sus métodos son estáticos, por lo que no es necesario crear
 objetos de esta clase.
*/
class ManejadorArchivos {
private:
    /*
     Divide una cadena en varias partes usando un delimitador especificado.
     Retorna un vector de strings con cada token separado.
    */
    static vector<string> split(const string &str, char delimiter) {
        vector<string> tokens;
        string token;
        stringstream ss(str);
        while (getline(ss, token, delimiter)) {
            tokens.push_back(token);
        }
        return tokens;
    }

    /*
     Elimina espacios, tabulaciones y saltos de línea al inicio y al final
     de una cadena. Si la cadena solo tenía espacios, retorna una cadena vacía.
    */
    static string trim(const string &str) {
        size_t first = str.find_first_not_of(" \t\r\n");
        if (first == string::npos)
            return "";
        size_t last = str.find_last_not_of(" \t\r\n");
        return str.substr(first, (last - first + 1));
    }

public:
    /*
     Guarda todos los productos del inventario en el archivo "productos.txt".
     Cada línea del archivo tiene el formato:
       nombre|stock|categoria|precio|estado
     donde 'estado' se guarda como 1 (disponible) o 0 (no disponible).
    */
    static void guardarProductos(GestorInventario &inventario) {
        ofstream file("productos.txt");
        if (!file.is_open())
            return;

        NodoProducto *actual = inventario.getCabeza();
        while (actual != nullptr) {
            Producto &p = actual->producto;
            file << p.nombre << "|" << p.stock << "|" << p.categoria << "|"
                 << p.precio << "|" << (p.estado ? 1 : 0) << "\n";
            actual = actual->siguiente;
        }
        file.close();
    }

    /*
     Carga los productos desde el archivo "productos.txt" al inventario.
     Lee cada línea, la separa por '|' y convierte los valores a los tipos
     correctos. Las líneas con formato incorrecto se omiten.
    */
    static void cargarProductos(GestorInventario &inventario) {
        ifstream file("productos.txt");
        if (!file.is_open())
            return;

        string line;
        while (getline(file, line)) {
            line = trim(line);
            if (line.empty())
                continue;
            auto tokens = split(line, '|');
            if (tokens.size() < 5)
                continue;

            string nombre = trim(tokens[0]);
            int stock = 0;
            string categoria = trim(tokens[2]);
            double precio = 0.0;
            bool estado = false;

            try {
                stock = stoi(trim(tokens[1]));
                precio = stod(trim(tokens[3]));
                estado = (stoi(trim(tokens[4])) == 1);
            } catch (...) {
                continue; // Omitir línea con error de formato
            }

            Producto p(nombre, stock, categoria, precio, estado);
            inventario.registrarProductoDirecto(p);
        }
        file.close();
    }

    /*
     Guarda el historial de pedidos de un cliente en "pedidos.txt".
     Por cada pedido escribe una cabecera con:
       id|nombreCliente|fechaHora|total|estado|cantItems
     y luego una línea por cada item:
       nombreProducto,cantidad,precioUnitario
    */
    static void guardarHistorial(Cliente &cliente) {
        ofstream file("pedidos.txt");
        if (!file.is_open())
            return;

        NodoHistorial *actual = cliente.historial.getCabeza();
        while (actual != nullptr) {
            Pedido &p = actual->pedido;
            file << p.id << "|" << p.nombreCliente << "|" << p.fechaHora << "|"
                 << p.total << "|" << p.estado << "|" << p.detalles.size() << "\n";
            for (const auto &item : p.detalles) {
                if (item.producto != nullptr) {
                    file << item.producto->nombre << "," << item.cantidad << ","
                         << item.precioUnitario << "\n";
                }
            }
            actual = actual->siguiente;
        }
        file.close();
    }

    /*
     Carga el historial de pedidos desde "pedidos.txt" para el cliente dado.
     Primero lee la cabecera de cada pedido y luego sus items uno por uno.
     Si un producto del historial ya no existe en el inventario, crea un
     producto temporal para poder reconstruir el pedido.
    */
    static void cargarHistorial(Cliente &cliente, GestorInventario &inventario) {
        ifstream file("pedidos.txt");
        if (!file.is_open())
            return;

        string line;
        while (getline(file, line)) {
            line = trim(line);
            if (line.empty())
                continue;
            auto tokens = split(line, '|');
            if (tokens.size() < 6)
                continue;

            int id = 0;
            string clienteNombre = trim(tokens[1]);
            string fecha = trim(tokens[2]);
            double total = 0.0;
            string estado = trim(tokens[4]);
            int cantItems = 0;

            try {
                id = stoi(trim(tokens[0]));
                total = stod(trim(tokens[3]));
                cantItems = stoi(trim(tokens[5]));
            } catch (...) {
                continue;
            }

            Pedido p(id, clienteNombre, fecha);
            p.total = total;
            p.estado = estado;

            for (int i = 0; i < cantItems; i++) {
                string itemLine;
                if (getline(file, itemLine)) {
                    itemLine = trim(itemLine);
                    auto itemTokens = split(itemLine, ',');
                    if (itemTokens.size() >= 3) {
                        string prodNombre = trim(itemTokens[0]);
                        int cantidad = 0;
                        double precio = 0.0;

                        try {
                            cantidad = stoi(trim(itemTokens[1]));
                            precio = stod(trim(itemTokens[2]));
                        } catch (...) {
                            continue;
                        }

                        Producto *prod = inventario.buscarPorNombre(prodNombre);
                        if (!prod) {
                            // Producto inexistente: se crea uno temporal para el historial
                            prod = new Producto(prodNombre, 0, "Historial", precio, false);
                        }
                        p.agregarDetalle(prod, cantidad);
                    }
                }
            }
            cliente.historial.agregarPedido(p);
        }
        file.close();
    }

    /*
     Agrega una línea al archivo "acciones.txt" con la descripción
     de una acción realizada en el sistema. El archivo se abre en
     modo append para no perder el historial previo.
    */
    static void registrarLog(const string &accion) {
        ofstream file("acciones.txt", ios::app);
        if (file.is_open()) {
            file << accion << "\n";
            file.close();
        }
    }

    // ===== CREDENCIALES DE ADMINISTRADOR =====

    /*
     Guarda las credenciales del administrador en "admin_credentials.txt".
     Escribe usuario, contraseña y correo en una sola línea separados por '|'.
    */
    static void guardarCredencialAdmin(const string &usuario,
                                       const string &contrasena,
                                       const string &correo) {
        ofstream file("admin_credentials.txt");
        if (file.is_open()) {
            file << usuario << "|" << contrasena << "|" << correo << "\n";
            file.close();
        }
    }

    /*
     Carga las credenciales del administrador desde "admin_credentials.txt".
     Si el archivo no existe, asigna credenciales por defecto y las guarda.
     Retorna true si pudo obtener credenciales válidas, false en caso contrario.
    */
    static bool cargarCredencialAdmin(string& usuario, string& contrasena, string& correo) {
        ifstream file("admin_credentials.txt");
        if (!file.is_open()) {
            // abrimos el archivo .txt, si no existe lo creamos con credenciales por defecto
            usuario = "administrador";
            contrasena = "admin123";
            correo = "gerencia@mercadotech.pe";
            guardarCredencialAdmin(usuario, contrasena, correo); // guardamos las credenciales por defecto en el archivo
            return true;
        }
        string line;
        if (getline(file, line)) {
            file.close();
            auto tokens = split(line, '|');
            if ((int)tokens.size() >= 3) {
                usuario = trim(tokens[0]);
                contrasena = trim(tokens[1]);
                correo = trim(tokens[2]);
                return true;
            }
        }
        file.close();
        return false;
    }
};
