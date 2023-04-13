struct Doubling {
private:
    ll sz;
    vector<vector<ll> > past;
    vector<vector<ll>> v;
    vector<ll> dis;
    void dfs(int now, int p = -1){
        past[now][0] = p;
        for(auto& to:v[now]){
            if(to == p)continue;
            dis[to] = dis[now] + 1;
            dfs(to, now);
        }
    }
public:
    // これを初めにやる
    void init(vector<vector<ll>> v1){
        v = v1;
        sz = v.size();
        dis.resize(sz); dis[0] = 0;
        past.resize(sz, vector<ll> (20, -1));
        dfs(0);
        for(int j=0;j<19;j++)for(int i=0;i<sz;i++){
            if(past[i][j] != -1) past[i][j+1] = past[past[i][j]][j];
        }
    }
    // nowのm個前
    ll par(ll now, ll m){
        for(int i=0,j=1;j<=m;i++,j*=2) if(m&j) now = past[now][i];
        return now;
    }
    // a, bの最小共通祖先
    ll lca(ll a,ll b){
        if(dis[a] < dis[b]) b = par(b, dis[b] - dis[a]);
        else if(dis[a] > dis[b]) a = par(a, dis[a] - dis[b]);
        ll le = -1, ri = dis[a], mid;
        while(ri - le > 1){
            mid = (ri + le) / 2;
            if(par(a,mid) == par(b,mid)) ri = mid;
            else le = mid;
        }
        return par(a, ri);
    }
    // a, bの距離
    ll dist(ll a, ll b){return dis[a] + dis[b] - dis[lca(a,b)] * 2;}
} d;