int n,m;
const int INF=1e9;
const int N=250;
long long graph[N][N],pre[N],flow[N];
long long bfs(int s,int t){
    for(int i=1;i<=n;i++)pre[i]=-1;
    flow[s]=INF,pre[s]=0;
    queue<int>q;q.push(s);
    while(!q.empty()){
        int u=q.front();q.pop();
        if(u==t)break;
        for(int i=1;i<=n;i++){
            if(i!=s&&graph[u][i]>0&&pre[i]==-1){
                pre[i]=u;
                q.push(i);
                flow[i]=min(flow[u],graph[u][i]);
            }
        }
    }
    if(pre[t]==-1)return -1;
    return flow[t];
}
long long MaxFlow(int s,int t){
    long long ans=0;
    while(1){
        long long res=bfs(s,t);
        if(res==-1)break;
        int cur=t;
        while(cur!=s){
            int fa=pre[cur];
            graph[fa][cur]-=res;
            graph[cur][fa]+=res;
            cur=fa;
        }
        ans+=res;
    }
    return ans;
}