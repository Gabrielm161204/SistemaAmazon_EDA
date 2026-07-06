#pragma once
#include <cstdlib>
#include <ctime>
#include <iomanip>
#include <iostream>
#include <string>
#include <vector>
#ifdef _WIN32
#include <conio.h>
#include <windows.h>
#endif

using namespace std;

#include "Categoria.h"
#include "GestorInventario.h"
#include "NodoProducto.h"
#include "Ordenamiento.h"
#include "Producto.h"

#include "Carrito.h"
#include "Cliente.h"
#include "Cola.h"
#include "GeneradorData.h"
#include "Historial.h"
#include "Marketplace.h"
#include "MetodoPago.h"
#include "Pedido.h"
#include "Perfil.h"
#include "Pila.h"

// Nuevas clases del Hito 2
#include "BST.h"
#include "Grafo.h"
#include "ManejadorArchivos.h"

class Sistema {
private:
  GeneradorData generador;
  GestorInventario inventario;
  Marketplace market;
  Cliente clienteActual;
  Ordenamiento ordenamientos;
  GrafoEnvio grafoEnvio;

  bool clienteRegistrado = false;
  int contadorPedidosGlobal = 0;

  // ===== CREDENCIALES ADMIN =====
  string adminUsuario;
  string adminContrasena;
  string adminCorreo;

  string getFecha() { return "2026-07-05"; }

  void limpiarPantalla() {
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
  }

  void mostrarCabecera(const string& titulo) {
      // Marco superior: 60 caracteres internos
      cout << "\033[1;36m +" << string(60, '=') << "+\033[0m" << endl;
      // Línea de título: 60 espacios internos con el texto alineado a la izquierda
      cout << "\033[1;36m | \033[1;33m" << setw(60) << left << titulo
          << "\033[1;36m|\033[0m" << endl;
      // Marco inferior
      cout << "\033[1;36m +" << string(60, '=') << "+\033[0m" << endl;
  }

  void mostrarSeparador(char c = '-', int ancho = 60) {
      // Separador con el mismo ancho interno que la cabecera (60)
      cout << "\033[1;36m +" << string(ancho, c) << "+\033[0m" << endl;
  }

  void mostrarOpcion(const string& num, const string& texto,
      bool esRojo = false) {
      string color = esRojo ? "\033[1;31m" : "\033[1;33m";
      cout << "\033[1;36m | \033[0m" << color << "[" << num << "]\033[0m "
          << texto << endl;
  }

  void pausar() {
    cout << "\n\033[1;37m  Presione Enter para continuar...\033[0m";
    cin.ignore();
    cin.get();
  }

  // ==== LEER CONTRASENA OCULTA (muestra * en lugar de caracteres) ====
  string leerContrasenaOculta() {
    string pass = "";
    while (true) {
#ifdef _WIN32
      int ch = _getch();
#else
      int ch = getchar();
#endif
      if (ch == 13 || ch == 10)
        break;                        // Enter
      if (ch == 8 && !pass.empty()) { // Backspace
        pass.pop_back();
        cout << "\b \b";
        cout.flush();
      } else if (ch >= 32 && ch <= 126) {
        pass += (char)ch;
        cout << '*';
        cout.flush();
      }
    }
    cout << endl;
    return pass;
  }

  // ==== ANIMACION DE PASO DE PROCESO ====
  void animarPaso(const string &texto, int msDelay = 600) {
    cout << "\033[1;33m  [>] \033[0m" << setw(50) << left << texto;
    cout.flush();
#ifdef _WIN32
    Sleep(msDelay / 4);
    cout << ".";
    cout.flush();
    Sleep(msDelay / 4);
    cout << ".";
    cout.flush();
    Sleep(msDelay / 4);
    cout << ".";
    cout.flush();
    Sleep(msDelay / 4);
#endif
    cout << " \033[1;32m[OK]\033[0m" << endl;
  }

  // ==== PANTALLA DE LOGIN ADMINISTRADOR ====
  bool loginAdmin() {
    ManejadorArchivos::cargarCredencialAdmin(adminUsuario, adminContrasena, adminCorreo);

    int intentos = 3;
    while (intentos > 0) {
      limpiarPantalla();

      // -- Zona Restringida --
      cout << "\033[1;31m" << endl;
      cout << "  +" << string(62, '!') << "+" << endl;
      cout << "  !" << string(62, ' ') << "!" << endl;
      cout << "  !      /!\\    ZONA DE ACCESO RESTRINGIDO   /!\\           !"
           << endl;
      cout << "  !           Solo personal autorizado puede ingresar        !"
           << endl;
      cout << "  !" << string(62, ' ') << "!" << endl;
      cout << "  +" << string(62, '!') << "+" << endl;
      cout << "\033[0m" << endl;

      // -- Panel de autenticacion --
      cout << "\033[1;36m  +" << string(60, '=') << "+\033[0m" << endl;
      cout << "\033[1;36m  |  \033[1;33m" << setw(58) << left
           << "   SISTEMA DE AUTENTICACION SEGURA - ADMIN"
           << "\033[1;36m|\033[0m" << endl;
      cout << "\033[1;36m  |  \033[0m" << setw(58) << left
           << "   MercadoTech Peru - Panel Administrativo"
           << "\033[1;36m|\033[0m" << endl;
      cout << "\033[1;36m  +" << string(60, '-') << "+\033[0m" << endl;
      cout << "\033[1;36m  |" << string(60, ' ') << "|\033[0m" << endl;

      // -- Intentos restantes con color dinamico --
      string ci = (intentos == 1)
                      ? "\033[1;31m"
                      : (intentos == 2 ? "\033[1;33m" : "\033[1;32m");
      string infoInt =
          "  Intentos restantes: [ " + to_string(intentos) + " / 3 ]";
      cout << "\033[1;36m  |  " << ci << setw(56) << left << infoInt
           << "\033[1;36m|\033[0m" << endl;
      cout << "\033[1;36m  |" << string(60, ' ') << "|\033[0m" << endl;

      // -- Inputs --
      // Limpiar el \n que deja cin >> op del menu (solo si hay basura en el
      // buffer)
      if (cin.peek() == '\n')
        cin.ignore();
      cout << "\033[1;36m  |  \033[1;37m  [>] Usuario    : \033[0m";
      string usuario;
      getline(cin, usuario);

      cout << "\033[1;36m  |  \033[1;37m  [>] Contrasena : \033[0m";
      string contrasena = leerContrasenaOculta();

      cout << "\033[1;36m  |" << string(60, ' ') << "|\033[0m" << endl;
      cout << "\033[1;36m  +" << string(60, '=') << "+\033[0m" << endl;
      cout << endl;

      if (usuario == adminUsuario && contrasena == adminContrasena) {
        animarPaso("Verificando credenciales de administrador", 450);
        animarPaso("Validando permisos y privilegios del sistema", 450);
        animarPaso("Inicializando panel de control seguro", 450);
        cout << endl;
        cout << "\033[1;32m  +" << string(58, '=') << "+\033[0m" << endl;
        cout << "\033[1;32m  |  [OK] ACCESO CONCEDIDO  --  Bienvenido, "
             << setw(17) << left << adminUsuario << "   |\033[0m" << endl;
        cout << "\033[1;32m  +" << string(58, '=') << "+\033[0m" << endl;
        ManejadorArchivos::registrarLog("Admin: Acceso concedido - " +
                                        getFecha());
#ifdef _WIN32
        Sleep(1400);
#endif
        return true;
      } else {
        intentos--;
        cout << "\033[1;31m  +" << string(56, '-') << "+\033[0m" << endl;
        cout << "\033[1;31m  |  [X] ACCESO DENEGADO - Credenciales incorrectas"
             << setw(8) << " " << "|\033[0m" << endl;
        if (intentos > 0)
          cout << "\033[1;31m  |  Intentos restantes: " << intentos << setw(33)
               << " " << "|\033[0m" << endl;
        cout << "\033[1;31m  +" << string(56, '-') << "+\033[0m" << endl;
        ManejadorArchivos::registrarLog(
            "ALERTA: Intento fallido acceso admin - " + getFecha());
#ifdef _WIN32
        Sleep(1800);
#endif
      }
    }

    // -- Acceso bloqueado --
    limpiarPantalla();
    cout << "\033[1;31m" << endl;
    cout << "  +" << string(62, '#') << "+" << endl;
    cout << "  #" << string(62, ' ') << "#" << endl;
    cout << "  #   [!!!] ACCESO BLOQUEADO - Intentos maximos alcanzados        "
            " #"
         << endl;
    cout << "  #   Este incidente fue registrado en el log de seguridad.       "
            " #"
         << endl;
    cout << "  #   Contacte al administrador si necesita ayuda.                "
            " #"
         << endl;
    cout << "  #" << string(62, ' ') << "#" << endl;
    cout << "  +" << string(62, '#') << "+" << endl;
    cout << "\033[0m" << endl;
    ManejadorArchivos::registrarLog(
        "ALERTA CRITICA: Admin BLOQUEADO - 3 intentos fallidos - " +
        getFecha());
    pausar();
    return false;
  }

  // ==== CAMBIO DE CONTRASENA CON SIMULACION DE CORREO ====
  void menuCambiarContrasenaAdmin() {
    limpiarPantalla();
    srand((unsigned int)time(nullptr));
    int codigoVerif = 100000 + rand() % 900000;

    mostrarCabecera("CAMBIO DE CONTRASENA - ADMINISTRADOR");
    cout << endl;
    cout << "\033[1;37m  [>] Nueva contrasena    : \033[0m";
    string nueva = leerContrasenaOculta();
    cout << "\033[1;37m  [>] Confirmar contrasena: \033[0m";
    string confirma = leerContrasenaOculta();

    if (nueva != confirma) {
      cout << "\n\033[1;31m  [ERROR] Las contrasenas no coinciden. Operacion "
              "cancelada.\033[0m"
           << endl;
      pausar();
      return;
    }
    if ((int)nueva.length() < 6) {
      cout << "\n\033[1;31m  [ERROR] Minimo 6 caracteres requeridos.\033[0m"
           << endl;
      pausar();
      return;
    }

    cout << endl;
    cout << "\033[1;33m  +" << string(58, '=') << "+\033[0m" << endl;
    cout << "\033[1;33m  |     PROCESO DE VERIFICACION POR CORREO ELECTRONICO  "
            "    |\033[0m"
         << endl;
    cout << "\033[1;33m  +" << string(58, '=') << "+\033[0m" << endl;
    cout << endl;

    animarPaso("Generando token de verificacion de 6 digitos", 700);
    animarPaso("Estableciendo conexion SMTP cifrada  TLS/SSL", 750);
    animarPaso("Autenticando con servidor de correo corporativo", 700);
    animarPaso("Enviando email de confirmacion a " + adminCorreo, 900);

    cout << endl;
    cout << "\033[1;32m  +" << string(58, '=') << "+\033[0m" << endl;
    cout << "\033[1;32m  |          EMAIL ENVIADO EXITOSAMENTE                 "
            "     |\033[0m"
         << endl;
    cout << "\033[1;32m  +" << string(58, '-') << "+\033[0m" << endl;
    cout << "\033[1;32m  |  Para    : \033[0m" << setw(47) << left
         << adminCorreo << "\033[1;32m|\033[0m" << endl;
    cout << "\033[1;32m  |  Asunto  : \033[0m" << setw(47) << left
         << "[MercadoTech] Verificacion cambio de clave" << "\033[1;32m|\033[0m"
         << endl;
    cout << "\033[1;32m  |  Codigo  : \033[1;33m" << setw(47) << left
         << ("[SIMULADO] " + to_string(codigoVerif)) << "\033[1;32m|\033[0m"
         << endl;
    cout << "\033[1;32m  +" << string(58, '=') << "+\033[0m" << endl;
    cout << endl;

    cout << "\033[1;36m  >> Ingrese el codigo de verificacion del correo: "
            "\033[1;33m";
    int codigoIngresado = 0;
    cin >> codigoIngresado;
    cout << "\033[0m";

    if (codigoIngresado == codigoVerif) {
      adminContrasena = nueva;
      ManejadorArchivos::guardarCredencialAdmin(adminUsuario, adminContrasena,
                                                adminCorreo);
      cout << "\n\033[1;32m  +" << string(42, '=') << "+\033[0m" << endl;
      cout
          << "\033[1;32m  |  [OK] Contrasena actualizada exitosamente. |\033[0m"
          << endl;
      cout << "\033[1;32m  +" << string(42, '=') << "+\033[0m" << endl;
      ManejadorArchivos::registrarLog("Admin: Contrasena cambiada - " +
                                      getFecha());
    } else {
      cout << "\n\033[1;31m  [ERROR] Codigo incorrecto. Operacion "
              "cancelada.\033[0m"
           << endl;
      ManejadorArchivos::registrarLog(
          "Admin: Codigo incorrecto en cambio de clave - " + getFecha());
    }
    pausar();
  }

public:
  Sistema() {}

  ~Sistema() {}

  void iniciar() {
    // Habilitar colores ANSI y UTF-8 en la consola de Windows (Visual Studio
    // 2022)
#ifdef _WIN32
    // UTF-8: evita que los caracteres Unicode del logo se corrompan
    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);
    // ANSI: habilita codigos de color \033[...m
    HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
    DWORD dwMode = 0;
    GetConsoleMode(hOut, &dwMode);
    SetConsoleMode(hOut, dwMode | ENABLE_VIRTUAL_TERMINAL_PROCESSING);
#endif

    // Inicializar marketplace
    market = Marketplace("MercadoTech Peru", &inventario);

    // Cargar productos del archivo de texto
    ManejadorArchivos::cargarProductos(inventario);

    // Si el archivo estaba vacío, cargar datos de prueba
    if (inventario.getCantidad() == 0) {
      generador.CargarDatosEjemplo(inventario, market);
      ManejadorArchivos::guardarProductos(inventario);
    } else {
      inventario.reconstruirBST();
    }

    // Cargar historial del archivo
    ManejadorArchivos::cargarHistorial(clienteActual, inventario);

    clienteActual.pilaAcciones.push("Sistema iniciado");
    ManejadorArchivos::registrarLog("Sistema iniciado - " + getFecha());

    int op;
    do {
      limpiarPantalla();

      // ====== CABECERA PRINCIPAL ======
      cout << "\033[1;33m" << endl;
      cout << "╔═══════════════════════════════════════════════════════════════"
              "═══════════════════════╗\n";
      cout << "║                                                               "
              "                       ║\n";
      cout << "║     █████╗ ███╗   ███╗ █████╗ ███████╗ ██████╗ ███╗   ██╗     "
              "                       ║\n";
      cout << "║    ██╔══██╗████╗ ████║██╔══██╗╚══███╔╝██╔═══██╗████╗  ██║     "
              "                       ║\n";
      cout << "║    ███████║██╔████╔██║███████║  ███╔╝ ██║   ██║██╔██╗ ██║     "
              "                       ║\n";
      cout << "║    ██╔══██║██║╚██╔╝██║██╔══██║ ███╔╝  ██║   ██║██║╚██╗██║     "
              "                       ║\n";
      cout << "║    ██║  ██║██║ ╚═╝ ██║██║  ██║███████╗╚██████╔╝██║ ╚████║     "
              "                       ║\n";
      cout << "║    ╚═╝  ╚═╝╚═╝     ╚═╝╚═╝  ╚═╝╚══════╝ ╚═════╝ ╚═╝  ╚═══╝     "
              "                       ║\n";
      cout << "║                                                               "
              "                       ║\n";
      cout << "║                    SISTEMA DE GESTION DE PEDIDOS Y DELIVERY   "
              "                       ║\n";
      cout << "║                         Amazon Console                        "
              "                       ║\n";
      cout << "║                                                               "
              "                       ║\n";
      cout << "╚═══════════════════════════════════════════════════════════════"
              "═══════════════════════╝\n";
      cout << "\033[0m" << endl;

      // ====== ESTADO SESION ======
      mostrarSeparador('-');
      if (clienteRegistrado) {
          string info = "[OK] Sesion activa: " + clienteActual.nombre +
              " | DNI: " + clienteActual.dni;
          cout << "\033[1;36m | \033[1;32m" << info
              << "\033[1;36m |\033[0m" << endl;
      }
      else {
          cout << "\033[1;36m | \033[1;31m"
              << "[!] Sin sesion de cliente activa -- Seleccione opcion 3 para registrarse"
              << "\033[1;36m          |\033[0m" << endl;
      }
      mostrarSeparador('-');

      cout << endl;

      // ====== MENU PRINCIPAL ======
      mostrarSeparador('=');
      cout << "\033[1;36m | \033[0m" << "MENU PRINCIPAL"
          << "\033[1;36m                                             |\033[0m" << endl;
      mostrarSeparador('-');

      mostrarOpcion(" 1 ", "Gestion de Inventario [Admin]");
      mostrarOpcion(" 2 ", "Marketplace - Explorar Productos");
      mostrarOpcion(" 3 ", "Registrar / Ver Mi Perfil");
      mostrarOpcion(" 4 ", "Carrito de Compras");
      mostrarOpcion(" 5 ", "Gestion de Pedidos y Rutas de Envio");

      // Línea vacía alineada con el marco
      cout << "\033[1;36m |" << string(60, ' ') << "|\033[0m" << endl;

      mostrarOpcion(" 0 ", "Salir del Sistema", true);
      mostrarSeparador('=');

      cout << "\033[1;33m\n >> Ingrese su opcion: \033[0m";
      cin >> op;

      switch (op) {
      case 1:
        menuInventario();
        break;
      case 2:
        menuMarketplace();
        break;
      case 3:
        limpiarPantalla();
        if (!clienteRegistrado)
          registrarCliente();
        else
          clienteActual.mostrarDatos();
        pausar();
        break;
      case 4:
        menuCarrito();
        break;
      case 5:
        menuPedidos();
        break;
      case 0:
        cout << "\n\033[1;33m  Guardando datos... \033[1;32m[OK]\033[0m"
             << endl;
        cout << "\033[1;33m  Hasta luego. Gracias por usar MercadoTech "
                "Peru!\033[0m"
             << endl;

        ManejadorArchivos::guardarProductos(inventario);
        if (clienteRegistrado) {
          ManejadorArchivos::guardarHistorial(clienteActual);
        }
        break;
      default:
        cout << "  Opcion invalida." << endl;
        pausar();
      }
    } while (op != 0);
  }

  void menuInventario() {
    // === AUTENTICACION REQUERIDA CADA VEZ ===
    if (!loginAdmin())
      return;

    int op;
    do {
      limpiarPantalla();
      mostrarCabecera("ADMINISTRACION - GESTION DE INVENTARIO");
      mostrarOpcion(" 1 ", "Registrar producto nuevo");
      mostrarOpcion(" 2 ", "Generar N productos aleatorios");
      mostrarOpcion(" 3 ", "Listar todos los productos  (Lista Recursiva)");
      mostrarOpcion(" 4 ", "Listar en orden alfabetico  (BST Inorden)");
      mostrarOpcion(" 5 ", "Buscar producto por nombre  (Tabla Hash)");
      mostrarOpcion(" 6 ", "Buscar producto por nombre  (BST)");
      mostrarOpcion(" 7 ", "Actualizar stock de un producto");
      mostrarOpcion(" 8 ", "Eliminar producto del inventario");
      mostrarOpcion(" 9 ", "Ordenar por precio           (Insertion Sort)");
      mostrarOpcion("10 ", "Ordenar por precio           (Quick Sort)");
      cout << "\033[1;36m  |\033[0m" << endl;
      mostrarOpcion("11 ", "Cambiar contrasena de administrador");
      cout << "\033[1;36m  |\033[0m" << endl;
      mostrarOpcion(" 0 ", "Volver al Menu Principal", true);
      mostrarSeparador('=');
      cout << "\033[1;33m\n  >> Ingrese su opcion: \033[0m";
      cin >> op;

      switch (op) {
      case 1:
        inventario.registrarProducto();
        ManejadorArchivos::guardarProductos(inventario);
        clienteActual.pilaAcciones.push("Registrar producto");
        ManejadorArchivos::registrarLog("Admin: Registrar producto nuevo");
        pausar();
        break;
      case 2: {
        int n;
        cout << "  Cantidad a generar: ";
        cin >> n;
        generador.CargarCantidadProductos(inventario, n);
        inventario.reconstruirBST();
        ManejadorArchivos::guardarProductos(inventario);
        clienteActual.pilaAcciones.push("Generar " + to_string(n) +
                                        " productos");
        ManejadorArchivos::registrarLog("Admin: Generar " + to_string(n) +
                                        " productos");
        cout << "  [OK] Productos generados." << endl;
        pausar();
        break;
      }
      case 3:
        inventario.mostrarProductosRegistrados();
        pausar();
        break;
      case 4:
        inventario.mostrarProductosBST();
        pausar();
        break;
      case 5:
        inventario.buscarProducto();
        pausar();
        break;
      case 6:
        inventario.buscarProductoBST();
        pausar();
        break;
      case 7:
        inventario.actualizarProducto();
        ManejadorArchivos::guardarProductos(inventario);
        clienteActual.pilaAcciones.push("Actualizar stock");
        ManejadorArchivos::registrarLog("Admin: Actualizar stock");
        pausar();
        break;
      case 8:
        inventario.eliminarProducto();
        ManejadorArchivos::guardarProductos(inventario);
        clienteActual.pilaAcciones.push("Eliminar producto");
        ManejadorArchivos::registrarLog("Admin: Eliminar producto");
        pausar();
        break;
      case 9:
        inventario.ordenarPorPrecio();
        pausar();
        break;
      case 10:
        inventario.ordenarQuickSort();
        pausar();
        break;
      case 11:
        menuCambiarContrasenaAdmin();
        break;
      case 0:
        break;
      default:
        cout << "  Opcion invalida." << endl;
        pausar();
      }
    } while (op != 0);
  }

  void menuMarketplace() {
    int op;
    do {
      limpiarPantalla();
      mostrarCabecera("TIENDA ONLINE - MARKETPLACE");
      mostrarOpcion(
          " 1 ",
          "Ver catalogo completo         (Orden Aleatorio Fisher-Yates)");
      mostrarOpcion(" 2 ", "Filtrar productos por categoria  (Lambdas)");
      mostrarOpcion(" 3 ", "Ver productos ordenados por precio");
      mostrarOpcion(" 4 ", "Mostrar categorias disponibles");
      cout << "\033[1;36m  |\033[0m" << endl;
      mostrarOpcion(" 0 ", "Volver al Menu Principal", true);
      mostrarSeparador('=');
      cout << "\033[1;33m\n  >> Ingrese su opcion: \033[0m";
      cin >> op;

      switch (op) {
      case 1:
        market.mostrarMercado();
        pausar();
        break;
      case 2: {
        string cat;
        market.mostrarCategorias();
        cout << "\n  Ingrese categoria: ";
        cin.ignore();
        getline(cin, cat);
        market.mostrarPorCategoria(cat);
        pausar();
        break;
      }
      case 3:
        market.mostrarOrdenadosPorPrecio();
        pausar();
        break;
      case 4:
        market.mostrarCategorias();
        pausar();
        break;
      case 0:
        break;
      default:
        cout << "  Opcion invalida." << endl;
        pausar();
      }
    } while (op != 0);
  }

  void registrarCliente() {
    string nom, dni;
    mostrarCabecera("REGISTRO DE CLIENTE NUEVO");
    cout << "  Ingrese Nombre: ";
    cin.ignore();
    getline(cin, nom);
    cout << "  Ingrese DNI   : ";
    cin >> dni;
    clienteActual = Cliente(nom, dni, getFecha());
    clienteRegistrado = true;
    ManejadorArchivos::registrarLog("Cliente registrado: " + nom +
                                    " - DNI: " + dni);
    cout << "\n\033[1;32m  [OK] Registro exitoso. ¡Bienvenido, " << nom
         << "!\033[0m" << endl;
  }

  void menuCarrito() {
    if (!clienteRegistrado) {
      limpiarPantalla();
      cout << "\033[1;31m  [!] Debe registrarse para acceder al carrito.\033[0m"
           << endl;
      registrarCliente();
      pausar();
    }

    int op;
    do {
      limpiarPantalla();
      mostrarCabecera("MI CARRITO DE COMPRAS");
      mostrarOpcion(" 1 ", "Ver catalogo de productos disponibles");
      mostrarOpcion(" 2 ", "Agregar un producto al carrito");
      mostrarOpcion(" 3 ", "Ver resumen de mi carrito");
      mostrarOpcion(" 4 ",
                    "Confirmar compra y elegir ruta de envio  (Dijkstra)");
      cout << "\033[1;36m  |\033[0m" << endl;
      mostrarOpcion(" 0 ", "Volver al Menu Principal", true);
      mostrarSeparador('=');
      cout << "\033[1;33m\n  >> Ingrese su opcion: \033[0m";
      cin >> op;

      switch (op) {
      case 1:
        market.mostrarMercado();
        pausar();
        break;
      case 2: {
        string nombre;
        int cant;
        cout << "  Nombre del producto: ";
        cin.ignore();
        getline(cin, nombre);
        cout << "  Cantidad a comprar : ";
        cin >> cant;

        // Buscar por BST para demostrar su uso
        Producto *p = inventario.buscarPorNombre(nombre);
        if (p) {
          clienteActual.agregarCarrito(p, cant);
          clienteActual.pilaAcciones.push("Agregar al carrito: " + nombre);
          ManejadorArchivos::registrarLog("Carrito: agregar " + nombre + " (" +
                                          to_string(cant) + ")");
          cout << "\n\033[1;32m  [OK] Producto agregado al carrito.\033[0m"
               << endl;
        } else {
          cout << "\n\033[1;31m  [!] Producto no encontrado.\033[0m" << endl;
        }
        pausar();
        break;
      }
      case 3:
        clienteActual.carrito.mostrarCarrito();
        pausar();
        break;
      case 4: {
        if (clienteActual.carrito.estaVacio()) {
          cout << "\n\033[1;31m  [!] El carrito esta vacio.\033[0m" << endl;
          pausar();
          break;
        }
        if (!clienteActual.carrito.validarStock()) {
          pausar();
          break;
        }

        // Selección del destino (Grafo)
        limpiarPantalla();
        mostrarCabecera("DESTINO DE ENVIO");
        cout << "  Ciudades de destino disponibles:" << endl;
        const auto &ciudades = grafoEnvio.getCiudades();
        for (size_t i = 0; i < ciudades.size(); i++) {
          cout << "    - " << ciudades[i]
               << (ciudades[i] == "Lima" ? " (Sede Central)" : "") << endl;
        }

        string destino;
        cout << "\n  Escriba la ciudad de destino: ";
        cin.ignore();
        getline(cin, destino);

        // Calcular la ruta más barata con Dijkstra
        RutaInfo ruta = grafoEnvio.calcularRuta("Lima", destino);
        if (ruta.costoTotal == -1) {
          cout << "\n\033[1;31m  [!] No se pudo encontrar una ruta de envio "
                  "hacia "
               << destino << "\033[0m" << endl;
          pausar();
          break;
        }

        cout << "\n\033[1;34m  +" << string(42, '-') << "+\033[0m" << endl;
        cout << "\033[1;34m  |      *** DETALLES DE ENVIO ***         |\033[0m"
             << endl;
        cout << "\033[1;34m  +" << string(42, '-') << "+\033[0m" << endl;
        cout << "  Ruta de entrega: ";
        for (size_t i = 0; i < ruta.path.size(); i++) {
          cout << ruta.path[i] << (i == ruta.path.size() - 1 ? "" : " -> ");
        }
        cout << endl;
        cout << "  Distancia Total: " << ruta.distanciaTotal << " km" << endl;
        cout << "  Costo de Envio : S/. " << ruta.costoTotal << endl;

        double subtotal = clienteActual.carrito.getTotal();
        double totalFinal = subtotal + ruta.costoTotal;
        cout << "  Subtotal Productos: S/. " << subtotal << endl;
        cout << "  Total Neto Compra : S/. " << totalFinal << endl;

        cout << "\n  Metodo de pago:\n" << endl;
        cout << "  1. Efectivo  2. Tarjeta  3. Yape" << endl;
        cout << "  Opcion: ";
        int mOp;
        cin >> mOp;
        string tipo = (mOp == 1 ? "Efectivo" : mOp == 2 ? "Tarjeta" : "Yape");

        MetodoPago pago(1, tipo, totalFinal, getFecha());
        if (pago.procesarPago(totalFinal)) {
          Pedido nuevoPedido = clienteActual.generarPedido(getFecha());
          nuevoPedido.total = totalFinal; // Actualizamos con el costo de envío
          nuevoPedido.cambiarEstado("En proceso (Envio a " + destino + ")");

          contadorPedidosGlobal++;
          market.colaPedidos.encolar(nuevoPedido.id);

          clienteActual.pilaAcciones.push(
              "Pedido #" + to_string(nuevoPedido.id) + " generado");
          ManejadorArchivos::registrarLog("Pedido #" +
                                          to_string(nuevoPedido.id) + " a " +
                                          destino + " pagado con " + tipo);
          ManejadorArchivos::guardarHistorial(clienteActual);
          ManejadorArchivos::guardarProductos(inventario);

          cout << "\n\033[1;32m  ¡Pedido y Envio procesados "
                  "exitosamente!\033[0m\n"
               << endl;
          nuevoPedido.mostrarResumen();
        }
        pausar();
        break;
      }
      case 0:
        break;
      default:
        cout << "  Opcion invalida." << endl;
        pausar();
      }
    } while (op != 0);
  }

  void menuPedidos() {
    int op;
    do {
      limpiarPantalla();
      mostrarCabecera("GESTION DE PEDIDOS Y RUTAS DE ENVIO");
      cout << "\033[1;36m  |  \033[1;33mPedidos pendientes en cola: \033[1;32m"
           << market.colaPedidos.getTamano() << "\033[0m" << endl;
      cout << "\033[1;36m  |\033[0m" << endl;
      mostrarOpcion(" 1 ", "Ver cola de pedidos pendientes");
      mostrarOpcion(" 2 ", "Procesar siguiente pedido  (Desencolar)");
      mostrarOpcion(" 3 ", "Ver mi historial de pedidos");
      mostrarOpcion(" 4 ", "Simular costo de envio entre ciudades  (Dijkstra)");
      cout << "\033[1;36m  |\033[0m" << endl;
      mostrarOpcion(" 0 ", "Volver al Menu Principal", true);
      mostrarSeparador('=');
      cout << "\033[1;33m\n  >> Ingrese su opcion: \033[0m";
      cin >> op;

      switch (op) {
      case 1:
        if (market.colaPedidos.estaVacia()) {
          cout << "\n  No hay pedidos en cola." << endl;
        } else {
          cout << "\n  Siguiente pedido a atender: #"
               << market.colaPedidos.verFrente() << endl;
          cout << "  Total en cola: " << market.colaPedidos.getTamano() << endl;
        }
        pausar();
        break;
      case 2:
        if (!market.colaPedidos.estaVacia()) {
          int id = market.colaPedidos.desencolar();
          cout << "\n\033[1;32m  [OK] Pedido #" << id
               << " procesado, enviado y entregado.\033[0m" << endl;
          clienteActual.pilaAcciones.push("Pedido #" + to_string(id) +
                                          " entregado");
          ManejadorArchivos::registrarLog("Pedido #" + to_string(id) +
                                          " entregado al cliente");
          ManejadorArchivos::guardarHistorial(clienteActual);
        } else {
          cout << "\n  No hay pedidos en cola por procesar." << endl;
        }
        pausar();
        break;
      case 3:
        if (clienteRegistrado) {
          clienteActual.historial.historialCompras();
          double totalRec = clienteActual.historial.getTotalRecursivo();
          cout << "  Total calculado recursivamente: S/. " << totalRec << endl;
        } else {
          cout << "\n\033[1;31m  [!] No hay un cliente registrado.\033[0m"
               << endl;
        }
        pausar();
        break;
      case 4: {
        string o, d;
        cout << "\n  Ciudades: Lima, Trujillo, Chiclayo, Piura, Arequipa, "
                "Cusco, Iquitos\n";
        cout << "  Ciudad Origen : ";
        cin.ignore();
        getline(cin, o);
        cout << "  Ciudad Destino: ";
        getline(cin, d);

        RutaInfo r = grafoEnvio.calcularRuta(o, d);
        if (r.costoTotal == -1) {
          cout << "\n\033[1;31m  [!] Ruta no encontrada entre " << o << " y "
               << d << "\033[0m" << endl;
        } else {
          cout << "\n\033[1;32m  +" << string(42, '-') << "+\033[0m" << endl;
          cout << "\033[1;32m  |   *** RUTA OPTIMA - DIJKSTRA ***      |\033[0m"
               << endl;
          cout << "\033[1;32m  +" << string(42, '-') << "+\033[0m" << endl;
          cout << "    Ruta     : ";
          for (size_t i = 0; i < r.path.size(); i++) {
            cout << r.path[i] << (i == r.path.size() - 1 ? "" : " -> ");
          }
          cout << "\n    Costo    : S/. " << r.costoTotal << endl;
          cout << "    Distancia: " << r.distanciaTotal << " km" << endl;
        }
        pausar();
        break;
      }
      case 0:
        break;
      default:
        cout << "  Opcion invalida." << endl;
        pausar();
      }
    } while (op != 0);
  }
};
