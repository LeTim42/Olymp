#include <iostream>
#include <sstream>
#include <cstdio>
#include <vector>
#include <algorithm>
#include <numeric>
#include <set>
#include <map>
#include <queue>
#include <stack>
#include <iomanip>
#include <functional>
#include <chrono>
#include <cmath>
#include <cstring>
#include <cassert>
#include <climits>
#include <ctime>
#include <random>
#ifdef LOCAL
#include <windows.h>
#endif

#define P pair
#define V vector
#define fi first
#define se second
#define be begin()
#define en end()
#define re return
#define pb emplace_back
#define mp make_pair
#define sq(x) ((x)*(x))
#define sqll(x) ((ll)(x)*(x))
#define sz(a) ((int)(a).size())
#define all(a) a.be, a.en
#define lbi(a,x) (lower_bound(all(a),(x)) - a.be)
#define ubi(a,x) (upper_bound(all(a),(x)) - a.be)
#define lbc(a,x,c) (lower_bound(all(a),(x),c) - a.be)
#define ubc(a,x,c) (upper_bound(all(a),(x),c) - a.be)
#define psum(a,b) (partial_sum(all(a), b.be))
#define adif(a,b) (adjacent_difference(all(a), b.be))
#define psum1(a,b) (partial_sum(all(a), b.be+1))
#define adif1(a,b) (adjacent_difference(all(a), b.be+1))
#define unq(a) (a.resize(unique(all(a)) - a.be))
#define erase1(a,x) a.erase(a.find(x))
#define inp(n,a) int n; cin >> n; vi a(n); cin >> a
#define inp2(n,m,a) int n, m; cin >> n >> m; vvi a(n,vi(m)); cin >> a
#define prec(n) fixed << setprecision(n)
#define bcount(a) __builtin_popcount(a)
#define bcountll(a) __builtin_popcountll(a)
#define bit(a,i) (((a)>>(i))&1)
#define lbit(a) (__lg((a)))
#define rbit(a) (lbit((a)&-(a)))
#define uid uniform_int_distribution
#define urd uniform_real_distribution
#define f0r(i,n) for (int i = 0; i < (n); ++i)
#define f0rr(i,n) for (int i = (n)-1; i >= 0; --i)
#define f0rbit(a,i,n) f0r(i,(n)) if (bit((a),i))
#define rep(i,s,n) for (int i = (s); i < (n); ++i)
#define repr(i,s,n) for (int i = (n)-1; i >= (s); --i)
#define ever for(;;)

using namespace std;

typedef long long ll;
typedef unsigned long long ull;
typedef bool bl;
typedef char ch;
typedef double ld;
typedef long double lld;
typedef string str;
typedef P<int,int> pii;
typedef P<ll,ll> pll;
typedef P<ld,ld> pdd;
typedef P<lld,lld> pld;
typedef P<int,ll> pill;
typedef P<ll,int> plli;
typedef P<int,bl> pib;
typedef P<bl,int> pbi;
typedef V<int> vi;
typedef V<ll> vll;
typedef V<bl> vb;
typedef V<ch> vc;
typedef V<ld> vd;
typedef V<lld> vld;
typedef V<str> vs;
typedef V<pii> vii;
typedef V<pll> vpll;
typedef V<pdd> vpdd;
typedef V<pld> vpld;
typedef V<vi> vvi;
typedef V<vll> vvll;
typedef V<vb> vvb;
typedef V<vc> vvc;
typedef V<vii> vvii;

template<class T1, class T2> ostream& operator<<(ostream& out, P<T1,T2>& a) { re out << a.fi << ' ' << a.se; }
template<class T1, class T2> istream& operator>>(istream& in, P<T1,T2>& a) { re in >> a.fi >> a.se; }
template<class T> istream& operator>>(istream& in, V<T>& a) { for (T& x : a) in >> x; re in; }
template<class T> ostream& operator<<(ostream& out, V<T>& a) { for (T& x : a) out << x << ' '; re out; }
ostream& operator<<(ostream& out, vb& a) { for (bl x : a) out << x << ' '; re out; }
template<class T> void print(T& a, char sep = '\n', ostream& out = cout) { for (auto& x : a) out << x << sep; }
template<class T> void print1(T& a, char sep = '\n', ostream& out = cout) { for (auto& x : a) out << x+1 << sep; }

#ifdef LOCAL
str _tab = "";
struct TAB_HELPER {
    TAB_HELPER() { _tab += "  "; }
    ~TAB_HELPER() { _tab = _tab.substr(0,sz(_tab)-2); }
};
#define PARENS ()
#define EXPAND(...) EXPAND4(EXPAND4(EXPAND4(EXPAND4(__VA_ARGS__))))
#define EXPAND4(...) EXPAND3(EXPAND3(EXPAND3(EXPAND3(__VA_ARGS__))))
#define EXPAND3(...) EXPAND2(EXPAND2(EXPAND2(EXPAND2(__VA_ARGS__))))
#define EXPAND2(...) EXPAND1(EXPAND1(EXPAND1(EXPAND1(__VA_ARGS__))))
#define EXPAND1(...) __VA_ARGS__
#define DIN TAB_HELPER _tab_helper;
#define DEB(...) cout << _tab; __VA_OPT__(EXPAND(DEB_HELPER(__VA_ARGS__))) cout << endl;
#define DEB_HELPER(var, ...) cout << ">> " << #var << " = " << var << " "; __VA_OPT__(DEB_HELPER_2 PARENS (__VA_ARGS__))
#define DEB_HELPER_2() DEB_HELPER
#else
#define DEB(...) ;
#define DIN ;
#endif

template<class T = int> T fadd(T a, T b) { re a+b; }
template<class T = int> T fmin(T a, T b) { re min(a,b); }
template<class T = int> T fmax(T a, T b) { re max(a,b); }

const int iINF = 2000000007;
const ll INF = 2000000000000000007;

// returns current time in nanoseconds
uint64_t now() {
    using namespace chrono;
    re duration_cast<nanoseconds>(steady_clock::now().time_since_epoch()).count();
}

// returns vector of pairs {a[i], i}
template<class T>
V<P<T,int>> indv(V<T>& a) {
    V<P<T,int>> res(sz(a));
    f0r(i,sz(a))
        res[i] = mp(a[i],i);
    re res;
}

// returns first x in [l; r) where f(x) is true (or r if f(x) is false in [l; r))
template<class T>
T bin_search(T l, T r, function<bl(T)> f) {
    while (l < r) {
        T x = (l+r)>>1;
        if (f(x)) r = x;
        else l = x+1;
    }
    re l;
}

// returns first x in [l; r) where f(x) is true (or r if f(x) is false in [l; r))
template<class T>
T exp_search(T l, T r, function<bl(T)> f) {
    T x = l, step = 1;
    while (l < r) {
        if (f(x)) re bin_search<T>(x-(step>>1),x,f);
        x += step;
        step <<= 1;
    }
    re bin_search<T>(x-(step>>1),r,f);
}

// modular arithmetic
namespace mod {
    const int MOD = 1000000007;

    int add(int a, int b) {
        re (a + b) % MOD;
    }

    int sub(int a, int b) {
        re (a - b + MOD) % MOD;
    }

    int mul(int a, int b) {
        re ((ll)a * b) % MOD;
    }

    int pow(int a, int n) {
        int x = 1;
        for (; n; n >>= 1) {
            if (n & 1)
                x = mul(x,a);
            a = mul(a,a);
        }
        re x;
    }

    // Requirements: a % b == 0, MOD - prime number
    int idiv(int a, int b) {
        re mul(a,pow(b,MOD-2));
    }

    int llmod(ll a) {
        re a % MOD + (a < 0 ? MOD : 0);
    }
}

// work with graphs
namespace graph {
    // returns graph adjacency lists from edges list
    vvi create(int n, vii& e, bl orient = 0, int first_index = 1) {
        vvi g(n);
        for (pii p : e) {
            g[p.fi-=first_index].pb(p.se-=first_index);
            if (!orient) g[p.se].pb(p.fi);
        }
        re g;
    }

    // returns weighted graph adjacency lists from edges list with weights
    template<class T = int>
    V<V<P<int,T>>> createW(int n, V<P<pii,T>>& e, bl orient = 0, int first_index = 1) {
        V<V<P<int,T>>> g(n);
        for (auto p : e) {
            g[p.fi.fi-=first_index].pb(mp(p.fi.se-=first_index, p.se));
            if (!orient) g[p.fi.se].pb(mp(p.fi.fi, p.se));
        }
        re g;
    }

    // returns edges list from graph adjacency lists
    vii edges(vvi& g, bl orient = 0, int first_index = 1) {
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
    V<P<pii,T>> edgesW(V<V<P<int,T>>>& g, bl orient = 0, int first_index = 1) {
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

    // heavy-light decomposition
    class hld {
    public:
        // parent[u] = parent of vertex u
        // depth[u] = depth of vertex u
        // heavy[u] = next vertex after vertex u in heavy path
        // head[u] = head of heavy path in which vertex u is
        // pos[u] = index of vertex u in segment tree
        vi parent, depth, heavy, head, pos;

        hld(vvi& g) {
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

        int dfs(vvi& g, int u = 0) {
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

        void decompose(vvi& g, int u = 0, int h = 0) {
            head[u] = h;
            pos[u] = t++;
            if (heavy[u] != -1)
                decompose(g,heavy[u],h);
            for (int v : g[u])
                if (v != parent[u] && v != heavy[u])
                    decompose(g,v,v);
        }
    };

    template<class T = int>
    V<T> dijkstra(V<V<P<int,T>>>& g, int s, T NIL = iINF) {
        int n = sz(g);
        V<T> d(n, NIL);
        auto cmp = [&](T a, T b) {
            if (d[a] == d[b])
                re a < b;
            re d[a] < d[b];
        };
        set<int,decltype(cmp)> q(cmp);
        d[s] = 0;
        q.insert(s);
        while (sz(q)) {
            auto it = q.be;
            int u = *it;
            q.erase(it);
            for (P<int,T> p : g[u]) {
                int v = p.fi, w = p.se;
                if (d[u] + w < d[v]) {
                    q.erase(v);
                    d[v] = d[u] + w;
                    q.insert(v);
                }
            }
        }
        re d;
    }

    vii bridges(vvi& g) {
        int n = sz(g);
        vb was(n);
        vi tin(n), fup(n);
        int t = 0;
        vii res;
        auto dfs = [&](int u, int p, auto& f) -> void {
            was[u] = 1;
            tin[u] = fup[u] = t++;
            for (int v : g[u]) {
                if (v == p) continue;
                if (was[v])
                    fup[u] = min(fup[u], tin[v]);
                else {
                    f(v,u,f);
                    fup[u] = min(fup[u], fup[v]);
                    if (fup[v] > tin[u])
                        res.pb(mp(u,v));
                }
            }
        };
        f0r(i,n)
            if (!was[i])
                dfs(i,-1,dfs);
        re res;
    }

    vi cut_points(vvi& g) {
        int n = sz(g);
        vb was(n);
        vi tin(n), fup(n);
        int t = 0;
        set<int> res;
        auto dfs = [&](int u, int p, auto& f) -> void {
            was[u] = 1;
            tin[u] = fup[u] = t++;
            int c = 0;
            for (int v : g[u]) {
                if (v == p) continue;
                if (was[v])
                    fup[u] = min(fup[u], tin[v]);
                else {
                    f(v,u,f);
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
                dfs(i,-1,dfs);
        re vi(all(res));
    }
}

// generate random stuff
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
    
    template<class T = ld>
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

    str s(int n, str chars) {
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
        auto cmp = [&](int a, int b) {
            if (c[a] != c[b])
                re c[a] < c[b];
            re a < b;
        };
        vi a(n);
        iota(all(a), 0);
        set<int, decltype(cmp)> s(all(a), cmp);
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

// work with geometry
namespace geom {
    lld eps = 1e-8;
    
    struct R {
        lld x, y;
        R() : x(0), y(0) {}
        R(lld _x, lld _y) : x(_x), y(_y) {}
        
        R operator+(R a) { re R(x+a.x, y+a.y); }
        R operator-(R a) { re R(x-a.x, y-a.y); }
        R operator-() { re R(-x, -y); }
        R operator*(lld a) { re R(x*a, y*a); }
        lld operator*(R a) { re x*a.x + y*a.y; }
        lld operator^(R a) { re x*a.y - y*a.x; }
    
        friend istream& operator>>(istream& in, R& a) { re in >> a.x >> a.y; }
        friend ostream& operator<<(ostream& out, R& a) { re out << a.x << ' ' << a.y; }
    };
    
    enum STYPE {
        line, ray, segment
    };

    struct S {
        R a, b;
        STYPE t;
        
        S() : a(), b(), t(line) {}
        S(R _a, R _b) : a(_a), b(_b), t(line) {}
        S(R _a, R _b, STYPE _t) : a(_a), b(_b), t(_t) {}
        S(lld ax, lld ay, lld bx, lld by) : a(ax,ay), b(bx,by), t(line) {}
        S(lld ax, lld ay, lld bx, lld by, STYPE _t) : a(ax,ay), b(bx,by), t(_t) {}
        
        R operator~() { re b-a; }
        lld operator^(S x) { re (b-a)^(~x); }
    
        friend istream& operator>>(istream& in, S& x) { re in >> x.a >> x.b; }
        friend ostream& operator<<(ostream& out, S& x) { re out << x.a << ' ' << x.b; }
    };
    
    lld dist(R a) {
        re sqrt(sq(a.x) + sq(a.y));
    }
    
    lld len(S x) {
        re dist(~x);
    }
    
    lld dist(S l, R m) {
        re abs((~l)^(m-l.a))/len(l);
    }
    
    lld tan(R a) {
        re a.y/a.x;
    }
    
    lld area(S a, S b) {
        re abs((~a)^(~b))/2;
    }
    
    bl lie(S x, lld t) {
        if (x.t == line) re 1;
        if (x.t == ray) re t >= 0;
        re t >= 0 && t <= 1;
    }
    
    R intersect(S x, S y, bl& is) {
        is = 0;
        lld d = -((~x)^(~y));
        if (abs(d) < eps) return R();
        lld t1 = ((x.a-y.a)^(~y))/d;
        lld t2 = ((~x)^(y.a-x.a))/d;
        is = lie(x,t1) && lie(y,t2);
        re x.a + (~x)*t1;
    }
    
    R projection(S l, R m) {
        R p = ~l;
        R q(-p.y,p.x);
        R r(p^l.b,p^m);
        lld d = p^q;
        re R((p^r)/d, (r^q)/d);
    }
    
    V<R> convexHull(V<R>& points) {
        R key(INF,INF);
        for (R& p : points)
            if (p.x < key.x || (p.x == key.x && p.y < key.y))
                key = p;
        sort(all(points), [&](R a, R b) {
           re ((a-key)^(b-a)) > 0; 
        });
        V<R> hull(1,key);
        for (R& p : points) {
            while (sz(hull) > 1 && ((hull.back() - hull[sz(hull)-2])^(p - hull.back())) <= 0)
                hull.pop_back();
            hull.pb(p);
        }
        re hull;
    }
}

// custom bitset
class bits {
private:
    size_t n, m;
    unsigned char r;
    ull extra;
    ull *a;
public:
    bits() {
        n = 64;
        m = 1;
        r = 64;
        extra = ~0ull;
        a = new ull[1];
        a[0] = 0;
    }

    bits(size_t _n) : n(_n) {
        r = n&63;
        m = (n>>6) + (r != 0);
        if (!r) r = 64;
        extra = ~0ull >> (64-r);
        a = new ull[m];
        memset(a, 0, 8*m);
    }

    bits(str s) {
        n = sz(s);
        r = n&63;
        m = (n>>6) + (r != 0);
        if (!r) r = 64;
        extra = ~0ull >> (64-r);
        a = new ull[m];
        a[m-1] = 0;
        f0r(j,r)
            a[m-1] = (a[m-1] << 1) | (s[j] != '0');
        f0rr(i,m-1) {
            a[i] = 0;
            f0r(j,64)
                a[i] = (a[i] << 1) | (s[r+64*(m-1-i)+j]);
        }
    }

    bits(const bits& b) {
        n = b.n;
        m = b.m;
        r = b.r;
        extra = b.extra;
        a = new ull[m];
        memcpy(a, b.a, 8*m);
    }

    ~bits() {
        delete[] a;
    }

    size_t size() const {
        return n;
    }

    bl get(size_t i) const {
        return (a[i>>6] >> (i&63)) & 1;
    }

    bits& reset() {
        memset(a, 0, 8*m);
        return *this;
    }

    bits& set() {
        memset(a, -1, 8*(m-1));
        a[m-1] = extra;
        return *this;
    }

    bits& set(size_t i, bl b = 1) {
        if (b) a[i>>6] |= 1ull << (i&63);
        else a[i>>6] &= ~(1ull << (i&63));
        return *this;
    }

    bits& flip() {
        f0r(i,m) a[i] = ~a[i];
        a[m-1] &= extra;
        return *this;
    }

    bl every() const {
        f0r(i,m-1) if (a[i] != ~0ull) return 0;
        return a[m-1] == extra;
    }

    bl any() const {
        f0r(i,m) if (a[i]) return 1;
        return 0;
    }

    bl none() const {
        return !any();
    }

    size_t count() const {
        size_t res = 0;
        f0r(i,m) res += bcountll(a[i]);
        re res;
    }

    str to_str() const {
        str s = "";
        s.reserve(n);
        f0r(i,m-1) {
            ull tmp = a[i];
            f0r(j,64) {
                s += (tmp & 1) ? '1' : '0';
                tmp >>= 1;
            }
        }
        ull tmp = a[m-1];
        f0r(j,r) {
            s += (tmp & 1) ? '1' : '0';
            tmp >>= 1;
        }
        reverse(all(s));
        re s;
    }

    ull to_ull() const {
        rep(i,1,m) if (a[i]) throw overflow_error("The bitset cannot be represented as a 64-bit integer");
        return a[0];
    }

    int left_bit() const {
        int res = -1;
        f0rr(i,m)
            if ((res = lbit(a[i])) != -1)
                return res+i*64;
        return -1;
    }

    int right_bit() const {
        int res = -1;
        f0r(i,m)
            if ((res = rbit(a[i])) != -1)
                return res+i*64;
        return -1;
    }

    bits& operator=(const bits& b) {
        if (m != b.m) {
            delete[] a;
            a = new ull[m];
            m = b.m;
        }
        n = b.n;
        r = b.r;
        extra = b.extra;
        memcpy(a, b.a, 8*m);
        return *this;
    }

    bl operator==(const bits& b) const {
        f0r(i,min(m,b.m)) if (a[i] != b.a[i]) return 0;
        if (m > b.m) rep(i,b.m,m) if (a[i]) return 0;
        else rep(i,m,b.m) if (b.a[i]) return 0;
        return 1;
    }

    bl operator!=(const bits& b) const {
        f0r(i,min(m,b.m)) if (a[i] != b.a[i]) return 1;
        if (m > b.m) rep(i,b.m,m) if (a[i]) return 1;
        else rep(i,m,b.m) if (b.a[i]) return 1;
        return 0;
    }

    bl operator[](size_t i) const {
        return get(i);
    }

    bits& operator&=(const bits& b) {
        assert(n >= b.n);
        f0r(i,b.m) a[i] &= b.a[i];
        return *this;
    }

    bits& operator|=(const bits& b) {
        assert(n >= b.n);
        f0r(i,b.m) a[i] |= b.a[i];
        return *this;
    }

    bits& operator^=(const bits& b) {
        assert(n >= b.n);
        f0r(i,b.m) a[i] ^= b.a[i];
        return *this;
    }

    bits& operator>>=(size_t shift) {
        const size_t d = shift/64;
        const size_t r = shift%64;
        const size_t l = m-d;
        if (r) {
            const size_t s = 64-r;
            f0r(i,l-1)
                a[i] = (a[i+d] >> r) | (a[i+d+1] << s);
            a[l-1] = a[m-1] >> r;
        } else f0r(i,l) a[i] = a[i+d];
        memset(a+l, 0, 8*d);
        re *this;
    }

    bits& operator<<=(size_t shift) {
        const size_t d = shift/64;
        const size_t r = shift%64;
        if (r) {
            const size_t s = 64-r;
            repr(i,d+1,m)
                a[i] = (a[i-d] << r) | (a[i-d-1] >> s);
            a[d] = a[0] << r;
        } else repr(i,d,m) a[i] = a[i-d];
        memset(a, 0, 8*d);
        a[m-1] &= extra;
        re *this;
    }

    bits operator>>(size_t shift) const {
        re bits(*this) >>= shift;
    }

    bits operator<<(size_t shift) const {
        re bits(*this) <<= shift;
    }

    bits operator~() const {
        return bits(*this).flip();
    }

    bits operator&(const bits& b) {
        re bits(*this) &= b;
    }

    bits operator|(const bits& b) {
        re bits(*this) |= b;
    }

    bits operator^(const bits& b) {
        re bits(*this) ^= b;
    }

    friend istream& operator<<(istream& in, bits& b) {
        str s; in >> s;
        b = bits(s);
        re in;
    }

    friend ostream& operator<<(ostream& out, const bits& b) {
        re out << b.to_str();
    }
};

// disjoint set
class dsu {
private:
    vi p, h;
public:
    dsu(int n) {
        p = vi(n);
        h = vi(n);
        iota(all(p),0);
    }
    
    int find(int x) {
        re x == p[x] ? x : p[x] = find(p[x]);
    }
    
    bl merge(int a, int b) {
        a = find(a);
        b = find(b);
        if (a == b) re 0;
        if (h[a] < h[b])
            swap(a,b);
        p[b] = a;
        h[a] += h[a] == h[b];
        re 1;
    }
};

template<class T = int>
class sparse_table {
private:
    V<V<T>> t;
    T(*f)(T,T);
public:
    sparse_table(V<T>& a, T(*_f)(T,T) = &fmin) : f(_f) {
        int n = sz(a), m = __lg(n);
        t = V<V<T>>(m+1);
        t[0] = a;
        f0r(i,m) {
            t[i+1] = V<T>(n-(2<<i)+1);
            f0r(j,sz(t[i+1]))
                t[i+1][j] = f(t[i][j], t[i][j+(1<<i)]);
        }
    }
    
    T get(int l, int r) { //[l; r)
        int i = __lg(r-l);
        re f(t[i][l], t[i][r-(1<<i)]);
    }
};

// Requirements:
// for add(i,x) T = T + T must be defined
// f(T,nil) == f(nil,T) == T
// if T is complicated then T() must has length 1
template<class T = int>
class seg_tree {
private:
    int n;
    V<T> t;
    T(*f)(T,T);
    T nil;
public:
    seg_tree(int _n, T(*_f)(T,T) = &fadd, T _nil = T()) : n(_n), f(_f), nil(_nil) {
        t = V<T>(n<<1);
    }
    
    void build(V<T>& a) {
        f0r(i,n) t[i+n] = a[i];
        f0rr(i,n) t[i] = f(t[i<<1], t[i<<1|1]);
    }
    
    void set(int i, T x) {
        for (t[i += n] = x; i > 1; i >>= 1)
            t[i>>1] = f(t[i], t[i^1]);
    }
    
    void add(int i, T x) {
        set(i, t[i+n] + x);
    }
    
    T get(int l, int r) { //[l; r)
        T resl = nil, resr = nil;
        for (l += n, r += n; l < r; l >>= 1, r >>= 1) {
            if (l&1) resl = f(resl, t[l++]);
            if (r&1) resr = f(t[--r], resr);
        }
        re f(resl,resr);
    }
    
    T get(int i) {
        re t[i+n];
    }
    
    void print(int i = 1, str tab = "") {
        cout << tab << i << ": " << t[i] << '\n';
        if (i < n) {
            if (i) print(i<<1, tab + "  ");
            print(i<<1|1, tab + "  ");
        }
    }
};

// Requirements:
// T = T + D must be defined
// D = D + D must be defined
// T + D() == T
// f(T,nil) == f(nil,T) == T
// if T is complicated then T() must has length 1
template<class T = int, class D = int>
class seg_tree_lp {
private:
    int n, h;
    V<T> t;
    V<D> d;
    T(*f)(T,T);
    T nil;
    
    void apply(int i, D x) {
        t[i] = t[i] + x;
        if (i < n) d[i] = d[i] + x;
    }
    
    void build(int i) {
        while (i > 1) {
            i >>= 1;
            t[i] = f(t[i<<1], t[i<<1|1]) + d[i];
        }
    }
    
    void push(int i) {
        repr(j,1,h+1) {
            int p = i >> j;
            if (d[p] != D()) {
                apply(p<<1, d[p]);
                apply(p<<1|1, d[p]);
                d[p] = D();
            }
        }
    }
public:
    seg_tree_lp(int _n, T(*_f)(T,T) = &fmax, T _nil = T()) : n(_n), f(_f), nil(_nil) {
        t = V<T>(n<<1);
        h = lbit(n)+1;
        d = V<D>(n);
    }
    
    void build(V<D>& a) {
        f0r(i,n) t[i+n] = t[i+n] + a[i];
        f0rr(i,n) t[i] = f(t[i<<1], t[i<<1|1]);
    }
    
    void add(int l, int r, D x) { //[l; r)
        l += n, r += n;
        int l0 = l, r0 = r;
        for (; l < r; l >>= 1, r >>= 1) {
            if (l&1) apply(l++, x);
            if (r&1) apply(--r, x);
        }
        build(l0);
        build(r0-1);
    }
    
    T get(int l, int r) { //[l; r)
        l += n, r += n;
        push(l);
        push(r-1);
        T resl = nil, resr = nil;
        for (; l < r; l >>= 1, r >>= 1) {
            if (l&1) resl = f(resl, t[l++]);
            if (r&1) resr = f(t[--r], resr);
        }
        re f(resl,resr);
    }
    
    T get(int i) {
        i += n;
        push(i);
        re t[i];
    }
    
    void print(int i = 1, str tab = "") {
        cout << tab << i << ": " << t[i];
        if (i < n) cout << " | " << d[i];
        cout << '\n';
        if (i < n) {
            if (i) print(i<<1, tab + "  ");
            print(i<<1|1, tab + "  ");
        }
    }
};

bl _fastio, _multitest;
char *_input, *_output;

void _settings();
void _solve();
void _test();

int main() {
    #ifdef LOCAL
    auto start = now();
    #endif
    _settings();
    if (_fastio) {
        ios::sync_with_stdio(0);
        cin.tie(0); cout.tie(0);
    }
    if (_input[0]) freopen(_input, "r", stdin);
    if (_output[0]) freopen(_output, "w", stdout);
    int t = 1;
    if (_multitest) cin >> t;
    while (t--) _solve();
    #ifdef LOCAL
    auto finish = now();
    cout << "\nWorking time: " << (int)round((finish - start) / 1e6) << "ms";
    #endif
    re 0;
}

// #define TEST
void _settings() {
    #ifdef TEST
    _test();
    #endif
    _fastio = 1;
    _multitest = 0;
    #ifdef LOCAL
    static char input[] = "input.txt";
    static char output[] = "";
    #else
    static char input[] = "";
    static char output[] = "";
    #endif
    _input = input;
    _output = output;
}

#ifdef TEST
auto slow(/*input*/);
auto fast(/*input*/);
void out(auto&);

void copy(str s) {
    auto glob = GlobalAlloc(GMEM_FIXED, sz(s)+1);
    memcpy(glob, s.c_str(), sz(s)+1);
    OpenClipboard(GetDesktopWindow());
    EmptyClipboard();
    SetClipboardData(CF_TEXT,glob);
    CloseClipboard();
}

bl check(auto& ans1, auto& ans2/*, input*/) {
    /* check if ans2 is a correct answer if one of the correct answers is ans1 */
    re ans1 == ans2;
}

void _test() {
    const uint64_t SECONDS = 5;
    auto _start = now();
    int _count;
    for (_count = 0; now() - _start < 1000000000*SECONDS; ++_count) {
        /* generate input */
        auto ans1 = slow(/*input*/);
        auto ans2 = fast(/*input*/);
        if (check(ans1, ans2/*, input*/)) continue;
        cout << "Wrong answer on test " << _count+1 << '\n';
        cout << "\n============ INPUT =============\n";
        stringstream ss;
        /* print input to stringstream */
        str str = ss.str();
        copy(str);
        cout << str;
        cout << "\n======== CORRECT ANSWER ========\n";
        out(ans1);
        cout << "\n========= WRONG ANSWER =========\n";
        out(ans2);
        exit(1);
    }
    cout << _count << " tests passed\n";
    exit(0);
}
#endif

auto slow(/*input*/) {
    re 0;
}

// ================ ACTUAL CODE STARTS HERE ================ //

void out(auto& ans) {
    cout << ans << '\n';
}

auto fast(/*input*/) {
    re 0;
}

void _solve() {
    /* get input */
    auto ans = fast(/*input*/);
    out(ans);
}
