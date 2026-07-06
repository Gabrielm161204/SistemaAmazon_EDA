#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <queue>

using namespace std;

/*
 Estructura: Arista
 Representa una conexión entre dos ciudades dentro del grafo de envíos.
 Guarda el índice de la ciudad destino, el costo del envío en soles
 y la distancia en kilómetros de la ruta.
*/
struct Arista {
    int destino;      // Índice de la ciudad destino en el vector 'ciudades'
    double costo;     // Costo económico del envío en soles
    double distancia; // Distancia de la ruta en kilómetros
};

/*
 Estructura: RutaInfo
 Almacena el resultado de calcular la ruta óptima entre dos ciudades.
 Contiene el camino (lista de ciudades), el costo total y la distancia
 total de la ruta.
*/
struct RutaInfo {
    vector<string> path;   // Secuencia de ciudades que forman la ruta
    double costoTotal;     // Costo total del envío en soles
    double distanciaTotal; // Distancia total recorrida en kilómetros
};

/*
 Clase: GrafoEnvio
 Modela la red de rutas de envío entre ciudades del Perú como un grafo
 no dirigido con pesos. Cada ciudad es un nodo y cada ruta una arista
 con costo económico y distancia en kilómetros. Permite calcular la
 ruta más económica entre dos ciudades usando el algoritmo de Dijkstra.
*/

class GrafoEnvio {
private:
    vector<string> ciudades;          // Lista de ciudades registradas como nodos del grafo
    vector<vector<Arista>> adj;       // Lista de adyacencia: rutas salientes de cada ciudad

    /*
     Busca el índice de una ciudad dentro del vector 'ciudades'.
     Retorna el índice si la encuentra o -1 si la ciudad no existe en el grafo.
    */
    int obtenerIndice(const string& ciudad) {
        for (size_t i = 0; i < ciudades.size(); i++) {
            if (ciudades[i] == ciudad) return (int)i;
        }
        return -1;
    }

public:
    /*
     Constructor por defecto.
     Inicializa el grafo con un conjunto de ciudades principales del Perú
     y agrega rutas predeterminadas con sus costos y distancias.
    */
    GrafoEnvio() {
        // Inicializar ciudades por defecto
        ciudades = {"Lima", "Trujillo", "Chiclayo", "Piura",
                    "Arequipa", "Cusco", "Iquitos"};
        adj.resize(ciudades.size());

        // Agregar conexiones por defecto (origen, destino, costo, distancia)
        agregarRuta("Lima", "Trujillo", 15.0, 560.0);
        agregarRuta("Trujillo", "Chiclayo", 10.0, 200.0);
        agregarRuta("Chiclayo", "Piura", 12.0, 250.0);
        agregarRuta("Lima", "Arequipa", 25.0, 1000.0);
        agregarRuta("Arequipa", "Cusco", 20.0, 500.0);
        agregarRuta("Lima", "Cusco", 35.0, 1100.0);
        agregarRuta("Lima", "Iquitos", 60.0, 1000.0);
    }

    /*
     Agrega una ruta bidireccional entre dos ciudades del grafo.
     Si ambas ciudades existen, crea una arista en cada dirección para
     permitir envíos de ida y vuelta.
    */
    void agregarRuta(const string& orig, const string& dest,
                     double costo, double dist) {
        int u = obtenerIndice(orig);
        int v = obtenerIndice(dest);
        if (u != -1 && v != -1) {
            // Grafo no dirigido: se agregan aristas en ambas direcciones
            adj[u].push_back({v, costo, dist});
            adj[v].push_back({u, costo, dist});
        }
    }

    /*
     Retorna la lista de ciudades registradas en el grafo.
    */
    const vector<string>& getCiudades() const {
        return ciudades;
    }

    /*
     Calcula la ruta más económica desde una ciudad origen hasta una ciudad destino.
     Usa el algoritmo de Dijkstra con una cola de prioridad (min-heap) para
     encontrar el camino de menor costo. Si alguna ciudad no existe o no
     hay ruta posible, retorna costoTotal y distanciaTotal en -1.
    */
    RutaInfo calcularRuta(const string& origen, const string& destino) {
        int src = obtenerIndice(origen);
        int dest = obtenerIndice(destino);

        RutaInfo info;
        info.costoTotal = -1;
        info.distanciaTotal = -1;

        if (src == -1 || dest == -1) return info;

        int n = (int)ciudades.size();
        vector<double> distCosto(n, INT_MAX); // costo mínimo acumulado hasta cada ciudad
        vector<double> distKms(n, 0);         // distancia acumulada hasta cada ciudad
        vector<int> prev(n, -1);              // predecesor de cada ciudad en la ruta

        // Cola de prioridad mínima: (costo, índice de nodo)
        priority_queue<
            pair<double, int>,
            vector<pair<double, int>>,
            greater<pair<double, int>>
        > pq;

        distCosto[src] = 0;
        pq.push({0.0, src});

        while (!pq.empty()) {
            double u_costo = pq.top().first;
            int u = pq.top().second;
            pq.pop();

            if (u_costo > distCosto[u]) continue;
            if (u == dest) break;

            for (const auto& edge : adj[u]) {
                int v = edge.destino;
                if (distCosto[u] + edge.costo < distCosto[v]) {
                    distCosto[v] = distCosto[u] + edge.costo;
                    distKms[v] = distKms[u] + edge.distancia;
                    prev[v] = u;
                    pq.push({distCosto[v], v});
                }
            }
        }

        if (distCosto[dest] == INT_MAX) {
            // No existe ruta entre origen y destino
            return info;
        }

        info.costoTotal = distCosto[dest];
        info.distanciaTotal = distKms[dest];

        // Reconstruir camino desde 'dest' hacia atrás usando 'prev'
        int curr = dest;
        while (curr != -1) {
            info.path.push_back(ciudades[curr]);
            curr = prev[curr];
        }
        reverse(info.path.begin(), info.path.end());

        return info;
    }
};
