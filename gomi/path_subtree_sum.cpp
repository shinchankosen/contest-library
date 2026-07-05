#include <bits/stdc++.h>
using namespace std;

#define all(v) (v).begin(),(v).end()
#define pb emplace_back
#define rep(i, n) for(int i=0;i<(n);i++)
#define foa(e, v) for(auto& e : v)
#define dout(a) cout<<fixed<<setprecision(10)<<a<<'\n';
#define Cout(a) cout<<a<<'\n';

using ll = long long;
using ld = long double;
using Int = __int128;
template <class T> using pqr = priority_queue<T, vector<T>, greater<T>>;

template <typename T1, typename T2> inline bool chmax(T1 &a, T2 b) {
    bool compare = a < b;
    if(compare) a = b;
    return compare;
}
template <typename T1, typename T2> inline bool chmin(T1 &a, T2 b) {
    bool compare = a > b;
    if(compare) a = b;
    return compare;
}
template <typename T> inline T back(std::set<T> &s) {
    return *s.rbegin();
}
template <typename T> inline T back(std::multiset<T> &s) {
    return *s.rbegin();
}
template <typename T> inline T pop_back(std::set<T> &s) {
    auto it = prev(s.end());
    T val = *it;
    s.erase(it); 
    return val;
}
template <typename T> inline T pop_back(std::multiset<T> &s) {
    auto it = prev(s.end());
    T val = *it;
    s.erase(it); 
    return val;
}

const int dy[8] = {-1, 0, 0, 1, 1, -1, 1, -1};
const int dx[8] = {0, -1, 1, 0, -1, -1, 1, 1};

const ll MOD7 = 1000000007, MOD998 = 998244353, INF = (3LL << 59);
const int inf = 1 << 30;
const char br = '\n';


template<class S, S (*op)(S, S), S (*e)(), class F, S (*mapping)(F, S), F (*composition)(F, F), F (*id)()>
struct lazy_segtree {
   public:
    explicit lazy_segtree(int n) : lazy_segtree(vector<S>(n, e())) {}
    explicit lazy_segtree(const vector<S>& v) : _n(int(v.size())) {
        size = 1;
        while(size < _n) size *= 2;
        log = __builtin_ctz(size);
        d = vector<S>(2 * size, e());
        lz = vector<F>(size, id());
        for(int i = 0; i < _n; i++) d[size + i] = v[i];
        for(int i = size - 1; i >= 1; i--) { update(i); }
    }

    void set(int p, S x) {
        p += size;
        for(int i = log; i >= 1; i--) push(p >> i);
        d[p] = x;
        for(int i = 1; i <= log; i++) update(p >> i);
    }

    S get(int p) {
        p += size;
        for(int i = log; i >= 1; i--) push(p >> i);
        return d[p];
    }

    S prod(int l, int r) {
        if(l == r) return e();

        l += size;
        r += size;

        for(int i = log; i >= 1; i--) {
            if(((l >> i) << i) != l) push(l >> i);
            if(((r >> i) << i) != r) push((r - 1) >> i);
        }

        S sml = e(), smr = e();
        while(l < r) {
            if(l & 1) sml = op(sml, d[l++]);
            if(r & 1) smr = op(d[--r], smr);
            l >>= 1;
            r >>= 1;
        }

        return op(sml, smr);
    }

    void apply(int l, int r, F f) {
        if(l == r) return;

        l += size;
        r += size;

        for(int i = log; i >= 1; i--) {
            if(((l >> i) << i) != l) push(l >> i);
            if(((r >> i) << i) != r) push((r - 1) >> i);
        }

        {
            int l2 = l, r2 = r;
            while(l < r) {
                if(l & 1) all_apply(l++, f);
                if(r & 1) all_apply(--r, f);
                l >>= 1;
                r >>= 1;
            }
            l = l2;
            r = r2;
        }

        for(int i = 1; i <= log; i++) {
            if(((l >> i) << i) != l) update(l >> i);
            if(((r >> i) << i) != r) update((r - 1) >> i);
        }
    }

    template<class G> int max_right(int l, G g) {
        if(l == _n) return _n;
        l += size;
        for(int i = log; i >= 1; i--) push(l >> i);
        S sm = e();
        do {
            while(l % 2 == 0) l >>= 1;
            if(!g(op(sm, d[l]))) {
                while(l < size) {
                push(l);
                l = (2 * l);
                if(g(op(sm, d[l]))) {
                    sm = op(sm, d[l]);
                    l++;
                }
                }
                return l - size;
            }
            sm = op(sm, d[l]);
            l++;
        } while((l & -l) != l);
        return _n;
    }

    template<class G> int min_left(int r, G g) {
        if(r == 0) return 0;
        r += size;
        for(int i = log; i >= 1; i--) push((r - 1) >> i);
        S sm = e();
        do {
            r--;
            while(r > 1 && (r % 2)) r >>= 1;
            if(!g(op(d[r], sm))) {
                while(r < size) {
                push(r);
                r = (2 * r + 1);
                if(g(op(d[r], sm))) {
                    sm = op(d[r], sm);
                    r--;
                }
                }
                return r + 1 - size;
            }
            sm = op(d[r], sm);
        } while((r & -r) != r);
        return 0;
    } 

    private:
    int _n, size, log;
    vector<S> d;
    vector<F> lz;

    void update(int k) { d[k] = op(d[2 * k], d[2 * k + 1]); }
    void all_apply(int k, F f) {
        d[k] = mapping(f, d[k]);
        if(k < size) lz[k] = composition(f, lz[k]);
    }
    void push(int k) {
        all_apply(2 * k, lz[k]);
        all_apply(2 * k + 1, lz[k]);
        lz[k] = id();
    }
};

class HLDcomposition {
  private:
  int V;
  vector<vector<int>> G;
  vector<int> stsize, parent, pathtop, in, out;
  int root;
  
  void build_stsize(int u, int p) {
    stsize[u] = 1, parent[u] = p;
    for(auto&& v : G[u]) {
        if(v == p) {
            swap(v, G[u].back());
            break;
        }
    }
    for(auto&& v : G[u]) {
      if(v == p) {
        continue;
      }
      build_stsize(v, u);
      stsize[u] += stsize[v];
      if(stsize[v] > stsize[G[u][0]]) swap(v, G[u][0]);
    }
  }  // 5a09a1

  void build_path(int u, int p, int& tm) {
    in[u] = tm++;
    for(auto v : G[u]) {
      if(v == p) continue;
      pathtop[v] = (v == G[u][0] ? pathtop[u] : v);
      build_path(v, u, tm);
    }
    out[u] = tm;
  }  // 9074ec

  public:
  void add_edge(int u, int v) {
    G[u].push_back(v);
    G[v].push_back(u);
  }

  void build(int _root = 0) {
    root = _root;
    int tm = 0;
    build_stsize(root, -1);
    pathtop[root] = root;
    build_path(root, -1, tm);
  }  // d594c1

  inline int index(int a) { return in[a]; }

  int lca(int a, int b) {
    int pa = pathtop[a], pb = pathtop[b];
    while(pa != pb) {
      if(in[pa] > in[pb]) {
        a = parent[pa], pa = pathtop[a];
      } else {
        b = parent[pb], pb = pathtop[b];
      }
    }
    if(in[a] > in[b]) swap(a, b);
    return a;
  }  // 2e2c69

  pair<int, int> subtree_query(int a) { return {in[a], out[a]}; }

  vector<tuple<int, int, bool>> path_query(int from, int to) {
    int pf = pathtop[from], pt = pathtop[to];
    using T = tuple<int, int, bool>;
    deque<T> front, back;
    while(pf != pt) {
      if(in[pf] > in[pt]) {
        front.push_back({in[pf], in[from] + 1, true});
        from = parent[pf], pf = pathtop[from];
      } else {
        back.push_front({in[pt], in[to] + 1, false});
        to = parent[pt], pt = pathtop[to];
      }
    }
    if(in[from] > in[to]) front.push_back({in[to], in[from] + 1, true});
    else front.push_back({in[from], in[to] + 1, false});
    vector<T> ret;
    while(!front.empty()) {
      ret.push_back(front.front());
      front.pop_front();
    }
    while(!back.empty()) {
      ret.push_back(back.front());
      back.pop_front();
    }
    return ret;
  }  // 47b288

  HLDcomposition(int node_size)
      : V(node_size), G(V), stsize(V, 0), parent(V, -1), pathtop(V, -1), in(V, -1), out(V, -1) {}
};

using S = pair<ll, ll>;

S op(S a, S b) {
    return S{a.first + b.first, a.second + b.second};
}

S e() {return S{0, 0};}

S mapping(S a, S b) {
    if(a.first == 1) {
        return S{a.second * b.second, b.second};
    }
    return S{b.first + a.second * b.second, b.second};
}

S composition(S a, S b) {
    if(a.first == 1) return a;
    return S{b.first, b.second + a.second};
}

void solve() {
    ll n, q; cin >> n >> q;
    vector<ll> a(n);
    rep(i, n) cin >> a[i];
    HLDcomposition hld(n);
    rep(i, n - 1) {
        int x, y; cin >> x >> y;
        x --; y --;
        hld.add_edge(x, y);
    }
    hld.build();
    lazy_segtree<S, op, e, S, mapping, composition, e> seg(n);
    rep(i, n) seg.set(hld.index(i), S{a[i], 1});
    rep(_, q) {
        int t; cin >> t;
        if(t == 1) {
            ll x, y, w; cin >> x >> y >> w;
            x --; y --;
            for(auto [l, r, f] : hld.path_query(x, y)) seg.apply(l, r, S{0, w});
        } else if(t == 2) {
            ll x, y, w; cin >> x >> y >> w;
            x --; y --;
            for(auto [l, r, f] : hld.path_query(x, y)) seg.apply(l, r, S{1, w});
        } else if(t == 3) {
            ll x, w; cin >> x >> w;
            x --;
            auto [l, r] = hld.subtree_query(x);
            seg.apply(l, r, S{0, w});
        } else if(t == 4) {
            ll x, w; cin >> x >> w;
            x --;
            auto [l, r] = hld.subtree_query(x);
            seg.apply(l, r, S{1, w});
        } else if(t == 5) {
            ll ans = 0;
            ll x, y; cin >> x >> y;
            x --; y --;
            for(auto [l, r, f] : hld.path_query(x, y)) ans += seg.prod(l, r).first;
            cout << ans << endl;
        } else { 
            ll ans = 0;
            ll x; cin >> x;
            x --; 
            auto [l, r] = hld.subtree_query(x);
            ans += seg.prod(l, r).first;
            cout << ans << endl;
        }
    }
}

int main() {
    cin.tie(0);
    ios::sync_with_stdio(false);

    int testcase = 1; 
    cin >> testcase;
    while(testcase --) solve();

    return 0;
}
