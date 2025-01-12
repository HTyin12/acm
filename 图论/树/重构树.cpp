const int N=5e5+5;
int f[N],cnt,val[N],st[20][N],dfn[N],timer;
vector<array<int,3>>e;
vector<int>G[N];
int find(int x){
	if(f[x]==x)return x;
	return f[x]=find(f[x]);
}
void dfs(int u,int F){
	st[0][dfn[u]=++timer]=F;
	for(int v:G[u])dfs(v,u);	
}
int mn(int x,int y){
	return dfn[x]<dfn[y]?x:y;
}
void init1(int n){
	for(int x=1;x<=19;x++)
		for(int y=1;y+(1<<x)-1<=n;y++)
			st[x][y]=mn(st[x-1][y],st[x-1][y+(1<<x-1)]);
}
int lca(int u,int v){
	if(u==v)return u;
	if((u=dfn[u])>(v=dfn[v]))swap(u,v);
	int k=__lg(v-u++);
	return mn(st[k][u],st[k][v-(1<<k)+1]);
}
void init(int n){
	cnt=n;timer=0;
	for(int i=1;i<=n;i++)f[i]=i;
	sort(e.begin(),e.end());
	for(auto [w,x,y]:e){
		if(find(x)==find(y))continue;
		G[++cnt].push_back(find(x));
		G[cnt].push_back(find(y));
		f[cnt]=cnt;val[cnt]=w;
		f[find(x)]=f[find(y)]=cnt;
	}
	for(int i=cnt;i>=1;i--)if(!dfn[i])dfs(i,i);
	init1(cnt);
}
