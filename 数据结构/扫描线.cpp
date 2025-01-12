const int N=1e5+5;
#define ls k<<1
#define rs k<<1|1
long long a[N];
struct node{
	double s;int lazy;
}tr[N<<2];
vector<double>b;
void PushUp(int k,int l,int r){
	if(tr[k].lazy){
		tr[k].s=b[r-1]-b[l-1];
	}else{
		tr[k].s=tr[ls].s+tr[rs].s;
	}
}
void updata(int L,int R,int v,int l,int r,int k){
	if(L<=l&&r<=R){
		tr[k].lazy+=v;
		PushUp(k,l,r);
		return;
	}
	int m=l+r>>1;
	if(m>L)updata(L,R,v,l,m,ls);
	if(m<R)updata(L,R,v,m,r,rs);
	PushUp(k,l,r);
}
struct Line{
	double y,l,r;int f;
}line[N];
int idx;
int li(double x){
	return (int)(lower_bound(b.begin(),b.end(),x)-b.begin()+1);
}
