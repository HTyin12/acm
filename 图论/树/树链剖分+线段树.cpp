const int N=2e5+5;
#define ls k<<1
#define rs k<<1|1
long long a[N],a_new[N],n;
struct node{
	int l,r;
	long long s,mx,mn,lazy;
}tr[N<<2];
void PushUp(node& x,node& l,node& r){
	x.s=l.s+r.s;
	x.mx=max(l.mx,r.mx);
	x.mn=min(l.mn,r.mn);
}
void UpData(node& x,long long v){
	x.lazy+=v;x.s+=v*(x.r-x.l+1);x.mx+=v;x.mn+=v;
}
void PushDown(node& x,node& l,node& r){
	if(x.lazy==0)return;
	UpData(l,x.lazy);UpData(r,x.lazy);x.lazy=0;
}
void PushUp(int k){PushUp(tr[k],tr[ls],tr[rs]);}
void PushDown(int k){PushDown(tr[k],tr[ls],tr[rs]);}
void build(int k,int l,int r){
	if(l==r)tr[k]={l,r,a_new[l],a_new[l],a_new[l]};
	else{
		tr[k]={l,r};
		int m=l+((r-l)>>1);
		build(ls,l,m);build(rs,m+1,r);
		PushUp(k);
	}
}
node Query(int L,int R,int l,int r,int k){
	if(L<=l&&r<=R)return tr[k];
	PushDown(k);
	int m=l+((r-l)>>1);
	if(R<=m)return Query(L,R,l,m,ls);
	if(L>=m+1)return Query(L,R,m+1,r,rs);
	node res,left=Query(L,R,l,m,ls),right=Query(L,R,m+1,r,rs);
	PushUp(res,left,right);
	return res; 
}
void Change(int L,int R,long long v,int l,int r,int k){
	if(L<=l&&r<=R){
		UpData(tr[k],v);
	}
	else{
		PushDown(k);
		int m=l+((r-l)>>1);
		if(R<=m)return Change(L,R,v,l,m,ls),PushUp(k);
		if(L>=m+1)return Change(L,R,v,m+1,r,rs),PushUp(k);
		Change(L,R,v,l,m,ls),Change(L,R,v,m+1,r,rs),PushUp(k);
	}
}
vector<int>p[N];
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
	a_new[idx]=a[u];
	top[u]=t;
	if(!son[u])return;
	dfs2(son[u],t);
	for(auto v:p[u]){
		if(v==fa[u]||v==son[u])continue;
		dfs2(v,v);
	}
}
int LCA(int u,int v){
	while(top[u]!=top[v]){
		if(dep[top[u]]<dep[top[v]])swap(u,v);
		u=fa[top[u]];
	}
	return dep[u]<dep[v]?u:v;
}
void updata_range(int u,int v,int z){
	while(top[u]!=top[v]){
		if(dep[top[u]]<dep[top[v]])swap(u,v);
		Change(id[top[u]],id[u],z,1,n,1);
		u=fa[top[u]];
	}
	if(dep[u]>dep[v])swap(u,v);
	Change(id[u],id[v],z,1,n,1);
}
node query_range(int x,int y){
	node ans={0};
	ans.mx=-1e9;ans.mn=1e9;
	while(top[x]!=top[y]){
		if(dep[top[x]]<dep[top[y]])swap(x,y);
		auto res=Query(id[top[x]],id[x],1,n,1);
		PushUp(ans,ans,res);
		x=fa[top[x]];
	}
	if(dep[x]>dep[y])swap(x,y);
	auto res=Query(id[x],id[y],1,n,1);
	PushUp(ans,ans,res);
	return ans;
}
void updata_tree(int x,long long v){Change(id[x],id[x]+sz[x]-1,v,1,n,1);}
long long query_tree(int x){return Query(id[x],id[x]+sz[x]-1,1,n,1).s;}
