const int N=1e4+5,INF=1e9,M=4e6+5;
int dep[N],now[N],cnt=1,head[N];
struct{int to,nex,w;}e[M];
void add(int u,int v,int w){
	e[++cnt]={v,head[u],w};head[u]=cnt;
}
void addflow(int u,int v,int w){
	add(u,v,w);
	add(v,u,0);
}
int bfs(int s,int t){
	for(int i=s;i<=t;i++)dep[i]=INF;
	dep[s]=0;
	now[s]=head[s];
	queue<int>q;q.push(s);
	while(!q.empty()){
		int u=q.front();q.pop();
		for(int i=head[u];i;i=e[i].nex){
			int v=e[i].to;
			if(e[i].w>0&&dep[v]==INF){
				q.push(v);
				now[v]=head[v];
				dep[v]=dep[u]+1;
				if(v==t)return 1;
			}
		}
	}
	return 0;
}
int dfs(int u,long long sum,int t){
	if(u==t||!sum)return sum;
	long long k,flow=0;
	for(int i=now[u];i&&sum;i=e[i].nex){
		now[u]=i;
		int v=e[i].to;
		if(e[i].w&&dep[v]==dep[u]+1){
			k=dfs(v,min(sum,(long long)e[i].w),t);
			if(!k)dep[v]=INF;
			e[i].w-=k,e[i^1].w+=k,flow+=k,sum-=k;   
		}
	}
	return flow;
}
void init(int s,int t){
	cnt=1;for(int i=s;i<=t;i++)head[i]=0;
}
long long MaxFlow(int s,int t){
	long long ans=0;
	while(bfs(s,t))ans+=dfs(s,INF,t);
	return ans;
}
//二分图匹配中间连边容量可以为INF更好理解,连边时只有左向右
//二分图最小点覆盖集：与s相连的dep=INF, 与t相连的dep!=INF点
//最长反链集为拆点后均在二分图最大独立集中的点
//最大权闭合子图,s连正权,t连负权,原来的闭合子图连INF,答案为正权和-最小割(即要么保留正的，要么放弃)


bool vis[N];

//求最小割的一种划分
void mincut(int u){
	vis[u]=1;
	for(int i=head[u];i;i=e[i].nex){
		int v=e[i].to;
		if(!vis[v]&&e[i].w)mincut(v);
	}
}

//求最小割的最小边数
long long minm(){
	for(int i=2;i<=cnt;i++){
		if(i&1){
			e[i].w=0;continue;
		}
		if(!e[i].w)e[i].w=1;
		else e[i].w=INF;
	}
	long long ans=0;
	while(bfs())ans+=dfs(s,INF);
	return ans;
}
//s=1,t=n
