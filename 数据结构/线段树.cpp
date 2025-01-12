struct TR{
#define ls k<<1
#define rs k<<1|1
	int n;
	struct node{
		int l,r;
		long long s,mx,mn,lazy;
	};
	vector<node>tr;
	void PushUp(node& x,node& l,node& r){
		x.l=l.l,x.r=r.r;
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
	void init(vector<int> &a){
		n = a.size()-1;
		tr.assign((n+1)<<2,{});
		auto build =[&](auto self,int k,int l,int r)->void{
			if(l==r)tr[k]={l,r,a[l],a[l],a[l]};
			else{
				tr[k]={0};
				int m=l+r>>1;
				self(self,ls,l,m);self(self,rs,m+1,r);
				PushUp(k);
			}
		};
		build(build,1,1,n);
	}
	void init(int m){
		n = m;
		tr.assign((n+1)<<2,{});
		auto build =[&](auto self,int k,int l,int r)->void{
			if(l==r)tr[k]={l,r};
			else{
				tr[k]={0};
				int m=l+r>>1;
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
		int m=l+r>>1;
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
			int m=l+r>>1;
			if(R<=m)return Change(L,R,v,l,m,ls),PushUp(k);
			if(L>=m+1)return Change(L,R,v,m+1,r,rs),PushUp(k);
			Change(L,R,v,l,m,ls),Change(L,R,v,m+1,r,rs),PushUp(k);
		}
	}
	int Qm(int L,int R,int x){return Qm(L,R,x,1,n,1);}
	int Qm(int L,int R,int x,int l,int r,int k){
		if(L<=l&&r<=R){
			if(tr[k].mx<x)return 0;//第一个大于等于x
			// if(tr[k].mn>x)return 0;
			// if(tr[k].mn>x||tr[k].mx<x)return 0;
			else if(l==r)return l;
		}
		PushDown(k);
		int m=l+r>>1;
		if(R<=m)return Qm(L,R,x,l,m,ls);
		if(L>=m+1)return Qm(L,R,x,m+1,r,rs);
		int left=Qm(L,R,x,l,m,ls);
		if(left)return left;
		return Qm(L,R,x,m+1,r,rs); 
	}
}t;
