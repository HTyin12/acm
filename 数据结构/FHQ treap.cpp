mt19937 rng (chrono::steady_clock::now().time_since_epoch().count());
const int N=4e6+5;
int idx,root,t1,t2,t3;
struct node{
	int ls,rs,val,pri,sz,sum,mx,mxl,mxr,lazyc,lazyr;
}tr[N];
int top,Space[N];
int newnode(int x){
	int id=top?Space[top--]:++idx;
	tr[id]={0,0,x,(int)rng(),1,x,x,max(0,x),max(0,x)};
	return id;
}
void pushup(int u){
	tr[u].sz=tr[tr[u].ls].sz+tr[tr[u].rs].sz+1;
	tr[u].sum=tr[tr[u].ls].sum+tr[tr[u].rs].sum+tr[u].val;
	tr[u].mxl=max({tr[tr[u].ls].mxl,tr[tr[u].rs].mxl+tr[tr[u].ls].sum+tr[u].val});
	tr[u].mxr=max({tr[tr[u].rs].mxr,tr[tr[u].ls].mxr+tr[tr[u].rs].sum+tr[u].val});
	tr[u].mx=tr[tr[u].ls].mxr+tr[tr[u].rs].mxl+tr[u].val;
	if(tr[u].ls)tr[u].mx=max(tr[u].mx,tr[tr[u].ls].mx);
	if(tr[u].rs)tr[u].mx=max(tr[u].mx,tr[tr[u].rs].mx);
}
void cover(int x,int v){
	tr[x].val=v;
	tr[x].sum=tr[x].sz*v;
	tr[x].mxl=tr[x].mxr=max(0,tr[x].sum);
	tr[x].mx=max(v,tr[x].sum);
	tr[x].lazyc=1;
}
void roate(int x){
	swap(tr[x].ls,tr[x].rs);
	swap(tr[x].mxl,tr[x].mxr);
	tr[x].lazyr^=1;
}
void pushdown(int u){
	if(tr[u].lazyr){
		roate(tr[u].ls);roate(tr[u].rs);
		tr[u].lazyr=0;
	}
	if(tr[u].lazyc){
		cover(tr[u].ls,tr[u].val);cover(tr[u].rs,tr[u].val);
		tr[u].lazyc=0;
	}
}
void split(int u,int x,int &L,int &R){
	if(!u){L=R=0;return;}
	if(tr[u].val<=x){L=u;split(tr[u].rs,x,tr[u].rs,R);}
	else {R=u;split(tr[u].ls,x,L,tr[u].ls);}
	pushup(u);
}
void splitrk(int u,int x,int &L,int &R){
	if(!u){L=R=0;return;}
	pushdown(u);
	if(tr[tr[u].ls].sz+1<=x){L=u;splitrk(tr[u].rs,x-tr[tr[u].ls].sz-1,tr[u].rs,R);}
	else {R=u;splitrk(tr[u].ls,x,L,tr[u].ls);}
	pushup(u);
}
int merge(int L,int R){
	if(!L||!R)return L+R;
	if(tr[L].pri>tr[R].pri){pushdown(L),tr[L].rs=merge(tr[L].rs,R);pushup(L);return L;}
	else {pushdown(R),tr[R].ls=merge(L,tr[R].ls);pushup(R);return R;}
}
void insert(int x){
	split(root,x,t1,t2);
	root=merge(merge(t1,newnode(x)),t2);
}
void remove(int x){
	Space[++top]=x;
}
void erase(int x){
	split(root,x,t1,t2);
	split(t1,x-1,t1,t3);
	remove(t3);
	t3=merge(tr[t3].ls,tr[t3].rs);
	root=merge(merge(t1,t3),t2);
}
int rk(int x){
	split(root,x-1,t1,t2);
	int ans=tr[t1].sz+1;
	root=merge(t1,t2);
	return ans;
}
int kth(int u,int k){
	if(k==tr[tr[u].ls].sz+1)return u;
	else if(k<=tr[tr[u].ls].sz)return kth(tr[u].ls,k);
	else return kth(tr[u].rs,k-tr[tr[u].ls].sz-1);
}
int pre(int x){
	split(root,x-1,t1,t2);
	int ans=tr[kth(t1,tr[t1].sz)].val;
	merge(t1,t2);
	return ans;
}
int nxt(int x){
	split(root,x,t1,t2);
	int ans=tr[kth(t2,1)].val;
	root=merge(t1,t2);
	return ans;
}
void inorder(int u){
	if(!u)return;
	pushdown(u);
	inorder(tr[u].ls);cout<<tr[u].val<<' ';inorder(tr[u].rs);
}
