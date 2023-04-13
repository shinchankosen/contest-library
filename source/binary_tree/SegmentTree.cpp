struct SegmentTree {
private:
    ll n;
    vector<ll> node;
    ll ID = INF; // min -> INF, max, sum -> 0
    inline ll func(ll a, ll b){return min(a, b);} /////////

public:
    SegmentTree(vector<ll> v) {
        int sz = v.size();
        n = 1; while(n < sz) n *= 2;
        node.resize(2*n-1, ID);
        for(int i=0; i<sz; i++) node[i+n-1] = v[i];
        for(int i=n-2; i>=0; i--) node[i] = func(node[2*i+1], node[2*i+2]);
    }

    void update(ll x, ll val) {
        x += (n - 1);
        node[x] = val;
        while(x > 0) {
            x = (x - 1) / 2;
            node[x] = func(node[2*x+1], node[2*x+2]);
        }
    }

    ll get(ll a, ll b, ll k=0, ll l=0, ll r=-1) {
        if(r < 0) r = n;
        if(r <= a || b <= l) return ID;
        if(a <= l && r <= b) return node[k];

        ll vl = get(a, b, 2*k+1, l, (l+r)/2);
        ll vr = get(a, b, 2*k+2, (l+r)/2, r);
        return func(vl, vr);
    }
};