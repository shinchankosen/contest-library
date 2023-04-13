vector<int> topo_sort(vector<pair<int, int>> &edges, int &n) {
    vector<vector<int>> g(n);
    vector<int> h(n, 0);
    stack<int> st;
    vector<int> ans;

    for(auto [a, b] : edges) {
        g[a].push_back(b);
        h[b] ++;
    }

    for(int i = 0; i < n; i ++) if(h[i] == 0) st.push(i);

    while(!st.empty()) {
        int i = st.top(); st.pop();
        ans.pb(i);
        for(auto& j : g[i]) {
            h[j]--;
            if(h[j] == 0) st.push(j);
        }
    }
    return ans;
} 
// ans.size() != nであればソート不可