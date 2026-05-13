/* TEST PER GRAFI */
#include "unidirected_edge.hpp"
#include "unidirected_graph.hpp"
#include <cstdlib>  //EXIT_SUCCESS, EXIT_FAILURE
#include <iostream>
#include <sstream>
#include <string>

// 1. INVARIANTE FROM < TO
static int test_edge_invariance() 
{
    unidirected_edge<int> a(1,2);
    if (a.from() != 1 || a.to() != 2) {
        std::cerr << "ERRORE: test_edge_invariance\n";
        return EXIT_FAILURE;
    }

    unidirected_edge<int> b(4,3);
    if (b.from() != 3 || b.to() != 4) {
        std::cerr << "ERRORE: test_edge_invariance, arco (4,3) non riordinato \n";
        return EXIT_FAILURE;
    }

    std::cout << "[OK] test_edge_invariance\n";
    return EXIT_SUCCESS;
}

// 2. OPERATORE<
static int test_edge_order() {
    unidirected_edge<int> a(1,2);
    unidirected_edge<int> b(1,3);
    unidirected_edge<int> c(2,3);

    if (!(a<b)) {
        std::cerr << "ERRORE: test_edge_order\n";
        return EXIT_FAILURE;
    }

    if (!(b<c)) {
        std::cerr << "ERRORE: test_edge_order\n";
        return EXIT_FAILURE;        
    }

    if (a<a) {
        std::cerr << "ERRORE: test_edge_order\n";
        return EXIT_FAILURE;
    }

    std::cout << "[OK] test_edge_order\n";
    return EXIT_SUCCESS;
}

// 3. OPERATORE==
static int test_edge_equality() {
    unidirected_edge<int> a(1,2);
    unidirected_edge<int> b(2,1);
    unidirected_edge<int> c(1,3);

    if (a != b) {
        std::cerr << "ERRORE: test_edge_equality\n";
        return EXIT_FAILURE;
    }

    if (a == c) {
        std::cerr << "ERRORE: test_edge_equality\n";
        return EXIT_FAILURE;
    }

    std::cout << "[OK] test_edge_equality\n";
    return EXIT_SUCCESS;
}

// 4. OPERATORE<<
static int test_edge_stream()
{
    unidirected_edge<int> edge(1,2);
    std::ostringstream out;
    out << edge;
    // std::cout << out.str();
    if (out.str() != "(1,2)\n") {
        std::cerr << "ERRORE: test_edge_stream\n";
        return EXIT_FAILURE;
    }

    std::cout << "[OK] test_edge_stream\n";
    return EXIT_SUCCESS;
}

// 5. AGGIUNTA ARCHI E POPOLAMENTO NODI 
static int test_graph_add_nodes()
{
    unidirected_graph<int> graph;
    graph.add_edge(unidirected_edge<int> (1,2));
    graph.add_edge(unidirected_edge<int> (2,3));
    graph.add_edge(unidirected_edge<int> (1,4));

    auto nodes=graph.all_nodes();
    if (nodes.size() != 4) {
        std:: cerr << "ERRORE test_graph_add_nodes\n";
        return EXIT_FAILURE;
    }

    if (!nodes.count(1) || !nodes.count(2) || !nodes.count(3) ||
        !nodes.count(4))
    {
        std::cerr << "ERRORE test_graph_add_nodes\n";
        return EXIT_FAILURE;
    }
    if (graph.num_edges() != 3) {
        std::cerr << "ERRORE test_graph_add_nodes\n";
        return EXIT_FAILURE;
    }
 
    std::cout << "[OK] test_graph_add_nodes\n";
    return EXIT_SUCCESS;
}

// 6. ARCO DUPLICATO
static int test_graph_duplicate_edge()
{
    unidirected_graph<int> graph;
    graph.add_edge(unidirected_edge<int> (1,2));
    graph.add_edge(unidirected_edge<int> (2,1));
    graph.add_edge(unidirected_edge<int> (1,2));    

    if (graph.num_edges() != 1) {
        std::cerr << "ERRORE: test_graph_duplicate_edge\n";
        return EXIT_FAILURE; 
    }

    std::cout << "[OK] test_graph_duplicate_edge\n";
    return EXIT_SUCCESS;
}

// 7. NEIGHBOURS()
static int test_graph_neighbours() 
{
    unidirected_graph<int> g;
    g.add_edge(unidirected_edge<int>(1, 2));
    g.add_edge(unidirected_edge<int>(1, 3));
    g.add_edge(unidirected_edge<int>(1, 4));
    g.add_edge(unidirected_edge<int>(2, 3));   
    
    auto n1 = g.neighbours(1);
    if (n1.size() != 3 || !n1.count(2) || !n1.count(3) || !n1.count(4)) {
        std::cerr << "ERRORE: test_graph_neighbours\n";
        return EXIT_FAILURE;
    }
 
    auto n2 = g.neighbours(2);
    if (n2.size() != 2 || !n2.count(1) || !n2.count(3)) {
        std::cerr << "ERRORE: test_graph_neighbours\n";
        return EXIT_FAILURE;
    }
 
    auto n42 = g.neighbours(42);
    if (!n42.empty()) {
        std::cerr << "ERRORE: test_graph_neighbours\n";
        return EXIT_FAILURE;
    }
 
    std::cout << "[OK] test_graph_neighbours\n";
    return EXIT_SUCCESS;
}

// 8. EDGE_NUMBER() e EDGE_AT() 
static int test_graph_edge_number_and_at()
{
    unidirected_graph<int> g;
    unidirected_edge<int> a(1, 2);
    unidirected_edge<int> b(2, 3);
    unidirected_edge<int> c(1, 4);
 
    g.add_edge(a);
    g.add_edge(b);
    g.add_edge(c);
 
    if (g.edge_number(a) != 0 || g.edge_number(b) != 1 || g.edge_number(c) != 2) {
        std::cerr << "ERRORE: test_graph_edge_number_and_at:\n";
        return EXIT_FAILURE;
    }

    if (!(g.edge_at(0) == a) || !(g.edge_at(1) == b) || !(g.edge_at(2) == c)) {
        std::cerr << "ERRORE: test_graph_edge_number_and_at\n";
        return EXIT_FAILURE;
    }
 
    std::cout << "[OK] test_graph_edge_number_and_at\n";
    return EXIT_SUCCESS;
}

// 9. COSTRUTTORE DI COPIA
static int test_graph_copy_is_independent()
{
    unidirected_graph<int> g;
    g.add_edge(unidirected_edge<int>(1, 2));
    g.add_edge(unidirected_edge<int>(2, 3));
 
    unidirected_graph<int> h(g);
    h.add_edge(unidirected_edge<int>(3, 4));
 
    if (g.num_edges() != 2) {
        std::cerr << "ERRORE: test_graph_copy_is_independent\n";
        return EXIT_FAILURE;
    }
    if (h.num_edges() != 3) {
        std::cerr << "ERRORE: test_graph_copy_is_independent\n";
        return EXIT_FAILURE;
    }
 
    std::cout << "[OK] test_graph_copy_is_independent\n";
    return EXIT_SUCCESS;
}
 
// 10. DIFFERENZA
static int test_graph_difference()
{
    unidirected_graph<int> g1;
    g1.add_edge(unidirected_edge<int>(1, 2));
    g1.add_edge(unidirected_edge<int>(2, 3));
    g1.add_edge(unidirected_edge<int>(3, 4));
 
    unidirected_graph<int> g2;
    g2.add_edge(unidirected_edge<int>(2, 3));
    g2.add_edge(unidirected_edge<int>(5, 6));
 
    unidirected_graph<int> diff = g1 - g2;
 
    if (diff.num_edges() != 2) {
        std::cerr << "ERRORE: test_graph_difference\n";
        return EXIT_FAILURE;
    }
 
    bool has12 = false, has34 = false, has23 = false;
    for (const auto& e : diff.all_edges()) {
        if (e == unidirected_edge<int>(1, 2)) {
            has12 = true; }
        if (e == unidirected_edge<int>(3, 4)) { 
            has34 = true; }
        if (e == unidirected_edge<int>(2, 3)) {
            has23 = true; }
    }
    if (!has12 || !has34 || has23) {
        std::cerr << "ERRORE: test_graph_difference\n";
        return EXIT_FAILURE;
    }
 
    std::cout << "[OK] test_graph_difference\n";
    return EXIT_SUCCESS;
}


// 11. GRAFO DI STRINGHE
static int test_graph_strings()
{
    unidirected_graph<std::string> g;
    g.add_edge(unidirected_edge<std::string>("Torino", "Milano"));
    g.add_edge(unidirected_edge<std::string>("Milano", "Roma"));
    g.add_edge(unidirected_edge<std::string>("Roma",   "Napoli"));
 
    if (g.num_nodes() != 4 || g.num_edges() != 3) {
        std::cerr << "ERRORE: test_graph_strings\n";
        return EXIT_FAILURE;
    }
 
    auto vicini_di_milano = g.neighbours("Milano");
    if (vicini_di_milano.size() != 2 ||
        !vicini_di_milano.count("Torino") ||
        !vicini_di_milano.count("Roma"))
    {
        std::cerr << "ERRORE: test_graph_strings\n";
        return EXIT_FAILURE;
    }
 
    std::cout << "[OK] test_graph_strings\n";
    return EXIT_SUCCESS;
}
 
 

int main()
{
    if (test_edge_invariance() == EXIT_FAILURE ||
        test_edge_equality() == EXIT_FAILURE || 
        test_edge_order() == EXIT_FAILURE ||
        test_edge_stream() == EXIT_FAILURE ||
        test_graph_add_nodes() == EXIT_FAILURE ||
        test_graph_duplicate_edge() == EXIT_FAILURE ||
        test_graph_neighbours() == EXIT_FAILURE ||
        test_graph_edge_number_and_at() == EXIT_FAILURE ||
        test_graph_copy_is_independent() == EXIT_FAILURE ||
        test_graph_difference() == EXIT_FAILURE || 
        test_graph_strings() == EXIT_FAILURE) {
            return EXIT_SUCCESS;
        }
}
 