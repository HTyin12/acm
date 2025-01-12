const int N=1e4+5;
bool zero;
long long a[N];
int cnt=0;
int Gauss(int n){
    int i,k=1;
    long long j=(long long)1<<62;
    for(;j;j>>=1){
        for(i=k;i<=n;i++)if(a[i]&j)break;
        if(i>n)continue;
        swap(a[i],a[k]);
        for(i=1;i<=n;i++)if(i!=k&&a[i]&j)a[i]^=a[k];
        k++;
    }
    k--;
    if(k!=n)zero=1;
    else zero=0;
    return k;
}
long long Query(long long x,int m){
    long long ans=0;
    if(zero)x--;
    if(!x)return 0;
    for(int i=m;i;i--){
        if(x&1)ans^=a[i];
        x>>=1;
    }
    if(x)return -1;
    return ans;
}