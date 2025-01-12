const int N=1e3+5;
long long c[N][N];
int n,m;
int lowbit(int x){return x & -x;}
//点(x,y)增加z 
void add(int x,int y,int z){
    for(int i=x;i<=n;i+=lowbit(i))
        for(int j=y;j<=m;j+=lowbit(j))
            c[i][j]+=z;
}
//求左上角为(1,1)右下角为(x,y) 的矩阵和
long long ask(int x,int y){
    long long tot=0;
    for(int i=x;i;i-=lowbit(i))
        for(int j=y;j;j-=lowbit(j))
            tot+=c[i][j];
    return tot;
}