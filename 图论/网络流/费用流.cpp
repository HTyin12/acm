const long long inf=1e18,V=1e6+5,E=1e6+5;
int tot,cnt=1,head[V],pre[V],vis[V];
long long dis[V],h[V];
struct Node{int to,nxt;long long w,c;}e[E<<1];
void add(int u,int v,int w,int c){e[++cnt]={v,head[u],w,c},head[u]=cnt;}
void addflow(int u,int v,int w,int c=0){add(u,v,w,c),add(v,u,0,-c);}
void spfa(int s){
	for(int i=1;i<=tot;i++)h[i]=inf;
	queue<int>q;vis[s]=1;h[s]=0;q.push(s);
	while(q.size()){
		int u=q.front();q.pop();vis[u]=0;
		for(int i=head[u];i;i=e[i].nxt){
			int v=e[i].to;
			if(e[i].w&&h[u]+e[i].c<h[v]){
				h[v]=h[u]+e[i].c;
				if(!vis[v])vis[v]=1,q.push(v);
			}
		}
	}
}
int dij(int s,int t){
	priority_queue<pair<long long,int>>q;
	for(int i=1;i<=tot;i++)dis[i]=inf,vis[i]=0;
	dis[s]=0;q.push({0,s});
	while(q.size()){
		int u=q.top().second;q.pop();
		if(vis[u])continue;vis[u]=1;
		for(int i=head[u];i;i=e[i].nxt){
			int v=e[i].to;
			if(e[i].w&&dis[u]+e[i].c+h[u]-h[v]<dis[v]){
				dis[v]=dis[u]+e[i].c+h[u]-h[v];
				pre[v]=i;
				if(!vis[v])q.push({-dis[v],v});
			}
		}
	}
	return dis[t]!=inf;
}
pair<long long,long long> mcmf(int s,int t,int n){ //O(f*m*logm)
	tot=n;spfa(s);long long f=0,c=0;
	while(dij(s,t)){
		long long flow=inf;
		for(int i=1;i<=tot;i++)h[i]+=dis[i];
		for(int x=t;x!=s;x=e[pre[x]^1].to)flow=min(flow,e[pre[x]].w);f+=flow;
		for(int x=t;x!=s;x=e[pre[x]^1].to)e[pre[x]].w-=flow,e[pre[x]^1].w+=flow,c+=e[pre[x]].c*flow;
	}
	return {f,c};
}
//有负费用时要注意
//负环处理
/*
int tot[N];
int res=0;
for(int i=1;i<=m;i++){
	int x,y,f,w;cin>>x>>y>>f>>w;
	if(w>=0)addflow(x,y,f,w);
	else{
		addflow(y,x,f,-w);
		tot[x]-=f,tot[y]+=f;
		res+=f*w;
	}
}
int ss=n+1,tt=n+2;//建立临时s,t
for(int i=1;i<=n;i++){
	if(tot[i]==0)continue;
	else if(tot[i]>0){
		addflow(ss,i,tot[i]);
	}else addflow(i,tt,-tot[i]);
}
auto [ff,cc]=EK(ss,tt,tt);
auto [f,c]=EK(s,t,n+2);
cout<<f<<' '<<c+res+cc;
*/
