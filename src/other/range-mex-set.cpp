struct range_mex_set {
    std::set<std::pair<long long, long long>> st;
    range_mex_set() {
        st.insert(make_pair(LLONG_MIN, LLONG_MIN));
        st.insert(make_pair(LLONG_MAX, LLONG_MAX));
    }
    bool contains(long long x) const {
        auto [le, ri] = *(--st.upper_bound(make_pair(x, LLONG_MAX)));
        return le <= x and x < ri;
    }
    void insert(long long le, long long ri) {
        auto itr = --st.lower_bound(make_pair(le, ri));
        if(itr->first <= le and le <= itr->second) {
            le = min(le, itr->first);
            ri = max(ri, itr->second);
            itr = st.erase(itr);
        } else itr ++;
        while(1) {
            if(le <= itr->first and itr->first <= ri) {
                ri = max(ri, itr->second);
                itr = st.erase(itr);
            } else break;
        }
        st.insert(make_pair(le, ri));
    }
    void insert(long long x) {
        insert(x, x + 1);
    }
    long long mex(long long x = 0) {
        auto [le, ri] = *(--st.upper_bound({x, LLONG_MAX}));
        if(le <= x and x < ri) return ri;
        return x;
    }
};