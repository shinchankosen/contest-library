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
        fill(used.begin(), used.end(), 0);
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
            sort(ng[i].begin(), ng[i].end());
            ng[i].erase(unique(ng[i].begin(), ng[i].end()), ng[i].end());
        }
        return k;
    }
    int size(){return nn;}
    vector<vector<int> > graph(){return ng;}
    vector<int> vertices(int v){return vs[v];}
};
