struct Node{
	int l,r;
	unsigned long long sum,cnt,lz;
}tr[21<<19];
int tot,root[1<<21];
void pushup(int x){
	tr[u].cnt=tr[tr[u].l].cnt+tr[tr[u].r].cnt;
	tr[u].sum=tr[tr[u].l].sum+tr[tr[u].r].sum;
}
void pushdown(int x){
	if(tr[x].lz==0)return;
	if(tr[x].l)tr[tr[x].l].sum+=tr[x].lz,tr[tr[x].l].lz+=tr[x].lz;
	if(tr[x].r)tr[tr[x].r].sum+=tr[x].lz,tr[tr[x].r].lz+=tr[x].lz;
	tr[x].lz=0;
}
void add(int &t,int l,int r,long long x){
	if(!t)t=++tot;
	{
		tr[t].cnt++;
		tr[t].sum+=x*x;	
	}
	if(l==r)return;
	int mid=l+r>>1;
	if(x<=mid)add(tr[t].l,l,mid,x);
	else add(tr[t].r,mid+1,r,x);
	pushup(t);
}
void merge(int a,int &b,int l,int r,unsigned long long&ans){
	if(!a||!b){
		b+=a;
		//lz
		return;
	}
	{
		ans+=(tr[tr[a].l].cnt*tr[tr[b].r].sum+tr[tr[b].l].cnt*tr[tr[a].r].sum)*2;
		if(l==r){
			ans+=(tr[a].cnt*tr[b].sum+tr[b].cnt*tr[a].sum);
		}
		tr[b].cnt+=tr[a].cnt;
		tr[b].sum+=tr[a].sum;
		pushdown(a);
		pushdown(b);
	}
	if(l==r){
		return;
	}
	int mid=l+r>>1;
	merge(tr[a].l,tr[b].l,l,mid,ans);
	merge(tr[a].r,tr[b].r,mid+1,r,ans);
	pushup(b);
}
int query(int x,int l,int r){
	if(tr[x].cnt==0)return 0;
	if(l==r){
		return l;
	}
	pushdown(x);
	int mid=l+r>>1;
	if(tr[tr[x].l].cnt>=tr[tr[x].r].cnt)return query(tr[x].l,l,mid);
	return query(tr[x].r,mid+1,r);
}
void change(int x,int l,int r,int L,int R,int v){
	if(!x)return;
	if(L<=l&&r<=R){
		tr[x].sum+=v;
		tr[x].lz+=v;
	}
	else{
		pushdown(x);
		int m=l+r>>1;
		if(R<=m)return change(tr[x].l,l,m,L,R,v),pushup(x);
		if(L>=m+1)return change(tr[x].l,m+1,r,L,R,v),pushup(x);
		change(tr[x].l,l,m,L,R,v),change(tr[x].l,m+1,r,L,R,v),pushup(x);
	}
}
void split(int &a,int &b,int L,int R,int l,int r){
	if(l>=L&&r<=R){
		b=a;a=0;
		return;
	}
	int mid=l+r>>1;
	if(L<=mid)split(tr[a].l,tr[b].l,L,R,l,mid);
	if(R>mid)split(tr[a].r,tr[b].r,L,R,mid+1,r);
	pushup(a);
	pushup(b);
}
