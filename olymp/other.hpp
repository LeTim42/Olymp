#ifndef OTHER_HPP
#define OTHER_HPP
#include "main.hpp"

namespace other {
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
}
#endif