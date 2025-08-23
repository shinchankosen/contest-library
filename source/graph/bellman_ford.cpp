//bellman_ford
template <typename T>
std::vector<long long> bellman_ford(T &G, int start, int lim = -1){
    // T -> vector<vector<pair<ll, int or ll>>> 
    // edge pair<ll, ll> -> pair<cost, to>
    int n = G.size();
    std::vector<long long> dis(n, INF);
    dis[start] = 0;
    
    bool update = 1;
    if(lim == -1) lim = n;

    for(int i = 0; i < lim; i ++) {// 2N 回やると検出とか楽
        update = 0;
        for(int j = 0; j < n; j ++) {
            for(auto [cost, to] : G[j]) {
                if(dis[j] + cost < dis[to]) {
                    dis[to] = dis[j] + cost;
                    update = 1;
                }
            }
        }
        if(!update) break;
    }
    return dis; 
}
