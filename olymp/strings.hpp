#ifndef STRINGS_HPP
#define STRINGS_HPP
#include "main.hpp"

// Work with strings
namespace strings {
    class AhoCorasick {
        struct state {
            vi next, go;
            int link, parent;
            ch c;
            bl leaf;
        };
    
        const ch F;
        const int C;

        int _go(int v, ch c) {
            if (st[v].go[c] == -1)
                if (st[v].next[c] != -1)
                    st[v].go[c] = st[v].next[c];
                else
                    st[v].go[c] = v ? _go(link(v), c) : 0;
            re st[v].go[c];
        }
    
    public:
        V<state> st;

        AhoCorasick(ch first_char = 'a', ch last_char = 'z') : F(first_char), C(last_char - first_char + 1) {
            st.assign(1, state{vi(C,-1), vi(C,-1), -1, -1, -1});
        }

        void add(const str& s) {
            int v = 0;
            for (ch c : s) {
                c -= F;
                if (st[v].next[c] == -1) {
                    st[v].next[c] = sz(st);
                    st.pb(state{vi(C,-1), vi(C,-1), -1, v, c});
                }
                v = st[v].next[c];
            }
            st[v].leaf = 1;
        }

        int link(int v) {
            if (st[v].link == -1)
                if (!v || !st[v].parent)
                    st[v].link = 0;
                else
                    st[v].link = _go(link(st[v].parent), st[v].c);
            re st[v].link;
        }

        int go(int v, ch c) {
            re _go(v,c-F);
        }
    };

    class SuffixArray {
        int n, m;
        vvi t;
        bl store_table;

    public:
        vi p;

        // add zero-char to the end of string if needed
        SuffixArray(const str& s, bl store_table = 0) : store_table(store_table) {
            n = sz(s), m = n ? lbit(n) : 0;
            p.resize(n);
            vi cnt(max(n,128));
            for (ch c : s)
                ++cnt[c];
            f0r1(i,128)
                cnt[i] += cnt[i-1];
            f0r(i,n)
                p[--cnt[s[i]]] = i;
            vi::iterator c, cn;
            vi _c, _cn;
            if (store_table) {
                t.assign(m+1, vi(n));
                c = t[0].be;
            } else {
                _c.resize(n);
                _cn.resize(n);
                c = _c.be;
                cn = _cn.be;
            }
            c[p[0]] = 0;
            int classes = 1;
            f0r1(i,n)
                c[p[i]] = (classes += s[p[i]] != s[p[i-1]]) - 1;
            vi pn(n);
            f0r(h,m) {
                if (store_table)
                    cn = t[h+1].be;
                f0r(i,n) {
                    pn[i] = p[i] - (1<<h);
                    if (pn[i] < 0)
                        pn[i] += n;
                }
                fill(cnt.be, cnt.be + classes, 0);
                f0r(i,n)
                    ++cnt[c[pn[i]]];
                f0r1(i,classes)
                    cnt[i] += cnt[i-1];
                f0rr(i,n)
                    p[--cnt[c[pn[i]]]] = pn[i];
                cn[p[0]] = 0;
                classes = 1;
                f0r1(i,n)
                    cn[p[i]] = (classes += (c[p[i]] != c[p[i-1]] || c[(p[i] + (1<<h)) % n] != c[(p[i-1] + (1<<h)) % n])) - 1;
                swap(c, cn);
            }
        }

        pii get(int l, int r) { // [l; r)
            assert(store_table);
            int i = lbit(r-l);
            re {t[i][l], t[i][r-(1<<i)]};
        }

        int lcp(int i, int j) {
            assert(store_table);
            int ans = 0;
            f0rr(k,m+1) {
                if (t[k][i] == t[k][j]) {
                    ans += 1 << k;
                    i += 1 << k;
                    j += 1 << k;
                }
            }
            re ans;
        }
    };

    class SuffixAutomaton {
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
    
    class Eertree {
        struct state {
            vi next;
            int len, link;
        };
    
        const ch F;
        const int C;
    
    public:
        V<state> st;
        int last, k;
        str s;
    
        Eertree(ch first_char = 'a', ch last_char = 'z') : F(first_char), C(last_char - first_char + 1), last(0), k(0) {
            st = {state{vi(C), 0, 1}, state{vi(C), -1, 1}};
            s.assign(1, C);
        }
    
        void build(const str& s) {
            this->s.reserve(sz(s) + 1);
            for (ch c : s)
                add(c);
        }
    
        int find_link(int v) const {
            while (s[k - st[v].len - 1] != s[k])
                v = st[v].link;
            re v;
        }
    
        void add(ch c) {
            ++k;
            c -= F;
            s += c;
            int q = find_link(last);
            if (st[q].next[c]) {
                last = st[q].next[c];
                re;
            }
            st.pb(state{vi(C), st[q].len + 2, st[find_link(st[q].link)].next[c]});
            st[q].next[c] = last = sz(st) - 1;
        }
    
        int next(int v, ch c) const {
            re st[v].next[c-F];
        }
    };

    bl is_palindrome(const str& s) {
        int n = sz(s);
        f0r(i,n/2)
            if (s[i] != s[n-i-1])
                re 0;
        re 1;
    }
    
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
    // d.first[i] = k -> substrings [i-j+1; i+j-1] are palindromes of length 2 * j - 1 for all j in [1; k]
    // d.second[i] = k -> substrings [i-j; i+j-1] are palindromes of length 2 * j for all j in [1; k]
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
#endif