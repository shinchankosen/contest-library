template <typename T>
vector<ll> dijkstra(T &G, int start){
    // T -> vector<vector<pair<ll, int or ll>>> 
    // edge pair<ll, ll> -> pair<cost, to>
    using P = pair<ll, int>;
    int n = G.size();
    vector<ll> dis(n, INF);
    dis[start] = 0;
    priority_queue<P, vector<P>, greater<P> > Q;
    Q.push({0, start});
    while(!Q.empty()){
        P p = Q.top();
        Q.pop();
        int cur = p.second;
        if(dis[cur] < p.first) continue;
        for(auto e : G[cur]) {
            if(dis[e.second] > dis[cur] + e.first) {
                dis[e.second] = dis[cur] + e.first;
                Q.push({dis[e.second], e.second});
            }
        }
    }
    return dis;
}
