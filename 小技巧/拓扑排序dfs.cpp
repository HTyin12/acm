#include <bits/stdc++.h>
using namespace std;
int n,m;
vector<int>p[30005];
bool c[30005];
int ans[30005],cnt;
bool dfs(int x,int k){
	c[x]=-1;
	for(auto it:p[x]){
		if(c[it]<0)return false;
		else if(!c[it]&&!dfs(it,k+1)) return false;
	}
	c[x]=1;
	ans[cnt--]=x;
	return true;
}
void solve(void)
{
	cin>>n>>m;cnt=n;
	for(int i=1;i<=n;i++)p[i].clear(),c[i]=0,ans[i]=i;
	for(int i=1;i<=m;i++){
		int a,b;cin>>a>>b;p[a].push_back(b);
	}
	int flag=0;
	for(int i=1;i<=n;i++){
		if(!c[i]&&!dfs(i,1)){flag=1;break;}
	}
	if(flag){
		cout<<-1<<'\n';
	}else{
		for(int i=1;i<=n;i++)cout<<ans[i]<<' ';cout<<'\n';
	}
}
int main(void){
	std::ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	int t;
	cin>>t;
	while(t--)
	solve();
	return 0;
}
