///////////union-find
/*
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
*/
////////network_flow
/*
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
*/


//////////dijkstra
/*
ll dis[100000];
vector<vector<pair<ll,ll> > > g(100000);
void dijkstra(ll start){
    for(int i=0;i<100000;i++)dis[i]=1e18;
    dis[start]=0;
    multiset<pair<ll,ll> > ms;
    ms.insert(make_pair(0,start));
    pair<ll,ll> p,niko;
    ll maki;
    while(!ms.empty()){
        p=*(ms.begin());
        ms.erase(ms.begin());
        if(dis[p.second]<p.first)continue;
        maki=g[p.second].size();
        for(int i=0;i<maki;i++){
            niko=g[p.second][i];
            if(dis[niko.first]>dis[p.second]+niko.second){
                dis[niko.first]=dis[p.second]+niko.second;
                ms.insert(make_pair(dis[niko.first],niko.first));
            }
        }
    }
    return;
}
*/


//topological sort
/*
typedef vector<int> VI;
VI g[100010];
int h[100010];
  int v, e;
  cin >> v >> e;
  REP(i, e) {
    int s, t;
    cin >> s >> t;
    s--;t--;
    g[s].push_back(t);
    h[t]++;
  }
  stack<int> st;
  REP(i, v) if(h[i] == 0) st.push(i);
  VI ans;
  while(st.size()) {
    int i = st.top(); st.pop();
    ans.push_back(i);
    for(auto& j: g[i]) {
      h[j]--;
      if(h[j] == 0) st.push(j);
    }
  }
  for(int i: ans) cout << i << endl;
*/



/////////bellman_ford
/*{
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
}*/
