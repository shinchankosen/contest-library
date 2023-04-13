//bellman_ford
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
