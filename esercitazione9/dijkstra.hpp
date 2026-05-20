#pragma once 
#include "unidirected_edge.hpp"
#include "unidirected_graph.hpp"
#include <map>
#include <queue>
#include <vector>
#include <algorithm>

/* PSEUDOCODICE DI RIFERIMENTO
    Dijkstra(LA, s, W, m):
        for i = 0..m-1:                                                  
            pred[i] = -1
            dist[i] = +infinito
        pred[s] = s
        dist[s] = 0
        for i = 0..m-1:                                                  
            PQ.Enqueue(i, dist[i])
        while (!PQ.empty()):
            (u, p) = PQ.Dequeue()                                           
            foreach w in LA[u]:
                if dist[w] > dist[u] + W[u,w]:                                
                    dist[w] = dist[u] + W[u,w]
                    pred[w] = u
                    PQ.DecreaseKey(w, dist[w])                                

Si tratta di una BFS modificata con coda con priorità PQ i cui elementi
sono i vertici del grafo e si assume peso unitario W[u,v]=1 per ogni arco.
*/

// L'algoritmo restituisce: distanze e predecessori
// Ho usato std::map e non array perchè, dato che ho un tipo Node che 
// è template generico, non sempre i nodi sono interi continugi che posso 
// usare come indici dell'array
template <typename Node>
struct result {
    std::map<Node, int> dist;   //dist[v]= distanza minima da s 
    std::map<Node, Node> pred;    //pred[v]=predecessore 
};

template <typename Node>
struct pq_node {
    Node node;
    int distance;

    bool operator>(const pq_node& other) const {    
        return distance > other.distance;       // confronto distanza 
    }
};

template <typename Node>
result<Node> dijkstra (const unidirected_graph<Node>& G, const Node& source)
{
    const int W_EDGE=1;  //peso unitario degli archi 
    result<Node> result;

    for (const Node& v : G.all_nodes()) {
        result.dist[v]=-1;              // sentinella -1 = non raggiunto 
    }

    result.dist[source]=0;   //dist[s]=0
    result.pred[source]=source;   //pred[s]=s

    // uso std::priority_queue della libreria standard
    std::priority_queue <pq_node<Node>, std::vector<pq_node<Node>>, std::greater<pq_node<Node>>> pq;
    pq.push({source,0});

    while (!pq.empty()) {
        auto top = pq.top();                 
        Node u   = top.node;
        int d_u  = top.distance;
        pq.pop();

        // alternativa alla DecreaseKey
        if (d_u > result.dist[u]) {
            continue;
        }

        for (const Node& w : G.neighbours(u)) {
            if (result.dist[w] == -1 || result.dist[w] > result.dist[u] + W_EDGE) {
                result.dist[w] = result.dist[u] + W_EDGE;
                result.pred[w] = u; 

                pq.push({w, result.dist[w]});
            }
        }
    }
    return result;
}

// Ricostruisco cammino minimo dalla sorgente a un nodo usando pred[]
template <typename Node> 
std::vector<Node> path(const result<Node>& res, const Node& arrive)
{
    std::vector<Node> path;
    auto it = res.pred.find(arrive);
    if (it == res.pred.end()) {
        return path;    // vuoto se mai raggiunto
    }
 
    Node cur = arrive;
    while (true) {
        path.push_back(cur);
        Node p = res.pred.at(cur);
        if (p == cur) {
            break;   // arrivati alla sorgente
        }
        cur = p;
    }
    std::reverse(path.begin(), path.end());
    return path;
}