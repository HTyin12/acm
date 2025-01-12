const int N=2e5+5;
long long ex_gcd(long long a,long long b,long long &x,long long &y){
    if(!b){x=1;y=0;return a;}
    long long d=ex_gcd(b,a%b,y,x);
    y-=a/b*x;
    return d;
}
long long excrt(int n,long long m[],long long r[]){
    long long m1,m2,r1,r2,p,q;
    m1=m[1],r1=r[1];
    for(int i=2;i<=n;i++){
        m2=m[i],r2=r[i];
        long long d=ex_gcd(m1,m2,p,q);
        if((r2-r1)%d)return -1;
        p=p*(r2-r1)/d;
        p=(p%(m2/d)+m2/d)%(m2/d);
        r1=m1*p+r1;
        m1=m1*m2/d;
    }
    return (r1%m1+m1)%m1;
}