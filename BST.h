#pragma once
#include <iostream>
#include <string>
#include <vector>
using namespace std;

/*
 Clase: NodoBST
 Representa un nodo dentro de un Árbol Binario de Búsqueda.
 Guarda una clave de tipo string usada para ordenar, el valor
 genérico asociado a esa clave y punteros a los hijos izquierdo
 y derecho.
*/
template <typename T>
class NodoBST {
public:
    string clave;       // Clave de comparación del nodo
    T valor;            // Valor genérico asociado a la clave
    NodoBST* izquierdo; // Puntero al hijo izquierdo (claves menores)
    NodoBST* derecho;   // Puntero al hijo derecho (claves mayores)

    /*
     Constructor con clave y valor.
     Inicializa el nodo con la clave y valor indicados y sus hijos en nullptr.
    */
    NodoBST(string k, T v) : clave(k), valor(v), izquierdo(nullptr), derecho(nullptr) {}
};

/*
 Clase: ArbolBinarioBusqueda BST
 Implementa un Árbol Binario de Búsqueda (BST) genérico que usa strings como claves. 
 Permite insertar elementos, buscarlos por clave y obtener un recorrido 
 inorden con los valores ordenados
 de menor a mayor según la clave.
*/
template <typename T>
class ArbolBinarioBusqueda {
private:
    NodoBST<T>* raiz; // Puntero al nodo raíz del árbol

    /*
     Libera recursivamente la memoria de todos los nodos de un subárbol.
	 Recorre en postorden (izquierdo, derecho, nodo) para eliminar hijos antes que el padre evitando
	 trata de acceder a memoria ya liberada.
    */
    void destruir(NodoBST<T>* nodo) {
        if (nodo != nullptr) {
            destruir(nodo->izquierdo);
            destruir(nodo->derecho);
            delete nodo;
        }
    }

    /*
     Inserta recursivamente un nodo con la clave y valor dados en el subárbol.
     Si la clave es menor se inserta en el hijo izquierdo, si es mayor en el derecho.
     Si la clave ya existe, solo actualiza el valor almacenado.
     Retorna el puntero al nodo actual luego de la inserción.
    */
    NodoBST<T>* insertarRecursivo(NodoBST<T>* nodo, string clave, T valor) {
        if (nodo == nullptr) {
            return new NodoBST<T>(clave, valor);
        }
        if (clave < nodo->clave) {
            nodo->izquierdo = insertarRecursivo(nodo->izquierdo, clave, valor);
        } else if (clave > nodo->clave) {
            nodo->derecho = insertarRecursivo(nodo->derecho, clave, valor);
        } else {
            // Clave duplicada: actualizamos el valor
            nodo->valor = valor;
        }
        return nodo;
    }

    /*
     Busca recursivamente un valor por su clave en el subárbol.
     Si encuentra la clave, retorna el valor asociado.
     Si no existe, retorna nullptr (pensado para tipos puntero).
    */
    T buscarRecursivo(NodoBST<T>* nodo, string clave) {
        if (nodo == nullptr) {
            return nullptr;
        }
        if (clave == nodo->clave) {
            return nodo->valor;
        }
        if (clave < nodo->clave) {
            return buscarRecursivo(nodo->izquierdo, clave);
        }
        return buscarRecursivo(nodo->derecho, clave);
    }

    /*
     Recorre el subárbol en orden inorden: izquierda, nodo, derecha.
     Va agregando cada valor visitado al vector resultado para obtener
     una lista ordenada por clave.
    */
    void inordenRecursivo(NodoBST<T>* nodo, vector<T>& resultado) {
        if (nodo != nullptr) {
            inordenRecursivo(nodo->izquierdo, resultado);
            resultado.push_back(nodo->valor);
            inordenRecursivo(nodo->derecho, resultado);
        }
    }

public:
    /*
     Constructor por defecto.
     Inicializa el árbol vacío con la raíz en nullptr.
    */
    ArbolBinarioBusqueda() : raiz(nullptr) {}

    /*
     Destructor.
     Libera toda la memoria ocupada por los nodos del árbol.
    */
    ~ArbolBinarioBusqueda() {
        destruir(raiz);
    }

    /*
     Inserta un nuevo elemento en el árbol con la clave y valor dados.
     Si la clave ya existe, solo actualiza el valor sin crear un nuevo nodo.
    */
    void insertar(string clave, T valor) {
        raiz = insertarRecursivo(raiz, clave, valor);
    }

    /*
     Busca un elemento por su clave.
     Retorna el valor asociado si la clave se encuentra,
     o nullptr si no existe (pensado para tipos puntero).
    */
    T buscar(string clave) {
        return buscarRecursivo(raiz, clave);
    }

    /*
     Retorna todos los valores del árbol en orden ascendente según su clave.
     La lista resultante se obtiene mediante el recorrido inorden.
    */
    vector<T> obtenerInorden() {
        vector<T> resultado;
        inordenRecursivo(raiz, resultado);
        return resultado;
    }

    /*
     Elimina todos los nodos del árbol y reinicia la raíz a nullptr.
     Útil para vaciar el árbol y reutilizarlo.
    */
    void limpiar() {
        destruir(raiz);
        raiz = nullptr;
    }
};
