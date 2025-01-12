long long ex_gcd(long long a,long long b,long long &x,long long &y)
{
    if(!b){x=1;y=0;return a;}
    long long d=ex_gcd(b,a%b,y,x);
    y-=a/b*x;
    return d;
}
long long getInv(int a,int mod)//求a在mod下的逆元，不存在逆元返回-1 
{
    long long x,y;
    long long d=ex_gcd(a,mod,x,y);
    return d==1?(x%mod+mod)%mod:-1;
}

//线性求逆元
const int N=2e5+5;
const int mod=;
long long inv[N];
void getinv(int n){
    inv[1]=1;
    for(int i=2;i<=n;i++)inv[i]=(mod-mod/i)*inv[mod%i]%mod;
}