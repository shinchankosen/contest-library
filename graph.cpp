///////////union-find
struct UnionFind {
    vector<int> par;
    UnionFind(int n) :par(n, -1) { }
    void init(int n) { par.assign(n, -1); }
    int root(int x) {
        if (par[x] < 0) return x;
        else return par[x] = root(par[x]);
    }
    bool connect(int x, int y) {
        x = root(x); y = root(y);
        if (x == y) return false;
        if (par[x] > par[y]) swap(x, y);
        par[x] += par[y];
        par[y] = x;
        return true;
    }
    int size(int x) {
        return -par[root(x)];
    }
};


// Doubling , LCA , dis , Tree
vector<vector<ll> > v;
struct Doubling {
private:
    ll sz;
    vector<vector<ll> > past;
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
    void init(){
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



////////network_flow
template<class FLOWTYPE> struct Edge {
    int rev, from, to;
    FLOWTYPE cap, icap;
    Edge(int r, int f, int t, FLOWTYPE c) : rev(r), from(f), to(t), cap(c), icap(c) {}
    friend ostream& operator << (ostream& s, const Edge& E) {
        if (E.cap > 0) return s << E.from << "->" << E.to << '(' << E.cap << ')';
        else return s;
    }
};

// graph class (for network-flow)
template<class FLOWTYPE> struct Graph {
    vector<vector<Edge<FLOWTYPE> > > list;
    
    Graph(int n = 0) : list(n) { }
    void init(int n = 0) { list.clear(); list.resize(n); }
    void reset() { for (int i = 0; i < (int)list.size(); ++i) for (int j = 0; j < list[i].size(); ++j) list[i][j].cap = list[i][j].icap; }
    inline vector<Edge<FLOWTYPE> >& operator [] (int i) { return list[i]; }
    inline const size_t size() const { return list.size(); }
    
    inline Edge<FLOWTYPE> &redge(Edge<FLOWTYPE> e) {
        if (e.from != e.to) return list[e.to][e.rev];
        else return list[e.to][e.rev + 1];
    }
    
    void addedge(int from, int to, FLOWTYPE cap) {
        list[from].push_back(Edge<FLOWTYPE>((int)list[to].size(), from, to, cap));
        list[to].push_back(Edge<FLOWTYPE>((int)list[from].size() - 1, to, from, 0));
    }
    
    void add_undirected_edge(int from, int to, FLOWTYPE cap) {
        list[from].push_back(Edge<FLOWTYPE>((int)list[to].size(), from, to, cap));
        list[to].push_back(Edge<FLOWTYPE>((int)list[from].size() - 1, to, from, cap));
    }
};

template<class FLOWTYPE> struct Dinic {
    const FLOWTYPE INF = 1<<30; // to be set
    vector<int> level, iter;

    Dinic() { }
    void dibfs(Graph<FLOWTYPE> &G, int s) {
        level.assign((int)G.size(), -1);
        level[s] = 0;
        queue<int> que;
        que.push(s);
        while (!que.empty()) {
            int v = que.front();
            que.pop();
            for (int i = 0; i < G[v].size(); ++i) {
                Edge<FLOWTYPE> &e = G[v][i];
                if (level[e.to] < 0 && e.cap > 0) {
                    level[e.to] = level[v] + 1;
                    que.push(e.to);
                }
            }
        }
    }
    
    FLOWTYPE didfs(Graph<FLOWTYPE> &G, int v, int t, FLOWTYPE f) {
        if (v == t) return f;
        for (int &i = iter[v]; i < G[v].size(); ++i) {
            Edge<FLOWTYPE> &e = G[v][i], &re = G.redge(e);
            if (level[v] < level[e.to] && e.cap > 0) {
                FLOWTYPE d = didfs(G, e.to, t, min(f, e.cap));
                if (d > 0) {
                    e.cap -= d;
                    re.cap += d;
                    return d;
                }
            }
        }
        return 0;
    }
    
    FLOWTYPE solve(Graph<FLOWTYPE> &G, int s, int t) {
        level.assign((int)G.size(), -1); iter.assign((int)G.size(), 0);
        FLOWTYPE res = 0;
        while (true) {
            dibfs(G, s);
            if (level[t] < 0) return res;
            for (int i = 0; i < (int)iter.size(); ++i) iter[i] = 0;
            FLOWTYPE flow = 0;
            while ((flow = didfs(G, s, t, INF)) > 0) {
                res += flow;
            }
        }
    }
};

Graph<int> G(n);
G.addedge(s,t,cap);
Dinic<int> di;
di.solve(G,s,t);



// Dijkstra 
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



//topological sort
{
    ll n, m, a, b;
    vector<ll> g[n];
    vector<int> h(n, 0);
    stack<int> st;
    vector<int> ans;

    for(int i=0;i<m;i++){
        cin >> a >> b;
        a--, b--;
        g[a].pb(b);
        h[b]++;
    }
    for(int i=0;i<n;i++) if(h[i] == 0) st.push(i);
    while(!st.empty()) {
        int i = st.top(); st.pop();
        ans.pb(i);
        for(auto& j : g[i]) {
            h[j]--;
            if(h[j] == 0) st.push(j);
        }
    }
    for(int i: ans) cout << i << endl;
}


/////////bellman_ford
{
    ll d[n];bool maki;
    struct edge{ll from,to,cost;};
    vector<edge> g;
    for(int i=0;i<n;i++)d[i]=INF;d[0]=0;
    for(int i=0;i<m;i++){
        cin>>a>>b>>c;
        g.push_back({a,b,c});
    }
    for(int i=0;i<n;i++){
        maki=false;
        for(int j=0;j<m;j++){
            if(d[g[j].from]!=INF&&d[g[j].to]>d[g[j].from]+g[j].cost){
                d[g[j].to]=d[g[j].from]+g[j].cost;
                maki=true;
            }
        }
    }
}

//////強連結成分分解
class SCC{
private:
    vector<vector<int> > gg, rg;
    vector<int> order, comp;
    vector<bool> used;
    vector<vector<int> > ng, vs;

    int n, nn;
public:
    SCC(){}
    SCC(int v) : gg(v), rg(v), comp(v, -1), used(v, 0), n(v){}

    void add_edge(int x, int y){
        gg[x].push_back(y);
        rg[y].push_back(x);
    }
    int operator[](int k){return comp[k];}
    void dfs(int v){
        used[v] = true;
        for(auto i: gg[v]) if(!used[i]) dfs(i);
        order.push_back(v);
    }

    void rdfs(int v, int k){
        used[v] = true;
        comp[v] = k;
        for(auto i: rg[v]) if(!used[i]) rdfs(i, k);
    }

    int build(){
        for(int i=0;i<n;i++) if(!used[i]) dfs(i);
        fill(be(used), 0);
        int k = 0;
        for(int i = order.size()-1;i >= 0;i--){
            if(!used[order[i]]) rdfs(order[i], k++);
        }
        nn = k;

        //---------それぞれの強連結成分に含まれる頂点の番号----------
        vs.resize(k, vector<int>());
        for(int i=0;i<n;i++) vs[comp[i]].push_back(i);
        //---------強連結成分をまとめた後のGraph----------------
        ng.resize(k, vector<int>());
        for(int i=0;i<n;i++) for(auto j: gg[i]){
            if(comp[i] != comp[j]) ng[comp[i]].push_back(comp[j]);
        }
        for(int i=0;i<nn;i++){
            sort(be(ng[i]));
            ng[i].erase(unique(be(ng[i])), ng[i].end());
        }
        return k;
    }
    int size(){return nn;}
    vector<vector<int> > graph(){return ng;}
    vector<int> vertices(int v){return vs[v];}
};
