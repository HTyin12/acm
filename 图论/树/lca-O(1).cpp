int st[20][N],dfn[N],timer;
void dfs(int u, int F){
	st[0][dfn[u]=++timer]=F;
	for(int v:G[u]){
		if(v==F)continue;
		dfs(v,u);
	}
}
int mn(int x,int y){
	return dfn[x]<dfn[y]?x:y;
}
void init(int n){
	for(int x=1;x<=19;x++)
		for(int y=1;y+(1<< x)-1<=n;y++)
			st[x][y]=mn(st[x-1][y],st[x-1][y+(1<<x-1)]);
}
int lca(int u,int v){
	if(u==v)return u;
	if((u=dfn[u])>(v=dfn[v]))swap(u,v);
	int k=__lg(v-u++);
	return mn(st[k][u],st[k][v-(1<<k)+1]);
}
