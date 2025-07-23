#ifndef POLYNOMIAL_HPP
#define POLYNOMIAL_HPP
#include "main.hpp"

namespace polynomial {
    const db EPS = 1e-8;

    template<class T>
    V<T> solve2(T a, T b) {
        a /= 2;
        T D = a*a-b;
        if (abs(D) < EPS)
            re {-a,-a};
        if (D < T())
            re {};
        T d = sqrt(D);
        re {-a-d, -a+d};
    }

    template<class T>
    V<T> solve3(T a, T b, T c) {
        T p = (-a*a+b*3)/9;
        T q = (a*a*a*2-a*b*9+c*27)/54;
        T p3 = p*p*p;
        T D = q*q+p3;
        V<T> ans;
        if (abs(D) < EPS) {
            T u = cbrt(-q);
            ans = {u*2, -u, -u};
        } else if (D < T()) {
            T phi = acos(-q/sqrt(-p3))/3;
            T t = sqrt(-p)*2;
            ans = {t*cos(phi), -t*cos(phi+PI/3), -t*cos(phi-PI/3)};
        } else {
            T d = sqrt(D);
            T u = cbrt(d-q);
            T v = -cbrt(d+q);
            ans = {u+v};
        } 
        for (T& i : ans)
            i -= a/3;
        re ans;
    }

    template<class T>
    V<T> solve4(T a, T b, T c, T d) {
        T p = (-a*a*3+b*8)/8;
        T q = (a*a*a-a*b*4+c*8)/8;
        T r = (-a*a*a*a*3+a*a*b*16-a*c*64+d*256)/256;
        V<T> ans;
        if (abs(r) < EPS) {
            ans = solve3<T>(T(),p,q);
            ans.pb(T());
        } else {
            ans = solve3<T>(-p/2, -r, (r*p*4-q*q)/8);
            T z = ans[0];
            T u = z*z-r;
            T v = z*2-p;
            if (abs(u) < EPS) u = T();
            else if (u > T()) u = sqrt(u);
            else re {};
            if (abs(v) < EPS) v = T();
            else if (v > T()) v = sqrt(v);
            else re {};
            if (q < T()) v = -v;
            ans = solve2<T>(v, z-u);
            V<T> ans2 = solve2<T>(-v, z+u);
            ans.insert(ans.en, all(ans2));
        }
        for (T& i : ans)
            i -= a/4;
        re ans;
    }

    template<class T>
    V<T> solve2(T a, T b, T c) {
        re solve2<T>(b/a, c/a);
    }

    template<class T>
    V<T> solve3(T a, T b, T c, T d) {
        re solve3<T>(b/a, c/a, d/a);
    }

    template<class T>
    V<T> solve4(T a, T b, T c, T d, T e) {
        re solve4<T>(b/a, c/a, d/a, e/a);
    }
}
#endif