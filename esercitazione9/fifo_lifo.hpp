#pragma once 
#include <queue>
#include <stack>


/* fifo<T>: coda FIFO
   put(x) inserisce l'elemento in fondo
   get() estrae l'elemento in testa alla coda (il più vecchio) 
*/
template <typename T>
class fifo {
public:
    fifo()=default;
    void put(const T& x) {
        q.push(x);          // inserts element at the end
    }

    T get() {
        T x=q.front();  // access the first element e copies value to x
        q.pop();        // removes the first element
        return x;
    }

    bool empty() {
        return q.empty();   // checks whether the container adaptor is empty
    }

private:
    std::queue<T> q;
};


/* lifo<T>: pila LIFO
   put(x) inserisce in cima allo stack
   get() estrae l'elemento in cima (il più recente)
*/
template<typename T>
class lifo {
public:
    lifo()=default;

    void put(const T& x) {
        s.push(x);          // inserts element at the top
    }

    T get() {
        T x=s.top();  // accesses the top element e copies value to x
        s.pop();    // removes the top element
        return(x);
    }

    bool empty() {
        return s.empty();   // checks whether the container adaptor is empty
    }
private:
    std::stack<T> s;
};