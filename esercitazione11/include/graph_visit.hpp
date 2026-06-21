#pragma once 
#include <set>
#include "unidirected_graph.hpp"
#include "unidirected_edge.hpp"

/* graph_visit(G,source,container)
   Template function: una sola implementazione fa BFS o DFS in base al
   tipo del contenitore passato.
   - Se 'container' e' un fifo<Node>, la visita e' in AMPIEZZA  (BFS).
   - Se 'container' e' un lifo<Node>, la visita e' in PROFONDITA' (DFS).
   Restituisce un nuovo unidirected_graph contenente l'albero di visita.

   L'algoritmo e' lo stesso per BFS e DFS:
   1) marca 'source' come visitato e mettilo nel contenitore;
   2) finche' il contenitore non e' vuoto:
        a. estrai un nodo u;
        b. per ogni vicino v di u non ancora visitato:
           - marca v come visitato,
           - aggiungi l'arco (u, v) all'albero di visita,
           - metti v nel contenitore.
*/

template <typename Node, typename Container>
unidirected_graph<Node> graph_visit (const unidirected_graph<Node>& G, 
                                    const Node& source, 
                                    Container& container) 
{
    unidirected_graph<Node> tree;
    std::set<Node> visited;         // registra i nodi già visitati 
                                    // non uso array perchè i nodi sono generici 

    visited.insert(source);         // nodo sorgente già visitato
    container.put(source);          // primo nodo nel contenitore

    while(!container.empty()) {
        Node u=container.get();     //  ui si materializza differenza tra BFS e DFS
        for (const Node& w : G.neighbours(u)) {
            if (visited.find(w)==visited.end()) {   // non visitato
                visited.insert(w);  // segna come visitato
                container.put(w);
                tree.add_edge(unidirected_edge<Node>(u,w));
            }
        }
    }

    return tree;
}

/* recursive_dfs<Node>(G, source)
   Versione ricorsiva della DFS.
   La funzione esterna prepara le strutture (albero + set 'visited') e invoca
   una helper ricorsiva.

   La helper e' una traduzione dello pseudocodice in CORMEN:
    DFS-VISIT(G, u):
        u.color = GRAY              // marca u come "in lavorazione"
        for each v ∈ G.Adj[u]:      // per ogni vicino
            if v.color == WHITE:    // se non ancora scoperto
                DFS-VISIT(G, v)     // ricorsione
        u.color = BLACK             // marca u come "completato"

   Lo pseudocodice classico associa a ciascun nodo uno di tre stati:
       WHITE : non ancora scoperto
       GRAY  : scoperto, in lavorazione (la sua chiamata ricorsiva e' attiva
               e sta esplorando il suo sottoalbero)
       BLACK : completato, tutti i suoi discendenti sono stati visitati

   Non uso la distinsione dei tre colori perchè ogni nodo ha due possibili 
   stati: "presente in 'visited'" oppure "non presente" e quindi unisco 
   GRAY e BLACK in un unico stato "visitato".
*/

template <typename Node>
void recursive_dfs_h(const unidirected_graph<Node>& G,
                     const Node& u,
                     std::set<Node>& visited,
                     unidirected_graph<Node>& tree)
{
    visited.insert(u);                          // equivale a u.color=GRAY
    for (const Node& w : G.neighbours(u)) {     // for each v ∈ G.Adj[u]
        if (visited.find(w)==visited.end()) {   // if v.color == WHITE
            recursive_dfs_h(G,w,visited,tree);  // DFS-VISIT(G, v) 
            tree.add_edge(unidirected_edge<Node> (u,w));
        }
    }
}

template <typename Node>
unidirected_graph<Node> recursive_dfs( const unidirected_graph<Node>& G, 
                                        const Node& source)
{
    unidirected_graph<Node> tree;
    std::set<Node> visited;
    recursive_dfs_h(G,source,visited,tree);

    return tree;
}


