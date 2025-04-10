#ifndef MAIN_HPP
#define MAIN_HPP
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
#include <ext/pb_ds/assoc_container.hpp>
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
#define uset unordered_set
#define umap unordered_map
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
template<class T> using oset = __gnu_pbds::tree<T, __gnu_pbds::null_type, less<T>, __gnu_pbds::rb_tree_tag, __gnu_pbds::tree_order_statistics_node_update>;

typedef long long ll;
typedef unsigned long long ull;
typedef bool bl;
typedef char ch;
typedef float fl;
typedef double db;
typedef long double ld;
typedef unsigned int uint;
typedef unsigned char uch;
typedef string str;
typedef stringstream sstr;
typedef P<int,int> pii;
typedef P<ll,ll> pll;
typedef P<db,db> pdd;
typedef P<ld,ld> pld;
typedef P<ch,ch> pcc;
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
typedef V<vd> vvd;
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
template<class T> T abs(const T& a) { re a > T(0) ? a : -a; }
template<class T1, class T2> T1_2 min(const T1& a, const T2& b) { re a < b ? a : b; }
template<class T1, class T2> T1_2 max(const T1& a, const T2& b) { re a > b ? a : b; }

void throw_divide_by_zero_exception() { vi a(2); cout << (a.fr + 1) / a.ba; }

const int iINF = 2000000007;
const ll INF = 2000000000000000007;
const db dINF = 1e100;
const db PI = 3.14159265358979323846;

// returns current time in nanoseconds
uint64_t now() {
    using namespace chrono;
    re duration_cast<nanoseconds>(steady_clock::now().time_since_epoch()).count();
}
#endif