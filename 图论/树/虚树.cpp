const int N=2e5+5;
vector<int>p[N],G[N];
int st[20][N],dfn[N],timer,dep[N];
void DFS(int u,int F){
	dep[u]=dep[F]+1;
	st[0][dfn[u]=++timer]=F;
	for(int v:p[u])if(v!=F)DFS(v,u);
}
int mn(int x,int y){
	return dfn[x]<dfn[y]?x:y;
}
void init(int n){
	timer=0;DFS(1,0);
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
int stk[N],tp;
int build(vector<int> &a){
	sort(a.begin(),a.end(),[&](int x,int y){
		return dfn[x]<dfn[y];
	});
	for(auto x:a){
		if(tp==0)stk[++tp]=x;
		else{
			int LCA=lca(x,stk[tp]);
			while(tp>1&&dep[LCA]<dep[stk[tp-1]]){
				G[stk[tp-1]].push_back(stk[tp]);tp--;
			}
			if(dep[LCA]<dep[stk[tp]])G[LCA].push_back(stk[tp--]);
			if(stk[tp]!=LCA)stk[++tp]=LCA;
			stk[++tp]=x;
		}
	}
	while(tp>1){
		G[stk[tp-1]].push_back(stk[tp]);tp--;
	}
	return stk[tp--];
}
void G_clear(int x){
	for(auto y:G[x]){
		G_clear(y);
	}
	G[x].clear();
}
