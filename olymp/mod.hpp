#ifndef MOD_HPP
#define MOD_HPP
#include "main.hpp"
#include "nums.hpp"

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
        if (nums::gcdex(a,m,x,y) != 1)
            re -1;
        re modll(x,m);
    }

    // a ^ x = b (mod m), a and m are coprime numbers
    vi log(int a, int b, int m = MOD) {
        int m2 = m;
        m /= gcd(a,m);
        int n = nums::sqrti(m) + 1;
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

    int generator(int m) {
        int phi = m-1;
        vii fact = nums::prime_factorization(phi);
        rep(g,2,m+1) {
            bl ok = 1;
            for (const pii& p : fact)
                if (pow(g, phi / p.fi, m) == 1)
                    brk(ok = 0)
            if (ok) re g;
        }
        re -1;
    }

    // x ^ k = a (mod m), m is a prime number
    vi root(int a, int k, int m = MOD, int g = -1) {
        if (g == -1) g = generator(m);
        int phi = m-1, sq = nums::sqrti(m) + 1;
        vii dec(sq);
        f0r(i,sq)
            dec[i] = {pow(g, mul((i+1)*sq, k, phi), m), i+1};
        sort(all(dec));
        int any_ans = -1;
        f0r(i,sq) {
            int my = mul(pow(g, mul(i, k, phi), m), a, m);
            auto it = lower_bound(all(dec), mp(my, 0));
            if (it != dec.en && it->fi == my)
                brk(any_ans = it->se * sq - i)
        }
        DEB(a,m,any_ans)
        if (any_ans == -1) re {0};
        int delta = phi / gcd(k, phi);
        vi ans;
        for (int cur = any_ans % delta; cur < phi; cur += delta)
            ans.pb(pow(g, cur, m));
        sort(all(ans));
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
    const int fft_root = 15311432;
    const int fft_root_1 = 469870224; // rev(root, fft_mod)
    const int fft_root_pw = 1 << 23;

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
            int wlen = inv ? fft_root_1 : fft_root;
            for (int i = len; i < fft_root_pw; i <<= 1)
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