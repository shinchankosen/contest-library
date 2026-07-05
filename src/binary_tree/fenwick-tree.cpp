template <class T> struct BIT {
    int n;
    vector<T> a;
    BIT(int m) : n(m), a(m + 1, 0) {}
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
    int upper_bound(T w) {
        int x = 0;
        for(int i = (1 << __lg(n)); i; i >>= 1) {
            if(x + i <= n) {
                if(a[x + i] <= w) {
                    w -= a[x + i];
                    x += i;
                }
            }
        }
        return x;
    }  
};