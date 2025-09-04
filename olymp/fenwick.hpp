#ifndef FENWICK_HPP
#define FENWICK_HPP
#include "main.hpp"

template<class T = int>
class FenwickTree {
    int n;
    V<T> t;

    void build(int n) {
        f0rr1(i,n)
            if (int j = i - (i & -i); j > 0)
                t[i] -= t[j];
    }

public:
    FenwickTree(int n, const T& x) : n(n) {
        t.resize(n+1);
        if (x != T()) {
            f0r(i,n)
                t[i+1] = t[i] + x;
            build(n);
        }
    }

    void build(const V<T>& a) {
        psum1(a,t);
        build(sz(a));
    }

    void update(int i, const T& delta) {
        for (++i; i <= n; i += i & -i)
            t[i] += delta;
    }

    T query(int i) const { // [0; i]
        T s = 0;
        for (++i; i > 0; i -= i & -i)
            s += t[i];
        re s;
    }

    int query(int l, int r) const { // [l; r]
        re query(r) - query(l-1);
    }

    // returns first x in [0; n) where query(x) >= r
    int search(const T& r) const {
        T s = 0;
        int x = 0;
        for (int i = lbit(n); i >= 0; --i) {
            if (int y = x + (1 << i); y < n && s + t[y] < r) {
                s += t[y];
                x = y;
            }
        }
        re x;
    }
};
#endif