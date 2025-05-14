#ifndef NUMS_HPP
#define NUMS_HPP
#include "main.hpp"
#include "bitset.hpp"

// Work with numbers and number theory algorithms
namespace nums {
    // returns rounded down square root of x
    template<class T = ll>
    T sqrti(const T& x) {
        T s = sqrt(x);
        while (s * s < x) ++s;
        while (s * s > x) --s;
        re s;
    }

    // extended euclidean algorithm
    template<class T = int>
    T gcdex(T a, T b, T& x, T& y) {
        T _a = a, _b = b;
        x = 1; y = 0;
        while (b) {
            T q = a / b;
            a -= q * b;
            x -= q * y;
            swap(a,b);
            swap(x,y);
        }
        y = _b ? (a - x * _a) / _b : 0;
        return a;
    }

    vi primes;
    int min_prime = 2;

    void precalc_primes(int max) {
        primes.clear();
        Bitset sieve(++max);
        int i;
        for (i = 2; i*i < max; ++i) {
            if (!sieve.get(i)) {
                primes.pb(i);
                for (int j = i*i; j < max; ++j)
                    sieve.set(i);
            }
        }
        for (; i < max; ++i)
            if (!sieve.get(i))
                primes.pb(i);
        min_prime = max;
    }

    template<class T = int>
    V<P<T,int>> prime_factorization(T x) {
        V<P<T,int>> res;
        auto check = [&](const T& d) {
            if (x % d == 0) {
                res.pb(d,0);
                do {
                    ++res.back().se;
                    x /= d;
                } while (x % d == 0);
            }
        };
        for (int d : primes) {
            if (d*d > x) {
                if (x != 1) res.pb(x,1);
                re res;
            }
            check(d);
        }
        for (T d = min_prime; d*d <= x; ++d)
            check(d);
        if (x != 1) res.pb(x,1);
        re res;
    }

    // returns s, where x = d*s^2 and d is not a square (and s is max)
    template<class T = int>
    T factorize_max_square(T x) {
        T s = 1;
        for (T d = 2, d2 = 4; d2*d <= x; d2 += (d++)*2+1) {
            while (x % d2 == 0) {
                s *= d;
                x /= d2;
            }
            if (x % d == 0)
                x /= d;
        }
        if (T r = sqrti(x); r*r == x)
            s *= r;
        re s;
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