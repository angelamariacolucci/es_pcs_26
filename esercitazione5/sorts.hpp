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

// MERGE 
template <typename T>
void merge(std::vector<T>& A, int left, int mid, int right)
{
    int n1=mid-left+1;  // lunghezza della metà di sinistra A[left..mid]
    int n2=right-mid;    // lunghezza della metà di destra A[mid+1 ..right]
   
    std::vector<T> leftVec(n1);
    std::vector<T> rightVec(n2);

    for (int i=0; i<n1; i++) {
        leftVec[i]=A[left+i];
    }

    for (int j=0; j<n2; j++) {
        rightVec[j]=A[mid+j+1];
    }
    
    int i = 0;
    int j = 0;
    int k = left;
 
    while (i<n1 && j<n2) {
        if (leftVec[i] <= rightVec[j]) {
            A[k] = leftVec[i];
            i++;
        }
        else {
            A[k] = rightVec[j];
            j++;
        }
        k++;
    }
    // copio gli elementi rimasti in leftVec o in rightVec
    while (i<n1) {
        A[k] = leftVec[i];
        i++;
        k++;
    }
    while (j<n2) {
        A[k] = rightVec[j];
        j++;
        k++;
    }
}
 
// MERGESORT
template <typename T>
void mergesort(std::vector<T>& A, int left, int right)
{
    if (left<right) {
        int mid=(left+right)/2; // divisione intera
        mergesort(A,left,mid);
        mergesort(A,mid+1,right);
        merge(A,left,mid,right);
    }
}

// MERGESORT: input solo vettore
template <typename T>
void mergesort_function(std::vector<T>& A)
{
    if (A.size()<=1) {
        return;
    }

    mergesort(A, 0, (int)A.size()-1);
}

// PARTITION 
template <typename T>
int partition(std::vector<T>& A, int left, int right) {
    T x=A[right];
    int i=left-1;
    for (int j=left; j<=right-1; j++) {
        if (A[j]<=x) {
            i=i+1;
            std::swap(A[i],A[j]);
        }
    }
    std::swap(A[i+1],A[right]);
    return i+1;
}

// QUICKSORT
template <typename T>
void quicksort(std::vector<T>& A, int left, int right) 
{
    if (left<right) {
        int mid=partition(A,left,right);
        quicksort(A,left,mid-1);
        quicksort(A,mid+1,right);
    }
}

// QUICKSORT: input solo vettore
template <typename T>
void quicksort_function(std::vector<T>& A)
{
    if (A.size()<=1) {
        return;
    }

    quicksort(A, 0, (int)A.size()-1);
}

// QUICKSORT_HYBRID
template <typename T>
void quicksort_hybrid(std::vector<T>& A, int left, int right, int threshold=50) 
    // metto valore di default se la soglia non viene trovata 
{
    if (left < right) {
        if (right - left + 1 <= threshold) {
            // insertion sort inline sul sottointervallo [left..right]
            for (int j = left + 1; j <= right; j++) {
                T key = A[j];
                int i = j - 1;
                while (i >= left && A[i] > key) {
                    A[i+1] = A[i];
                    i--;
                }
                A[i+1] = key;
            }
        } else {
            int mid = partition(A, left, right);
            quicksort_hybrid(A, left, mid - 1, threshold);
            quicksort_hybrid(A, mid + 1, right, threshold);
        }
    }
}

template <typename T>
void quicksort_hybrid_function(std::vector<T>& A, int threshold = 50)
{
    if (A.size() <= 1) {
        return;
    }

    quicksort_hybrid(A, 0, (int)A.size() - 1, threshold);
}
