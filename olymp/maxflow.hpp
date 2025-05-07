#ifndef MAXFLOW_HPP
#define MAXFLOW_HPP
#include "main.hpp"

namespace maxflow {
    // O(n * m^2)
    template<class T = int>
    T edmonds_karp(V<V<P<T,T>>>& cf, int s, int t, T inf = iINF) {
        int n = sz(cf);
        vvi g(n);
        f0r(i,n) f0r(j,n)
            if (cf[i][j].fi > cf[i][j].se)
                g[i].pb(j);
        T res{};
        vi was(n,-1), p(n,-1);
        queue<int> q;
        for (int i = 0; ; ++i) {
            was[s] = i;
            q.push(s);
            while (sz(q)) {
                int u = q.fr; q.pop();
                for (int v : g[u]) {
                    if (was[v] != i && cf[u][v].fi > cf[u][v].se) {
                        p[v] = u;
                        was[v] = i;
                        q.push(v);
                    }
                }
            }
            if (was[t] != i) break;
            T augflow = inf;
            for (int u = t; u != s; u = p[u])
                amin(augflow, cf[p[u]][u].fi - cf[p[u]][u].se);
            for (int u = t; u != s; u = p[u]) {
                cf[p[u]][u].se += augflow;
                cf[u][p[u]].se -= augflow;
                if (cf[u][p[u]].fi > cf[u][p[u]].se)
                    g[u].pb(p[u]);
            }
            res += augflow;
        }
        re res;
    }

    // O(n^2 * m)
    template<class T = int>
    T dinic(V<V<P<T,T>>>& cf, int s, int t, T inf = iINF) {
        int n = sz(cf);
        vvi g(n);
        f0r(i,n) f0r(j,n)
            if (cf[i][j].fi > cf[i][j].se)
                g[i].pb(j);
        T res{};
        queue<int> q;
        vi d(n), id(n);
        lambda(T, dfs, int u, T flow) {
            if (!flow) re {};
            if (u == t) re flow;
            for (; id[u] < sz(g[u]); ++id[u]) {
                int v = g[u][id[u]];
                if (d[v] != d[u] + 1) continue;
                if (T pushed = dfs(v, min(flow, cf[u][v].fi - cf[u][v].se))) {
                    cf[u][v].se += pushed;
                    cf[v][u].se -= pushed;
                    if (cf[v][u].fi > cf[v][u].se)
                        g[v].pb(u);
                    re pushed;
                }
            }
            re {};
        };
        ever {
            fill(all(d), -1);
            d[s] = 0;
            q.push(s);
            while (sz(q)) {
                int u = q.fr; q.pop();
                for (int v : g[u]) {
                    if (d[v] == -1 && cf[u][v].fi > cf[u][v].se) {
                        d[v] = d[u] + 1;
                        q.push(v);
                    }
                }
            }
            if (d[t] == -1) break;
            fill(all(id), 0);
            while (T pushed = dfs(s,inf))
                res += pushed;
        }
        re res;
    }

    // O(n*m + n^2*sqrt(m))
    template<class T = int>
    T push_relabel(V<V<P<T,T>>>& cf, int s, int t) {
        int n = sz(cf);
        V<T> e(n);
        vi h(n);
        h[s] = n-1;
        f0r(i,n) {
            cf[s][i].se = cf[s][i].fi;
            cf[i][s].se = -cf[s][i].se;
            e[i] = cf[s][i].fi;
        }
        vi maxh(n);
        int cnt = 0;
        ever {
            if (!cnt)
                f0r(i,n)
                    if (i != s && i != t && e[i] > T()) {
                        if (cnt && h[i] > h[maxh[0]])
                            cnt = 0;
                        if (!cnt || h[i] == h[maxh[0]])
                            maxh[cnt++] = i;
                    }
            if (!cnt) break;
            while (cnt) {
                int i = maxh[cnt-1];
                bl pushed = 0;
                f0r(j,n) {
                    if (cf[i][j].fi > cf[i][j].se && h[i] == h[j] + 1) {
                        pushed = 1;
                        T addflow = min(cf[i][j].fi - cf[i][j].se, e[i]);
                        cf[i][j].se += addflow, cf[j][i].se -= addflow;
                        e[i] -= addflow, e[j] += addflow;
                        if (!e[i]) brk(--cnt)
                    }
                }
                if (!pushed) {
                    h[i] = iINF;
                    f0r(j,n)
                        if (cf[i][j].fi > cf[i][j].se)
                            amin(h[i], h[j] + 1);
                    if (h[i] > h[maxh[0]])
                        brk(cnt = 0)
                }
            }
        }
        re e[t];
    }
};
#endif