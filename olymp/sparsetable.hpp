#ifndef SPARSETABLE_HPP
#define SPARSETABLE_HPP
#include "main.hpp"

template<class T = int>
class SparseTable {
    V<V<T>> t;
    function<T(const T&, const T&)> f;

public:
    SparseTable(const V<T>& a, const function<T(const T&, const T&)>& f = fmin<T>) : f(f) {
        int n = sz(a), m = n ? lbit(n) : 0;
        t = V<V<T>>(m+1);
        t[0] = a;
        f0r(i,m) {
            t[i+1] = V<T>(n-(2<<i)+1);
            f0r(j,sz(t[i+1]))
                t[i+1][j] = f(t[i][j], t[i][j+(1<<i)]);
        }
    }
    
    T get(int l, int r) { //[l; r)
        int i = lbit(r-l);
        re f(t[i][l], t[i][r-(1<<i)]);
    }
};
#endif