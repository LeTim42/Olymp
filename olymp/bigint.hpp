#ifndef BIGINT_HPP
#define BIGINT_HPP
#include "main.hpp"
#include "other.hpp"

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
        re sz(nums) > 1 || (sign == 1 && nums[0] != x) || (sign == -1 && nums[0] != -ul(x)) || (!sign && x);
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
#endif