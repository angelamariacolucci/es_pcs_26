#pragma once 
#include <iostream>

template <typename T>
class unidirected_edge {
public:
    /* COSTRUTTORE
       Prende i due nodi connessi dall'arco e garantisce che from_<=to_
    */ 
    unidirected_edge (const T& a, const T& b)
    {
        if (a<b) {
            from_ = a;
            to_ = b;
        } else {
            from_ = b;
            to_ = a;
        }
    }

    /* FROM() e TO()
       Due metodi che restituiscono i due estremi
    */
    const T& from() const {
        return from_;
    }

    const T& to() const {
        return to_;
    }

    /* OPERATORE<
       Permette di ordinare gli archi 
    */
    bool operator< (const unidirected_edge& other) const
    {
        if (from_ != other.from_) {
            return from_<other.from_;
        }
        return to_<other.to_;
    }

    /* OPERATORE==
       Gli archi sono uguali se hanno gli stessi estremi.
    */
    bool operator== (const unidirected_edge& other) const
    {
        return from_==other.from_ && to_==other.to_;
    }

    bool operator!= (const unidirected_edge& other) const
    {
        return !(*this==other);
    }

    /* OPERATORE<<
       Stampa l'arco come (from_, to_)
       E' dichiarato 'friend' poichè non è un metodo (il primo argomento è
       lo stream, non l'arco); serve ad accedere ai membri privati.
       In alternativa definsico operator<< fuori dalla classe
    */

    friend std::ostream& operator<< (std::ostream& out, const unidirected_edge& edge)
    {
        out << "(" << edge.from_ << "," << edge.to_ << ")\n";
        return out;
    }
private:
    T from_;
    T to_;
};

// altervativa OPERATORE<<
/*
template <typename T>
std::ostream& operator<<(std::ostream& out, const unidirected_edge<T>& edge)
{
    out << "(" << edge.from() << ", " << edge.to() << ")\n";
    return out;
}
*/