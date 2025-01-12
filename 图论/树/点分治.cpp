int sz[N],son[N],vis[N],SZ,MX,rt;
void dfs(int x,int fa,int sum,int val){
	
}
void findrt(int u,int fa){ 
	sz[u]=1,son[u]=0;
	for(auto v:p[u]){
		if(vis[v]||v==fa)continue;
		findrt(v,u);
		sz[u]+=sz[v];
		son[u]=max(son[u],sz[v]);
	} 
	son[u]=max(son[u],SZ-sz[u]);
	if(son[u]<MX)MX=son[u],rt=u;
}
void divide(int u){
	mp.clear();
	dfs(u,0,a[c[u]],w[u]); 
	vis[u]=1;
	int totsz=SZ;
	for(auto v:p[u]){
		if(vis[v])continue; 
		MX=1e9,rt=0;SZ=sz[v]>sz[u]?totsz-sz[u]:sz[v]; 
		findrt(v,0);
		divide(rt);
	}
}
void divide_tree(int n){
	MX=1e9;SZ=n;
	findrt(1,0);
	divide(rt);
}
