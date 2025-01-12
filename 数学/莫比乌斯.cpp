const int maxn=2e5+5;
bool p[maxn];
int pr[maxn],tot,phi[maxn],mu[maxn];
void get(int n){
    p[1]=phi[1]=mu[1]=1;
    for(int i=2;i<n;i++){
        if(!p[i])p[i]=1,mu[i]=-1,pr[++tot]=i,phi[i]=i-1;
        for(int j=1;j<=tot&&i*pr[j]<n;j++){
            p[i*pr[j]]=1;
            if(i%pr[j]){
                mu[i*pr[j]]=-mu[i];
                phi[i*pr[j]]=phi[i]*phi[pr[j]];
            }else{
                phi[pr[j]*i]=phi[i]*pr[j];
                break;
            }
        }
    }
}