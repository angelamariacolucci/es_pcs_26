#include <vector>
#include <iostream>
#include <algorithm>
#include "sorts.hpp"
#include "randfiller.h"
#include "timecounter.h"


int main() {
    timecounter tc; /* instantiate the timecounter */
    randfiller rf;  /* instantiate the randfiller */
    
    for (int n=4; n<=8192; n*=2) {
        std::vector<int> vec; //creo vettore vuoto
        vec.resize(n);  //vettore di lunghezza n
        rf.fill(vec,-1000,1000);    //riempio il vettore con numeri casuali

        // BUBBLE_SORT
        std::vector<int> vec_copy = vec;    //faccio copia perchè algortimo modifica ordine 
        tc.tic();
        bubble_sort(vec_copy);
        double time_bubblesort=tc.toc();

        // INSERTION_SORT
        vec_copy = vec;    
        tc.tic();
        insertion_sort(vec_copy);
        double time_insertionsort=tc.toc();
        
        // SELECTION_SORT
        vec_copy = vec;   
        tc.tic();
        selection_sort(vec_copy);
        double time_selectionsort=tc.toc();

        // std::sort
        vec_copy = vec;    
        tc.tic();
        std::sort(vec_copy.begin(),vec_copy.end());
        double time_stdsort=tc.toc();
        

        // stampo i risultati
        std::cout << "Dimensione del vettore: "<< n << "\n";
        std::cout << "Bubble sort:     "<< time_bubblesort << "\n";
        std::cout << "Insertion sort:  "<< time_insertionsort << "\n";
        std::cout << "Selection sort:  "<< time_selectionsort << "\n";
        std::cout << "std::sort():     "<< time_stdsort << "\n";
        std::cout << "\n";
    }
    return EXIT_SUCCESS;
}