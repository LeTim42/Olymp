#ifndef SEARCH_HPP
#define SEARCH_HPP
#include "main.hpp"

// Some search functions
namespace search {
    // returns first x in [l; r) where f(x) is true (or r if f(x) is false in [l; r))
    template<class T>
    T binary(T l, T r, const function<bl(T)>& f) {
        while (l < r) {
            T x = (l+r)>>1;
            if (f(x)) r = x;
            else l = x+1;
        }
        re l;
    }

    // returns minimal x with precision eps in [l; r] where f(x) is true
    template<class T>
    T binary_real(T l, T r, const function<bl(T)>& f, T eps = 1e-8, int count = 100) {
        for (int i = 0; i < count && r-l > eps; ++i) {
            T x = (l+r)/2;
            if (f(x)) r = x;
            else l = x;
        }
        re r;
    }

    // returns first x in [l; r) where f(x) is true (or r if f(x) is false in [l; r))
    template<class T>
    T exponential(T l, T r, const function<bl(T)>& f) {
        T x = l, step = 1;
        while (l < r) {
            if (f(x)) re binary<T>(x-(step>>1),x,f);
            x += step;
            step <<= 1;
        }
        re binary<T>(x-(step>>1),r,f);
    }

    // returns x in [l; r] for which value of unimodal funciton f(x) is maximal (or minimal if cmp = less<T>())
    template<class T, class R>
    T ternary(T l, T r, const function<R(T)>& f, const function<bl(R,R)>& cmp = greater<R>()) {
        while (r - l >= 3) {
            T x1 = l+(r-l)/3;
            T x2 = r-(r-l)/3;
            if (cmp(f(x1),f(x2))) r = x2;
            else l = x1;
        }
        T x = l;
        R y = f(l);
        rep(x2,l+1,r)
            if (R y2 = f(x2); cmp(y2,y))
                x = x2, y = y2;
        re x;
    }

    // returns x with precision eps in [l; r] for which value of unimodal funciton f(x) is maximal (or minimal if cmp = less<T>())
    template<class T, class R>
    T ternary_real(T l, T r, const function<R(T)>& f, const function<bl(R,R)>& cmp = greater<R>(), T eps = 1e-8, int count = 100) {
        for (int i = 0; i < count && r-l > eps; ++i) {
            T x1 = l+(r-l)/3;
            T x2 = r-(r-l)/3;
            if (cmp(f(x1),f(x2))) r = x2;
            else l = x1;
        }
        re r;
    }
};
#endif