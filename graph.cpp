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
