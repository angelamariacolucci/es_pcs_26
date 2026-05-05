#include "sorts.hpp"
#include <vector>
#include <string>
#include "randfiller.h"
#include <cstdlib>

int main() {
    // 100 vettori di interi casuali
    randfiller rf;
    for (int i=0; i<100; i++) {
        std::vector<int> size_vec(1); //vettore di un solo elemento 
        rf.fill(size_vec,0,200); //lo riempio con un numero tra 0 e 200 che è la dimensione
        std::vector<int> vec;    // creo vettore vuoto 
        vec.resize(size_vec[0]);    // ridimensiono il vettore alla dimensione casuale ottenuta
        rf.fill(vec, -1000,1000);
        mergesort(vec, 0, (int)vec.size()-1);
        if (!is_sorted(vec)) {
            return EXIT_FAILURE;
        }
    }

    // vettore di stringhe
    std::vector<std::string> vec={"mamma", "papà", "fratello", "sorella", "zio", 
        "cugino", "nonno",  "marito", "moglie", "cognata"};
    mergesort(vec,  0, (int)vec.size()-1);
    if (!is_sorted(vec)) {
        return EXIT_FAILURE;
    }

    // vettore vuoto -> deve essere ordinato
    std::vector<int> empty;
    mergesort(empty,  0, (int)empty.size()-1);
    if (!is_sorted(empty)) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}