const int N=2e5+5;
struct Node{
	int a,b,c,v,f,id;
}a[N],b[N];
long long t[N];
#define lowbit(x) ((x)&(-x))
void add(int x,long long k){while(x<N)t[x]+=k,x+=lowbit(x);}
long long ask(int x){long long ans=0;while(x)ans+=t[x],x-=lowbit(x);return ans;}
bool cmpx(Node x,Node y){
	if(x.a!=y.a)return x.a<y.a;
	if(x.b!=y.b)return x.b<y.b;
	return x.c<y.c;
}
int ans[N];
bool cmpy(Node x,Node y){
	return x.b>y.b;
}
void merge(int l,int r){
	int mid=l+r>>1;
	int pl=l,pr=mid+1;
	for(int i=1;i<=r-l+1;i++){
		if(pl<=mid&&pr<=r&&a[pl].b>=a[pr].b||pr>r){
			a[pl].f=1;
			add(a[pl].c,1);
			pl++;
		}else{
			ans[a[pr].id]+=ask(a[pr].c);
			pr++;
		}
	}
	for(int i=1;i<=r-l+1;i++){
		if(a[l+i-1].f){
			add(a[l+i-1].c,-1);
			a[l+i-1].f=0;
		}
	}
}
void cdq(int l,int r){
	if(l==r)return;
	int mid=l+r>>1;
	cdq(l,mid);
	sort(a+l,a+mid+1,cmpy);
	sort(a+mid+1,a+r+1,cmpy);
	merge(l,r);
	sort(a+mid+1,a+r+1,cmpx);
	cdq(mid+1,r);
}
