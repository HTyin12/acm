const int N=2e3+7;
int n1,n2,m,f[N],v[N],fid;
vector<int>p[N];
bool dfs(int x){
    for(auto it:p[x]){
        if(v[it]-fid==0)continue;
        v[it] = fid;
        if(!f[it]||dfs(f[it]))
        return f[it]=x,1;
    }
    return 0;
}
int xyl(void){//O(nm)
    int ans = 0;fid=1;
    // n1左部数量 n2右部数量
    for(int i=1;i<=m;i++){
        int x,y;cin>>x>>y;
        // y+=n1;
        p[x].push_back(y);
        p[y].push_back(x);
    }
    for(int i=1;i<=n1;i++,fid++){
        ans+=dfs(i);
    }
    return ans;
}
