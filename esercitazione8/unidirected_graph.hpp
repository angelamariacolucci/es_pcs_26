#pragma once
#include "unidirected_edge.hpp"
#include <set>
#include <list>
#include <map>
#include <unordered_map>
#include <iostream>
#include <cstddef>
#include <optional>

template <typename T>
class unidirected_graph {
public:
    unidirected_graph() = default; // crea un grafo vuoto
    unidirected_graph(const unidirected_graph& other) = default;
    
    /* NEIGHBOURS()
       Dato un nodo restituisce i suoi vicini.
       Se il nodo non è nel grafo, restituisce un set vuoto */
    std::set<T> neighbours (const T& node) const
    {
        auto it= adiacenza.find(node);
        if (it != adiacenza.end()) {
            return it -> second;    // (*it).second
        } else {
            return {};
        }

        //if (adiacenza.count(node)==0) {    
        //    return {};
        //} 
        //return adiacenza.at(node);

    }

    /* ADD_EDGE()
       Permette di aggiungere un arco al grafo.
       Se l'arco è già presente, non viene eseguita alcuna operazione, 
       in modo da evitare duplicati.
    */
    void add_edge (const unidirected_edge<T>& edge)
    {
        auto it=edge_num.find(edge);
        if (it != edge_num.end()) {     // arco già nel grafo
            return;
        }

        const std::size_t num=edges.size(); // numero archi
        edges.push_back (edge);
        edge_num.insert ({edge, num}); //emplace(edge, num)
        num_edge.insert ({num, edge});

        // Adiacenza simmetrica (grafo non diretto)
        adiacenza[edge.from()].insert(edge.to());
        adiacenza[edge.to()].insert(edge.from());
        // Assicuro che entrambi i nodi compaiano nella lista di adiacenza 
        // (operator[] crea nuovo elemento se manca).

    }

    /* ALL_EDGES()
       Restituisce tutti gli archi */
    const std::list<unidirected_edge<T>>& all_edges() const
    {
        return edges;
    }

    /* ALL_NODES()
       Restituisce tutti i nodi a partire dalle chiavi della 
       lista di adiacenza */
    std::set<T> all_nodes() const
    {
        std::set<T> nodes;
        for (const auto& elemento : adiacenza) {
            nodes.insert(elemento.first);    
        }
        return nodes;
    }

        //for (auto it = adjacency_.begin(); it != adjacency_.end(); ++it) {
        //    nodes.insert(it->first);
        //}



    /* EDGE_NUMBER()
       Dato un arco restituisce la sua numerazione all'interno del grafo.
    */
    std::optional<std::size_t> edge_number(const unidirected_edge<T>& edge) const 
    {
        auto it = edge_num.find(edge);
        if (it==edge_num.end()) {
            std::cout << "edge_num: arco non presente nel grafo \n";
            return std::nullopt;
        }
        return it -> second;
    }

    /* EDGE_AT()
       Dato un numero d'arco, restituisce il corrispondente arco nel grafo */
    std::optional<unidirected_edge<T>> edge_at (std::size_t num) const  //std::optional non può restituire riferimenti
    {
        auto it =num_edge.find(num);
        if (it==num_edge.end()) {
            std::cout << "num_edge: numero d'arco non valido\n";
            return std::nullopt;
        }
        return it -> second;
    }

    /* OPERATOR-()
       Permette di calcolare la differenza tra due grafi:
       dati G1 e G2, la differenza G1-G2 è un nuovo grafo con gli archi presenti 
       in G1 e non presenti in G2 (differenza insiemistica). */
    unidirected_graph operator-(const unidirected_graph& other) const 
    {
        unidirected_graph differenza;
        for (const unidirected_edge<T>& edge : edges) {
            auto it = other.edge_num.find(edge);
            if (it==other.edge_num.end()) {
                differenza.add_edge(edge);
            }
        }
        return differenza;
    }

    std::size_t num_edges() const 
    { 
        return edges.size(); 
    }
    std::size_t num_nodes() const 
    { 
        return adiacenza.size(); 
    }

private:
    std::map<T, std::set<T>>    adiacenza; // per ogni nodo si ha la vista dei suoi vicini
                                        // std::set evita duplicati ed è ordinato
    std::map<unidirected_edge<T>, std::size_t>  edge_num;   // arco -> numero
    std::list<unidirected_edge<T>>  edges;  // lista ordinata di archi nell'rdine di inserimento 
    std::unordered_map<std::size_t, unidirected_edge<T>> num_edge;   // numero -> arco 

};

// I nodi non sono entità indipendneti ma sono visti come estremi di archi.
// Aggiungendo un arco (a,b) mediante add_edge, automaticamente a e b vengono 
// inseriti come chiavi nella lista di adiacenza e sono visibili traminte 
// all_nodes().
// Quindi un metodo add_node() sarebbe ridondante.