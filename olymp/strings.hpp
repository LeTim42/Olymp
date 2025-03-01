#ifndef STRINGS_HPP
#define STRINGS_HPP
#include "main.hpp"

// Work with strings
namespace strings {
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
    
    class Eertree {
    private:
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