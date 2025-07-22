#ifndef OTHER_HPP
#define OTHER_HPP
#include "main.hpp"
#include "bitset.hpp"

namespace other {
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
        if (!sz(a)) re;
        sort(all(a));
        int i = 0;
        f0r1(j,sz(a))
            if (a[i].se < a[j].fi)
                a[++i] = a[j];
            else
                amax(a[i].se, a[j].se);
        a.resize(i+1);
    }

    // solves system of linear equations and returns number of solutions
    template<class T = db>
    int gauss(V<V<T>> a, V<T>& ans, const T& EPS = 1e-8) {
        int n = sz(a), m = sz(a[0]) - 1;
        vi where(m,-1);
        for (int col = 0, row = 0; col < m && row < n; ++col) {
            int sel = row;
            rep(i,row,n)
                if (abs(a[i][col]) > abs(a[sel][col]))
                    sel = i;
            if (abs(a[sel][col]) <= EPS)
                continue;
            swap(a[sel], a[row]);
            where[col] = row;
            f0r(i,n) if (i != row) {
                T c = a[i][col] / a[row][col];
                rep(j,col,m+1)
                    a[i][j] -= a[row][j] * c;
            }
            ++row;
        }
        ans.assign(m,T());
        f0r(i,m)
            if (where[i] != -1)
                ans[i] = a[where[i]][m] / a[where[i]][i];
        f0r(i,n) {
            T sum();
            f0r(j,m)
                sum += ans[j] * a[i][j];
            if (abs(sum - a[i][m]) > EPS)
                re 0;
        }
        f0r(i,m)
            if (where[i] == -1)
                re iINF;
        re 1;
    }

    // solves system of linear equations and returns number of solutions
    int gauss(V<Bitset> a, Bitset& ans) {
        int n = sz(a), m = a[0].size() - 1;
        vi where(m,-1);
        for (int col = 0, row = 0; col < m && row < n; ++col) {
            rep(i,row,n)
                if (a[i][col])
                    brk(swap(a[i], a[row]))
            if (!a[row][col])
                continue;
            where[col] = row;
            f0r(i,n)
                if (i != row && a[i][col])
                    a[i] ^= a[row];
            ++row;
        }
        ans = Bitset(m);
        f0r(i,m)
            if (where[i] != -1)
                ans.set(i, a[where[i]][m]);
        f0r(i,n) {
            bl sum = 0;
            f0r(j,m)
                sum ^= ans[j] & a[i][j];
            if (sum ^ a[i][m])
                re 0;
        }
        f0r(i,m)
            if (where[i] == -1)
                re iINF;
        re 1;
    }
}
#endif