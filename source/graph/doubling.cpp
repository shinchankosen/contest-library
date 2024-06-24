struct Doubling {
private:
    static constexpr int max_bit = 20;
    std::vector<std::array<int, max_bit>> nx;
    std::vector<int> dis;
public:
    Doubling(std::vector<std::vector<int>> v, int s = 0) noexcept { 
        int n = v.size();
        dis.resize(n, 1 << 30);
        nx.resize(n);
        dis[s] = 0;
        auto dfs = [&] (auto dfs, int now, int p = -1) -> void {
            nx[now][0] = p;
            for(int to : v[now]) {
                if(to == p) continue;
                dis[to] = dis[now] + 1;
                dfs(dfs, to, now);
            }
        };
        dfs(dfs, s);
        for(int j = 0; j < max_bit - 1; j ++) for(int i = 0; i < n; i ++) {
            if(nx[i][j] != -1) nx[i][j + 1] = nx[nx[i][j]][j];
        }
    }
    Doubling(std::vector<int> nx_) noexcept {
        int n = nx_.size();
        nx.resize(n);
        for(int i = 0; i < n; i ++) nx[i][0] = nx_[i];
        for(int j = 0; j < max_bit - 1; j ++) for(int i = 0; i < n; i ++) {
            if(nx[i][j] != -1) nx[i][j + 1] = nx[nx[i][j]][j];
        }
    }

    // nowのm個先 (LCAではm個親)
    int par(int now, long long m) {
        while(m) {
            if(now == -1) return -1;
            int t = __builtin_ctz(m);
            now = nx[now][t];
            m ^= 1LL << t;
        }
        return now;
    }

    // Lowest Common Ancestor
    int lca(int a, int b) {
        if(dis[a] != dis[b]) {
            if(dis[a] > dis[b]) swap(a, b);
            b = par(b, dis[b] - dis[a]);
        }
        if(a == b) return a;
        for(int i = __lg(dis[a]); i >= 0; i --) {
            if(dis[a] < (1 << i)) continue;
            if(nx[a][i] != nx[b][i]) a = nx[a][i], b = nx[b][i];
        }
        return nx[a][0];
    }

    // distance between a and b
    int dist(int a, int b){return dis[a] + dis[b] - (dis[lca(a, b)] << 1);}
};
