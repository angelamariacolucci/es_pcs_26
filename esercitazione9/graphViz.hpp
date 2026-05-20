#pragma once 
#include "unidirected_graph.hpp"
#include <ostream>
 
template <typename Node>
void to_dot (std::ostream& out,
            const unidirected_graph<Node>& G)
{
    out << "graph G {\n";
    for (const auto& v : G.all_nodes()) {
        out << "  \"" << v << "\"\n";
    }
    for (const auto& e : G.all_edges()) {
        out << "  \"" << e.from() << "\" -- \"" << e.to() << "\"\n";
    }
    out << "}\n";
}