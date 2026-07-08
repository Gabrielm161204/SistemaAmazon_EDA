## trabajo tipo Amazon (curso: Estructura de datos avanzados)

- link de los requisitos para la TB2: https:
https://drive.google.com/file/d/1yroJGwWxFXuh4CUHn4GPmzjqBY5jW02M/view?usp=sharing

- link de la propuesta de diagrama de clases modificando algunas partes:
https://sweet-crisp-6233c1.netlify.app/

Hito 1: Semana 13: Domingo 28 de junio del 2026 (5 puntos) 

Hito 2: Semana 14 (entrega final): Domingo 05 de julio del 2026 (15 puntos)

---

## ✅ Requisitos del Hito 1 — Semana 13

### 📊 Análisis Big O — 9 funciones identificadas

| # | Función | Archivo | Complejidad |
|---|---|---|---|
| 1 | `bubbleSort()` | `Ordenamiento.h` | O(n²) |
| 2 | `selectionSort()` | `Ordenamiento.h` | O(n²) |
| 3 | `insertionSort()` | `Ordenamiento.h` | O(n²) peor / O(n) mejor |
| 4 | `quickSort()` | `Ordenamiento.h` | O(n log n) promedio |
| 5 | `fisherYates()` | `Ordenamiento.h` | O(n) |
| 6 | `buscarRecursivo()` | `GestorInventario.h` | O(n) |
| 7 | `buscarPorNombre()` via HashTable | `HashTable.h` | O(1) promedio |
| 8 | `cuentaRegresiva()` | `Sistema.h` | O(n) |
| 9 | `calcularTotalRecursivo()` | `Historial.h` | O(n) |

---

### 🧩 Uso de Templates — 8 usos

| # | Template | Archivo |
|---|---|---|
| 1 | `Pila<T>` + `NodoPila<T>` | `Pila.h` |
| 2 | `Cola<T>` + `NodoCola<T>` | `Cola.h` |
| 3 | `HashTable<T>` + `NodoHash<T>` | `HashTable.h` |
| 4 | `bubbleSort<T, Comparador>` | `Ordenamiento.h` |
| 5 | `selectionSort<T, Comparador>` | `Ordenamiento.h` |
| 6 | `insertionSort<T, Comparador>` | `Ordenamiento.h` |
| 7 | `quickSort<T, Comparador>` | `Ordenamiento.h` |
| 8 | `fisherYates<T>` | `Ordenamiento.h` |

---

### 🔁 Uso de Recursividad — 5 funciones

| # | Función | Archivo | Descripción |
|---|---|---|---|
| 1 | `buscarRecursivo()` | `GestorInventario.h` | Recorre lista buscando por nombre |
| 2 | `mostrarRecursivo()` | `GestorInventario.h` | Muestra todos los productos |
| 3 | `calcularTotalRecursivo()` | `Historial.h` | Suma totales del historial |
| 4 | `quickSort()` | `Ordenamiento.h` | Se llama a sí mismo con subarreglos |
| 5 | `cuentaRegresiva()` | `Sistema.h` | Recursividad simple con caso base |

---

### 🔷 Uso de Lambdas — 7 lambdas

| # | Lambda | Archivo |
|---|---|---|
| 1 | `sumarSubtotales` — acumula total del carrito | `Carrito.h` |
| 2 | `tieneStockSuficiente` — valida stock de items | `Carrito.h` |
| 3 | `esDeLaCategoria` — filtra productos por categoría | `Marketplace.h` |
| 4 | Comparador por defecto `bubbleSort` | `Ordenamiento.h` |
| 5 | Comparador por defecto `selectionSort` | `Ordenamiento.h` |
| 6 | Comparador por defecto `insertionSort` | `Ordenamiento.h` |
| 7 | Comparador por defecto `quickSort` | `Ordenamiento.h` |

---

### 🗂️ Uso de Estructuras de Datos — 4 estructuras

| # | Estructura | Tipo | Implementada en |
|---|---|---|---|
| 1 | Lista enlazada simple | Inventario de productos | `GestorInventario.h` + `NodoProducto.h` |
| 2 | Lista doblemente enlazada | Historial de pedidos | `Historial.h` |
| 3 | Pila (LIFO) | Acciones del cliente | `Pila.h` → `Cliente.h` |
| 4 | Cola (FIFO) | Pedidos del marketplace | `Cola.h` → `Marketplace.h` |

---

### ⚡ Ordenamientos Avanzados — 2 algoritmos

| # | Algoritmo | Usado en |
|---|---|---|
| 1 | `quickSort` | `Ordenamiento.h` → `GestorInventario.h` |
| 2 | `fisherYates` | `Ordenamiento.h` → `Marketplace.h` |

---

### #️⃣ Implementación de Hash Table — 1 implementación propia

| Clase | Archivo | Detalle |
|---|---|---|
| `HashTable<T>` + `NodoHash<T>` | `HashTable.h` | Hash polinomial base 31, chaining con `list`, nodo propio |

Usada en `GestorInventario.h` como índice de búsqueda rápida (`indicePorNombre`).

---

### 🗃️ Generador de Dataset — 1 clase dedicada

| Clase | Archivo | Detalle |
|---|---|---|
| `GeneradorData` | `GeneradorData.h` | Carga datos fijos + genera N productos aleatorios |

Usada en `Sistema.h` al iniciar el sistema y desde el menú de inventario.
