#ifndef GEOM_HPP
#define GEOM_HPP
#include "main.hpp"

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

        friend opin(F,f) { re in >> f.x; }
        friend opout(F,f) { re out << f.x; }
        friend F sqrt(const F& f) { re F(sqrt(f.x)); }

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
        template<class F1> Point(const Point<F1>& p) : x(p.x), y(p.y) {}
        
        template<class F1> Point<F>& operator=(const Point<F1>& other) { x = other.x; y = other.y; re *this; }
        template<class F1> Point<F>& operator+=(const Point<F1>& other) { x += other.x; y += other.y; re *this; }
        template<class F1> Point<F>& operator-=(const Point<F1>& other) { x -= other.x; y -= other.y; re *this; }
        template<class F1> Point<F>& operator*=(const F1& factor) { x *= factor; y *= factor; re *this; }
        template<class F1> Point<F>& operator/=(const F1& factor) { x /= factor; y /= factor; re *this; }

        friend opin(Point<F>,p) { re in >> p.x >> p.y; }
        friend opout(Point<F>,p) { re out << p.x << ' ' << p.y; }
    };

    #define DONT_CLEAN
    #define FUNC1(name, arg, expr) template<class F> inline auto name(const arg) -> decltype(expr) { re expr; }
    #define FUNC2(name, arg1, arg2, expr) template<class F1, class F2> inline auto name(const arg1, const arg2) -> decltype(expr) { re expr; }
    #define FUNC3(name, arg1, arg2, arg3, expr) template<class F1, class F2, class F3> inline auto name(const arg1, const arg2, const arg3) -> decltype(expr) { re expr; }
    
    template<class F> inline Point<F> make_point(const F& x, const F& y) { re Point<F>(x, y); }

    FUNC1(operator-, Point<F>& point, make_point(-point.x, -point.y))
    FUNC2(operator+, Point<F1>& lhs, Point<F2>& rhs, make_point(lhs.x + rhs.x, lhs.y + rhs.y))
    FUNC2(operator-, Point<F1>& lhs, Point<F2>& rhs, make_point(lhs.x - rhs.x, lhs.y - rhs.y))
    FUNC2(operator*, F1& factor, Point<F2>& rhs, make_point(F2(factor) * rhs.x, F2(factor) * rhs.y))
    FUNC2(operator*, Point<F1>& lhs, F2& factor, make_point(lhs.x * F1(factor), lhs.y * F1(factor)))
    FUNC2(operator/, Point<F1>& lhs, F2& factor, make_point(lhs.x / F1(factor), lhs.y / F1(factor)))
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
        template<class F1> Line(const Line<F1>& l) : a(l.a), ab(l.ab), t(l.t) {}

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
        res += Point<F3>(l.ab) * (F3(s) / sqn(l.ab));
    }

    // reflection of point p around line l
    template<class F1, class F2, class F3>
    void reflection(const Point<F1>& p, const Line<F2>& l, Point<F3>& res) {
        projection(p, l, res);
        res = res * 2 - p;
    }

    template<class F1, class F2>
    bl circumcenter(const Point<F1>& a, const Point<F1>& b, const Point<F1>& c, Point<F2>& res) {
        Point<F2> A = Point<F2>(a + b) / 2;
        Point<F2> B = A + perp(A - a);
        Point<F2> C = Point<F2>(a + c) / 2;
        Point<F2> D = C + perp(C - a);
        F2 denom = (B - A) ^ (D - C);
        if (denom == F2()) re 0;
        res = A + (B - A) * (((C - A) ^ (D - C)) / denom);
        re 1;
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

    // intersection of two circles with centers at points c0 and c1 and radii r0 and r1 respectively
    template<class F1, class F2, class F3>
    V<Point<F1>> intersect(const Point<F2>& c0, const F2& r0, const Point<F3>& c1, const F3& r1) {
        auto d2 = dist2(c0, c1);
        if (d2 > sq(r0 + r1) || d2 < sq(r0 - r1) || (d2 == decltype(d2)() && r0 == r1)) re {};
        F1 d = sqrt(d2);
        F1 a = (sq(r0) - sq(r1) + d2) / F1(d * 2);
        Point<F1> m = Point<F1>(c1 - c0) * (a / d) + c0;
        if (d2 == sq(r0 + r1)) re {m};
        Point<F1> v = perp(c1 - c0);
        F1 h = sqrt(sq(r0) - sq(a));
        v *= h / d;
        re {m - v, m + v};
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
#endif