#include <vector>
#include <fstream>
#include <iostream>
#include <algorithm>
#include "sorts.hpp"
#include "randfiller.h"
#include "timecounter.h"

/* Misura il tempo medio per ordinare un singolo vettore, ordinando in
 * sequenza tutti i vettori contenuti in 'timeVec' tramite la funzione 'T'.
 *
 * Strategia:
 *   1) si parte da una copia indipendente dei vettori (così l'ordinamento
 *      modifica 'timeVec_copy' e non 'timeVec', e si possono confrontare piu' algoritmi
 *      sugli stessi dati di partenza);
 *   2) tic()/toc() fuori al ciclo for che ordina tutti i vettori;
 */
template <typename algoritmo>
double measure_sort(const std::vector<std::vector<int>>& timeVec, algoritmo T)
{
    const std::size_t N = timeVec.size();
    std::vector<std::vector<int>> timeVec_copy = timeVec;   // copia 

    timecounter tc;
    tc.tic();
    for (std::size_t i = 0; i < N; i++) {
        T(timeVec_copy[i]);
    }
    double total = tc.toc();

    return total / N;
}


template <typename T>
void std_sort (std::vector<T>& v) 
{
    std::sort(v.begin(), v.end());
}


int main()
{
    randfiller rf;
    static const int M = 100; // numero di vettori per ogni dimensione

    std::ofstream ofs("measure_sort2.txt");
    if (!ofs) {
        std::cerr << "Impossibile aprire measure_sort2.txt in scrittura\n";
        return EXIT_FAILURE;
    }

    ofs << "n   bubble   insertion   selection   merge   quick  std::sort   quick_hybrid\n";

    int n0=0;

    for (int n = 5; n <= 100; n+=5) {
        // 100 vettori riempiti una volta sola con numeri casuali in [-1000,1000]
        std::vector<std::vector<int>> timeVec(M, std::vector<int>(n));
        for (std::vector<int>& v : timeVec) {
            rf.fill(v, -1000000, 1000000);
        }

        double t_bubble = measure_sort(timeVec, bubble_sort<int>);
        double t_insertion = measure_sort(timeVec, insertion_sort<int>);
        double t_selection = measure_sort(timeVec, selection_sort<int>);
        double t_merge = measure_sort (timeVec, mergesort_function<int>);
        double t_quick = measure_sort (timeVec, quicksort_function<int>);
        double t_std = measure_sort (timeVec, std_sort<int>);
        

        /* Calcolo la soglia: cerco il primo n per cui il piu' veloce
         * tra gli algoritmi logaritmici batte il piu' veloce dei quadratici. */
        double quadratico=std::min({t_bubble, t_insertion, t_selection});
        double logaritmico=std::min({t_merge,t_quick});

        if (n0==0 && logaritmico<quadratico) {
            n0=n;   //la soglia è il primo n per cui il logaritmo batte il quadratico
        }

        // calcolo il tempo di quicksort senza measure_sort perchè devo passare anche n0
        const std::size_t N = timeVec.size();
        std::vector<std::vector<int>> timeVec_copy = timeVec;   // copia 

        timecounter tc;
        tc.tic();
        for (std::size_t i = 0; i < N; i++) {
            quicksort_hybrid_function(timeVec_copy[i], n0);
        }
        double total = tc.toc();
        double t_quickHybrid = total / N;

        ofs << n
            << "  " << t_bubble
            << "  " << t_insertion
            << "  " << t_selection
            << "  " << t_merge
            << "  " << t_quick
            << "  " << t_std  
            << "  " << t_quickHybrid << "\n";
    }
    if (n0!=0) {
        std::cout << "Soglia trovata: n0 = " << n0 << "\n";
    } else {
        std::cout << "Nessuna soglia trovata in [5,100] \n";
    }

    ofs.close();
    std::cout << "Risultati salvati in measure_sort2.txt\n";
    

    return EXIT_SUCCESS;
}
