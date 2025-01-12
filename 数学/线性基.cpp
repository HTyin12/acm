const int M=63;
long long p[M+5];
int zero;
void Insert(long long x){
    for(int i=M;i>=0;i--)
    if(x>>i)
    if(p[i]==0){p[i]=x;return;}
    else x^=p[i];
    zero++;
}
