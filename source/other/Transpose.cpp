template<class T> vector<T> Transpose(const vector<T> &v) {
    int n = v.size(), m = v[0].size();
    vector<T> ret(m);
    for(int i = 0; i < m; i ++) {
        ret[i].resize(n);
        for(int j = 0; j < n; j ++) {
            ret[i][j] = v[j][i];
        }
    }
    return ret;
}
