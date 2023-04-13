// 牛ゲー 負辺がなければdijkstraに依存
vector<ll> USHI(ll n, vector<tuple<ll, ll, ll>> edges, ll s) {
    // v : x_i - x_j <= M
    vector<vector<pair<ll, ll>>> G(n);
    bool minus = 0;
    for(auto [i, j, M] : edges) {
        G[j].push_back({M, i});
        if(M < 0) minus = 1;
    }
    if(!minus) { // 負辺がない場合
        return dijkstra(G, s);
    }

    vector<ll> dist(n, INF);
    dist[s] = 0;

    bool update = 1;
    rep(_, n) {
        update = 0;
        rep(i, n) {
            for(auto [d, node]: G[i]) {
                if(dist[i] + d < dist[node]) {
                    dist[node] = dist[i] + d;
                    update = 1;
                }
            }
        }
        if(!update) break;
    }
    return dist;
}