#ifndef RND_HPP
#define RND_HPP
#include "main.hpp"
#include "graph.hpp"

// Generation of random stuff
namespace rnd {
    mt19937 engine;
    
    void seed() {
        engine.seed(now());
    }
    
    void seed(int val) {
        engine.seed(val);
    }
    
    template<class T>
    void shuffle(V<T>& a) {
        shuffle(all(a), engine);
    }

    bl b() {
        re uid<int>(0,1)(engine);
    }
    
    template<class T = int>
    T i(T l, T r) { //[l; r]
        re uid<T>(l,r)(engine);
    }
    
    template<class T = db>
    T d(T l, T r) { //[l; r]
        re urd<T>(l,r)(engine);
    }
    
    template<class T = int>
    P<T,T> p(T l, T r, bl fi_less_se = 0, bl fi_not_se = 0) { //[l; r]
        uid<T> rangeL(l,r);
        uid<T> rangeR(l,r-fi_not_se);
        P<T,T> p(rangeL(engine), rangeR(engine));
        p.se += fi_not_se && p.se >= p.fi;
        if (fi_less_se && p.fi > p.se) swap(p.fi, p.se);
        re p;
    }

    str s(int n, ch l = 'a', ch r = 'z') { //[l; r]
        uid<ch> range(l,r);
        str s(n,0);
        for (ch& c : s) c = range(engine);
        re s;
    }

    str s(int n, const str& chars) {
        uid<int> range(0,sz(chars)-1);
        str s(n,0);
        for (ch& c : s) c = chars[range(engine)];
        re s;
    }

    template<class T = int>
    V<T> v(int n, T l, T r, bl distinct = 0) { //[l; r]
        V<T> a(n);
        set<T> s;
        uid<T> range(l,r);
        for (T& x : a) {
            do x = range(engine);
            while (distinct && s.find(x) != s.en);
            if (distinct) s.insert(x);
        }
        re a;
    }
    
    template<class T = int>
    V<P<T,T>> vp(int n, T l, T r, bl fi_less_se = 0, bl fi_not_se = 0, bl distinct = 0) { //[l; r]
        V<P<T,T>> a(n);
        set<P<T,T>> s;
        uid<T> rangeL(l,r);
        uid<T> rangeR(l,r-fi_not_se);
        for (P<T,T>& p : a) {
            do {
                p = mp(rangeL(engine), rangeR(engine));
                p.se += fi_not_se && p.se >= p.fi;
                if (fi_less_se && p.fi > p.se) swap(p.fi, p.se);
            } while (distinct && s.find(p) != s.en);
            if (distinct) s.insert(p);
        }
        re a;
    }
    
    template<class T = int>
    V<T> perm(int n, int first = 1) {
        V<T> a(n);
        iota(all(a),first);
        shuffle(a);
        re a;
    }

    vvi graph(int n, int m, bl orient = 0) {
        vvi g(n);
        for (pii p : vp(m, 0, n-1, !orient, 1, 1)) {
            g[p.fi].pb(p.se);
            if (!orient) g[p.se].pb(p.fi);
        }
        re g;
    }
    
    vvi tree(int n) {
        vi p = v(n-2,0,n-1);
        vi c(n);
        for (int i : p) ++c[i];
        vi a(n);
        iota(all(a), 0);
        auto cmp = [&](int a, int b) {
            if (c[a] != c[b])
                re c[a] < c[b];
            re a < b;
        };
        set<int,decltype(cmp)> s(all(a), cmp);
        vvi g(n);
        f0r(i,n-2) {
            auto it = s.be;
            int u = *it, v = p[i];
            s.erase(it);
            s.erase(v);
            --c[v];
            s.insert(v);
            g[u].pb(v);
            g[v].pb(u);
        }
        int u = *s.be, v = *--s.en;
        g[u].pb(v);
        g[v].pb(u);
        re g;
    }

    vvi graph_conn(int n, int m) {
        vvi g = tree(n);
        vii e = graph::edges(g,0,0);
        set<pii> s(all(e));
        uid<int> rangeL(0,n-1);
        uid<int> rangeR(0,n-2);
        for (m -= n-1; m > 0; --m) {
            pii p;
            do {
                p = mp(rangeL(engine), rangeR(engine));
                p.se += p.se >= p.fi;
                if (p.fi > p.se) swap(p.fi, p.se);
            } while (s.find(p) != s.en);
            s.insert(p);
            g[p.fi].pb(p.se);
            g[p.se].pb(p.fi);
        }
        re g;
    }
    
    // returns graph with random weights from graph g
    template<class T = int>
    V<V<P<int,T>>> w(vvi g, T l, T r, bl orient = 0) { //[l; r]
        int n = sz(g);
        V<V<P<int,T>>> gw(n);
        f0r(i,n) {
            gw[i] = V<P<int,T>>(sz(g[i]));
            if (!orient) sort(all(g[i]));
        }
        vi a(n);
        uid<T> range(l,r);
        f0r(u,n) {
            rep(i,a[u],sz(g[u])) {
                int v = g[u][i];
                T w = range(engine);
                gw[u][i] = mp(v,w);
                if (!orient) gw[v][a[v]++] = mp(u,w);
            }
            if (!orient) shuffle(g[u]);
        }
        re gw;
    }
}
#endif