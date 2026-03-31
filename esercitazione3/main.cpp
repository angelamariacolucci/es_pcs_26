#include <iostream>
#include "rational.hpp"
using namespace std;
int main(void)
{
    rational<int> a(1, 2);
    rational<int> b(1, 3);
    rational<int> c(3, 6);   // deve stampare 1/2
    rational<int> zero(0,1);      
    rational<int> neg(3, -4); // segno al numeratore => -3/4

    cout << "a = " << a << "\n";   // 1/2
    cout << "b = " << b << "\n";   // 1/3
    cout << "c(3,6) = " << c << "\n";   // 1/2  (semplificato)
    cout << "zero = " << zero << "\n";   // 0
    cout << "neg = " << neg << "\n";   // -3/4

    
    cout << "a + b = " << (a + b) << "\n";   // 5/6
    cout << "a - b = " << (a - b) << "\n";   // 1/6
    cout << "a + neg = " << (a + neg) << "\n"; // -1/4

    cout << "a * b = " << (a * b) << "\n";   // 1/6
    cout << "a / b = " << (a / b) << "\n";   // 3/2

    rational<int> x(1, 4);
    x += rational<int>(1, 4);
    cout << "1/4 += 1/4 => " << x << "\n"; // 1/2
    x *= rational<int>(2, 1);
    cout << "*= 2 => " << x << "\n";   // 1
    x -= rational<int>(3, 1);
    cout << "-= 3 => " << x << "\n";   // -2
    x /= rational<int>(4, 1);
    cout << "/= 4 => " << x << "\n";   // -1/2

    rational<int> inf_pos(1, 0);   // +Inf
    rational<int> inf_neg(-1, 0);  // -Inf
    rational<int> nan(0, 0);       // NaN

    cout << "inf_pos = " << inf_pos << "\n";  // +Inf
    cout << "inf_neg = " << inf_neg << "\n";  // -Inf
    cout << "nan = " << nan << "\n";  // NaN

    cout << "a + inf_pos  = " << (a + inf_pos) << "\n"; // +Inf
    cout << "inf_pos + inf_pos = " << (inf_pos + inf_pos) << "\n"; // +Inf
    cout << "inf_pos + inf_neg = " << (inf_pos + inf_neg) << "\n"; // NaN
    cout << "a + nan = " << (a + nan) << "\n"; // NaN
    cout << "inf_pos * zero = " << (inf_pos * zero)  << "\n"; // NaN
    cout << "inf_pos * a = " << (inf_pos * a)   << "\n"; // +Inf
    cout << "a / zero = " << (a / zero) << "\n"; // +Inf

    return 0;
}