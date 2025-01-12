long long mul(long long a,long long b,long long mod)
{
    long long c=(long double)a/mod*b;
    long long res=(unsigned long long)a*b-(unsigned long long)c*mod;
    return (res+mod)%mod;
}
long long fast_pow(long long a,long long n,long long mod)
{
    long long res=1;
    while(n)
    {
        if(n&1) res=mul(res,a,mod);
        a=mul(a,a,mod);
        n>>=1;
    }
    return res;
}
bool MRtest(long long n)
{
    if(n<3||n%2==0) return n==2;
    long long u=n-1,t=0;
    while(u%2==0) u/=2,++t;
    long long ud[]={2,325,9375,28178,450775,9780504,1795265022};
    for(long long a:ud)
    {
        long long v=fast_pow(a,u,n);
        if(v==1||v==n-1||v==0) continue;
        for(int j=1;j<=t;j++)
        {
            v=mul(v,v,n);
            if(v==n-1&&j!=t){v=1;break;}
            if(v==1) return 0;
        }
        if(v!=1) return 0;
    }
    return 1;
}
