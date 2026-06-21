#pragma once
#include <vector>
#include <set>
#include <iostream>
#include <stack>
#include <algorithm>
#include "fifo_lifo.hpp"
#include "unidirected_edge.hpp"
#include "unidirected_graph.hpp"
#include "graph_visit.hpp"   

/* CICLI_DFS 
   Dato un grafo planare connesso G(V,E), trova una base di cicli (non
   necessariamente di peso minimo) costituita da k = |E| - |V| + 1 cicli.

       1. Calcola l'albero DFS T = dfs(G).
       2. Calcola il coalbero C = G \ T.
       3. Per ogni arco (u,v) del coalbero:
            - trova il cammino unico in T da u a v (ricorsivo con backtracking)
            - quel cammino + l'arco (u,v) forma un ciclo della base.
*/

// potrei usare Dijkstra già implementata nelle scorse esercitazioni 
// ma ha costo computazionale O((|V|+|E|)log|V|) a causa della priority queue,
// o meglio in un albero (dato che |E|=|V|-1) sarebbe O(|V|log|V|) e considerando le 
// k chiamate in cicli_DFS otteniamo O(k|V|log|V|).
// La funzione implementata ha costo O(|V|+|E|)=O(|V|)
template <typename T>
std::vector<T> find_path (const unidirected_graph<T>& T_graph,
                          const T& source,
                          const T& dest)
{
    std::set<T>    visited;
    std::map<T, T> parent;
    std::stack<T>  stack;

    stack.push(source);
    visited.insert(source);
    parent.insert({source, source}); 

    while (!stack.empty()) {
        T u = stack.top();
        stack.pop();

        if (u == dest) {
            // Ricostruisco il cammino risalendo i parent
            std::vector<T> path;
            T cur = dest;
            while (true) {
                path.push_back(cur);
                const T& p = parent.at(cur);
                if (p == cur) {
                    break;              // arrivato alla radice
                }
                cur = p;
            }
            std::reverse(path.begin(), path.end());
            return path;
        }

        for (const T& v : T_graph.neighbours(u)) {
            if (visited.find(v) == visited.end()) {
                visited.insert(v);
                parent.insert({v, u});
                stack.push(v);
            }
        }
    }

    return {};      // dest non raggiungibile
}


/* Restituisce una base di cicli del grafo G come vector di vector<T>.
   Ogni elemento e' il CAMMINO in T fra gli estremi dell'arco del
   coalbero; il ciclo si chiude con l'arcon(path.back(), path.front()) del coalbero. */
template <typename T>
std::vector<std::vector<T>> cicli_DFS (const unidirected_graph<T>& G)
{
    if (G.num_edges() == 0) {
        return {};
    }

    // Radice = primo nodo del primo arco.
    const auto& first_edge = G.all_edges().front();
    T nodo_radice = first_edge.from();

    // Albero DFS: graph_visit con lifo == stack == DFS
    lifo<T> stack_container;
    unidirected_graph<T> T_graph = graph_visit(G, nodo_radice, stack_container);

    // Coalbero C = G \ T
    unidirected_graph<T> C_graph = G - T_graph;

    const auto& coalbero = C_graph.all_edges();
    const std::size_t  k  = coalbero.size();

    if (k == 0) {
        return {};      // G e' un albero: nessun ciclo
    }

    // Per ogni arco del coalbero trovo il cammino in T fra i suoi estremi
    std::vector<std::vector<T>> cicli;
    cicli.reserve(k);
    
    for (const unidirected_edge<T>& e : coalbero) {
        const T& a = e.from();
        const T& b = e.to();

        std::vector<T> path = find_path(T_graph, a, b);

        if (path.empty()) {
            std::cerr << "[cicli_DFS] ERRORE: cammino non trovato tra "
                      << a << " e " << b << "\n";
            return {};
        }
        cicli.push_back(std::move(path));   // chiusura implicita b -> a
    }

    return cicli;
}
