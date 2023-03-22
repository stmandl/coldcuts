/*
This problem was asked by Palantir.

The ancient Egyptians used to express fractions as a sum of several terms where each numerator is one.
For example, 4 / 13 can be represented as 1 / 4 + 1 / 18 + 1 / 468.

Create an algorithm to turn an ordinary fraction a / b, where a < b, into an Egyptian fraction.
*/

#include <bits/stdc++.h>
using namespace std;


int gcd(int a, int b) {return b==0?a : gcd(b, a%b);}

struct Frac;
ostream& operator<<(ostream& o, const Frac& f);

struct Frac {
    int num;
    int den;
    Frac(int n_, int d_) : num(n_), den(d_) {
        normalize();
    }
    void normalize() {
        int g = gcd(num, den);
        num /= g;
        den /= g;
    }
    Frac operator-(const Frac& o) {        
        return {num * o.den - o.num * den, den * o.den };
    }
    bool isZero() {
        return num == 0;
    }
    bool operator<=(const Frac& o) {

        bool res = num * o.den  <= o.num * den;
        //cerr << *this << " < " << o << " : " << res << endl;
        return res;
    }
};

ostream& operator<<(ostream& o, const Frac& f)  {
    o << to_string(f.num) << " / " << to_string(f.den);
    return o;
}

int main() {
    Frac f{5,121};

    cerr << f << " = " << endl;

    int d = 2;
    while (!f.isZero()) {
        Frac o{1,d++};
        if (o <= f) {
            cerr << o << endl;
            f = f - o;
        }
    }

    return 0;
}

//g++ --std=c++20 1314-egyptian-fractions.cpp 