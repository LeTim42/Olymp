#ifndef BITSET_HPP
#define BITSET_HPP
#include "main.hpp"

// Custom bitset
class Bitset {
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

    Bitset& resize(size_t _n) {
        n = _n;
        r = n & 63;
        m = (n >> 6) + (r != 0);
        if (!r) r = 64;
        extra = ~0ull >> (64-r);
        a.resize(m,0);
        if (m) a[m-1] &= extra;
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
        rep(i,b.m,m) a[i] = 0;
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
#endif