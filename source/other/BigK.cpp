template<class T> struct BigK {
    int k; // size
    T sum_big, sum_sml;
    std::multiset<T> ms_big, ms_sml;

    BigK(std::vector<T> v, int k) noexcept : k(k) {
        sum_big = 0, sum_sml = 0;
        std::sort(v.begin(), v.end());
        int n = v.size();
        for(int i = 0; i < n - k; i ++) {
            sum_sml += v[i];
            ms_sml.insert(v[i]);
        }
        for(int i = n - k; i < n; i ++) {
            sum_big += v[i];
            ms_big.insert(v[i]);
        }
    }
    BigK(int k = -1) noexcept : k(k) {
        sum_big = 0, sum_sml = 0;
    }
    void fit(size_t sz) {
        while(ms_big.size() < sz) {
            auto itr = prev(ms_sml.end());
            sum_big += *itr;
            ms_big.insert(*itr);
            sum_sml -= *itr;
            ms_sml.erase(itr);
        }
        while(ms_big.size() > sz) {
            auto itr = ms_big.begin();
            sum_sml += *itr;
            ms_sml.insert(*itr);
            sum_big -= *itr;
            ms_big.erase(itr);
        }
        if(ms_sml.empty() or ms_big.empty()) return;
        while(*prev(ms_sml.end()) > *ms_big.begin()) {
            auto itr1 = prev(ms_sml.end());
            sum_sml -= *itr1;
            ms_big.insert(*itr1);
            sum_big += *itr1;
            ms_sml.erase(itr1);
            auto itr2 = ms_big.begin();
            sum_sml += *itr2;
            ms_sml.insert(*itr2);
            sum_big -= *itr2;
            ms_big.erase(itr2);
        }
    }
    void insert(T y, int sz = -1) {
        ms_big.insert(y);
        sum_big += y;
        sz = std::max(sz, k);
        if(sz >= 0) fit(sz);
        return;
    }
    void erase(T y, int sz = -1) {
        if(ms_big.find(y) != ms_big.end()) {
            ms_big.erase(ms_big.find(y));
            sum_big -= y;
        } else {
            ms_sml.erase(ms_sml.find(y));
            sum_sml -= y;
        }
        sz = std::max(sz, k);
        if(sz >= 0) fit(sz);
        return;
    }
};