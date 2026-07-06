template<class T>
struct Rui {
    int dim;
    vector<int> sz, pw;
    vector<T> dat;
    
    Rui(const vector<int> _sz) {
        sz = _sz;
        dim = sz.size();
        pw.resize(dim + 1);
        pw[0] = 1;
        for(int i = 0; i < dim; i ++) pw[i + 1] = pw[i] * sz[i];
        dat.assign(pw[dim], T());
    }

    template<class... Args>
    Rui(Args... args) : Rui(vector<int>{args...}) {}
    
    int index(const vector<int> &a) const {
        assert((int)a.size() == dim);
        int id = 0;
        for(int i = 0; i < dim; i ++) {
            assert(0 <= a[i] and a[i] < sz[i]);
            id += a[i] * pw[i];
        }
        return id;
    }

    template<class... Args>
    int index(Args... args) const {
        static_assert(sizeof...(Args) >= 1);
        assert((int)sizeof...(Args) == dim);
        return index(vector<int>{args...});
    }

    template<class... Args>
    T& at(const vector<int> &a) {
        return dat[index(a)];
    }

    template<class... Args>
    T& at(Args... args) {
        return dat[index(args...)];
    }

    void build() {
        int n = pw[dim];
        for(int d = 0; d < dim; d ++) {
            for(int i = 0; i < n; i ++) {
                int j = i + pw[d];
                if(j / pw[d + 1] == i / pw[d + 1]) {
                    dat[j] += dat[i];
                }
            }
        }
    }

    T query(const vector<int> &a) const {
        assert((int)a.size() == dim * 2);
        vector<int> b = a;
        for(int d = 0; d < dim; d ++) {
            if(b[2 * d] >= b[2 * d + 1]) return T();
            b[2 * d] --;
            b[2 * d + 1] --;
        }

        T ret = T();
        for(int bit = 0; bit < (1 << dim); bit ++) {
            int id = 0, sign = 1;
            for(int d = 0; d < dim; d ++) {
                int x;
                if(bit >> d & 1) {
                    x = b[2 * d];
                    sign = -sign;
                } else {
                    x = b[2 * d + 1];
                }
                assert(-1 <= x and x < sz[d]);
                if(x == -1) id = pw[dim];
                else id += x * pw[d];
            }
            if(id < pw[dim]) ret += dat[id] * sign;
        }
        return ret;
    }

    template<class... Args>
    T query(Args... args) const {
        static_assert(sizeof...(Args) % 2 == 0);
        assert((int)sizeof...(Args) == dim * 2);
        return query(vector<int>{args...});
    }
};