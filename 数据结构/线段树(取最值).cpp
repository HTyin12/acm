#define N 1000005
const long long INF=1e18;
long long a[N],t[N<<2],lazy[N<<2];
void PushUp(int k){
	t[k]=max(t[k<<1],t[k<<1|1]);
}
void build(int k,int l,int r){
	if(l==r)t[k]=a[l];
	else{
		int m=l+((r-l)>>1);
		build(k<<1,l,m);
		build(k<<1|1,m+1,r);
		PushUp(k);
	}
}
void PushDown(int k,int l,int r){
	if(lazy[k]){
        int m=l+((r-l)>>1);
		lazy[k<<1]+=lazy[k];
		lazy[k<<1|1]+=lazy[k];
		t[k<<1]+=lazy[k];
		t[k<<1|1]+=lazy[k];
		lazy[k]=0;
	}
}
long long Query(int L,int R,int l,int r,int k){
	if(L<=l&&r<=R)return t[k];
	else{
        PushDown(k,l,r);
		long long res=-INF;
		int m=l+((r-l)>>1);
		if(L<=m)res=max(res,Query(L,R,l,m,k<<1));
		if(R>=m+1)res=max(res,Query(L,R,m+1,r,k<<1|1));
		return res;	
	}
}
void Add(int L,int R,int v,int l,int r,int k){
	if(L<=l&&r<=R){
		lazy[k]+=v;
		t[k]+=v;
	}
	else{
		PushDown(k,l,r);
		int m=l+((r-l)>>1);
		if(L<=m)Add(L,R,v,l,m,k<<1);
		if(R>=m+1)Add(L,R,v,m+1,r,k<<1|1);
		PushUp(k);
	}
}