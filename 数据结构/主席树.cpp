const int N=2e5+5;
int idx,root[N],a[N];
#define lc(x) tr[x].l
#define rc(x) tr[x].r
struct node{
	int l,r;
	long long s,lz;
}tr[N<<5];
void PushUp(node& x,node& l,node& r,int L,int R){
	x.s=l.s+r.s+x.lz*(R-L+1);
}
void PushUp(int k,int l,int r){PushUp(tr[k],tr[lc(k)],tr[rc(k)],l,r);}
void build(int &x,int l,int r){
	x=++idx;tr[x].lz=0;
	if(l==r){tr[x].s=a[l];return;}
	int m=l+r>>1;
	build(lc(x),l,m);
	build(rc(x),m+1,r);
	PushUp(x,l,r);
}
void updata(int x,int &y,int L,int R,long long v,int l,int r){
	y=++idx,tr[y]=tr[x];
	if(l>=L&&r<=R){tr[y].lz+=v,tr[y].s+=v*(r-l+1);return;}
	int m=l+r>>1;
	if(L<=m)updata(lc(x),lc(y),L,R,v,l,m);
	if(m+1<=R)updata(rc(x),rc(y),L,R,v,m+1,r);
	PushUp(y,l,r);
}
void change(int x,int &y,int l,int r,int p,int v){
	y=++idx,tr[y]=tr[x];
	if(l==r){tr[y].s=v;return;}
	int m=l+r>>1;
	if(p<=m)change(lc(x),lc(y),l,m,p,v);
	else change(rc(x),rc(y),m+1,r,p,v);
}
long long query(int x,int L,int R,int l,int r,long long v=0){
	if(l>=L&&r<=R){return v*(r-l+1)+tr[x].s;}
	int m=l+r>>1;
	long long ans=0;
	if(L<=m)ans+=query(lc(x),L,R,l,m,v+tr[x].lz);
	if(m+1<=R)ans+=query(rc(x),L,R,m+1,r,v+tr[x].lz);
	return ans;
}
void add(int x,int &y,int l,int r,int v){
	y=++idx,tr[y]=tr[x],tr[y].s++;
	if(l==r)return;
	int m=l+r>>1;
	if(v<=m)add(lc(x),lc(y),l,m,v);
	else add(rc(x),rc(y),m+1,r,v);
}
int queryk(int x,int y,int l,int r,int k){
	if(l==r)return l;
	int m=l+r>>1;
	int s=tr[lc(y)].s-tr[lc(x)].s;
	if(k<=s)return queryk(lc(x),lc(y),l,m,k);
	else return queryk(rc(x),rc(y),m+1,r,k-s);
}
int querylr(int x,int y,int l,int r,int L,int R){
	if(L<=l&&r<=R)return tr[y].s-tr[x].s;
	int m=l+r>>1;
	int res=0;
	if(L<=m)res+=querylr(lc(x),lc(y),l,m,L,R);
	if(R>m)res+=querylr(rc(x),rc(y),m+1,r,L,R);
	return res;
}
