template<class T> std::vector<T> transpose(const std::vector<T> &v) {
    int n = v.size();
    if(n == 0) return v;
    int m = v[0].size();
    std::vector<T> ret(m);
    for(int i = 0; i < m; i ++) {
        ret[i].resize(n);
        for(int j = 0; j < n; j ++) ret[i][j] = v[j][i];
    }
    return ret;
}

template<class T> std::vector<T> rev_lr(std::vector<T> v) {
    int n = v.size();
    for(int i = 0; i < n; i ++) reverse(v[i].begin(), v[i].end());
    return v;
}

template<class T> std::vector<T> rev_ud(std::vector<T> v) {
    reverse(v.begin(), v.end());
    return v;
}

template<class T> std::vector<T> rotate(const std::vector<T> &v, int k) {
    k %= 4;
    if(k == 0) return v;
    if(k < 0) k += 4;
    if(k == 2) return rev_lr(rev_ud(v));
    int n = v.size(); if(n == 0) return v;
    int m = v[0].size();
    std::vector<T> ret(m);
    if(k == 1) {
        for(int i = 0; i < m; i ++) {
            ret[i].resize(n);
            for(int j = 0; j < n; j ++) ret[i][j] = v[n - j - 1][i];
        }
    } else {
        for(int i = 0; i < m; i ++) {
            ret[i].resize(n);
            for(int j = 0; j < n; j ++) ret[i][j] = v[j][m - i - 1];
        }
    }
    return ret;
}

constexpr int safe_mod(int x, int m) noexcept {
    x %= m;
    if (x < 0) x += m;
    return x;
}

template<class T> std::vector<T> shift(std::vector<T> v, int dy, int dx) {
    int n = v.size();
    if(n == 0) return v;
    int m = v[0].size();
    std::vector<T> ret = v;
    for(int i = 0; i < n; i ++) {
        for(int j = 0; j < m; j ++) {
            ret[safe_mod(i + dy, n)][safe_mod(j + dx, m)] = v[i][j];
        }
    }
    return ret;
}

template<class T> std::vector<T> shift_l(std::vector<T> v, int k) { return shift(v, 0, -k); }
template<class T> std::vector<T> shift_r(std::vector<T> v, int k) { return shift(v, 0, k); }
template<class T> std::vector<T> shift_u(std::vector<T> v, int k) { return shift(v, -k, 0); }
template<class T> std::vector<T> shift_d(std::vector<T> v, int k) { return shift(v, k, 0); }
