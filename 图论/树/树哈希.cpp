const int N=2e5+5;
vector<int>p[N];
int f[N];
long long Hash[N],seed=rand()*rand()*rand()*rand()*rand();
//srand(time(0));
// const unsigned long long mask = std::chrono::steady_clock::now().time_since_epoch().count();
long long getHash(long long x){
    // x^=mask;
    x^=x<<13;
    x^=x>>7;
    x^=x<<17;
    // x^=mask;
    return x;
}
void dfs(int x,int fa){
    long long sum=seed,res=0;
    for(auto it:p[x]){
        if(it==fa)continue;
        dfs(it,x);
        sum+=getHash(Hash[it]);
        res^=getHash(Hash[it]);
    }
    Hash[x]=sum;
}