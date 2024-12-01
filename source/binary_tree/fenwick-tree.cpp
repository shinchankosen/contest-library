template <class T> struct BIT {
    int n;
    vector<T> a;
    void add(int x, T y) {
        x ++;
        while(x <= n) {
            a[x] += y;
            x += x & -x;
        }
    }
    T sum(int x) {
        T r = 0;
        while(x > 0) {
            r += a[x];
            x -= x & -x;
        }
        return r;
    }
    T sum(int x, int y) {
        return sum(y) - sum(x);
    }
};