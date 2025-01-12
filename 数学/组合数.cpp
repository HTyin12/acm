const int N=1e6,mod=1e9+7;
long long fac[N+5],inv[N+5];
long long qp(long long a,long long b){
    long long ans=1;
    while(b){
        if(b&1)ans*=a,ans%=mod;
        a=a*a;a%=mod;
        b>>=1;
    }
    return ans;
}
void init(void){
    fac[0]=fac[1]=1;
    for(int i=2;i<=N;i++)fac[i]=fac[i-1]*i%mod;
    inv[N]=qp(fac[N],mod-2);
    for(int i=N-1;i>=0;i--)inv[i]=inv[i+1]*(i+1)%mod;
}
long long C(long long n,long long m){if(n<m||n<0||m<0)return 0;return fac[n]*inv[m]%mod*inv[n-m]%mod;}
