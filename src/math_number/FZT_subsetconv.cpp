template <typename T> void fzt(vector<T>& f) {
    int n = f.size();
    for (int i = 1; i < n; i <<= 1) {
        for (int j = 0; j < n; j ++) {
            if ((j & i) == 0) f[j | i] += f[j];
        }
    }
}
template <typename T> void ifzt(vector<T>& f) {
    int n = f.size();
    for (int i = 1; i < n; i <<= 1) {
        for (int j = 0; j < n; j ++) {
            if ((j & i) == 0) f[j | i] -= f[j];
        }
    }
}

template<typename T> vector<T> subset_conv(vector<T> a, vector<T> b) {
    int m = a.size();
    int n = 0;
    while((1 << n) < m) n ++;
    vector A(n + 1, vector(m, T(0))), B(n + 1, vector(m, T(0)));
    for(int i = 0; i < m; i ++) {
        A[__builtin_popcount(i)][i] += a[i];
        B[__builtin_popcount(i)][i] += b[i];
    }
    for(int i = 0; i <= n; i ++) {
        fzt(A[i]); fzt(B[i]);
    }
    vector C(n + 1, vector(m, T(0)));
    for(int i = 0; i <= n; i ++) {
        for(int j = 0; i + j <= n; j ++) {
            for(int bit = 0; bit < m; bit ++) {
                C[i + j][bit] += A[i][bit] * B[j][bit];
            }
        }
    }
    for(int i = 0; i <= n; i ++) ifzt(C[i]);
    vector<T> ret(m);
    for(int i = 0; i < m; i ++) ret[i] = C[__builtin_popcount(i)][i];
    return ret;
}