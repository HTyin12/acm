//O(n^2 log(n) + m log(n))
const int N=3e3+5;
vector<pair<int,long long>>p[N];
long long h[N],d[N];int cnt[N],vis[N];
long long square[N][N];
int n,m;
bool spfa(int s){
    for(int i=1;i<=n;i++)h[i]=1e9;
    queue<int>q;
    h[s]=0,vis[s]=1;q.push(s);
    while(q.size()){
        int u=q.front();q.pop();vis[u]=0;
        for(auto it:p[u]){
            int v=it.first；long long w=it.second;
            if(h[v]>h[u]+w){
                h[v]=h[u]+w;
                cnt[v]=cnt[u]+1;
                if(cnt[v]>n)return 1;//1存在负环
                if(!vis[v])q.push(v),vis[v]=1;
            }
        }
    }
    return 0;
}
void dij(int s){
    for(int i=0;i<=n;i++)d[i]=1e9,vis[i]=0;
    priority_queue<pair<long long,int>>q;
    d[s]=0;q.push({0,s});
    while(q.size()){
        auto it=q.top();q.pop();
        int u=it.second;
        if(vis[u])continue;
        vis[u]=1;
        for(auto it:p[u]){
            int v=it.first;long long w=it.second;
            if(d[v]>d[u]+w){
                d[v]=d[u]+w;
                q.push({-d[v],v});
            }
        }
    }
}
bool johnson(){
    for(int i=1;i<=n;i++){
        for(int j=1;j<=n;j++){
            square[i][j]=1e9;
        }
    }
    for(int i=1;i<=n;i++)p[0].push_back({i,0});
    if(spfa(0))return 1;//存在负环
    for(int i=1;i<=n;i++){
        for(auto &it:p[i]){
            it.second+=h[i]-h[it.first];
        }
    }
    for(int i=1;i<=n;i++){
        dij(i);
        for(int j=1;j<=n;j++){
            if(d[j]!=1e9)square[i][j]=min(square[i][j],d[j]+h[j]-h[i]);
        }
    }
    return 0;
}