const int N=;
int fa[N][20],deep[N];
vector<int>G[N];
void dfs(int x,int F){
    deep[x]=deep[F]+1;
    fa[x][0]=F;
    for(int i=1;i<=19;i++){
        fa[x][i]=fa[fa[x][i-1]][i-1];
    }
    for(auto it:G[x]){
        if(it==F)continue;
        dfs(it,x);
    }
}
int LCA(int x,int y){
    if(deep[x]<deep[y])swap(x,y);
    for(int i=19;i>=0;i--){
        if(deep[x]-(1<<i)>=deep[y])
        x=fa[x][i];
    }
    if(x==y)return x;
    for(int i=19;i>=0;i--){
        if(fa[x][i]!=fa[y][i]){
            x=fa[x][i];y=fa[y][i];
        }
    }
    return fa[x][0];
}
