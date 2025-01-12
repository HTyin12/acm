const int N=1e6+5;
#define ls k<<1
#define rs k<<1|1
long long a[N];
struct node{
    int l,r;
    long long s,add,mul;
}t[N<<2];
long long mod;
void PushUp(node& x,node& l,node& r){
	x.s=(l.s+r.s)%mod;
}
void PushUp(int k){
	PushUp(t[k],t[ls],t[rs]);
}
void build(int k,int l,int r){
	if(l==r)t[k]={l,l,a[l],0,1};
	else{
		t[k]={l,r,0,0,1};
		int m=l+((r-l)>>1);
		build(k<<1,l,m);
		build(k<<1|1,m+1,r);
		PushUp(k);
	}
}
void PushDown(int k,int l,int r){
        int m=l+((r-l)>>1);
		t[ls].mul=t[ls].mul*t[k].mul%mod;
		t[rs].mul=t[rs].mul*t[k].mul%mod;
		t[ls].add=(t[ls].add*t[k].mul%mod+t[k].add)%mod;
		t[rs].add=(t[rs].add*t[k].mul%mod+t[k].add)%mod;
		t[ls].s=(t[ls].s*t[k].mul%mod+t[k].add*(m-l+1))%mod;
		t[rs].s=(t[rs].s*t[k].mul%mod+t[k].add*(r-m))%mod;
		t[k].add=0,t[k].mul=1;
}
void Add(int L,int R,int v,int l,int r,int k){
	if(L<=l&&r<=R){
		t[k].add=(t[k].add+v)%mod;
		t[k].s=(t[k].s+1LL*v*(r-l+1))%mod;
	}
	else{
		PushDown(k,l,r);
		int m=l+((r-l)>>1);
		if(L<=m)Add(L,R,v,l,m,k<<1);
		if(R>=m+1)Add(L,R,v,m+1,r,k<<1|1);
		PushUp(k);
	}
}
void Mul(int L,int R,int v,int l,int r,int k){
	if(L<=l&&r<=R){
		t[k].mul=t[k].mul*v%mod;
        t[k].add=t[k].add*v%mod;
        t[k].s=t[k].s*v%mod;
	}
	else{
        PushDown(k,l,r);
		int m=l+((r-l)>>1);
		if(L<=m)Mul(L,R,v,l,m,k<<1);
		if(R>=m+1)Mul(L,R,v,m+1,r,k<<1|1);
		PushUp(k);
	}
}
node Query(int L,int R,int l,int r,int k){
	if(L<=l&&r<=R)return t[k];
	else{
        PushDown(k,l,r);
		int m=l+((r-l)>>1);
		if(R<=m)return Query(L,R,l,m,k<<1);
		if(L>=m+1)return Query(L,R,m+1,r,k<<1|1);
        node res,left=Query(L,R,l,m,k<<1),right=Query(L,R,m+1,r,k<<1|1);
		PushUp(res,left,right);
		return res;	
	}
}