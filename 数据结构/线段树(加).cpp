const int N=1e5+5;
#define ls k<<1
#define rs k<<1|1
long long a[N];
struct node{
    int l,r;
    long long s,add;
}t[N<<2];
void PushUp(node& x,node& l,node& r){
	x.s=l.s+r.s;
}
void PushUp(int k){
	PushUp(t[k],t[ls],t[rs]);
}
void build(int k,int l,int r){
	if(l==r)t[k]={l,l,a[l]};
	else{
		t[k]={l,r};
		int m=l+((r-l)>>1);
		build(k<<1,l,m);
		build(k<<1|1,m+1,r);
		PushUp(k);
	}
}
void PushDown(int k,int l,int r){
	if(t[k].add){
        int m=l+((r-l)>>1);
		t[ls].add+=t[k].add;t[rs].add+=t[k].add;
		t[ls].s+=t[k].add*(m-l+1);t[rs].s+=t[k].add*(r-m);
		t[k].add=0;
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
void Add(int L,int R,int v,int l,int r,int k){
	if(L<=l&&r<=R){
		t[k].add+=v;
		t[k].s+=1LL*v*(r-l+1);
	}
	else{
		PushDown(k,l,r);
		int m=l+((r-l)>>1);
		if(L<=m)Add(L,R,v,l,m,k<<1);
		if(R>=m+1)Add(L,R,v,m+1,r,k<<1|1);
		PushUp(k);
	}
}