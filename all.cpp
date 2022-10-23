ll ftoll(string s, ll dig){
    ll m = s.length(), id = -1;
    rep(i, m) if(s[i] == '.') id = i;
    if(id == -1) s += string(dig, '0');
    else{
        s = s.substr(0, id) + s.substr(id + 1, m - id - 1);
        s += string(dig + 1 - m + id, '0');
    }
    return stoll(s);
}


////lambda
auto f = [&](auto&& f,int x) -> int{return x;};



struct node{
    int x,y;
    // 最後のconstを忘れると"instantiated from here"というエラーが出てコンパイルできないので注意
    bool operator<( const node& right ) const {
        return x == right.x ? y < right.y : x < right.x;
    }
    node& operator+=(const node& v) { x += v.x; return *this;}
    node operator+(const node& v) const { return node(*this) += v;}
    int inner(const node& right) const { return x*right.x + y*right.y;}
};


istream& operator>>(istream& is, node& v) {
  is >> v.x >> v.y; return is;
}

/////3変数構造体
struct node{
    int x,y,z;
    bool operator<( const node& right ) const {
        if(x == right.x){
            if(y == right.y) return z < right.z;
            else return y < right.y;
        }else return x < right.x;
    }
};


////第3引数sort
bool judge( const node& left, const node& right ) {
    return left.x == right.x ? left.y < right.y : left.x < right.x;
}


long long floor_sum(long long n, long long m, long long a, long long b) {
    long long ans = 0;
    if (a >= m) {
        ans += (n - 1) * n * (a / m) / 2;
        a %= m;
    }
    if (b >= m) {
        ans += n * (b / m);
        b %= m;
    }

    long long y_max = (a * n + b) / m, x_max = (y_max * m - b);
    if (y_max == 0) return ans;
    ans += (n - (x_max + a - 1) / a) * y_max;
    ans += floor_sum(y_max, a, m, (a - x_max % a) % a);
    return ans;
}




{
//Z-algorithm
    vector<int> Z(S.size());
    Z[0] = S.size();
    int i = 1, j = 0;
    while(i < S.size()){
        while(i + j < S.size() && S[j] == S[i + j]) j++;
        Z[i] = j;
        if(j == 0) { i++; continue; }
        int k = 1;
        while(i + k < S.size() && k + Z[k] < j){
            Z[i + k] = Z[k];
            k++;
        }
        i += k; j -= k;
    }
}



//// RollingHash
struct RollingHash {
    static const int base1 = 1007, base2 = 2009;
    static const int mod1 = 1000000007, mod2 = 1000000009;
    vector<long long> hash1, hash2, power1, power2;
 
    // construct
    RollingHash(const string &S) {
        int n = (int)S.size();
        hash1.assign(n+1, 0);
        hash2.assign(n+1, 0);
        power1.assign(n+1, 1);
        power2.assign(n+1, 1);
        for (int i = 0; i < n; ++i) {
            hash1[i+1] = (hash1[i] * base1 + S[i]) % mod1;
            hash2[i+1] = (hash2[i] * base2 + S[i]) % mod2;
            power1[i+1] = (power1[i] * base1) % mod1;
            power2[i+1] = (power2[i] * base2) % mod2;
        }
    }
    
    // get hash of S[left:right)
    inline pair<long long, long long> get(int l, int r) const {
        long long res1 = hash1[r] - hash1[l] * power1[r-l] % mod1;
        if (res1 < 0) res1 += mod1;
        long long res2 = hash2[r] - hash2[l] * power2[r-l] % mod2;
        if (res2 < 0) res2 += mod2;
        return {res1, res2};
    }
 
    // get lcp of S[a:) and T[b:)
    inline int getLCP(int a, int b) const {
        int len = min((int)hash1.size()-a, (int)hash1.size()-b);
        int low = -1, high = len;
        while (high - low > 1) {
            int mid = (low + high) / 2;
            if (get(a, a+mid) != get(b, b+mid)) high = mid;
            else low = mid;
        }
        return low;
    }
};






///////Matrix
template<class T> struct Matrix {
    vector<vector<T> > val;
    //　縦, 横, 初期値
    Matrix(int n = 1, int m = 1, T v = 0) : val(n, vector<T>(m, v)) {}
    void init(int n, int m, T v = 0) {val.assign(n, vector<T>(m, v));}
    Matrix<T>& operator = (const Matrix<T> &A) {
        val = A.val; return *this;
    }
    size_t size() const {return val.size();}
    vector<T>& operator [] (int i) {return val[i];}
    const vector<T>& operator [] (int i) const {return val[i];}
    friend ostream& operator << (ostream& s, const Matrix<T>& M) {
        s << endl;
        for (int i = 0; i < (int)M.size(); ++i) s << M[i] << endl;
        return s;
    }
};

template<class T> Matrix<T> operator * (const Matrix<T> &A, const Matrix<T> &B) {
    Matrix<T> R(A.size(), B[0].size());
    for (int i = 0; i < A.size(); ++i)
        for (int j = 0; j < B[0].size(); ++j)
            for (int k = 0; k < B.size(); ++k)
                R[i][j] += A[i][k] * B[k][j];
    return R;
}

template<class T> Matrix<T> pow(const Matrix<T> &A, long long n) {
    Matrix<T> R(A.size(), A.size());
    auto B = A;
    for (int i = 0; i < A.size(); ++i) R[i][i] = 1;
    while (n > 0) {
        if (n & 1) R = R * B;
        B = B * B;
        n >>= 1;
    }
    return R;
}

template<class T> vector<T> operator * (const Matrix<T> &A, const vector<T> &B) {
    vector<T> v(A.size());
    for (int i = 0; i < A.size(); ++i)
        for (int k = 0; k < B.size(); ++k)
            v[i] += A[i][k] * B[k];
    return v;
}

template<class T> Matrix<T> operator + (const Matrix<T> &A, const Matrix<T> &B) {
    Matrix<T> R(A.size(), A[0].size());
    for (int i = 0; i < A.size(); ++i)
        for (int j = 0; j < A[0].size(); ++j)
            R[i][j] = A[i][j] + B[i][j];
    return R;
}

template<class T> Matrix<T> operator - (const Matrix<T> &A, const Matrix<T> &B) {
    Matrix<T> R(A.size(), A[0].size());
    for (int i = 0; i < A.size(); ++i)
        for (int j = 0; j < A[0].size(); ++j)
            R[i][j] = A[i][j] - B[i][j];
    return R;
}





////extEuclid
long long extGCD(long long a, long long b, long long &x, long long &y) {
    if (b == 0) {
        x = 1;
        y = 0;
        return a;
    }
    long long d = extGCD(b, a%b, y, x);
    y -= a/b * x;
    return d;
}





//////negative vector
struct nev{
private:
    ll a;
    vector<ll> v;
public:
    nev(ll a, ll n = 0):a(a), v(n, 0){}
    void resize(int m) {v.resize(m);}
    void push_back(ll n) {v.push_back(n);}
    size_t size() const {return v.size();}
    ll& operator [] (int i) {return v[i - a];}
};


// Fraction
struct Fraction {
    long long x, y;
    void reduc() {
        if(y < 0) y = -y, x = -x;
        long long g = abs(__gcd(x, y));
        x /= g; y /= g;
    }
    Fraction(long long x=0, long long y=1): x(x), y(y) {reduc();}
    bool operator<( const Fraction& right ) const { return x*right.y < y*right.x; }
    bool operator>( const Fraction& right ) const { return x*right.y > y*right.x; }
    bool operator==( const Fraction& right ) const { return x == right.x && y == right.y; }
    Fraction operator-() const {return Fraction(-x, y);}
    Fraction& operator+=(const Fraction& v) { 
        x = x*v.y + y*v.x;
        y *= v.y;
        reduc();
        return *this;
    }
    Fraction operator+(const Fraction& v) const { return Fraction(*this) += v;}
    Fraction& operator-=(const Fraction& v) { 
        x = x*v.y - y*v.x;
        y *= v.y;
        reduc();
        return *this;
    }
    Fraction operator-(const Fraction& v) const { return Fraction(*this) -= v;}
    Fraction& operator*=(const Fraction& v) { 
        x *= v.x;
        y *= v.y;
        reduc();
        return *this;
    }
    Fraction operator*(const Fraction& v) const { return Fraction(*this) *= v;}
    Fraction& operator/=(const Fraction& v) { 
        x *= v.y;
        y *= v.x;
        reduc();
        return *this;
    }
    Fraction operator/(const Fraction& v) const { return Fraction(*this) /= v;}

    bool operator<( const int& right ) const { return x < y*right; }
    bool operator>( const int& right ) const { return x > y*right; }
    bool operator==( const int& right ) const { return x == right && y == 1; }
    Fraction& operator+=(const int& v) { 
        x += y*v;
        return *this;
    }
    Fraction operator+(const int& v) const { return Fraction(*this) += v;}
    Fraction& operator-=(const int& v) { 
        x -= y*v;
        return *this;
    }
    Fraction operator-(const int& v) const { return Fraction(*this) -= v;}
    Fraction& operator*=(const int& v) { 
        x *= v;
        reduc();
        return *this;
    }
    Fraction operator*(const int& v) const { return Fraction(*this) *= v;}
    Fraction& operator/=(const int& v) {
        y *= v;
        reduc();
        return *this;
    }
    Fraction operator/(const int& v) const { return Fraction(*this) /= v;}

    bool operator<( const long long& right ) const { return x < y*right; }
    bool operator>( const long long& right ) const { return x > y*right; }
    bool operator==( const long long& right ) const { return x == right && y == 1; }
    Fraction& operator+=(const long long& v) { 
        x += y*v;
        return *this;
    }
    Fraction operator+(const long long& v) const { return Fraction(*this) += v;}
    Fraction& operator-=(const long long& v) { 
        x -= y*v;
        return *this;
    }
    Fraction operator-(const long long& v) const { return Fraction(*this) -= v;}
    Fraction& operator*=(const long long& v) { 
        x *= v;
        reduc();
        return *this;
    }
    Fraction operator*(const long long& v) const { return Fraction(*this) *= v;}
    Fraction& operator/=(const long long& v) {
        y *= v;
        reduc();
        return *this;
    }
    Fraction operator/(const long long& v) const { return Fraction(*this) /= v;}

    Fraction inv() const { return Fraction(y, x); }
    Fraction pow(int t) const {
        if(t < 0) return inv().pow(-t);
        Fraction a(1, 1), d = *this;
        while(t) {
            d *= d;
            if(t & 1) a *= d;
            t >>= 1;
        }
        return a;
    }
    friend ostream& operator << (ostream& os, const Fraction& v) { return os << v.x << "/" << v.y; }  
};


/// modpow
long long modpow(long long a, long long n) {
    long long res = 1;
    while (n > 0) {
        if (n & 1) res = res * a % mod;
        a = a * a % mod;
        n >>= 1;
    }
    return res;
}

long long modinv(long long a, long long m) {
    long long b = m, u = 1, v = 0;
    while (b) {
        long long t = a / b;
        a -= t * b; swap(a, b);
        u -= t * v; swap(u, v);
    }
    u %= m; 
    if (u < 0) u += m;
    return u;
}




///////// combination
const ll N = 200007;
ll fac[N],finv[N],inv[N];
void cominit(){
    fac[0]=fac[1]=1;
    finv[0]=finv[1]=1;
    inv[1]=1;
    for(int i=2;i<N;i++){
        fac[i]=fac[i-1]*i%mod;
        inv[i]=mod-inv[mod%i]*(mod/i)%mod;
        finv[i]=finv[i-1]*inv[i]%mod;
    }
}
ll com(ll n,ll k){
    if(n<k)return 0;
    if(n<0 || k<0)return 0;
    return fac[n]*(finv[k]*finv[n-k]%mod)%mod;
}

ll COM(ll n, ll k){
    if(n < k or n < 0 or k < 0) return 0;
    k = min(n - k, k);
    ll ret = finv[k]; // for() modpow(a, mod - 2);
    for(ll r=n-k+1;r<=n;r++){
        ret *= r;
        ret %= mod;
    }
    return ret;
}

main-> cominit();



///////modint
struct mint {
    ll x; // typedef long long ll;
    mint(ll x=0):x((x%mod+mod)%mod){}
    mint operator-() const { return mint(-x);}
    mint& operator+=(const mint a) {
        if ((x += a.x) >= mod) x -= mod;
        return *this;
    }
    mint& operator-=(const mint a) {
        if ((x += mod-a.x) >= mod) x -= mod;
        return *this;
    }
    mint& operator*=(const mint a) { (x *= a.x) %= mod; return *this;}
    mint operator+(const mint a) const { return mint(*this) += a;}
    mint operator-(const mint a) const { return mint(*this) -= a;}
    mint operator*(const mint a) const { return mint(*this) *= a;}
    mint pow(ll t) const {
        if (!t) return 1;
        mint a = pow(t>>1);
        a *= a;
        if (t&1) a *= *this;
        return a;
    }

    // for prime mod
    mint inv() const { return pow(mod-2);}
    mint& operator/=(const mint a) { return *this *= a.inv();}
    mint operator/(const mint a) const { return mint(*this) /= a;}
};



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


/////BIT ****(1-index)****
template <class Abel> struct BIT {
    const Abel UNITY_SUM = 0;           
    vector<Abel> dat;
   
    // [1, n]
    BIT(int n) : dat(n + 1, UNITY_SUM) { }
    void init(int n) { dat.assign(n + 1, UNITY_SUM); }
    
    // a is 1-indexed
    inline void add(int a, Abel x) {
        for (int i = a; i < (int)dat.size(); i += i & -i)
            dat[i] = dat[i] + x;
    }
    
    // [1, a], a is 1-indexed
    inline Abel sum(int a) {
        Abel res = UNITY_SUM;
        for (int i = a; i > 0; i -= i & -i)
            res = res + dat[i];
        return res;
    }
    
    // [a, b), a and b are 1-indexed
    inline Abel sum(int a, int b) {
        return sum(b - 1) - sum(a - 1);
    }
};







/////////segmenttree
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




///////Lazy_segmenttree
struct LazySegmentTree {
private:
    int n;
    vector<ll> node, lazy;

public:
    LazySegmentTree(vector<ll> v) {
        int sz = (int)v.size();
        n = 1; while(n < sz) n *= 2;
        node.resize(2*n-1);
        lazy.resize(2*n-1, 0);

        for(int i=0; i<sz; i++) node[i+n-1] = v[i];
        for(int i=n-2; i>=0; i--) node[i] = node[i*2+1] + node[i*2+2];
    }

    void eval(int k, int l, int r) {
        if(lazy[k] != 0) {
            node[k] += lazy[k];
            if(r - l > 1) {
                lazy[2*k+1] += lazy[k] / 2;
                lazy[2*k+2] += lazy[k] / 2;
            }
            lazy[k] = 0;
        }
    }

    void add(int a, int b, ll x, int k=0, int l=0, int r=-1) {
        if(r < 0) r = n;
        eval(k, l, r);
        if(b <= l || r <= a) return;
        if(a <= l && r <= b) {
            lazy[k] += (r - l) * x;
            eval(k, l, r);
        }
        else {
            add(a, b, x, 2*k+1, l, (l+r)/2);
            add(a, b, x, 2*k+2, (l+r)/2, r);
            node[k] = node[2*k+1] + node[2*k+2];
        }
    }

    ll getsum(int a, int b, int k=0, int l=0, int r=-1) {
        if(r < 0) r = n;
        eval(k, l, r);
        if(b <= l || r <= a) return 0;
        if(a <= l && r <= b) return node[k];
        ll vl = getsum(a, b, 2*k+1, l, (l+r)/2);
        ll vr = getsum(a, b, 2*k+2, (l+r)/2, r);
        return vl + vr;
    }
};
//add_sum





////////////
struct LazySegmentTree {
private:
    int n;
    vector<int> node, lazy;
    vector<bool> lazyFlag;

public:
    LazySegmentTree(vector<int> v) {
        int sz = (int)v.size();
        n = 1; while(n < sz) n *= 2;
        node.resize(2*n-1);
        lazy.resize(2*n-1, INF);
        lazyFlag.resize(2*n-1, false);

        for(int i=0; i<sz; i++) node[i+n-1] = v[i];
        for(int i=n-2; i>=0; i--) node[i] = min(node[i*2+1], node[i*2+2]);
    }

    void lazyEvaluate(int k, int l, int r) {
        if(lazyFlag[k]) {
            node[k] = lazy[k];
            if(r - l > 1) {
                lazy[k*2+1] = lazy[k*2+2] = lazy[k];
                lazyFlag[k*2+1] = lazyFlag[k*2+2] = true;
            }
            lazyFlag[k] = false;
        }
    }

    void update(int a, int b, int x, int k=0, int l=0, int r=-1) {
        if(r < 0) r = n;
        lazyEvaluate(k, l, r);
        if(b <= l || r <= a) return;
        if(a <= l && r <= b) {
            lazy[k] = x;
            lazyFlag[k] = true;
            lazyEvaluate(k, l, r);
        }
        else {
            update(a, b, x, 2*k+1, l, (l+r)/2);
            update(a, b, x, 2*k+2, (l+r)/2, r);
            node[k] = min(node[2*k+1], node[2*k+2]);
        }
    }

    ll find(int a, int b, int k=0, int l=0, int r=-1) {
        if(r < 0) r = n;
        lazyEvaluate(k, l, r);
        if(b <= l || r <= a) return INF;
        if(a <= l && r <= b) return node[k];
        ll vl = find(a, b, 2*k+1, l, (l+r)/2);
        ll vr = find(a, b, 2*k+2, (l+r)/2, r);
        return min(vl, vr);
    }
};
//update_min

struct LazySegmentTree {
private:
    ll n;
    vector<ll> node, lazy;
    vector<bool> lazyFlag;

public:
    LazySegmentTree(vector<ll> v) {
        ll sz = (int)v.size();
        n = 1; while(n < sz) n *= 2;
        node.resize(2*n-1);
        lazy.resize(2*n-1, 0);
        lazyFlag.resize(2*n-1, false);

        for(int i=0; i<sz; i++) node[i+n-1] = v[i];
        for(int i=n-2; i>=0; i--) node[i] = min(node[i*2+1], node[i*2+2]);
    }

    void lazyEvaluate(ll k, ll l, ll r) {
        if(lazyFlag[k]) {
            node[k] += lazy[k] / (r - l);
            if(r - l > 1) {
                lazy[k*2+1] += lazy[k] / 2;
                lazy[k*2+2] += lazy[k] / 2;
                lazyFlag[k*2+1] = lazyFlag[k*2+2] = true;
            }
            lazyFlag[k] = false;
            lazy[k] = 0;
        }
    }

    void add(int a, int b, ll x, int k=0, int l=0, int r=-1) {
        if(r < 0) r = n;
        lazyEvaluate(k, l, r);
        if(b <= l || r <= a) return;
        if(a <= l && r <= b) {
            lazy[k] += x * (r - l);
            lazyFlag[k] = true;
            lazyEvaluate(k, l, r);
        }
        else {
            add(a, b, x, 2*k+1, l, (l+r)/2);
            add(a, b, x, 2*k+2, (l+r)/2, r);
            node[k] = min(node[2*k+1], node[2*k+2]);
        }
    }

    ll find(int a, int b, int k=0, int l=0, int r=-1) {
        if(r < 0) r = n;
        lazyEvaluate(k, l, r);
        if(b <= l || r <= a) return INF;
        if(a <= l && r <= b) return node[k];
        ll vl = find(a, b, 2*k+1, l, (l+r)/2);
        ll vr = find(a, b, 2*k+2, (l+r)/2, r);
        return min(vl, vr);
    }
};

//RMQ and RAQ
