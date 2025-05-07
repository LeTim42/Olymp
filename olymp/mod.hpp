#ifndef MOD_HPP
#define MOD_HPP
#include "main.hpp"
#include "other.hpp"

// Modular arithmetic
namespace mod {
    int MOD = 1000000007;

    int add(int a, int b, int m = MOD) {
        re (ll(a) + b) % m;
    }

    int sub(int a, int b, int m = MOD) {
        re ((ll(a) - b) % m + ll(m)) % m;
    }

    int mul(int a, int b, int m = MOD) {
        re (ll(a) * b) % m;
    }

    int pow(int a, int n, int m = MOD) {
        int x = 1;
        for (; n; n >>= 1) {
            if (n & 1)
                x = mul(x,a,m);
            a = mul(a,a,m);
        }
        re x;
    }

    // Requirements: a % b == 0, m is a prime number
    int idiv(int a, int b, int m = MOD) {
        re mul(a,pow(b,m-2,m),m);
    }

    int modll(ll a, int m = MOD) {
        re (a % m + m) % m;
    }

    int rev(int a, int m = MOD) {
        int x, y;
        if (other::gcdex(a,m,x,y) != 1)
            re -1;
        re modll(x,m);
    }

    vi log(int a, int b, int m = MOD) {
        int m2 = m;
        m /= __gcd(a,m);
        int n = other::sqrti(m) + 1;
        int an = pow(a,n,m);
        int x = an;
        multimap<int,int> vals;
        f0r1(i,n+1) {
            vals.insert(mp(x,i));
            x = mul(x,an,m);
        }
        x = b;
        vi ans;
        f0r(i,n+1) {
            auto r = vals.equal_range(x);
            for (auto it = r.fi; it != r.se; ++it) {
                int x = (*it).se * n - i;
                if (x >= m) continue;
                if (pow(a,x,m2) == b)
                    ans.pb(x);
            }
            x = mul(x,a,m);
        }
        sort(all(ans));
        unq(ans);
        re ans;
    }

    vvi mul(const vvi& a, const vvi& b, int m = MOD) {
        int n = sz(a), s = sz(b[0]), l = sz(a[0]);
        assert(l == sz(b));
        vvi c(n, vi(s));
        f0r(i,n)
            f0r(j,s)
                f0r(k,l)
                    c[i][j] = add(c[i][j], mul(a[i][k], b[k][j], m), m);
        re c;
    }

    vvi pow(vvi a, int n, int m = MOD) {
        int s = sz(a);
        assert(s == sz(a[0]));
        vvi x(s, vi(s));
        f0r(i,s) x[i][i] = 1;
        for (; n; n >>= 1) {
            if (n & 1)
                x = mul(x,a,m);
            a = mul(a,a,m);
        }
        re x;
    }

    const int fft_mod = 998244353;
    const int root = 15311432;
    const int root_1 = 469870224; // rev(root, fft_mod)
    const int root_pw = 1 << 23;

    void fft(vi& a, bl inv) {
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
            int wlen = inv ? root_1 : root;
            for (int i = len; i < root_pw; i <<= 1)
                wlen = mul(wlen, wlen, fft_mod);
            for (int i = 0; i < n; i += len) {
                int w = 1;
                f0r(j,len/2) {
                    int u = a[i+j], v = mul(a[i+j+len/2], w, fft_mod);
                    a[i+j] = add(u, v, fft_mod);
                    a[i+j+len/2] = sub(u, v, fft_mod);
                    w = mul(w, wlen, fft_mod);
                }
            }
        }
        if (inv) {
            int n_1 = rev(n, fft_mod);
            for (int& x : a)
                x = mul(x, n_1, fft_mod);
        }
    }

    vi mul_fft(vi a, vi b) {
        int m = 1;
        while (m < sz(a) + sz(b))
            m <<= 1;
        m <<= 1;
        a.resize(m), b.resize(m);
        fft(a, 0), fft(b, 0);
        f0r(i,m)
            a[i] *= b[i];
        fft(a, 1);
        re a;
    }

    vi pow_fft(vi a, int n) {
        int m = 1;
        while (m < sz(a) * n)
            m <<= 1;
        a.resize(m);
        fft(a, 0);
        for (int& i : a)
            i = pow(i, n, fft_mod);
        fft(a, 1);
        re a;
    }
}
#endif