    int n;
    cin >> n;
    vector<vector<int>> v(n * 2 - 1);
    rep(i, n - 1) {
        int a, b;
        cin >> a >> b;
        v[a].pb(i + n);
        v[b].pb(i + n);
        v[i + n].pb(a);
        v[i + n].pb(b);
    }
    int d = 0, id = 0;
    auto dfs1 = [&](auto&& dfs1, int now, int count, int p) -> void{
        if(count >= d) {
            d = count;
            id = now;
        }
        all(e, v[now]) {
            if(e == p) continue;
            dfs1(dfs1, e, count + 1, now);
        }
        return;
    };

    dfs1(dfs1, 0, 0, -1);
    dfs1(dfs1, id, 0, -1);

    auto dfs2 = [&](auto&& dfs2, int now, int count, int p) -> void{
        if(count * 2 == d) {
            id = now;
            return;
        }
        all(e, v[now]) {
            if(e == p) continue;
            dfs2(dfs2, e, count + 1, now);
        }
        return;
    };

    dfs2(dfs2, id, 0, -1);
