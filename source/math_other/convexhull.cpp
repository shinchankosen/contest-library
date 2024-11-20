ll cross(ll x1, ll y1, ll x2, ll y2) {
    return x1 * y2 - x2 * y1;
}
using P = pair<ll, ll>;
vector<P> ConvexHull(vector<P> ps) {
    int n = (int)ps.size();
    if(n <= 2) return ps;
    vector<P> res(2*n);
    sort(all(ps));
    int k = 0;
    for (int i = 0; i < n; ++i) {
        if (k >= 2) {
            while(cross(res[k - 1].first - res[k - 2].first, res[k - 1].second - res[k - 2].second, 
            ps[i].first - res[k - 2].first, ps[i].second - res[k - 2].second) <= 0LL) {
                k --;
                if(k < 2) break;
            }
        }
        res[k] = ps[i]; ++ k;
    }
    int t = k + 1;
    for (int i = n - 2; i >= 0; --i) {
        if (k >= t) {
            while(cross(res[k - 1].first - res[k - 2].first, res[k - 1].second - res[k - 2].second, 
            ps[i].first - res[k - 2].first, ps[i].second - res[k - 2].second) <= 0LL) {
                -- k;
                if (k < t) break;
            }
        }
        res[k] = ps[i]; ++ k;
    }
    res.resize(k-1);
    return res;
}