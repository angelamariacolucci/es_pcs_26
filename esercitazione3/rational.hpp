#pragma once

#include <concepts>
#include <iostream>

template <typename I> requires std::integral<I>
class rational {
	I num_;
	I den_;

	//semplificazione
	void semplificazione()
    {
        if (den_ == I{0}) //non semplifico 
		{
            return;
		}
        if (den_ < I{0}) { //porto il segno negativo al numeratore
            num_ = -num_;
            den_ = -den_;
        }

        if (num_ == I{0}) {
            den_ = I{1};
            return;
        }

        // MCD
        I a;
		if (num_ < I{0}) {
			a = -num_;
		}
		else {
			a = num_;
		}

		I b = den_;

		while (b != I{0}) {
			I temp = b;
			b = a % b;
			a = temp;
		}

		num_ /= a;
		den_ /= a;
    }


public:
	// default constructor
	rational()
		: num_(I{0}), den_(I{1})
	{}

	// user-defined constructor
	rational(const I& num, const I& den)
		: num_(num), den_(den)
	{
		semplificazione();
	}
	
	rational(const I& num)
		: num_(num), den_(I{1})
	{
		semplificazione();
	}

	I num() const {		//restituisce copia
		return num_; 
	}
    I den() const { 
		return den_; 
	}

	// CASI PARTICOLARI
	bool is_nan() const {
		if (num_ == I{0} && den_ == I{0})
			return true;
		return false;
	}

	bool is_inf() const {
		if (num_ != I{0} && den_ == I{0})
			return true;
		return false;
	}

	bool is_ok() const {
		if (den_ != I{0})
			return true;
		return false;
	}

	// OPERATORS -> ho 3 casi: NanN, Inf,frazione. Devo gestire:
	// NaN_NaN, Nan_Inf, NaN_frazione, Inf_Inf, Inf_frazione, frazione_frazione

	rational& operator+=(const rational& other) //con questo operatore sto modficando primo addendo
    {
        // NaN + frazione o Inf o NaN = NaN (oppure frazione o Inf o NaN + NaN = NaN)
        if (is_nan() || other.is_nan()) {
            num_ = I{0}; // modifico primo addendo in modo che sia NaN
			den_ = I{0};
            return *this;
        }
        // Inf + Inf = Inf; Inf + (-Inf) = NaN
        if (is_inf() && other.is_inf()) {
            if ((num_ > I{0}) == (other.num_ > I{0})) {
                return *this;	// stesso segno = Inf
			} 
            num_ = I{0}; // sto modificando primo addendo in modo che sia NaN
			den_ = I{0}; // segni opposti = NaN
            return *this;
            
        }
        // Inf + frazione = Inf (posso restituire primo addendo)
        if (is_inf())
            return *this;
        // frazione + Inf = Inf (devo modificare primo addendo)
        if (other.is_inf()) {
            num_ = other.num_; 
			den_ = I{0};
            return *this;
        }

		// caso standard: frazione + frazione = frazione
        // a/b + c/d = (a*d + c*b) / (b*d)
        num_ = num_ * other.den_ + other.num_ * den_;
        den_ = den_ * other.den_;
        semplificazione();	
        return *this;
    }

    rational operator+(const rational& other) const //lascio intatti gli addendi e creo un nuovo oggetto
    {
        rational ret = *this; //creo una copia di primo addendo
        ret += other; //applica operatore += sulla copia
        return ret;	// restituiamo il nuovo oggetto
    }

    rational& operator-=(const rational& other)
    {
        rational neg = other; //creo una copia del secondo addendo
        neg.num_ = -neg.num_;  // nega il numeratore
        return *this += neg; // sommo l'opposto per non implementare tutto di nuovo
    }

    rational operator-(const rational& other) const
    {
        rational ret = *this;
        ret -= other;
        return ret;
    }

    rational& operator*=(const rational& other)
    {
        // NaN * frazione o Inf o NaN = NaN (oppure frazione o Inf o NaN + NaN = NaN)
        if (is_nan() || other.is_nan()) {
            num_ = I{0}; 
			den_ = I{0};
            return *this;
        }
        // Inf * 0 = NaN; Inf * !0 = Inf
        if (is_inf() || other.is_inf()) {
            bool this_zero  = (is_ok()  && num_ == I{0});
            bool other_zero = (other.is_ok() && other.num_ == I{0});
            if (this_zero || other_zero) {
                num_ = I{0}; 
				den_ = I{0}; // 0 * Inf = NaN
            } 
			else {
            	bool pos = (num_ < I{0}) == (other.num_ < I{0});
				if (pos) {
					num_ = I{1};   // +Inf
				} 
				else {
					num_ = I{-1};  // -Inf
				}
				den_ = I{0};
			}
            return *this;
        }

        // (a/b) * (c/d) = (a*c) / (b*d)
        num_ *= other.num_;
        den_ *= other.den_;
        semplificazione();
        return *this;
    }

    rational operator*(const rational& other) const
    {
        rational ret = *this;
        ret *= other;
        return ret;
    }

	rational& operator/=(const rational& other) 
	{
		if (is_nan() || other.is_nan()) { 
			num_ = I{0}; 
			den_ = I{0};
			return *this;
		}
		rational reciproco = other;	// devo prima fare una copia poichè other è const
		reciproco.num_ = other.den_;
		reciproco.den_ = other.num_;
		return *this *= reciproco;
	}

    rational operator/(const rational& other) const
    {
        rational ret = *this;
        ret /= other;
        return ret;
    }
};

template<typename I> requires std::integral<I>
std::ostream& 
operator<<(std::ostream& os, const rational<I>& r)
{
    if (r.is_nan()) {
        os << "NaN";
    } 
	else if (r.is_inf()) {
		if (r.num() > I{0}) {
    		os << "+Inf";
		}
		else {
			os << "-Inf";
		}
    } 
	else if (r.den() == I{1}) {
        os << r.num();
    } 
	else {
        os << r.num() << "/" << r.den();
    }
    return os;
}



