#pragma once
#include "list" // usamos la biblioteca lista evitar crear una clase lista generica demas
#include "vector"
// ya que solo necesitamos su logica de nodos
#include "string"
using namespace std;
/*
Clase: NodoHash
Representa un nodo de la tabla hash que almacena un par clave-valor que
seran almacenados en la lista de cada bucket de la tabla hash.
La clave es un string y el valor es de tipo T.
*/
template <typename T> class NodoHash {
public:
  string clave;
  T valor;
};

/*
 Clase: HashTable
 Tabla hash generica con manejo de colisiones por encadenamiento (chaining).
 Permite insertar, buscar y eliminar pares clave-valor donde la clave es
 un string que puede ser el nombre del producto, o cualquier string que queramos
 y el valor es de tipo T para retornar cualquier tipo de dato. Usa la funcion
 hash polinomial de base 31.
*/
template <typename T> class HashTable {
private:
  /*
  vector<list<pair<string, T>>> tabla; (alternativa usando la strutura pair,
  pero se tiene que incluir #include <utility>)
  */
  vector<list<NodoHash<T>>> tabla; // Vector de listas de pares clave-valor
  int m;                           // Tama�o de la tabla (numero de buckets)

  /*
   Funcion hash polinomial de base 31.
   Convierte una clave string en un indice entero dentro del rango [0, m-1].
  */
  int hashFunction(string &key) {
    unsigned long h = 0;
    for (char c : key) {
      h = h * 31 + (unsigned char)c;
    }
    return h % m;
  }

public:
  /*
   Constructor.
   Inicializa la tabla con el tamanio indicado.
  */
  HashTable(int tam) : tabla(tam), m(tam) {}

  /*
   Inserta un par clave-valor en la tabla.
   Si la clave ya existe en su bucket, actualiza el valor.
   Si no existe, agrega el nuevo par al bucket correspondiente.
   // Complejidad: O(n) peor caso, O(1) mejor caso
  */
  void insertar(string clave, T valor) {
    int idx = hashFunction(clave);
    auto &bucket = tabla[idx];

    for (auto &nodo : bucket) {
      if (nodo.clave == clave) {
        nodo.valor = valor; // actualiza si ya existe
        return;
      }
    }
    NodoHash<T> nuevo;
    nuevo.clave = clave;
    nuevo.valor = valor;
    bucket.push_back(nuevo); // inserta nuevo
  }

  /*
   Busca un valor por clave en la tabla.
   Si lo encuentra, lo asigna al parametro de salida y retorna true.
   Si no lo encuentra, retorna false.
   // Complejidad: O(n) peor caso, O(1) mejor caso
  */
  bool encontrado(string &clave, T &out) {
    int idx = hashFunction(clave);
    auto &bucket = tabla[idx];

    for (auto &nodo : bucket) {
      if (nodo.clave == clave) {
        out = nodo.valor;
        return true;
      }
    }
    return false;
  }

  /*
   Elimina un par clave-valor de la tabla.
   Retorna true si la clave fue encontrada y eliminada.
   Retorna false si la clave no existe en la tabla.
   // Complejidad: O(n) peor caso, O(1) mejor caso
  */
  bool borrar(string &clave) {
    int idx = hashFunction(clave);
    auto &bucket = tabla[idx];

    for (auto it = bucket.begin(); it != bucket.end(); ++it) {
      if (it->clave == clave) {
        bucket.erase(it);
        return true;
      }
    }
    return false;
  }
};
