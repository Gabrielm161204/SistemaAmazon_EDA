#pragma once

#include <iostream>
#include <string>
#include <vector>
#include <cstdlib>
#include <ctime>
using namespace std;

// Clase con los algoritmos de ordenamientos.
class Ordenamiento {
public:
    // --- Bubble Sort (Burbuja) ---
    // Compara pares adyacentes e intercambia si estan en orden incorrecto
    // Complejidad: O(n^2)
    // "comp" indica si el primer elemento debe ir DESPUES del segundo (igual que > en orden ascendente)
    template <typename T, typename Comparador>
    static void bubbleSort(vector<T>& arr, Comparador comp) {
        int n = arr.size();
        for (int i = 0; i < n - 1; i++) {
            for (int j = 0; j < n - i - 1; j++) {
                if (comp(arr[j], arr[j + 1])) {
                    T temp = arr[j];
                    arr[j] = arr[j + 1];
                    arr[j + 1] = temp;
                }
            }
        }
    }

    // Version sin comparador: orden ascendente por defecto (para vector<double>)
    template <typename T>
    static void bubbleSort(vector<T>& arr) {
        bubbleSort(arr, [](const T& a, const T& b) { return a > b; });
    }

    // --- Selection Sort (Seleccion) ---
    // Busca el minimo (segun el comparador) y lo coloca al inicio en cada iteracion
    // Complejidad: O(n^2)
    template <typename T, typename Comparador>
    static void selectionSort(vector<T>& arr, Comparador comp) {
        int n = arr.size();
        for (int i = 0; i < n - 1; i++) {
            int minIdx = i;
            for (int j = i + 1; j < n; j++) {
                if (comp(arr[minIdx], arr[j])) minIdx = j;
            }
            T temp = arr[minIdx];
            arr[minIdx] = arr[i];
            arr[i] = temp;
        }
    }

    template <typename T>
    static void selectionSort(vector<T>& arr) {
        selectionSort(arr, [](const T& a, const T& b) { return a > b; });
    }

    // --- Insertion Sort (Insercion) ---
    // Inserta cada elemento en su posicion correcta dentro de la parte ordenada
    // Complejidad: O(n^2) peor caso, O(n) mejor caso
    template <typename T, typename Comparador>
    static void insertionSort(vector<T>& arr, Comparador comp) {
        int n = arr.size();
        for (int i = 1; i < n; i++) {
            T key = arr[i];
            int j = i - 1;
            while (j >= 0 && comp(arr[j], key)) {
                arr[j + 1] = arr[j];
                j--;
            }
            arr[j + 1] = key;
        }
    }

    template <typename T>
    static void insertionSort(vector<T>& arr) {
        insertionSort(arr, [](const T& a, const T& b) { return a > b; });
    }

    // --- Quick Sort (Recursivo) ---
    // RECURSIVIDAD: la funcion se llama a si misma con subproblemas mas pequenos
    // Complejidad: O(n log n) promedio
    template <typename T, typename Comparador>
    static void quickSort(vector<T>& arr, int bajo, int alto, Comparador comp) {
        if (bajo < alto) {
            int pi = particion(arr, bajo, alto, comp);
            quickSort(arr, bajo, pi - 1, comp);   // Recursion izquierda
            quickSort(arr, pi + 1, alto, comp);   // Recursion derecha
        }
    }

    template <typename T>
    static void quickSort(vector<T>& arr, int bajo, int alto) {
        quickSort(arr, bajo, alto, [](const T& a, const T& b) { return a > b; });
    }

    // ============================================================
    // FISHER-YATES SHUFFLE
    // Genera permutacion aleatoria sin sesgo - O(n)
    // ============================================================
    template<typename T>
    static void fisherYates(vector<T>& arr) {
        srand((unsigned int)time(0));
        int n = arr.size();
        for (int i = n - 1; i > 0; i--) {
            int j = rand() % (i + 1);   // indice aleatorio entre 0 e i
            T temp = arr[i];
            arr[i] = arr[j];
            arr[j] = temp;
        }
    }

    // Mostrar vector de doubles
    static void mostrarVector(vector<double>& arr, string titulo) {
        cout << titulo << ": [ ";
        for (double x : arr) cout << x << " ";
        cout << "]" << endl;
    }

private:
    // Usada internamente por quickSort; no hace falta exponerla afuera
    template <typename T, typename Comparador>
    static int particion(vector<T>& arr, int bajo, int alto, Comparador comp) {
        T pivote = arr[alto];
        int i = bajo - 1;
        for (int j = bajo; j < alto; j++) {
            if (!comp(arr[j], pivote)) {   // arr[j] "<=" pivote segun el comparador
                i++;
                T temp = arr[i]; arr[i] = arr[j]; arr[j] = temp;
            }
        }
        T temp = arr[i + 1]; arr[i + 1] = arr[alto]; arr[alto] = temp;
        return i + 1;
    }
};