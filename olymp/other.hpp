#ifndef OTHER_HPP
#define OTHER_HPP
#include "main.hpp"

namespace other {
    // returns rounded down square root of x
    ll sqrti(ll x) {
        ll s = sqrt(x);
        while (s * s < x) ++s;
        while (s * s > x) --s;
        re s;
    }

    // extended euclidean algorithm
    int gcdex(int a, int b, int& x, int& y) {
        int _a = a, _b = b;
        x = 1; y = 0;
        while (b) {
            int q = a / b;
            a -= q * b;
            x -= q * y;
            swap(a,b);
            swap(x,y);
        }
        y = _b ? (a - x * _a) / _b : 0;
        return a;
    }

    // returns vector of pairs {a[i], i}
    template<class T>
    V<P<T,int>> idxv(const V<T>& a) {
        V<P<T,int>> res(sz(a));
        f0r(i,sz(a))
            res[i] = mp(a[i],i);
        re res;
    }

    // sorts and merges intersecting segments
    template<class T = int>
    void merge_segments(V<P<T,T>>& a) {
        sort(all(a));
        int i = 0;
        f0r1(j,sz(a))
            if (a[i].se < a[j].fi)
                a[++i] = a[j];
            else
                amax(a[i].se, a[j].se);
        a.resize(i+1);
    }

    using base = complex<db>;

    void fft(V<base>& a, bl inv) {
        int n = sz(a);
        for (int i = 1, j = 0; i < n; ++i) {
            int bit = n >> 1;
            for (; j & bit; bit >>= 1)
                j ^= bit;
            j ^= bit;
            if (i < j)
                swap(a[i], a[j]);
        }
        for (int len = 2; len <= n; len <<= 1) {
            db ang = 2 * PI / len * (inv ? -1 : 1);
            base wlen(cos(ang), sin(ang));
            for (int i = 0; i < n; i += len) {
                base w(1);
                f0r(j,len/2) {
                    base u = a[i+j], v = a[i+j+len/2] * w;
                    a[i+j] = u + v;
                    a[i+j+len/2] = u - v;
                    w *= wlen;
                }
            }
        }
        if (inv)
            for (base& x : a)
                x /= n;
    }

    template<class R, class T>
    V<R> mul_fft(const V<T>& a, const V<T>& b) {
        V<base> fa(all(a)), fb(all(b));
        int n = 1;
        while (n < sz(fa) + sz(fb))
            n <<= 1;
        fa.resize(n), fb.resize(n);
        fft(fa, 0), fft(fb, 0);
        f0r(i,n)
            fa[i] *= fb[i];
        fft(fa, 1);
        V<R> res(n);
        f0r(i,n)
            res[i] = round(fa[i].real());
        re res;
    }
}
#endif