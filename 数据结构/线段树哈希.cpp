constexpr long long BASE1 = 233, MOD1 = 1004535809;
long long qp(long long a,long long b){
	long long ans=1;
	while(b){
		if(b&1){
			ans=a*ans%MOD1;	
		}
		a=a*a%MOD1;
		b>>=1;
	}
	return ans;
}
long long ny=qp(BASE1-1,MOD1-2),mod=65536;
struct TR{
#define ls k<<1
#define rs k<<1|1
	int n;
	struct node{
		int l,r;
		long long s,mx,mn,lazy;
	};
	vector<node>tr;
	vector<long long>p;
	void PushUp(node& x,node& l,node& r){
		x.l=l.l,x.r=r.r;
		int len=r.r-r.l+1;
		x.s=(l.s*p[len]%MOD1+r.s)%MOD1;
		x.mx=max(l.mx,r.mx);
		x.mn=min(l.mn,r.mn);
	}
	void UpData(node& x,long long v){
		int len=x.r-x.l+1;
		x.s=(x.s+(p[len]-1+MOD1)%MOD1*ny%MOD1*v)%MOD1;
		x.lazy+=v;x.mx+=v;x.mn+=v;
	}
	void PushDown(node& x,node& l,node& r){
		if(x.lazy==0)return;
		UpData(l,x.lazy);UpData(r,x.lazy);x.lazy=0;
	}
	void PushUp(int k){PushUp(tr[k],tr[ls],tr[rs]);}
	void PushDown(int k){PushDown(tr[k],tr[ls],tr[rs]);}
	void init(vector<int> &a) {
		n = a.size()-1;
		tr.assign((n+1)<<2,{0});
		p.assign((n+1),{0});
		p[0]=1;
		for(int i=1;i<=n;i++)p[i]=(p[i-1]*BASE1)%MOD1;
		auto build =[&](auto self,int k,int l,int r)->void{
			if(l==r)tr[k]={l,r,a[l],a[l],a[l]};
			else{
				tr[k]={0};
				int m=l+((r-l)>>1);
				self(self,ls,l,m);self(self,rs,m+1,r);
				PushUp(k);
			}
		};
		build(build,1,1,n);
	}
	node Query(int L,int R){return Query(L,R,1,n,1);}
	node Query(int L,int R,int l,int r,int k){
		if(L<=l&&r<=R)return tr[k];
		PushDown(k);
		int m=l+((r-l)>>1);
		if(R<=m)return Query(L,R,l,m,ls);
		if(L>=m+1)return Query(L,R,m+1,r,rs);
		node res={0},left=Query(L,R,l,m,ls),right=Query(L,R,m+1,r,rs);
		PushUp(res,left,right);
		return res; 
	}
	void Change(int L,int R,long long v){Change(L,R,v,1,n,1);}
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
	vector<int> find(){return find(1,n,1);}
	vector<int> find(int l,int r,int k){
		if(l==r)return {l};
		vector<int>resl,resr;
		int mid=l+r>>1;
		PushDown(k);
		if(tr[ls].mx==mod)resl=find(l,mid,ls);
		if(tr[rs].mx==mod)resr=find(mid+1,r,rs);
		for(auto it:resr)resl.push_back(it);
		return resl;
	}
}t;
