#ifndef RATIONAL_HPP
#define RATIONAL_HPP
#include "main.hpp"

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

public:
    Rational() : n(0), d(1) {}
    template<class T1> Rational(const T1& n) : n(n), d(1) {}
    template<class T1> Rational(const T1& n, const T1& d) : n(n), d(d) { reduce(); }
    template<class T1> Rational(const Rational<T1>& other) : n(other.n), d(other.d) {}

    T numerator() const { re n; }
    T denominator() const { re d; }

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

    fl to_fl() const { re stof(to_str(numeric_limits<fl>::digits10 + 1)); }
    db to_db() const { re stod(to_str(numeric_limits<db>::digits10 + 1)); }
    ld to_ld() const { re stold(to_str(numeric_limits<ld>::digits10 + 1)); }

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
#endif