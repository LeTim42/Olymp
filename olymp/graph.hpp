#ifndef GRAPH_HPP
#define GRAPH_HPP
#include "main.hpp"
#include "dsu.hpp"

// Work with graphs
namespace graph {
    // returns graph adjacency lists from edges list
    vvi create(int n, const vii& e, bl orient = 0, int first_index = 1) {
        vvi g(n);
        for (pii p : e) {
            g[p.fi-=first_index].pb(p.se-=first_index);
            if (!orient) g[p.se].pb(p.fi);
        }
        re g;
    }

    // returns weighted graph adjacency lists from edges list with weights
    template<class T = int>
    V<V<P<int,T>>> create(int n, const V<P<pii,T>>& e, bl orient = 0, int first_index = 1) {
        V<V<P<int,T>>> g(n);
        for (auto p : e) {
            g[p.fi.fi-=first_index].pb(mp(p.fi.se-=first_index, p.se));
            if (!orient) g[p.fi.se].pb(mp(p.fi.fi, p.se));
        }
        re g;
    }

    // returns edges list from graph adjacency lists
    vii edges(const vvi& g, bl orient = 0, int first_index = 1) {
        int n = sz(g);
        vii res;
        vi a(n);
        f0r(u,n) {
            vi e(all(g[u]));
            if (!orient) sort(all(e));
            rep(i,a[u],sz(e)) {
                int v = e[i];
                a[v] += !orient;
                res.pb(mp(u+first_index,v+first_index));
            }
        }
        re res;
    }

    // returns edges list with weights from weighted graph adjacency lists
    template<class T = int>
    V<P<pii,T>> edges(const V<V<P<int,T>>>& g, bl orient = 0, int first_index = 1) {
        int n = sz(g);
        V<P<pii,T>> res;
        vi a(n);
        f0r(u,n) {
            V<P<int,T>> e(all(g[u]));
            if (!orient) sort(all(e));
            rep(i,a[u],sz(e)) {
                int v = e[i].fi;
                T w = e[i].se;
                a[v] += !orient;
                res.pb(mp(mp(u+first_index,v+first_index),w));
            }
        }
        re res;
    }

    vvi list_to_matrix(const vvi& g) {
        int n = sz(g);
        vvi res(n,vi(n));
        f0r(u,n)
            for (int v : g[u])
                ++res[u][v];
        re res;
    }

    vvi matrix_to_list(const vvi& g) {
        int n = sz(g);
        vvi res(n);
        f0r(u,n) f0r(v,n)
            f0r(i,g[u][v])
                res[u].pb(v);
        re res;
    }

    // Heavy-Light Decomposition
    class HLD {
    public:
        // parent[u] = parent of vertex u
        // depth[u] = depth of vertex u
        // heavy[u] = next vertex after vertex u in heavy path
        // head[u] = head of heavy path in which vertex u is
        // pos[u] = index of vertex u in segment tree
        vi parent, depth, heavy, head, pos;

        HLD(const vvi& g) {
            int n = sz(g);
            parent = vi(n);
            depth = vi(n);
            heavy = vi(n,-1);
            head = vi(n);
            pos = vi(n);
            dfs(g);
            decompose(g);
        }
    private:
        int t = 0;

        int dfs(const vvi& g, int u = 0) {
            int size = 1, max_c_size = 0;
            for (int v : g[u]) if (v != parent[u]) {
                parent[v] = u;
                depth[v] = depth[u] + 1;
                int c_size = dfs(g,v);
                size += c_size;
                if (c_size > max_c_size) {
                    max_c_size = c_size;
                    heavy[u] = v;
                }
            }
            re size;
        }

        void decompose(const vvi& g, int u = 0, int h = 0) {
            head[u] = h;
            pos[u] = t++;
            if (heavy[u] != -1)
                decompose(g,heavy[u],h);
            for (int v : g[u])
                if (v != parent[u] && v != heavy[u])
                    decompose(g,v,v);
        }
    };

    vvi reverse(const vvi& g) {
        int n = sz(g);
        vvi gr(n);
        f0r(i,n)
            for (int j : g[i])
                gr[j].pb(i);
        re gr;
    }

    template<class T = int>
    V<T> dijkstra(const V<V<P<int,T>>>& g, int s, T NIL = iINF) {
        int n = sz(g);
        V<T> d(n, NIL);
        priority_queue<P<T,int>, V<P<T,int>>, greater<>> pq;
        d[s] = 0;
        pq.push(mp(0,s));
        while (sz(pq)) {
            auto p = pq.top();
            pq.pop();
            int u = p.se;
            if (p.fi > d[u]) continue;
            for (auto p : g[u]) {
                int v = p.fi;
                T w = p.se;
                if (d[u] + w < d[v]) {
                    d[v] = d[u] + w;
                    pq.push(mp(d[v],v));
                }
            }
        }
        re d;
    }

    vvi connected_components(const vvi& g, bl orient = 0) {
        int n = sz(g);
        vb was(n);
        vi order;
        vvi gr;
        if (orient) {
            gr = reverse(g);
            order.reserve(n);
            lambda(void, dfs2, int u) {
                was[u] = 1;
                for (int v : g[u])
                    if (!was[v])
                        dfs2(v);
                order.pb(u);
            };
            f0r(i,n)
                if (!was[i])
                    dfs2(i);
            reverse(all(order));
            was.assign(n,0);
        } else {
            gr = g;
            order.resize(n);
            iota(all(order), 0);
        }
        vi component;
        vvi ans;
        lambda(void, dfs, int u) {
            was[u] = 1;
            component.pb(u);
            for (int v : gr[u])
                if (!was[v])
                    dfs(v);
        };
        for (int i : order) if (!was[i]) {
            component.clear();
            dfs(i);
            ans.pb(component);
        }
        re ans;
    }

    P<vvi,vvi> condensation(const vvi& g) {
        int n = sz(g);
        vvi comp = connected_components(g,1);
        vi c(n);
        f0r(i,sz(comp))
            for (int u : comp[i])
                c[u] = i;
        set<pii> s;
        f0r(u,n)
            for (int v : g[u])
                if (c[u] != c[v])
                    s.insert(mp(c[u],c[v]));
        vvi cond(sz(comp));
        for (const pii& p : s)
            cond[p.fi].pb(p.se);
        re mp(comp,cond);
    }

    vi topological_sort(const vvi& g) {
        int n = sz(g);
        vc was(n);
        vi res;
        res.reserve(n);
        lambda(bl, dfs, int u) {
            was[u] = 1;
            for (int v : g[u])
                if (was[v] == 1 || (!was[v] && !dfs(v)))
                    re 0;
            res.pb(u);
            was[u] = 2;
            re 1;
        };
        f0r(i,n)
            if (!was[i] && !dfs(i))
                re {}; // has cycle
        reverse(all(res));
        re res;
    }

    vii bridges(const vvi& g) {
        int n = sz(g);
        vb was(n);
        vi tin(n), fup(n);
        int t = 0;
        vii res;
        lambda(void, dfs, int u, int p) {
            was[u] = 1;
            tin[u] = fup[u] = t++;
            for (int v : g[u]) {
                if (v == p) continue;
                if (was[v])
                    fup[u] = min(fup[u], tin[v]);
                else {
                    dfs(v,u);
                    fup[u] = min(fup[u], fup[v]);
                    if (fup[v] > tin[u])
                        res.pb(mp(u,v));
                }
            }
        };
        f0r(i,n)
            if (!was[i])
                dfs(i,-1);
        re res;
    }

    vi cut_points(const vvi& g) {
        int n = sz(g);
        vb was(n);
        vi tin(n), fup(n);
        int t = 0;
        set<int> res;
        lambda(void, dfs, int u, int p) {
            was[u] = 1;
            tin[u] = fup[u] = t++;
            int c = 0;
            for (int v : g[u]) {
                if (v == p) continue;
                if (was[v])
                    fup[u] = min(fup[u], tin[v]);
                else {
                    dfs(v,u);
                    fup[u] = min(fup[u], fup[v]);
                    if (fup[v] >= tin[u] && p != -1)
                        res.insert(u);
                    ++c;
                }
            }
            if (p == -1 && c > 1)
                res.insert(u);
        };
        f0r(i,n)
            if (!was[i])
                dfs(i,-1);
        re vi(all(res));
    }

    V<P<pii,int>> kruskal(int n, V<P<pii,int>> e, int first_index = 1) {
        sort(all(e), [](const P<pii,int>& lhs, const P<pii,int>& rhs) {
            re lhs.se < rhs.se;
        });
        V<P<pii,int>> res;
        DSU dsu(n);
        for (const auto& p : e)
            if (dsu.merge(p.fi.fi - first_index, p.fi.se - first_index))
                res.pb(p);
        re res;
    }

    V<P<pii,int>> kruskal(const vvii& g) {
        re kruskal(sz(g), edges(g,0,0), 0);
    }

    vi euler_cycle(vvi g, bl orient = 0, bl is_matrix = 1) {
        if (!is_matrix)
            g = list_to_matrix(g);
        int n = sz(g);
        int first = -1, m = 0;
        f0rr(i,n) f0r(j,n)
            if (g[i][j])
                first = i, m += g[i][j];
        if (!m) re {0};
        if (first == -1) re {};
        if (!orient) m /= 2;
        vi last(n);
        stack<int> st;
        st.push(first);
        vi res;
        res.reserve(m+1);
        while (sz(st)) {
            int u = st.top();
            int& v = last[u];
            while (v < n && !g[u][v]) ++v;
            if (v == n) {
                res.pb(u);
                st.pop();
            } else {
                --g[u][v];
                if (!orient)
                    --g[v][u];
                st.push(v);
            }
        }
        reverse(all(res));
        re sz(res) == m+1 ? res : vi{};
    }

    vi euler_path(vvi g, bl orient = 0, bl is_matrix = 1) {
        if (!is_matrix)
            g = list_to_matrix(g);
        int n = sz(g);
        vi deg(n);
        f0r(i,n) f0r(j,n) {
            deg[i] += g[i][j];
            if (orient)
                deg[j] -= g[i][j];
        }
        int v1 = -1, v2 = -1;
        f0r(i,n)
            if (orient) {
                if (deg[i] == 1) {
                    if (v1 == -1) v1 = i;
                    else re {};
                } else if (deg[i] == -1) {
                    if (v2 == -1) v2 = i;
                    else re {};
                } else if (deg[i]) re {};
            } else if (deg[i] & 1) {
                if (v1 == -1) v1 = i;
                else if (v2 == -1) v2 = i;
                else re {};
            }
        if (v1 == -1 || v2 == -1) re {};
        ++g[v2][v1];
        if (!orient)
            ++g[v1][v2];
        vi res = euler_cycle(g,orient);
        f0r1(i,sz(res)) {
            if ((res[i-1] == v2 && res[i] == v1) || (!orient && res[i-1] == v1 && res[i] == v2)) {
                vi res2;
                res2.reserve(sz(res));
                res2.insert(res2.en, res.be+i, res.en);
                res2.insert(res2.en, res.be+1, res.be+i);
                re res2;
            }
        }
        assert(!sz(res));
        re res;
    }
}
#endif