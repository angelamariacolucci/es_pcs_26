#pragma once 

#include <vector> 

// Verifico se un vettore è ordinato in modo crescente.
template<typename T>
bool is_sorted(const std::vector<T>& vec)
{
    if (vec.size()==0) {
        return true;
    }

    for (int i=0; i<(int)vec.size()-1; i++) {
        if (vec[i]>vec[i+1]) {
            return false;
        }
    }
    return true;
}

// BUBBLE_SORT 
template<typename T> 
void bubble_sort(std::vector<T>& A)
{
    if (A.size()==0) {
        return;
    }

    for (int i=0; i<=(int)A.size()-2; i++) {
        for (int j=(int)A.size()-1; j>=i+1; j--) {
            if (A[j]<A[j-1]) {
                std::swap(A[j],A[j-1]);
            }
        }
    }
}

// INSERTION_SORT
template<typename T>
void insertion_sort(std::vector<T>& A)
{
    if (A.size()==0) {
        return;
    }

    for (int j=1; j<=(int)A.size()-1; j++) {
        T key=A[j];
        int i=j-1;
        while (i>=0 && A[i]>key) {
            A[i+1]=A[i];
            i--;
        }
        A[i+1]=key;
    }
}

// SELECTION_SORT
template <typename T>
void selection_sort(std::vector<T>& A)
{
    if (A.size()==0) {
        return;
    }
    
    for (int i=0; i<=(int)A.size()-2; i++) {
        int minimo=i;
        for (int j=i+1; j<=(int)A.size()-1; j++) {
            if (A[j]<A[minimo]) {
                minimo=j;
            }
        }
        std::swap(A[i],A[minimo]);
    }
}