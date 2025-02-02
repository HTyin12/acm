int w;
struct Complex{
    int x,y;
    Complex(int _x=0,int _y=0):x(_x),y(_y){}
    friend Complex operator *(const Complex a,const Complex b){
        return Complex((a.x*b.x%P+w*a.y%P*b.y%P)%P,(a.x*b.y%P+a.y*b.x%P)%P);
    }
};
int fastpow(Complex a,int b){
    Complex ans(1,0);
    while(b){if(b&1)ans=ans*a;a=a*a;b>>=1;}
    return ans.x;
}
int Cipolla(int x){
    srand(time(0));
    if(x<=1)return x;
    if(fastpow(x,(P-1)>>1)==P-1)return -1;
    while(1){
        int a=(1ll*rand()<<15|rand())%P;
        w=(a*a%P+P-x)%P;
        if(fastpow(w,(P-1)>>1)==P-1){
            int res=fastpow(Complex(a,1),(P+1)>>1);
            return min(res,P-res);
        }
    }
}