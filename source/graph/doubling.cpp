struct Doubling {
private:
    std::vector<std::vector<int>> nx;
    std::vector<long long> dis;
public:
    Doubling(std::vector<std::vector<int>> v, int s = 0) noexcept { 
        int n = v.size();
        dis.resize(n, INF);
        nx.resize(n, std::vector<int> (63, -1));
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
        for(int j = 0; j < 62; j ++) for(int i = 0; i < n; i ++) {
            if(nx[i][j] != -1) nx[i][j + 1] = nx[nx[i][j]][j];
        }
    }
    Doubling(std::vector<int> nx_) noexcept {
        int n = nx_.size();
        nx.resize(n, std::vector<int> (63, -1));
        for(int i = 0; i < n; i ++) nx[i][0] = nx_[i];
        for(int j = 0; j < 62; j ++) for(int i = 0; i < n; i ++) {
            if(nx[i][j] != -1) nx[i][j + 1] = nx[nx[i][j]][j];
        }
    }

    // nowのm個先 (LCAではm個親)
    int par(int now, long long m) {
        for(long long i = 0, j = 1; j <= m; i ++, j <<= 1) {
            if(m & j) now = nx[now][i];
        }
        return now;
    }
};