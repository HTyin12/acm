const int N=2e5+5;
vector<pair<int,int>>p[N];
int d[N],cnt[N],vis[N];
int n,m;
//o(n*m)
bool spfa(int s){
    for(int i=1;i<=n;i++)d[i]=3e9;
    queue<int>q;
    d[s]=0,vis[s]=1;q.push(s);
    while(q.size()){
        int u=q.front();q.pop();vis[u]=0;
        for(auto it:p[u]){
            int v=it.first,w=it.second;
            if(d[v]>d[u]+w){
                d[v]=d[u]+w;
                cnt[v]=cnt[u]+1;
                if(cnt[v]>n)return 1;//1则有负环
                if(!vis[v])q.push(v),vis[v]=1;
            }
        }
    }
    return 0;
}