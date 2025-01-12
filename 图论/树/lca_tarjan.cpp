const int N=;
int fa[N],ans[N];
bool vis[N];
vector<int>G[N];
vector<pair<int,int>>head_query[N];
int find(int x){
    if(fa[x]==x)return x;
    return fa[x]=find(fa[x]);
}
void tarjan(int x){
    vis[x]=1;
    for(auto it:G[x]){
        if(!vis[it]){
            tarjan(it);
            fa[it]=x;
        }
    }
    for(auto it:head_query[x]){
        int x=it.first,y=it.second;
        if(vis[x]){
            ans[y]=find(x);
        }
    }
}