#pragma once
#include <vector>
#include <set>
#include <utility>          // std::pair
#include <algorithm>        // std::count
#include <limits>
#include <iostream>
#include "unidirected_edge.hpp"
#include "unidirected_graph.hpp"
#include "graph_visit.hpp"  
#include "dijkstra.hpp"

/* DE PINA 
   Costruisce la base di cicli MINIMI di un grafo planare connesso G(V,E),
   usando algebra lineare su vettori booleani in Z_2 e una tecnica di
   lifting per ridurre la ricerca del ciclo minimo a un problema di
   cammino minimo (Dijkstra).

   Si rappresentano i cicli come vettori booleani di lunghezza m=|E|. 
   Lo spazio dei cicli ha dimensione k=|E|-|V|+1
   e si costruisce iterativamente una base C_1,...,C_k tale che ogni
   C_i sia il ciclo di peso minimo che soddisfa <C_i, S_i> = 1, dove
   gli S_i sono "test vector".

   1. Calcolo albero DFS + coalbero.
   2. Inizializzo k vettori S_i = e_{idx(arco_coalbero_i)}.
   3. Per ogni i:
        (a) C_i = find_minimal_cycle(G, S_i)  
        (b) per ogni j > i: se <C_i, S_j>=1, S_j = S_j XOR S_i (eliminazione di Gauss)
*/


/* PRODOTTO SCALARE MOD 2
   <a,b> = (sum_i a_i * b_i)  mod 2
   Restituisce 1 se a e b hanno un numero DISPARI di posizioni dove
   entrambi valgono 1 */
static int scalar_product_mod2 (const std::vector<bool>& a,
                                const std::vector<bool>& b)
{
    int count = 0;
    for (std::size_t i = 0; i < a.size(); ++i) {
        if (a[i] && b[i]) {
            ++count;
        }
    }
    return count % 2;
}


/* DIFFERENZA SIMMETRICA (XOR vettoriale)
   (a XOR b)_i = a_i XOR b_i */
static std::vector<bool> symmetric_difference (const std::vector<bool>& a,
                                               const std::vector<bool>& b)
{
    std::vector<bool> result(a.size(), false);
    for (std::size_t i = 0; i < a.size(); ++i) {
        result[i] = (a[i] != b[i]);        // XOR
    }
    return result;
}


/* =========================================================================
   LIFTING + DIJKSTRA per trovare il ciclo minimo con parita' dispari
   ========================================================================= */

/* NODO LIFTED
   Segno: 0 = "+", 1 = "-".
   Uso std::pair perche' ha gia' operator< lessicografico.
*/
template <typename T>
using lifted_node = std::pair<T, int>;


/* BUILD_LIFTING
   Costruisce il grafo G' a partire da G e dal test vector Si.
   - Per ogni vertice v di G: due copie  (v,0)=v+  e  (v,1)=v-
   - Per ogni arco (u,v) di G:
        se ATTIVO in Si  -> aggiungo  (u+,v-) e (u-,v+)  
        se NON attivo    -> aggiungo  (u+,v+) e (u-,v-) 

    Un cammino in G' da v- a v+ corrisponde ad una passeggiata in G
    che parte e arriva in v ATTRAVERSANDO UN NUMERO DISPARI DI ARCHI
    ATTIVI, esattamente la condizione che cerchiamo.
*/
template <typename T>
unidirected_graph<lifted_node<T>>
build_lifting (const unidirected_graph<T>& G,
               const std::vector<bool>& Si)
{
    unidirected_graph<lifted_node<T>> Gprimo;

    for (const unidirected_edge<T>& e : G.all_edges()) {
        auto idx_ptr = G.edge_number(e);
        const std::size_t idx = *idx_ptr;
        const bool active = Si[idx];

        const T& u = e.from();
        const T& v = e.to();

        const lifted_node<T> u_plus  {u, 0};
        const lifted_node<T> u_minus {u, 1};
        const lifted_node<T> v_plus  {v, 0};
        const lifted_node<T> v_minus {v, 1};

        if (active) {
            // archi incrociati: cambiano segno
            Gprimo.add_edge(unidirected_edge<lifted_node<T>>(u_plus,  v_minus));
            Gprimo.add_edge(unidirected_edge<lifted_node<T>>(u_minus, v_plus ));
        } else {
            // archi paralleli: mantengono segno
            Gprimo.add_edge(unidirected_edge<lifted_node<T>>(u_plus,  v_plus ));
            Gprimo.add_edge(unidirected_edge<lifted_node<T>>(u_minus, v_minus));
        }
    }
    return Gprimo;
}


/* FIND_MINIMAL_CYCLE
   Trova il ciclo di peso minimo che soddisfa <C, Si> = 1.
   Per ogni vertice v di G:
      - calcola il cammino minimo in G' da v- a v+ (Dijkstra)
      - proietta il cammino su G come vettore d'incidenza booleano
        (XOR-incrementando le posizioni degli archi attraversati)
   Tiene il candidato con piu' pochi 1 (peso unitario per arco).
*/
template <typename T>
std::vector<bool> find_minimal_cycle (const unidirected_graph<T>& G,
                                      const std::vector<bool>& Si)
{
    const std::size_t m = G.num_edges();
    unidirected_graph<lifted_node<T>> Gprimo = build_lifting(G, Si);

    std::vector<bool> best_cycle;
    int best_weight = std::numeric_limits<int>::max();

    for (const T& v : G.all_nodes()) {
        const lifted_node<T> v_plus  {v, 0};
        const lifted_node<T> v_minus {v, 1};

        // Dijkstra da v-
        result<lifted_node<T>> res = dijkstra(Gprimo, v_minus);

        // v+ raggiunto?
        auto it = res.dist.find(v_plus);
        if (it == res.dist.end() || it->second < 0) {
            continue;       // nessun cammino con parita' dispari attraverso v
        }

        // Ricostruisco il cammino da v- a v+
        std::vector<lifted_node<T>> lpath = path(res, v_plus);
        if (lpath.size() < 2) {
            continue;
        }

        // Proietto il cammino in G come vettore d'incidenza
        std::vector<bool> cycle(m, false);
        for (std::size_t i = 0; i + 1 < lpath.size(); ++i) {
            const T& a = lpath[i].first;
            const T& b = lpath[i+1].first;
            unidirected_edge<T> orig_edge(a, b);
            auto idx_ptr = G.edge_number(orig_edge);
            if (idx_ptr.has_value()) {
                // XOR-incremento: se passo due volte per lo stesso arco
                // si cancella.
                const std::size_t idx = *idx_ptr;
                cycle[idx] = !cycle[idx];
            }
        }

        // Peso del ciclo: numero di 1 nel vettore (peso unitario per arco)
        const int weight = static_cast<int>(
            std::count(cycle.begin(), cycle.end(), true));

        if (weight > 0 && weight < best_weight) {
            best_weight = weight;
            best_cycle  = cycle;
        }
    }

    return best_cycle;
}


// ALGORITMO PRINCIPALE DI DE PINA

template <typename T>
std::vector<std::vector<bool>> de_pina (const unidirected_graph<T>& G)
{
    if (G.num_edges() == 0) {
        return {};
    }

    // Albero DFS e coalbero
    const auto& first_edge = G.all_edges().front();
    T root = first_edge.from();

    unidirected_graph<T> T_graph = recursive_dfs(G, root);
    unidirected_graph<T> C_graph = G - T_graph;

    const auto& cotree = C_graph.all_edges();
    const std::size_t  k  = cotree.size();
    const std::size_t  m  = G.num_edges();

    if (k == 0) {
        return {};      // grafo senza cicli (albero)
    }

    // Inizializzazione dei test vector S_i
    std::vector<std::vector<bool>> S(k, std::vector<bool>(m, false));
    std::size_t z = 0;
    for (const unidirected_edge<T>& e : cotree) {
        S[z][*G.edge_number(e)] = true;
        ++z;
    }

    // Loop principale
    std::vector<std::vector<bool>> base;
    base.reserve(k);

    for (std::size_t i = 0; i < k; ++i) {
        // (a) ciclo minimo C_i con <C_i, S_i> = 1
        std::vector<bool> Ci = find_minimal_cycle(G, S[i]);
        if (Ci.empty()) {
            std::cerr << "[de_pina] ERRORE: ciclo minimo non trovato all'"
                      << "iterazione " << i << "\n";
            return {};
        }
        base.push_back(Ci);

        // (b) aggiornamento dei test vector successivi
        for (std::size_t j = i + 1; j < k; ++j) {
            if (scalar_product_mod2(Ci, S[j]) == 1) {
                S[j] = symmetric_difference(S[j], S[i]);
            }
        }
    }

    return base;
}


//conversione "vettore d'incidenza" -> lista di archi

template <typename T>
std::vector<unidirected_edge<T>>
incidence_to_edges (const unidirected_graph<T>& G,
                    const std::vector<bool>& cycle)
{
    std::vector<unidirected_edge<T>> result;
    for (std::size_t i = 0; i < cycle.size(); ++i) {
        if (cycle[i]) {
            auto e_opt = G.edge_at(i);
            if (e_opt.has_value()) {
                result.push_back(*e_opt);
            }
        }
    }
    return result;
}
