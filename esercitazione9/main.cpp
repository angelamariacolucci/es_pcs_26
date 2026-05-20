#include "dijkstra.hpp"
#include "fifo_lifo.hpp"
#include "graph_visit.hpp"
#include "graphViz.hpp"
#include "unidirected_graph.hpp"
#include "unidirected_edge.hpp"

#include <fstream>
#include <iostream>
#include <string>


unidirected_graph<int> test_graph()
{
    unidirected_graph<int> g;
    g.add_edge(unidirected_edge<int>(1, 2));
    g.add_edge(unidirected_edge<int>(1, 4));
    g.add_edge(unidirected_edge<int>(1, 3));
    g.add_edge(unidirected_edge<int>(1, 6));

    g.add_edge(unidirected_edge<int>(2, 7));
    g.add_edge(unidirected_edge<int>(2, 5));
    g.add_edge(unidirected_edge<int>(2, 4));

    g.add_edge(unidirected_edge<int>(3, 6));
    g.add_edge(unidirected_edge<int>(4, 6));
    g.add_edge(unidirected_edge<int>(4, 7));

    g.add_edge(unidirected_edge<int>(5, 7));
    g.add_edge(unidirected_edge<int>(6, 7));
    g.add_edge(unidirected_edge<int>(6, 8));
    g.add_edge(unidirected_edge<int>(7, 9));
    g.add_edge(unidirected_edge<int>(8, 9));
    return g;
}

void test_dijkstra_int()
{
    std::cout <<"Test Dijkstra (grafo int, source=1)\n";
    auto g= test_graph();
    auto res= dijkstra(g, 1);
 
    for (const auto& [v, d] : res.dist) {
        std::cout << "  dist[" << v << "] = " << d;
        auto cammino = path(res, v);
        std::cout << "  (cammino: ";
        for (const auto& n : cammino) {
            std::cout << n << " ";
        }
        std::cout << ")\n";
    }
}

unidirected_graph<std::string> test_graph_string()
{
    unidirected_graph<std::string> g;
    g.add_edge(unidirected_edge<std::string>("Milano",  "Torino"));
    g.add_edge(unidirected_edge<std::string>("Milano",  "Bologna"));
    g.add_edge(unidirected_edge<std::string>("Torino",  "Roma"));
    g.add_edge(unidirected_edge<std::string>("Bologna",  "Firenze"));
    g.add_edge(unidirected_edge<std::string>("Bologna", "Genova"));
    g.add_edge(unidirected_edge<std::string>("Firenze", "Genova"));
    return g;
}

void test_dijkstra_string()
{
    std::cout << "Test Dijkstra (grafo stringhe, source=Milano)\n";
    auto g= test_graph_string();
    auto res= dijkstra(g, std::string("Milano"));
 
    for (const auto& [v, d] : res.dist) {
        std::cout << "  dist[" << v << "] = " << d;
        auto cammino = path(res, v);
        std::cout << "  (cammino: ";
        for (const auto& n : cammino) {
            std::cout << n << " ";
        }
        std::cout << ")\n";
    }
}

void int_dot()
{
    auto g = test_graph();

    fifo<int> q;
    auto bfs_tree = graph_visit(g, 1, q);

    lifo<int> s;
    auto dfs_tree = graph_visit(g, 1, s);

    auto rec_tree = recursive_dfs(g, 1);

    std::ofstream f1("grafo_originale.dot");
    to_dot(f1, g);
    std::ofstream f2("albero_bfs.dot");
    to_dot(f2, bfs_tree);
    std::ofstream f3("albero_dfs.dot");
    to_dot(f3, dfs_tree);
    std::ofstream f4("albero_dfs_rec.dot");
    to_dot(f4, rec_tree);   
}

void string_dot()
{
    auto g=test_graph_string();

    fifo<std::string> q;
    auto bfs_tree = graph_visit(g, std::string("Milano"), q);

    lifo<std::string> s;
    auto dfs_tree = graph_visit(g, std::string("Milano"), s);
    
    auto rec_tree = recursive_dfs(g, std::string("Milano"));
 
    std::ofstream f1("grafo_stringhe.dot");
    to_dot(f1, g);
    std::ofstream f2("bfs_stringhe.dot");
    to_dot(f2, bfs_tree);
    std::ofstream f3("dfs_stringhe.dot");
    to_dot(f3, dfs_tree);
    std::ofstream f4("dfs_rec_stringhe.dot");
    to_dot(f4, rec_tree);

}
int main()
{
    int_dot();
    string_dot();
    test_dijkstra_int();
    test_dijkstra_string();
}