#pragma once
#include <iostream>
#include <string>
using namespace std;
/*
 Clase: Perfil
 Clase base que representa el perfil de un usuario en el sistema.
 Almacena datos personales basicos: nombre, DNI y fecha de registro.
 Es heredada por la clase Cliente para extender su funcionalidad.
*/
class Perfil {
public:
  string nombre;        // Nombre completo del usuario
  string dni;           // Numero de DNI del usuario
  string fechaRegistro; // Fecha en que se registro el usuario en el sistema

  // Constructor por defecto. Inicializa todos los campos como cadenas vacias.
  Perfil() : nombre(""), dni(""), fechaRegistro("") {}

  // Constructor con parametros. Recibe nombre, DNI y fecha de registro.
  Perfil(string nom, string d, string fecha)
      : nombre(nom), dni(d), fechaRegistro(fecha) {}

  // Muestra en consola el nombre, DNI y fecha de registro del perfil
  void mostrarPerfil() {
    cout << "  Nombre         : " << nombre << endl;
    cout << "  DNI            : " << dni << endl;
    cout << "  Fecha registro : " << fechaRegistro << endl;
  }

  /*
   Actualiza el nombre del perfil al valor indicado.
   Muestra en consola la confirmacion del cambio.
  */
  void actualizarNombre(string nuevoNombre) {
    nombre = nuevoNombre;
    cout << "  [OK] Nombre actualizado a: " << nombre << endl;
  }

  // Retorna el nombre del perfil
  string getNombre() { return nombre; }

  // Retorna el DNI del perfil
  string getDni() { return dni; }
};
