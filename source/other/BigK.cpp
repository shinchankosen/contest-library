template<class T> struct BigK {
    int k, n;
    T sum_big, sum_sml;
    std::vector<T> v;
    std::multiset<T> ms_big, ms_sml;

    constexpr BigK(std::vector<T> v_, int k) noexcept : k(k), n(v_.size()), v(v_) {
        sum_big = 0, sum_sml = 0;
        sort(v_.begin(), v_.end(), [&](T i, T j) {return i > j;});
        for(int i = 0; i < k; i ++) {
            sum_big += v_[i];
            ms_big.insert(v_[i]);
        }
        for(int i = k; i < n; i ++) {
            sum_sml += v_[i];
            ms_sml.insert(v_[i]);
        }
    }

    // a[x] = y
    constexpr void update(int x, T y) noexcept {
        if(ms_big.find(v[x]) == ms_big.end()) {
            auto itr = ms_sml.lower_bound(v[x]);
            sum_sml -= *itr;
            ms_sml.erase(itr);
            ms_sml.insert(y);
            sum_sml += y;
        } else {
            auto itr = ms_big.lower_bound(v[x]);
            sum_big -= *itr;
            ms_big.erase(itr);
            ms_big.insert(y);
            sum_big += y;
        }
        v[x] = y;
        if(!ms_big.empty() and !ms_sml.empty() and *ms_big.begin() < *ms_sml.rbegin()) {
            auto itr1 = ms_big.begin();
            auto itr2 = --ms_sml.end();
            sum_big += *itr2 - *itr1;
            sum_sml += *itr1 - *itr2;
            ms_big.insert(*itr2);
            ms_sml.insert(*itr1);
            ms_sml.erase(itr2);
            ms_big.erase(itr1);
        }
        return;
    }

    // 大きい順で i 番目 (1-indexed)
    constexpr T k_num(int i) {
        if(i == k) return *ms_big.begin();
        if(i == k + 1) return *ms_sml.rbegin();
        if(i <= k) {
            if(i == 1) return *ms_big.rbegin();
            if(i == n) return *ms_big.begin();
        } else {
            if(i == 1) return *ms_sml.rbegin();
            if(i == n) return *ms_sml.begin();
        }
        assert(0);
    };
    constexpr T big_sum() noexcept {
        return sum_big;
    }
    constexpr T small_sum() noexcept {
        return sum_sml;
    }
};