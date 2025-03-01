#ifndef SEGTREE_HPP
#define SEGTREE_HPP
#include "olymp.hpp"

// Requirements:
// for add(i,x) T = T + T must be defined
// f(T,nil) == f(nil,T) == T
// if T is complicated then T() must has length 1
template<class T = int>
class SegTree {
private:
    int n;
    V<T> t;
    function<T(const T&, const T&)> f;
    T nil;
public:
    SegTree(int n, const function<T(const T&, const T&)>& f = fadd<T>, const T& nil = T()) : n(n), f(f), nil(nil) {
        t = V<T>(n<<1);
    }
    
    void build(const V<T>& a) {
        f0r(i,n) t[i+n] = a[i];
        f0rr(i,n) t[i] = f(t[i<<1], t[i<<1|1]);
    }
    
    void set(int i, const T& x) {
        for (t[i += n] = x; i > 1; i >>= 1)
            t[i>>1] = f(t[i], t[i^1]);
    }
    
    void add(int i, const T& x) {
        set(i, t[i+n] + x);
    }
    
    T get(int l, int r) { //[l; r)
        T resl = nil, resr = nil;
        for (l += n, r += n; l < r; l >>= 1, r >>= 1) {
            if (l&1) resl = f(resl, t[l++]);
            if (r&1) resr = f(t[--r], resr);
        }
        re f(resl,resr);
    }
    
    T get(int i) {
        re t[i+n];
    }
    
    void print(int i = 1, str tab = "") {
        cout << tab << i << ": " << t[i] << '\n';
        if (i < n) {
            if (i) print(i<<1, tab + "  ");
            print(i<<1|1, tab + "  ");
        }
    }
};

// Requirements:
// T = T + D must be defined
// D = D + D must be defined
// T + D() == T
// f(T,nil) == f(nil,T) == T
// if T is complicated then T() must has length 1
template<class T = int, class D = int>
class SegTreeLP {
private:
    int n, h;
    V<T> t;
    V<D> d;
    function<T(const T&, const T&)> f;
    T nil;
    
    void apply(int i, const D& x) {
        t[i] = t[i] + x;
        if (i < n) d[i] = d[i] + x;
    }
    
    void build(int i) {
        while (i > 1) {
            i >>= 1;
            t[i] = f(t[i<<1], t[i<<1|1]) + d[i];
        }
    }
    
    void push(int i) {
        f0rr1(j,h+1) {
            int p = i >> j;
            if (d[p] != D()) {
                apply(p<<1, d[p]);
                apply(p<<1|1, d[p]);
                d[p] = D();
            }
        }
    }
public:
    SegTreeLP(int n, const function<T(const T&, const T&)>& f = fmax<T>, const T& nil = T()) : n(n), f(f), nil(nil) {
        t = V<T>(n<<1);
        h = lbit(n)+1;
        d = V<D>(n);
    }
    
    void build(const V<D>& a) {
        f0r(i,n) t[i+n] = t[i+n] + a[i];
        f0rr(i,n) t[i] = f(t[i<<1], t[i<<1|1]);
    }
    
    void add(int l, int r, const D& x) { //[l; r)
        l += n, r += n;
        int l0 = l, r0 = r;
        for (; l < r; l >>= 1, r >>= 1) {
            if (l&1) apply(l++, x);
            if (r&1) apply(--r, x);
        }
        build(l0);
        build(r0-1);
    }
    
    T get(int l, int r) { //[l; r)
        l += n, r += n;
        push(l);
        push(r-1);
        T resl = nil, resr = nil;
        for (; l < r; l >>= 1, r >>= 1) {
            if (l&1) resl = f(resl, t[l++]);
            if (r&1) resr = f(t[--r], resr);
        }
        re f(resl,resr);
    }
    
    T get(int i) {
        i += n;
        push(i);
        re t[i];
    }
    
    void print(int i = 1, str tab = "") {
        cout << tab << i << ": " << t[i];
        if (i < n) cout << " | " << d[i];
        cout << '\n';
        if (i < n) {
            if (i) print(i<<1, tab + "  ");
            print(i<<1|1, tab + "  ");
        }
    }
};
#endif