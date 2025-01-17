#include <iostream>
#include <sstream>
#include <cstdio>
#include <vector>
#include <algorithm>
#include <numeric>
#include <set>
#include <map>
#include <unordered_set>
#include <unordered_map>
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
#include <complex>
#ifdef LOCAL
#include <thread>
#include <future>
#include <windows.h>
#endif

#define P pair
#define V vector
#define fi first
#define se second
#define re return
#define pb emplace_back
#define pp pop_back
#define mp make_pair
#define be begin()
#define en end()
#define fr front()
#define ba back()
#define amin(a,b) (a = min(a,b))
#define amax(a,b) (a = max(a,b))
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
#define prec(n) fixed << setprecision(n)
#define bcount(a) __builtin_popcount(a)
#define bcountll(a) __builtin_popcountll(a)
#define bit(a,i) (((a)>>(i))&1)
#define lbit(a) (__lg((a)))
#define rbit(a) (lbit((a)&-(a)))
#define lambda(ret,name,args...) const function<ret(args)> name = [&](args) -> ret
#define opin(class, name) istream& operator>>(istream& in, class& name)
#define opout(class, name) ostream& operator<<(ostream& out, const class& name)
#define uid uniform_int_distribution
#define urd uniform_real_distribution
#define f0r(i,n) for (int i = 0; i < (n); ++i)
#define f0rr(i,n) for (int i = (n)-1; i >= 0; --i)
#define f0r1(i,n) for (int i = 1; i < (n); ++i)
#define f0rr1(i,n) for (int i = (n)-1; i >= 1; --i)
#define f0rbit(a,i,n) f0r(i,(n)) if (bit((a),i))
#define rep(i,s,n) for (int i = (s); i < (n); ++i)
#define repr(i,s,n) for (int i = (n)-1; i >= (s); --i)
#define brk(...) { __VA_ARGS__; break; }
#define ever for(;;)
#define COMMA ,

using namespace std;

typedef long long ll;
typedef unsigned long long ull;
typedef bool bl;
typedef char ch;
typedef float fl;
typedef double db;
typedef long double ld;
typedef unsigned int uint;
typedef string str;
typedef stringstream sstr;
typedef P<int,int> pii;
typedef P<ll,ll> pll;
typedef P<db,db> pdd;
typedef P<ld,ld> pld;
typedef P<str,str> pss;
typedef P<int,ll> pill;
typedef P<ll,int> plli;
typedef P<int,bl> pib;
typedef P<bl,int> pbi;
typedef V<int> vi;
typedef V<ll> vll;
typedef V<bl> vb;
typedef V<ch> vc;
typedef V<db> vd;
typedef V<ld> vld;
typedef V<str> vs;
typedef V<pii> vii;
typedef V<pll> vpll;
typedef V<pdd> vpdd;
typedef V<pld> vpld;
typedef V<pss> vpss;
typedef V<vi> vvi;
typedef V<vll> vvll;
typedef V<vb> vvb;
typedef V<vc> vvc;
typedef V<vs> vvs;
typedef V<vii> vvii;

#define DONT_CLEAN
template<class T> istream& operator>>(istream&,V<T>&);
template<class T> ostream& operator<<(ostream&,const V<T>&);
template<class T1, class T2> opin(P<T1 COMMA T2>, a) { re in >> a.fi >> a.se; }
template<class T1, class T2> opout(P<T1 COMMA T2>, a) { re out << a.fi << ' ' << a.se; }
template<class T> opin(V<T>, a) { for (T& x : a) in >> x; re in; }
template<class T> opout(V<T>, a) { for (const T& x : a) out << x << ' '; re out; }
#undef DONT_CLEAN
template<class T1, class T2> void print(const P<T1,T2>& a, char sep = '\n', ostream& out = cout) { out << a.fi << sep << a.se; }
template<class T1, class T2> void print1(const P<T1,T2>& a, char sep = '\n', ostream& out = cout) { out << a.fi+1 << sep << a.se+1; }
template<class T> void print(const T& a, char sep = '\n', ostream& out = cout) { for (auto& x : a) out << x << sep; }
template<class T> void print1(const T& a, char sep = '\n', ostream& out = cout) { for (auto& x : a) out << x+1 << sep; }
template<class T> void print_table(const V<V<T>>& a, int width = 5) { for (const auto& v : a) { for (const T& x : v) cout << setw(width) << x; cout << '\n'; } }

template<int D, class T>
struct VV : public V<VV<D-1,T>> {
    static_assert(D >= 1, "Vector dimension must be greater than zero!");
    template<class... Args>
    VV(int n = 0, Args... args) : V<VV<D-1,T>>(n, VV<D-1,T>(args...)) {}
};
template<class T>
struct VV<1,T> : public V<T> {
    VV(int n = 0, const T& val = T()) : V<T>(n, val) {}
};

template<typename ...P> void _inp(P &&... params) { (void(cin >> forward<P>(params)), ...); }
#define inp(T,...) T __VA_ARGS__; _inp(__VA_ARGS__)
#define inpv(T,n,a) int n; cin >> n; V<T> a(n); cin >> a
#define inpvv(T,n,m,a) int n, m; cin >> n >> m; V<V<T>> a(n,V<T>(m)); cin >> a

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
#define DEB(...) { cout << _tab; __VA_OPT__(EXPAND(DEB_HELPER(__VA_ARGS__))) cout << endl; }
#define DEB_HELPER(var, ...) cout << ">> " << #var << " = " << (var) << " "; __VA_OPT__(DEB_HELPER_2 PARENS (__VA_ARGS__))
#define DEB_HELPER_2() DEB_HELPER
#else
#define DEB(...) ;
#define DIN ;
#endif

template<class T = int> T fadd(const T& a, const T& b) { re a+b; }
template<class T = int> T fmin(const T& a, const T& b) { re min(a,b); }
template<class T = int> T fmax(const T& a, const T& b) { re max(a,b); }

#define T1_2 decltype(T1()+T2())
template<class T> T sq(const T& a) { re a * a; }
template<class T> ll sqll(const T& a) { re ll(a) * a; }
template<class T> T abs(const T& a) { re a > 0 ? a : -a; }
template<class T1, class T2> T1_2 min(const T1& a, const T2& b) { re a < b ? a : b; }
template<class T1, class T2> T1_2 max(const T1& a, const T2& b) { re a > b ? a : b; }

void throw_divide_by_zero_exception() { vi a(2); cout << (a.fr + 1) / a.ba; }

const int iINF = 2000000007;
const ll INF = 2000000000000000007;
const db PI = 3.14159265358979323846;

namespace other {
    // returns current time in nanoseconds
    uint64_t now() {
        using namespace chrono;
        re duration_cast<nanoseconds>(steady_clock::now().time_since_epoch()).count();
    }

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

// Some search functions
namespace search {
    // returns first x in [l; r) where f(x) is true (or r if f(x) is false in [l; r))
    template<class T>
    T binary(T l, T r, const function<bl(T)>& f) {
        while (l < r) {
            T x = (l+r)>>1;
            if (f(x)) r = x;
            else l = x+1;
        }
        re l;
    }

    // returns minimal x with precision eps in [l; r] where f(x) is true
    template<class T>
    T binary_real(T l, T r, const function<bl(T)>& f, T eps = 1e-8, int count = 100) {
        for (int i = 0; i < count && r-l > eps; ++i) {
            T x = (l+r)/2;
            if (f(x)) r = x;
            else l = x;
        }
        re r;
    }

    // returns first x in [l; r) where f(x) is true (or r if f(x) is false in [l; r))
    template<class T>
    T exponential(T l, T r, const function<bl(T)>& f) {
        T x = l, step = 1;
        while (l < r) {
            if (f(x)) re binary<T>(x-(step>>1),x,f);
            x += step;
            step <<= 1;
        }
        re binary<T>(x-(step>>1),r,f);
    }

    // returns x in [l; r] for which value of unimodal funciton f(x) is maximal (or minimal if cmp = less<T>())
    template<class T, class R>
    T ternary(T l, T r, const function<R(T)>& f, const function<bl(R,R)>& cmp = greater<R>()) {
        while (r - l >= 3) {
            T x1 = l+(r-l)/3;
            T x2 = r-(r-l)/3;
            if (cmp(f(x1),f(x2))) r = x2;
            else l = x1;
        }
        T x = l;
        R y = f(l);
        rep(x2,l+1,r)
            if (R y2 = f(x2); cmp(y2,y))
                x = x2, y = y2;
        re x;
    }

    // returns x with precision eps in [l; r] for which value of unimodal funciton f(x) is maximal (or minimal if cmp = less<T>())
    template<class T, class R>
    T ternary_real(T l, T r, const function<R(T)>& f, const function<bl(R,R)>& cmp = greater<R>(), T eps = 1e-8, int count = 100) {
        for (int i = 0; i < count && r-l > eps; ++i) {
            T x1 = l+(r-l)/3;
            T x2 = r-(r-l)/3;
            if (cmp(f(x1),f(x2))) r = x2;
            else l = x1;
        }
        re r;
    }
};

// Modular arithmetic
namespace mod {
    int MOD = 1000000007;

    int add(int a, int b, int m = MOD) {
        re (ll(a) + b) % m;
    }

    int sub(int a, int b, int m = MOD) {
        re (ll(a) - b + m) % m;
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
        re mul(a,pow(b,m-2));
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
    V<V<P<int,T>>> createW(int n, const V<P<pii,T>>& e, bl orient = 0, int first_index = 1) {
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
    V<P<pii,T>> edgesW(const V<V<P<int,T>>>& g, bl orient = 0, int first_index = 1) {
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
                int v = p.fi;
                T w = p.se;
                if (d[u] + w < d[v]) {
                    q.erase(v);
                    d[v] = d[u] + w;
                    q.insert(v);
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

    vi euler_cycle(vvi g, bl orient = 0, bl is_matrix = 1) {
        if (!is_matrix)
            g = list_to_matrix(g);
        int n = sz(g);
        int first = -1, m = 0;
        f0rr(i,n) f0r(j,n)
            if (g[i][j])
                first = i, m += g[i][j];
        if (first == -1) re {};
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

// Generation of random stuff
namespace rnd {
    mt19937 engine;
    
    void seed() {
        engine.seed(other::now());
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

// Work with geometry
namespace geom {
    const db EPS = 1e-8;

    // Double with eps precision on comparisons
    struct F {
        db x;

        F() : x() {}
        template<class T> F(T x) : x(x) {}

        operator db() const { re x; }
        F& operator=(const F& f) { x = f.x; re *this; }
        F& operator+=(const F& f) { x += f.x; re *this; }
        F& operator-=(const F& f) { x -= f.x; re *this; }
        F& operator*=(const F& f) { x *= f.x; re *this; }
        F& operator/=(const F& f) { x /= f.x; re *this; }

        friend istream& operator>>(istream& in, F& f) { re in >> f.x; }
        friend ostream& operator<<(ostream& out, const F& f) { re out << f.x; }

        F operator-() const { re F(-x); }
        F operator+(const F& f) const { re F(x + f.x); }
        F operator-(const F& f) const { re F(x - f.x); }
        F operator*(const F& f) const { re F(x * f.x); }
        F operator/(const F& f) const { re F(x / f.x); }

        bl operator==(const F& f) const { re fabs(x - f.x) < EPS; }
        bl operator!=(const F& f) const { re !(*this == f); }
        bl operator<(const F& f) const { re *this != f && x < f.x; }
        bl operator>(const F& f) const { re f < *this; }
        bl operator<=(const F& f) const { re !(*this > f); }
        bl operator>=(const F& f) const { re !(*this < f); }
    };

    template<class F>
    struct Point {
        F x, y;

        Point() : x(0), y(0) {}
        Point(const F& x, const F& y) : x(x), y(y) {}
        
        template<class F1> Point<F>& operator=(const Point<F1>& other) { x = other.x; y = other.y; re *this; }
        template<class F1> Point<F>& operator+=(const Point<F1>& other) { x += other.x; y += other.y; re *this; }
        template<class F1> Point<F>& operator-=(const Point<F1>& other) { x -= other.x; y -= other.y; re *this; }
        template<class F1> Point<F>& operator*=(const F1& factor) { x *= factor; y *= factor; re *this; }
        template<class F1> Point<F>& operator/=(const F1& factor) { x /= factor; y /= factor; re *this; }

        friend istream& operator>>(istream& in, Point<F>& p) { re in >> p.x >> p.y; }
        friend ostream& operator<<(ostream& out, const Point<F>& p) { re out << p.x << ' ' << p.y; }
    };

    #define DONT_CLEAN
    #define FUNC1(name, arg, expr) template<class F> inline auto name(const arg) -> decltype(expr) { re expr; }
    #define FUNC2(name, arg1, arg2, expr) template<class F1, class F2> inline auto name(const arg1, const arg2) -> decltype(expr) { re expr; }
    #define FUNC3(name, arg1, arg2, arg3, expr) template<class F1, class F2, class F3> inline auto name(const arg1, const arg2, const arg3) -> decltype(expr) { re expr; }
    
    template<class F> inline Point<F> make_point(const F& x, const F& y) { re Point<F>(x, y); }

    FUNC1(operator-, Point<F>& point, make_point(-point.x, -point.y))
    FUNC2(operator+, Point<F1>& lhs, Point<F2>& rhs, make_point(lhs.x + rhs.x, lhs.y + rhs.y))
    FUNC2(operator-, Point<F1>& lhs, Point<F2>& rhs, make_point(lhs.x - rhs.x, lhs.y - rhs.y))
    FUNC2(operator*, F1& factor, Point<F2>& rhs, make_point(factor * rhs.x, factor * rhs.y))
    FUNC2(operator*, Point<F1>& lhs, F2& factor, make_point(lhs.x * factor, lhs.y * factor))
    FUNC2(operator/, Point<F1>& lhs, F2& factor, make_point(lhs.x / factor, lhs.y / factor))
    FUNC2(operator*, Point<F1>& lhs, Point<F2>& rhs, lhs.x * rhs.x + lhs.y * rhs.y)
    FUNC2(operator^, Point<F1>& lhs, Point<F2>& rhs, lhs.x * rhs.y - lhs.y * rhs.x)
    FUNC2(operator==, Point<F1>& lhs, Point<F2>& rhs, lhs.x == rhs.x && lhs.y == rhs.y)
    FUNC2(operator!=, Point<F1>& lhs, Point<F2>& rhs, !(lhs == rhs))
    FUNC2(operator<, Point<F1>& lhs, Point<F2>& rhs, lhs.x < rhs.x || (lhs.x == rhs.x && lhs.y < rhs.y))
    FUNC2(operator>, Point<F1>& lhs, Point<F2>& rhs, rhs < lhs)
    FUNC2(operator<=, Point<F1>& lhs, Point<F2>& rhs, !(lhs > rhs))
    FUNC2(operator>=, Point<F1>& lhs, Point<F2>& rhs, !(lhs < rhs))

    FUNC1(angle, Point<F>& p, atan2(p.y, p.x)) // angle between vector p and x-axis
    FUNC2(angle, Point<F1>& lhs, Point<F2>& rhs, atan2(lhs ^ rhs, lhs * rhs)) // angle between vectors lhs and rhs
    FUNC3(angle, Point<F1>& lhs, Point<F2>& rhs, Point<F3>& origin, angle(lhs - origin, rhs - origin)) // angle between vectors (lhs - origin) and (rhs - origin)

    FUNC3(rotate, Point<F1>& p, F2& angleSin, F3& angleCos, make_point(angleCos * p.x - angleSin * p.y, angleSin * p.x + angleCos * p.y))
    FUNC2(rotate, Point<F1>& p, F2& angle, rotate(p, sin(angle), cos(angle))) // rotate vector p by angle radians
    FUNC3(rotate, Point<F1>& p, F2& angle, Point<F3>& origin, origin + rotate(p - origin, angle)) // rotate vector p by angle radians around point origin

    FUNC1(perp, Point<F>& p, Point<F>(-p.y, p.x))
    FUNC1(sqn, Point<F>& p, p * p) // length^2 of vector p
    FUNC1(norm, Point<F>& p, sqrt(sqn(p))) // length of vector p
    FUNC2(dist, Point<F1>& lhs, Point<F2>& rhs, norm(lhs - rhs)) // distance between points lhs and rhs
    FUNC2(dist2, Point<F1>& lhs, Point<F2>& rhs, sqn(lhs - rhs)) // distance^2 between points lhs and rhs
    FUNC2(bisector, Point<F1>& lhs, Point<F2>& rhs, lhs * norm(rhs) + rhs * norm(lhs)) // bisector between vectors lhs and rhs
    FUNC3(bisector, Point<F1>& lhs, Point<F2>& rhs, Point<F3>& origin, bisector(lhs - origin, rhs - origin) + origin) // bisector between vectors lhs and rhs at point origin
    FUNC2(coef, Point<F1>& a, Point<F2>& b, mp(perp(b-a), a^b)) // coefficients of line with points a and b

    #undef FUNC3
    #undef FUNC2
    #undef FUNC1
    #undef DONT_CLEAN

    enum LINE_TYPE {
        LINE, SEGMENT, RAY
    };

    template<class F>
    struct Line {
        Point<F> a, ab;
        LINE_TYPE t;

        Line() : a(), ab(), t(LINE) {}
        Line(const LINE_TYPE t) : a(), ab(), t(t) {}
        Line(const Point<F>& a, const Point<F>& b) : a(a), ab(b-a), t(LINE) {}
        Line(const Point<F>& a, const Point<F>& b, const LINE_TYPE t) : a(a), ab(b-a), t(t) {}
        Line(const F& a, const F& b, const F& c) : a(a==0?0:-c/a,a==0?-c/b:0), ab(b,-a), t(LINE) {}
        Line(const F& a, const F& b, const F& c, const LINE_TYPE t) : a(-c/a,0), ab(b,-a), t(t) {}
        Line(const F& ax, const F& ay, const F& bx, const F& by) : a(ax, ay), ab(bx-ax, by-ay), t(LINE) {}
        Line(const F& ax, const F& ay, const F& bx, const F& by, const LINE_TYPE t) : a(ax, ay), ab(bx-ax, by-ay), t(t) {}

        template<class F1>
        Line<F>& operator=(const Line<F1>& other) {
            a = other.a; ab = other.ab; t = other.t; return *this;
        }

        Point<F> b() const {
            re a + ab;
        }
    };

    // is point p lies on line l
    template<class F1, class F2>
    bl lay(const Point<F1>& p, const Line<F2>& l) {
        if (l.ab == Point<F2>()) re p == l.a;
        auto a = l.a - p, b = l.b() - p;
        auto s = a ^ b;
        if (s != decltype(s)()) re 0;
        if (l.t == LINE) re 1;
        if (l.t == SEGMENT) {
            auto s = a * b;
            re s <= decltype(s)();
        }
        auto s2 = a * l.ab;
        re s2 <= decltype(s2)();
    }

    template<class F1, class F2> using distF = decltype(sqrt(F1() + F2()));

    // distance between point p and line l
    template<class F1, class F2>
    distF<F1,F2> dist(const Point<F1>& p, const Line<F2>& l) {
        if (l.ab == Point<F2>()) re dist(p, l.a);
        auto s = (p - l.a) * l.ab;
        if (l.t != LINE && s <= decltype(s)()) re dist(p, l.a);
        auto s2 = (p - l.b()) * l.ab;
        if (l.t == SEGMENT && s2 >= decltype(s2)()) re dist(p, l.b());
        re abs((p - l.a) ^ l.ab) / norm(l.ab);
    }

    // projection of point p to line l
    template<class F1, class F2, class F3>
    void projection(const Point<F1>& p, const Line<F2>& l, Point<F3>& res) {
        res = l.a;
        if (l.ab == Point<F2>()) re;
        auto s = (p - l.a) * l.ab;
        if (l.t != LINE && s <= decltype(s)()) re;
        auto s2 = (p - l.b()) * l.ab;
        if (l.t == SEGMENT && s2 >= decltype(s2)()) { res = l.b(); re; }
        res += l.ab * (F3)s / sqn(l.ab);
    }

    // reflection of point p around line l
    template<class F1, class F2, class F3>
    void reflection(const Point<F1>& p, const Line<F2>& l, Point<F3>& res) {
        projection(p, l, res);
        res = res * 2 - p;
    }

    // intersection of lines lhs and rhs
    template<class F1, class F2, class F3>
    bl intersect(const Line<F1>& lhs, const Line<F2>& rhs, Point<F3>& res) {
        if (lhs.ab == Point<F1>() || rhs.ab == Point<F2>()) re 0;
        auto s = lhs.ab ^ rhs.ab;
        if (s == decltype(s)()) re 0;
        auto ls = (rhs.a - lhs.a) ^ rhs.ab;
        auto rs = (rhs.a - lhs.a) ^ lhs.ab;
        if (s < decltype(s)()) s = -s, ls = -ls, rs = -rs;
        res = lhs.a + lhs.ab * ((F3)ls / s);
        re (lhs.t == LINE || (ls >= decltype(ls)() && (lhs.t == RAY || ls <= s))) &&
           (rhs.t == LINE || (rs >= decltype(rs)() && (rhs.t == RAY || rs <= s)));
    }

    // intersection of line l and circle with center at point c and radius r
    template<class F1, class F2, class F3, class F4>
    P<bl,bl> intersect(const Line<F1>& l, const Point<F2>& c, const F3& r, P<Point<F4>,Point<F4>>& res) {
        if (l.ab == Point<F1>() || r <= F3()) re mp(0,0);
        auto A = sqn(l.ab);
        auto B = l.a*l.ab - l.ab*c;
        auto C = sqn(l.a) + sqn(c) - sq(r);
        auto D = B*B - A*C;
        if (D < decltype(D)()) re mp(0,0);
        #define lay(s) l.t == LINE || (s >= decltype(s)() && (l.t == RAY || s <= decltype(s)(1)))
        if (D == decltype(D)()) {
            auto t = -(F4)B / A;
            res.fi = res.se = l.a + (F4)t*l.ab;
            re mp(lay(t), 0);
        }
        auto t1 = F4(-B + sqrt(D)) / A, t2 = F4(-B - sqrt(D)) / A;
        res.fi = l.a + (F4)t1*l.ab;
        res.se = l.a + (F4)t2*l.ab;
        re mp(lay(t1), lay(t2));
        #undef lay
    }

    // distance between lines lhs and rhs
    template<class F1, class F2>
    distF<F1,F2> dist(const Line<F1>& lhs, const Line<F2>& rhs) {
        if (lhs.ab == Point<F1>()) re dist(lhs.a, rhs);
        if (rhs.ab == Point<F2>()) re dist(rhs.a, lhs);
        Point<distF<F1,F2>> p;
        if (intersect(lhs, rhs, p)) re 0;
        distF<F1,F2> d = min(dist(lhs.a, rhs), dist(rhs.a, lhs));
        if (lhs.t == SEGMENT) amin(d, dist(lhs.b(), rhs));
        if (rhs.t == SEGMENT) amin(d, dist(rhs.b(), lhs));
        re d;
    }

    template<class F>
    distF<F,F> perimeter(const V<Point<F>>& points) {
        int n = sz(points);
        distF<F,F> ans;
        f0r(i,n) ans += dist(points[i], points[(i+1)%n]);
        re ans;
    }

    template<class F>
    V<Point<F>> convex_hull(V<Point<F>>& points) {
        Point<F> key(iINF,iINF);
        for (const Point<F>& p : points)
            if (p < key)
                key = p;
        sort(all(points), [&](const Point<F>& a, const Point<F>& b) {
            F c = (a - key) ^ (b - a);
            if (c == F()) re dist2(a,key) < dist2(b,key);
            re c > F();
        });
        V<Point<F>> hull;
        for (const Point<F>& p : points) {
            while (sz(hull) > 1 && ((hull.ba - hull[sz(hull)-2]) ^ (p - hull.ba)) <= F())
                hull.pp();
            hull.pb(p);
        }
        re hull;
    }
}

class SuffixAutomaton {
private:
    struct state {
        vi next;
        int len, link;
        #define DONT_CLEAN
        bl is_clon;
        int first_pos;
        #undef DONT_CLEAN
    };

    const ch F;
    const int C;

public:
    V<state> st;
    int last;

    SuffixAutomaton(ch first_char = 'a', ch last_char = 'z') : F(first_char), C(last_char - first_char + 1), last(0) {
        st.assign(1, state{vi(C), 0, -1, 0, -1});
    }

    void build(const str& s) {
        for (ch c : s)
            add(c);
    }

    void add(ch c) {
        c -= F;
        int cur = sz(st);
        st.pb(state{vi(C), st[last].len + 1, 0, 0, st[last].len});
        int p;
        for (p = last; p != -1 && !st[p].next[c]; p = st[p].link)
            st[p].next[c] = cur;
        last = cur;
        if (p == -1) return;
        int q = st[p].next[c];
        if (st[p].len + 1 == st[q].len) {
            st[cur].link = q;
            return;
        }
        int clone = cur + 1;
        st.pb(state{st[q].next, st[p].len + 1, st[q].link, 1, st[q].first_pos});
        for (; p != -1 && st[p].next[c] == q; p = st[p].link)
            st[p].next[c] = clone;
        st[q].link = st[cur].link = clone;
    }

    int next(int v, ch c) const {
        re st[v].next[c-F];
    }
};

namespace strings {
    // returns prefix-function of string
    // p[i] = k -> max length k < i of prefix of string that is equal to suffix of substring [0; i]
    vi prefix_function(const str& s) {
        int n = sz(s);
        vi p(n);
        f0r1(i,n) {
            int j = p[i-1];
            while (j > 0 && s[i] != s[j])
                j = p[j-1];
            j += s[i] == s[j];
            p[i] = j;
        }
        re p;
    }

    // returns z-function of string
    // z[i] = k -> max length k of prefix of string that is equal to prefix of substring [i; n)
    vi z_function(const str& s) {
        int n = sz(s);
        vi z(n);
        for (int i = 1, l = 0, r = 0; i < n; ++i) {
            if (i <= r)
                z[i] = min(r-i+1, z[i-l]);
            while (i+z[i] < n && s[z[i]] == s[i+z[i]])
                ++z[i];
            if (i+z[i]-1 > r)
                l = i, r = i+z[i]-1;
        }
        re z;
    }

    // finds all palindromes in string
    // d.first[i] = k -> substrings [i-j+1; i+j-1] are palindromes of length 2 * j - 1 for all j = [1; k]
    // d.second[i] = k -> substrings [i-j; i+j-1] are palindromes of length 2 * j for all j = [1; k]
    P<vi,vi> manacher(const str& s) {
        int n = sz(s);
        P<vi,vi> d{vi(n),vi(n)};
        int l = 0, r = -1;
        f0r(i,n) {
            int k = i > r ? 1 : min(d.fi[l+r-i], r-i+1);
            while (0 <= i-k && i+k < n && s[i-k] == s[i+k]) ++k;
            d.fi[i] = k;
            if (i+k-1 > r)
                l = i-k+1, r = i+k-1;
        }
        l = 0, r = -1;
        f0r(i,n) {
            int k = i > r ? 0 : min(d.se[l+r-i+1], r-i+1);
            while (0 <= i-k-1 && i+k < n && s[i-k-1] == s[i+k]) ++k;
            d.se[i] = k;
            if (i+k-1 > r)
                l = i-k, r = i+k-1;
        }
        re d;
    }
}

// Custom bitset
class Bitset {
private:
    size_t n, m;
    unsigned char r;
    ull extra;
    V<ull> a;
public:
    Bitset() : n(0), m(0), r(0), extra(0), a(0) {}

    Bitset(size_t _n) : n(_n) {
        r = n & 63;
        m = (n >> 6) + (r != 0);
        if (!r) r = 64;
        extra = ~0ull >> (64-r);
        a.assign(m,0);
    }

    Bitset(const str& s) {
        n = sz(s);
        r = n & 63;
        m = (n >> 6) + (r != 0);
        if (!r) r = 64;
        extra = ~0ull >> (64-r);
        a.assign(m,0);
        if (!m) re;
        size_t j = 0;
        f0r(k,r)
            a[m-1] = (a[m-1] << 1) | (s[j++] != '0');
        f0rr(i,m-1)
            f0r(k,64)
                a[i] = (a[i] << 1) | (s[j++] != '0');
    }

    Bitset(const Bitset& b) {
        n = b.n;
        m = b.m;
        r = b.r;
        extra = b.extra;
        a = b.a;
    }

    size_t size() const {
        re n;
    }

    bl get(size_t i) const {
        re (a[i>>6] >> (i&63)) & 1;
    }

    Bitset& reset() {
        a.assign(m,0);
        re *this;
    }

    Bitset& set() {
        if (!m) re *this;
        a.assign(m,~0ull);
        a[m-1] = extra;
        re *this;
    }

    Bitset& set(size_t i, bl b = 1) {
        if (b) a[i>>6] |= 1ull << (i&63);
        else a[i>>6] &= ~(1ull << (i&63));
        re *this;
    }

    Bitset& flip() {
        if (!m) re *this;
        f0r(i,m) a[i] = ~a[i];
        a[m-1] &= extra;
        re *this;
    }

    bl every() const {
        if (!m) re 0;
        f0r(i,m-1) if (a[i] != ~0ull) re 0;
        re a[m-1] == extra;
    }

    bl any() const {
        f0r(i,m) if (a[i]) re 1;
        re 0;
    }

    bl none() const {
        re !any();
    }

    size_t count() const {
        size_t res = 0;
        f0r(i,m) res += bcountll(a[i]);
        re res;
    }

    str to_str() const {
        str s = "";
        if (!m) re s;
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
        if (!m) re 0;
        f0r1(i,m) if (a[i]) throw overflow_error("The bitset cannot be represented as a 64-bit integer");
        re a[0];
    }

    int left_bit() const {
        f0rr(i,m)
            if (a[i])
                re lbit(a[i])+i*64;
        re -1;
    }

    int right_bit() const {
        f0r(i,m)
            if (a[i])
                re rbit(a[i])+i*64;
        re -1;
    }

    Bitset& operator=(const Bitset& b) {
        n = b.n;
        m = b.m;
        r = b.r;
        extra = b.extra;
        a = b.a;
        re *this;
    }

    bl operator==(const Bitset& b) const {
        f0r(i,min(m,b.m)) if (a[i] != b.a[i]) re 0;
        if (m > b.m) rep(i,b.m,m) if (a[i]) re 0;
        else rep(i,m,b.m) if (b.a[i]) re 0;
        re 1;
    }

    bl operator!=(const Bitset& b) const {
        f0r(i,min(m,b.m)) if (a[i] != b.a[i]) re 1;
        if (m > b.m) rep(i,b.m,m) if (a[i]) re 1;
        else rep(i,m,b.m) if (b.a[i]) re 1;
        re 0;
    }

    bl operator<(const Bitset& b) const {
        if (m > b.m) repr(i,b.m,m) if (a[i]) re 0;
        else rep(i,m,b.m) if (b.a[i]) re 1;
        f0rr(i,min(m,b.m)) if (a[i] != b.a[i]) re a[i] < b.a[i];
        re 0;
    }

    bl operator>(const Bitset& b) const {
        if (m > b.m) repr(i,b.m,m) if (a[i]) re 1;
        else rep(i,m,b.m) if (b.a[i]) re 0;
        f0rr(i,min(m,b.m)) if (a[i] != b.a[i]) re a[i] > b.a[i];
        re 0;
    }

    bl operator<=(const Bitset& b) const {
        re !(*this > b);
    }

    bl operator>=(const Bitset& b) const {
        re !(*this < b);
    }

    bl operator[](size_t i) const {
        re get(i);
    }

    Bitset& operator&=(const Bitset& b) {
        assert(n >= b.n);
        f0r(i,b.m) a[i] &= b.a[i];
        re *this;
    }

    Bitset& operator|=(const Bitset& b) {
        assert(n >= b.n);
        f0r(i,b.m) a[i] |= b.a[i];
        re *this;
    }

    Bitset& operator^=(const Bitset& b) {
        assert(n >= b.n);
        f0r(i,b.m) a[i] ^= b.a[i];
        re *this;
    }

    Bitset& operator>>=(size_t shift) {
        if (!m) re *this;
        const size_t d = shift/64;
        if (m < d) {
            a.assign(m,0);
            re *this;
        }
        const size_t r = shift%64;
        const size_t l = m-d;
        if (r) {
            const size_t s = 64-r;
            f0r(i,l-1)
                a[i] = (a[i+d] >> r) | (a[i+d+1] << s);
            a[l-1] = a[m-1] >> r;
        } else f0r(i,l) a[i] = a[i+d];
        rep(i,l,m) a[i] = 0;
        re *this;
    }

    Bitset& operator<<=(size_t shift) {
        if (!m) re *this;
        const size_t d = shift/64;
        const size_t r = shift%64;
        if (r) {
            const size_t s = 64-r;
            repr(i,d+1,m)
                a[i] = (a[i-d] << r) | (a[i-d-1] >> s);
            a[d] = a[0] << r;
        } else repr(i,int(d),m) a[i] = a[i-d];
        f0r(i,d) a[i] = 0;
        a[m-1] &= extra;
        re *this;
    }

    Bitset operator>>(size_t shift) const {
        re Bitset(*this) >>= shift;
    }

    Bitset operator<<(size_t shift) const {
        re Bitset(*this) <<= shift;
    }

    Bitset operator~() const {
        re Bitset(*this).flip();
    }

    Bitset operator&(const Bitset& b) const {
        re Bitset(*this) &= b;
    }

    Bitset operator|(const Bitset& b) const {
        re Bitset(*this) |= b;
    }

    Bitset operator^(const Bitset& b) const {
        re Bitset(*this) ^= b;
    }

    friend istream& operator>>(istream& in, Bitset& b) {
        str s; in >> s;
        b = Bitset(s);
        re in;
    }

    friend ostream& operator<<(ostream& out, const Bitset& b) {
        re out << b.to_str();
    }
};

#define FFT_MULT
#ifdef FFT_MULT
const uint32_t FFT_THRESHOLD = 2800;
const uint32_t FFT_LEN = 8;
static_assert(32 % FFT_LEN == 0);
const uint32_t FFT_COUNT = 32 / FFT_LEN;
const uint32_t FFT_MASK = (1 << FFT_LEN) - 1;
#endif

// Long arithmetics
class BigInt {
private:
    using u = uint32_t;
    using ul = uint64_t;

    const ul BASE = ul(1) << 32; // DO NOT CHANGE!

    void remove_leading_zeros() {
        while (sz(nums) && !nums.ba)
            nums.pp();
        if (!sz(nums))
            sign = 0;
    }

    void make_same_len(const BigInt& other, V<u>& a, V<u>& b) const {
        a = nums;
        b = other.nums;
        if (sz(a) < sz(b))
            a.resize(sz(b), 0);
        else
            b.resize(sz(a), 0);
    }

public:
    V<u> nums;
    ch sign;

    BigInt() : nums(), sign(0) { }
    BigInt(int n) { set_num(n); }
    BigInt(u n) { set_num(n); }
    BigInt(ll n) { set_num(n); }
    BigInt(ul n) { set_num(n); }
    BigInt(const BigInt& other) : sign(other.sign) { nums = other.nums; }
    BigInt(const str& s) : nums(), sign(0) {
        ch sign = 1;
        for (char c : s) {
            if (c == '-')
                sign = -1;
            else {
                *this *= 10;
                *this += c - '0';
            }
        }
        this->sign *= sign;
    }

    template<class T>
    void set_num(T n) {
        nums.clear();
        if (n == T()) {
            sign = 0;
            re;
        }
        if (n < T())
            n = -n, sign = -1;
        else
            sign = 1;
        while (n != T()) {
            nums.pb(n);
            n /= BASE;
        }
    }

    template<class T>
    T to_num() const {
        T res = 0;
        for (u i : nums)
            res = res * BASE + i;
        res *= sign;
        re res;
    }

    friend BigInt pow(BigInt a, BigInt n) {
        BigInt x = 1;
        while (n.sign) {
            if (n.nums[0] % 2) x *= a;
            a *= a;
            n >>= 1;
        }
        re x;
    }

    friend BigInt sqrt(BigInt x) {
        BigInt res = x, tmp = (x + BigInt(1)) >> 1;
        while (tmp < res) res = tmp, tmp = (tmp + x / tmp) >> 1;
        re res;
    }

    str naive_base(BigInt x, int base) const {
        str s;
        do {
            auto p = x.divide_with_remainder(10);
            s += (p.se.sign ? p.se.nums[0] : 0) + '0';
            x = p.fi;
        } while (x.sign);
        re s;
    }

    str fast_base(const BigInt& x, int base, int order = -1) const {
        if (order == -1) {
            order = 1;
            BigInt b(base);
            while (b * base <= x) {
                b *= b;
                order *= 2;
            }
        }
        if (!order) re naive_base(x, base);
        BigInt sep = pow(BigInt(base), order);
        auto p = x.divide_with_remainder(sep);
        re fast_base(p.se, base, order / 2) + fast_base(p.fi, base, order / 2);
    }

    operator str() const {
        BigInt n(*this);
        n.sign = abs(n.sign);
        str s = fast_base(n, 10);
        while (sz(s) > 1 && s.ba == '0')
            s.pp();
        if (sign == -1)
            s += '-';
        reverse(all(s));
        re s;
    }

    BigInt& operator=(const BigInt& other) {
        nums = other.nums;
        sign = other.sign;
        re *this;
    }

    bl operator==(const BigInt& other) const {
        re sign == other.sign && nums == other.nums;
    }

    bl operator!=(const BigInt& other) const {
        re sign != other.sign || nums != other.nums;
    }

    bl operator<(const BigInt& other) const {
        if (sign != other.sign)
            re sign < other.sign;
        if (sz(nums) != sz(other.nums))
            re sz(nums) < sz(other.nums);
        f0rr(i,sz(nums))
            if (nums[i] != other.nums[i])
                re (nums[i] < other.nums[i]) ^ (sign == -1);
        re 0;
    }

    bl operator>(const BigInt& other) const {
        re other < *this;
    }

    bl operator<=(const BigInt& other) const {
        re !(other < *this);
    }

    bl operator>=(const BigInt& other) const {
        re !(*this < other);
    }

    bl operator!=(int x) const { // for __gcd
        re sz(nums) > 1 || (sign == 1 && nums[0] != x) || (sign == -1 && nums[0] != -ul(x)) || (!sign && !x);
    }

    BigInt& operator>>=(size_t shift) {
        int m = sz(nums);
        if (!m) re *this;
        const size_t d = shift/32;
        if (m < d) {
            nums.clear();
            sign = 0;
            re *this;
        }
        const size_t r = shift%32;
        const size_t l = m-d;
        if (r) {
            const size_t s = 32-r;
            f0r(i,l-1)
                nums[i] = (nums[i+d] >> r) | (nums[i+d+1] << s);
            nums[l-1] = nums[m-1] >> r;
        } else f0r(i,l) nums[i] = nums[i+d];
        nums.resize(l);
        remove_leading_zeros();
        re *this;
    }

    BigInt& operator<<=(size_t shift) {
        int m = sz(nums);
        if (!m) re *this;
        const size_t d = shift/32;
        const size_t r = shift%32;
        m += d+1;
        nums.resize(m);
        if (r) {
            const size_t s = 32-r;
            repr(i,d+1,m)
                nums[i] = (nums[i-d] << r) | (nums[i-d-1] >> s);
            nums[d] = nums[0] << r;
        } else repr(i,int(d),m) nums[i] = nums[i-d];
        f0r(i,d) nums[i] = 0;
        remove_leading_zeros();
        re *this;
    }

    BigInt operator-() const {
        BigInt res(*this);
        res.sign = -res.sign;
        re res;
    }

    BigInt& operator+=(const BigInt& other) {
        if (!other.sign)
            re *this;
        if (!sign)
            re *this = other;
        if (sign != other.sign)
            re *this -= -other;
        V<u> a, b;
        make_same_len(other, a, b);
        bl carry = 0;
        nums.resize(sz(a));
        f0r(i,sz(a)) {
            ul sum = ul(a[i]) + b[i] + carry;
            if (carry = sum > ~u(); carry)
                sum -= BASE;
            nums[i] = sum;
        }
        if (carry)
            nums.pb(1);
        re *this;
    }

    BigInt& operator-=(const BigInt& other) {
        if (!other.sign)
            re *this;
        if (!sign) {
            nums = other.nums;
            sign = -other.sign;
            re *this;
        }
        if (sign != other.sign)
            re *this += -other;
        if (nums == other.nums) {
            nums.clear();
            sign = 0;
            re *this;
        }
        V<u> a, b;
        make_same_len(other, a, b);
        bl less = 0;
        f0rr(i,sz(a))
            if (a[i] != b[i]) {
                less = a[i] < b[i]; break; }
        if (less) {
            swap(a,b);
            sign = -sign;
        }
        bl carry = 0;
        nums.resize(sz(a));
        f0r(i,sz(a)) {
            nums[i] = (a[i] - b[i] - carry);
            carry = a[i] < ul(b[i]) + carry;
        }
        remove_leading_zeros();
        re *this;
    }

    BigInt& multiply_classic(const BigInt& other) {
        if (!other.sign)
            re *this = other;
        if (!sign)
            re *this;
        sign *= other.sign;
        V<u> a = nums, b = other.nums;
        nums.assign(sz(a) + sz(b), 0);
        f0r(i,sz(a)) {
            u carry = 0;
            for (int j = 0; j < sz(b) || carry; ++j) {
                ul mul = nums[i+j] + a[i] * ul(j < sz(b) ? b[j] : 0) + carry;
                nums[i+j] = mul;
                carry = mul >> 32;
            }
        }
        remove_leading_zeros();
        re *this;
    }

    #ifdef FFT_MULT
    BigInt& multiply_fft(const BigInt& other) {
        sign *= other.sign;
        V<u> a(sz(nums) * FFT_COUNT);
        f0r(i,sz(nums))
            f0r(j,FFT_COUNT)
                a[FFT_COUNT * i + j] = (nums[i] >> (j * FFT_LEN)) & FFT_MASK;
        V<u> b(sz(nums) * FFT_COUNT);
        f0r(i,sz(other.nums))
            f0r(j,FFT_COUNT)
                b[FFT_COUNT * i + j] = (other.nums[i] >> (j * FFT_LEN)) & FFT_MASK;
        auto res = other::mul_fft<ul>(a,b);
        u n = sz(res);
        nums.assign(n,0);
        ul carry = 0;
        f0r(i,n) {
            u x = (res[i] & FFT_MASK) + (carry & FFT_MASK);
            nums[i / FFT_COUNT] += (x & FFT_MASK) << ((i % FFT_COUNT) * FFT_LEN);
            carry >>= FFT_LEN;
            carry += (res[i] >> FFT_LEN) + (x >> FFT_LEN);
        }
        remove_leading_zeros();
        re *this;
    }
    #endif

    BigInt& operator*=(const BigInt& other) {
        #ifdef FFT_MULT
        if (sz(nums) >= FFT_THRESHOLD && sz(other.nums) >= FFT_THRESHOLD)
            re multiply_fft(other);
        #endif
        re multiply_classic(other);
    }

    P<BigInt, BigInt> divide_with_remainder(const BigInt& other) const {
        assert(other.sign);
        if (!sign)
            re mp(BigInt(), BigInt());
        if (nums == other.nums)
            re mp(BigInt(sign * other.sign), BigInt());
        BigInt r;
        BigInt base(BASE);
        BigInt b(other);
        b.sign = 1;
        int i = sz(nums) - 1;
        while (i >= 0 && r * base + nums[i] < b) {
            r *= base;
            r += nums[i--];
        }
        u size = 0;
        BigInt n;
        n.nums.resize(sz(nums));
        for (; i >= 0; --i) {
            r = r * base + nums[i];
            u cc = ~u();
            if (r < b * cc) {
                u max = cc;
                cc = 0;
                while (cc < max) {
                    u x = (ul(cc) + max) >> 1;
                    if (r < b * x) max = x;
                    else cc = x + 1;
                }
                --cc;
            }
            r -= b * cc;
            n.nums[size++] = cc;
        }
        n.nums.resize(size);
        reverse(all(n.nums));
        if (!size) n.sign = 0;
        else n.sign = sign * other.sign;
        r.sign *= other.sign;
        re mp(n, r);
    }

    BigInt& operator/=(const BigInt& other) {
        re *this = divide_with_remainder(other).fi;
    }

    BigInt& operator%=(const BigInt& other) {
        re *this = divide_with_remainder(other).se;
    }

    BigInt operator>>(size_t shift) const {
        re BigInt(*this) >>= shift;
    }

    BigInt operator<<(size_t shift) const {
        re BigInt(*this) <<= shift;
    }

    BigInt operator+(const BigInt& other) const {
        re BigInt(*this) += other;
    }

    BigInt operator-(const BigInt& other) const {
        re BigInt(*this) -= other;
    }

    BigInt operator*(const BigInt& other) const {
        re BigInt(*this) *= other;
    }

    BigInt operator/(const BigInt& other) const {
        re BigInt(*this) /= other;
    }

    BigInt operator%(const BigInt& other) const {
        re BigInt(*this) %= other;
    }
};

// Rational number
template<class T>
class Rational {
private:
    T n, d;

    void reduce() {
        if (d == T()) throw_divide_by_zero_exception();
        T g = __gcd<T>(n,d);
        n /= g;
        d /= g;
        if (d < T()) {
            n = -n;
            d = -d;
        }
    }

    str to_str(size_t precision) {
        auto x = n < T() ? -n : n;
        str s = (n < T() ? "-" : "") + str(x/d);
        x = x%d;
        if (x == T()) re s;
        T m(1);
        f0r(i,precision) m *= 10;
        x *= m;
        str r = x/d;
        reverse(all(r));
        while (sz(r) < precision)
            r += '0';
        reverse(all(r));
        s += "." + r;
        re s;
    }

public:
    Rational() : n(0), d(1) {}
    Rational(const T& n) : n(n), d(1) {}
    Rational(const T& n, const T& d) : n(n), d(d) { reduce(); }
    Rational(const Rational<T>& other) : n(other.n), d(other.d) {}

    T numerator() const { re n; }
    T denominator() const { re d; }

    operator fl() { re stof(to_str(numeric_limits<fl>::digits10 + 1)); }
    operator db() { re stod(to_str(numeric_limits<db>::digits10 + 1)); }
    operator ld() { re stold(to_str(numeric_limits<ld>::digits10 + 1)); }

    Rational<T>& operator=(const Rational<T>& other) {
        n = other.n;
        d = other.d;
        re *this;
    }

    Rational<T> operator-() const { re Rational{-n,d}; }

    Rational<T> operator+(const Rational<T>& other) const {
        T g = __gcd<T>(d,other.d);
        re Rational<T>{other.d/g*n + d/g*other.n, d/g*other.d};
    }

    Rational<T> operator-(const Rational<T>& other) const {
        T g = __gcd<T>(d,other.d);
        re Rational{other.d/g*n - d/g*other.n, d/g*other.d};
    }

    Rational<T> operator*(const Rational<T>& other) const {
        re Rational<T>{n*other.n, d*other.d};
    }

    Rational operator/(const Rational& other) const {
        re Rational{n*other.d, d*other.n};
    }

    Rational<T>& operator+=(const Rational<T>& other) { re *this = *this + other; }
    Rational<T>& operator-=(const Rational<T>& other) { re *this = *this - other; }
    Rational<T>& operator*=(const Rational<T>& other) { re *this = *this * other; }
    Rational<T>& operator/=(const Rational<T>& other) { re *this = *this / other; }

    bl operator==(const Rational<T>& other) const {
        re n == other.n && d == other.d;
    }

    bl operator<(const Rational<T>& other) const {
        if (d == other.d)
            re n < other.n;
        if (other.n == T())
            re n < T();
        if (n == T())
            re other.n >= T();
        re (*this + other).n < T();
    }

    bl operator>(const Rational<T>& other) const { re other < *this; }
    bl operator!=(const Rational<T>& other) const { re !(*this == other); }
    bl operator<=(const Rational<T>& other) const { re !(*this > other); }
    bl operator>=(const Rational<T>& other) const { re !(*this < other); }

    friend ostream& operator<<(ostream& out, const Rational<T>& x) {
        re out << x.n << '/' << x.d;
    }
};

// Disjoint Set Union
class DSU {
private:
    vi p, h;
public:
    DSU(int n) {
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
class SparseTable {
private:
    V<V<T>> t;
    function<T(const T&, const T&)> f;
public:
    SparseTable(const V<T>& a, const function<T(const T&, const T&)>& f = fmin<T>) : f(f) {
        int n = sz(a), m = lbit(n);
        t = V<V<T>>(m+1);
        t[0] = a;
        f0r(i,m) {
            t[i+1] = V<T>(n-(2<<i)+1);
            f0r(j,sz(t[i+1]))
                t[i+1][j] = f(t[i][j], t[i][j+(1<<i)]);
        }
    }
    
    T get(int l, int r) { //[l; r)
        int i = lbit(r-l);
        re f(t[i][l], t[i][r-(1<<i)]);
    }
};

// Requirements:
// for add(i,x) T = T + T must be defined
// f(T,nil) == f(nil,T) == T
// if T is complicated then T() must has length 1
template<class T = int>
class SegTree {
private:
    int n;
    V<T> t;
    function<T(const T&, const T&)> f;
    T nil;
public:
    SegTree(int n, const function<T(const T&, const T&)>& f = fadd<T>, const T& nil = T()) : n(n), f(f), nil(nil) {
        t = V<T>(n<<1);
    }
    
    void build(const V<T>& a) {
        f0r(i,n) t[i+n] = a[i];
        f0rr(i,n) t[i] = f(t[i<<1], t[i<<1|1]);
    }
    
    void set(int i, const T& x) {
        for (t[i += n] = x; i > 1; i >>= 1)
            t[i>>1] = f(t[i], t[i^1]);
    }
    
    void add(int i, const T& x) {
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
class SegTreeLP {
private:
    int n, h;
    V<T> t;
    V<D> d;
    function<T(const T&, const T&)> f;
    T nil;
    
    void apply(int i, const D& x) {
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
        f0rr1(j,h+1) {
            int p = i >> j;
            if (d[p] != D()) {
                apply(p<<1, d[p]);
                apply(p<<1|1, d[p]);
                d[p] = D();
            }
        }
    }
public:
    SegTreeLP(int n, const function<T(const T&, const T&)>& f = fmax<T>, const T& nil = T()) : n(n), f(f), nil(nil) {
        t = V<T>(n<<1);
        h = lbit(n)+1;
        d = V<D>(n);
    }
    
    void build(const V<D>& a) {
        f0r(i,n) t[i+n] = t[i+n] + a[i];
        f0rr(i,n) t[i] = f(t[i<<1], t[i<<1|1]);
    }
    
    void add(int l, int r, const D& x) { //[l; r)
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
#ifdef LOCAL
void _test();
#endif

int main() {
    #ifdef LOCAL
    auto start = other::now();
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
    auto finish = other::now();
    cout << "\nWorking time: " << (int)round((finish - start) / 1e6) << "ms";
    #endif
    re 0;
}

// #define TEST
#ifdef TEST
// move defines input_args, input_vars, output before define TEST if needed
output slow(input_args); // slow but 100% correct solution
output fast(input_args); // fast but not sure if it's a correct solution
void out(const output&);

void copy(str s) {
    auto glob = GlobalAlloc(GMEM_FIXED, sz(s)+1);
    memcpy(glob, s.c_str(), sz(s)+1);
    OpenClipboard(GetDesktopWindow());
    EmptyClipboard();
    SetClipboardData(CF_TEXT,glob);
    CloseClipboard();
}

bl check(const output& ans1, const output& ans2/*, input_args*/) {
    /* check if ans2 is a correct answer if one of the correct answers is ans1 */
    re ans1 == ans2;
}

void _test() {
    const uint64_t TEST_TIME_SECONDS = 5;
    const uint64_t TIME_LIMIT_MILLISECONDS = 0;
    auto _start = other::now();
    int _count;
    for (_count = 0; other::now() - _start < 1000000000 * TEST_TIME_SECONDS; ++_count) {
        /* generate input */
        output ans1 = slow(input_vars);
        output ans2;
        bl _tle = 0;
        if (TIME_LIMIT_MILLISECONDS) {
            promise<output> _p;
            future<output> _f = _p.get_future();
            thread([&]{ _p.set_value(fast(input_vars)); }).detach();
            if (_tle = (_f.wait_for(chrono::milliseconds(TIME_LIMIT_MILLISECONDS)) != future_status::ready))
                cout << "Time limit exceeded on test " << _count+1 << '\n';
            else ans2 = _f.get();
        } else ans2 = fast(input_vars);
        if (!_tle) {
            if (check(ans1, ans2/*, input_vars*/)) continue;
            cout << "Wrong answer on test " << _count+1 << '\n';
        }
        cout << "\n============ INPUT =============\n";
        sstr ss;
        if (_multitest) ss << "1\n";
        /* print input to stringstream */
        str _str = ss.str();
        copy(_str);
        cout << _str;
        cout << "\n======== CORRECT ANSWER ========\n";
        out(ans1);
        if (_tle) exit(1);
        cout << "\n========= WRONG ANSWER =========\n";
        out(ans2);
        exit(1);
    }
    cout << _count << " tests passed\n";
    exit(0);
}
#endif

void _settings() {
    _fastio = 1;
    _multitest = 0;
    #ifdef TEST
    _test();
    #endif
    #ifdef LOCAL
    static char input_[] = "input.txt";
    static char output_[] = "";
    #else
    static char input_[] = "";
    static char output_[] = "";
    #endif
    _input = input_;
    _output = output_;
}

/// ================ ACTUAL CODE STARTS HERE ================ ///

#define input_args 
#define input_vars 
#define output int

const str NY[] = {"N", "Y"};
const str NoYes[] = {"No", "Yes"};
const str NOYES[] = {"NO", "YES"};

void out(const output& ans) {
    cout << ans << '\n';
}

output slow(input_args) {
    re {};
}

output fast(input_args) {
    re {};
}

void _solve() {
    /* get input */
    auto ans = fast(input_vars);
    out(ans);
}
