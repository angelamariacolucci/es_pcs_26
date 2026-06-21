#include "unidirected_edge.hpp"
#include "unidirected_graph.hpp"
#include "de_pina.hpp"

#include <cstdlib>
#include <iostream>
#include <map>
#include <vector>
#include <algorithm>

/* Test unitari per de_pina (base di cicli minimi via lifting + Dijkstra).

   Usiamo gli stessi grafi di test_cicliDFS.cpp:
     - F_albero:  4 nodi, 3 archi  -> albero, nessun ciclo
     - G_ciclico: F_albero + 2 archi -> 2 cicli minimi (2 triangoli, peso 3+3=6)
*/

unidirected_graph<int> F_albero;
unidirected_graph<int> G_ciclico;


/* Numero di archi in un ciclo rappresentato come vettore d'incidenza. */
static int peso_ciclo (const std::vector<bool>& cycle)
{
    return static_cast<int>(std::count(cycle.begin(), cycle.end(), true));
}


/* Somma dei pesi di una base di cicli (vettori d'incidenza). */
static int peso_totale (const std::vector<std::vector<bool>>& base)
{
    int tot = 0;
    for (const auto& c : base) {
        tot += peso_ciclo(c);
    }
    return tot;
}


/* Verifica che 'cycle' (vettore d'incidenza) sia un ciclo valido in G:
   - almeno 3 archi,
   - nel sottografo dei suoi archi, ogni nodo ha grado pari
     (proprieta' algebrica che caratterizza un ciclo).
*/
static bool is_ciclo_valido (const unidirected_graph<int>& G,
                             const std::vector<bool>& cycle)
{
    if (peso_ciclo(cycle) < 3) {
        return false;
    }

    std::map<int, int> grado;
    for (std::size_t i = 0; i < cycle.size(); i++) {
        if (!cycle[i]) continue;
        auto e_opt = G.edge_at(i);
        if (!e_opt.has_value()) return false;
        ++grado[e_opt->from()];
        ++grado[e_opt->to()];
    }
    for (const auto& [nodo, deg] : grado) {
        (void)nodo;
        if (deg % 2 != 0) return false;
    }
    return true;
}


/* 1) Su un albero non devono esserci cicli */
static int test_de_pina_albero ()
{
    auto cicli = de_pina(F_albero);
    if (!cicli.empty()) {
        std::cerr << "ERRORE: test_de_pina_albero: attesi 0 cicli, trovati "
                  << cicli.size() << "\n";
        return EXIT_FAILURE;
    }
    std::cout << "[OK] test_de_pina_albero\n";
    return EXIT_SUCCESS;
}


/* 2) Numero di cicli corretto: k = m - n + 1 */
static int test_de_pina_numero ()
{
    auto cicli = de_pina(G_ciclico);
    const int n = static_cast<int>(G_ciclico.num_nodes());
    const int m = static_cast<int>(G_ciclico.num_edges());
    const int attesi = m - n + 1;

    if (static_cast<int>(cicli.size()) != attesi) {
        std::cerr << "ERRORE: test_de_pina_numero: attesi " << attesi
                  << " cicli, trovati " << cicli.size() << "\n";
        return EXIT_FAILURE;
    }
    std::cout << "[OK] test_de_pina_numero\n";
    return EXIT_SUCCESS;
}


/* 3) Ogni ciclo restituito deve essere un ciclo strutturalmente valido
      (grado pari su tutti i nodi del sottografo). */
static int test_de_pina_validita ()
{
    auto cicli = de_pina(G_ciclico);

    for (std::size_t i = 0; i < cicli.size(); i++) {
        if (!is_ciclo_valido(G_ciclico, cicli[i])) {
            std::cerr << "ERRORE: test_de_pina_validita: ciclo " << i
                      << " non valido\n";
            return EXIT_FAILURE;
        }
    }
    std::cout << "[OK] test_de_pina_validita\n";
    return EXIT_SUCCESS;
}


/* 4) Il peso totale della base deve essere il minimo noto.
      G_ciclico (quadrato 0-1-2-3 + diagonale 0-2) -> due triangoli
      {0,1,2} e {0,2,3}, peso totale 3+3 = 6. */
static int test_de_pina_peso_minimo ()
{
    auto cicli = de_pina(G_ciclico);
    const int peso   = peso_totale(cicli);
    const int atteso = 6;

    if (peso != atteso) {
        std::cerr << "ERRORE: test_de_pina_peso_minimo: atteso " << atteso
                  << ", trovato " << peso << "\n";
        return EXIT_FAILURE;
    }
    std::cout << "[OK] test_de_pina_peso_minimo\n";
    return EXIT_SUCCESS;
}


int main ()
{
    F_albero.add_edge(unidirected_edge<int>(0, 1));
    F_albero.add_edge(unidirected_edge<int>(1, 2));
    F_albero.add_edge(unidirected_edge<int>(2, 3));

    G_ciclico.add_edge(unidirected_edge<int>(0, 1));
    G_ciclico.add_edge(unidirected_edge<int>(1, 2));
    G_ciclico.add_edge(unidirected_edge<int>(2, 3));
    G_ciclico.add_edge(unidirected_edge<int>(3, 0));
    G_ciclico.add_edge(unidirected_edge<int>(0, 2));

    int falliti = 0;
    falliti += test_de_pina_albero()      == EXIT_SUCCESS ? 0 : 1;
    falliti += test_de_pina_numero()      == EXIT_SUCCESS ? 0 : 1;
    falliti += test_de_pina_validita()    == EXIT_SUCCESS ? 0 : 1;
    falliti += test_de_pina_peso_minimo() == EXIT_SUCCESS ? 0 : 1;

    if (falliti == 0) {
        std::cout << "\nTutti i test su De Pina sono passati.\n";
        return EXIT_SUCCESS;
    } else {
        std::cerr << "\n" << falliti << " test falliti.\n";
        return EXIT_FAILURE;
    }
}