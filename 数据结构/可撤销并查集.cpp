const int N=2e5+5;
int fa[N],stkx[N],stky[N],sz[N],tp,nt[N];
int find(int x){
	if(fa[x]==x)return x;
	return find(fa[x]);
}
void merge(int x,int y,int z){
	if((x=find(x))==(y=find(y)))return;
	if(sz[x]>sz[y])swap(x,y);
	fa[x]=y,stkx[++tp]=x,stky[tp]=y,sz[y]+=sz[x],nt[tp]=z;
}
void undo(){//撤销的时候要检查一下
	sz[stky[tp]]-=sz[stkx[tp]];
	fa[stkx[tp]]=stkx[tp];
	tp--;
}