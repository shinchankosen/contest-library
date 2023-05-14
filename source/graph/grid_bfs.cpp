    vector dis(h * w, INF);
    auto bfs = [&] (int sty, int stx) -> void {
        int dy[4] = {-1, 1, 0, 0};
        int dx[4] = {0, 0, -1, 1};
        dis[sty * w + stx] = 0;
        queue<int> q;
        q.push(sty * w + stx);
        while(!q.empty()) {
            int now = q.front();
            q.pop();
            int i = now / w;
            int j = now % w;
            rep(k, 4) {
                int y = i + dy[k];
                int x = j + dx[k];
                if(y < 0 || y >= h || x < 0 || x >= w) continue;
                if(s[y][x] == '#') continue;
                if(dis[y * w + x] == INF) {
                    dis[y * w + x] = dis[i * w + j] + 1;
                    q.push(y * w + x);
                }
            }
        }
    };