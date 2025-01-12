#include<bits/stdc++.h>
using namespace std;
const int N=2e5+5;
vector<pair<int,int>>p[N<<2];
void dfs(int x,int y,int L,int R,int l,int r,int k){
	if(l>=L&&r<=R){
		p[k].push_back({x,y});
		return;
	}
	int m=l+((r-l)>>1);
	if(R<=m)return dfs(x,y,L,R,l,m,k<<1);
	if(L>=m+1)return dfs(x,y,L,R,m+1,r,k<<1|1);
	dfs(x,y,L,R,l,m,k<<1),dfs(x,y,L,R,m+1,r,k<<1|1);
}
int fa[N],n,h[N];
vector<pair<int,int>>st;
int find(int x){
	while(fa[x]!=x)x=fa[x];
	return x;
}
void merge(int x,int y){
	if(h[x]>h[y])swap(x,y);
	st.push_back({x,h[x]==h[y]});
	fa[x]=y;
	h[y]+=(h[y]==h[x]);
}
int mx;
void dfs2(int l,int r,int k){
	int f=0;
	int pos=st.size();
	for(auto [x,y]:p[k]){
		int fx=find(x),fy=find(y);
		if(fx==fy){
			for(int i=l;i<=r;i++)cout<<"No\n";
			f=1;
			break;
			
		}
		merge(fx,find(y+n));
		merge(fy,find(x+n));
	}
	if(!f){
		if(l==r){
			cout<<"Yes\n";	
		}else{
			int mid=l+r>>1;
			dfs2(l,mid,k<<1);
			dfs2(mid+1,r,k<<1|1);
		}
	}
	while(st.size()>pos){
		auto [x,vis]=*st.rbegin();
		if(vis)h[fa[x]]--;
		fa[x]=x;
		st.pop_back();
	}
}
void solve(){
	int m,k;cin>>n>>m>>k;
	for(int i=1;i<=m;i++){
		int x,y,l,r;cin>>x>>y>>l>>r;
		l++;r++;
		if(l<r)dfs(x,y,l,r-1,1,k,1);
	}
	for(int i=1;i<=2*n;i++)fa[i]=i;
	dfs2(1,k,1);
}
signed main(void) {
	cin.tie(0)->sync_with_stdio(0);
//	int t;cin>>t;
//	while(t--)	
	solve();
}
