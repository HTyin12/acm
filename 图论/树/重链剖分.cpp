vector<int>dep(n+1),sz(n+1),son(n+1);
auto dfs1=[&](auto self,int x,int fa)->void{
	dep[x]=dep[fa]+1;sz[x]=1;
	for(auto y:p[x]){
		if(y==fa)continue;
		self(self,y,x);
		sz[x]+=sz[y];
		if(sz[y]>sz[son[x]])son[x]=y;
	}
};
auto dfs2=[&](auto self,int x,int fa,int keep=0)->void{
	for(auto y:p[x]){
		if(y==fa||y==son[x])continue;
		self(self,y,x);
	}
	if(son[x])self(self,son[x],x,1);
	for(auto y:p[x]){
		if(y==fa||y==son[x])continue;
	}
	if(!keep);
};