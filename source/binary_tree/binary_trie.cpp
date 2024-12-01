using ar = array<int, 3>;
ar base = {-1, -1, 0};
template <class T> struct Btrie {
    vector<ar> vec;
    int lim;
    Btrie(int lim_ = 30) : vec(1, base), lim(lim_) {}
    void add(T x) {
        int cur = 0;
        for(int i = lim - 1; i >= 0; i --) {
            vec[cur][2] ++;
            if(x >> i & 1) {
                if(vec[cur][1] == -1) {
                    vec[cur][1] = vec.size();
                    vec.pb(base);
                }
                cur = vec[cur][1];
            } else {
                if(vec[cur][0] == -1) {
                    vec[cur][0] = vec.size();
                    vec.pb(base);
                }
                cur = vec[cur][0];
            }
        }
        vec[cur][2] ++;
    }
};
