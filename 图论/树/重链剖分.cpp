int fa[N],dep[N],son[N],sz[N],top[N],id[N],idx;
void dfs1(int u,int F){
	fa[u]=F,dep[u]=dep[F]+1,sz[u]=1;
	for(auto v:p[u]){
		if(v==F)continue;
		dfs1(v,u);
		sz[u]+=sz[v];
		if(sz[son[u]]<sz[v])son[u]=v;
	}
}
void dfs2(int u,int t){
	id[u]=++idx;
	top[u]=t;
	if(!son[u])return;
	dfs2(son[u],t);
	for(auto v:p[u]){
		if(v==fa[u]||v==son[u])continue;
		dfs2(v,v);
	}
}
