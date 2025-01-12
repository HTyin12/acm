const int N=2e5+5;
vector<pair<int,int>>p[N];
int d[N],vis[N];
void dij(int s,int n){
    for(int i=1;i<=n;i++)d[i]=1e18,vis[i]=0;
    priority_queue<pair<int,int>>q;
    d[s]=0;q.push({0,s});
    while(q.size()){
        auto it=q.top();q.pop();
        int u=it.second;
        if(vis[u])continue;
        vis[u]=1;
        for(auto it:p[u]){
            int v=it.first,w=it.second;
            if(d[v]>d[u]+w){
                d[v]=d[u]+w;
                q.push({-d[v],v});
            }
        }
    }
}
