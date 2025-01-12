const int N=1e6;
long long vis[N],prime[N],phi[N];
void get_phi(void){
    phi[1]=1;
    int cnt=0;
    for(int i=2;i<=N;i++){
        if(!vis[i]){
            prime[cnt++]=i;
            phi[i]=i-1;
        }
        for(int j=0;j<cnt&&i*prime[j]<=N;j++){
            vis[i*prime[j]]=1;
            if(i%prime[j]==0){
                phi[i*prime[j]]=phi[i]*prime[j];
                break;
            }
            phi[i*prime[j]]=phi[i]*(prime[j]-1);
        }
    }
}

long long phi(long long x)
{
    long long res = x;
    for (long long i = 2; i <= x / i; i ++ )
        if (x % i == 0)
        {
            res = res / i * (i - 1);
            while (x % i == 0) x /= i;
        }
    if (x > 1) res = res / x * (x - 1);

    return res;
}
