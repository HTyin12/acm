const int matrixN=5,Mn=2;
const int mod=998244353;
struct matrix{
    long long a[matrixN][matrixN];
    matrix operator *(const matrix &b)const{
        matrix tmp;
        tmp.clear();
        for(int k=1;k<=Mn;k++)
            for(int i=1;i<=Mn;i++)
                for(int j=1;j<=Mn;j++)
                    tmp.a[i][j]=(tmp.a[i][j]+a[i][k]*b.a[k][j]%mod)%mod;
        return tmp;
    }
    matrix operator *=(const matrix &b){
        return *this=*this*b;
    }
    matrix operator +(const matrix &b)const{
        matrix tmp;
        tmp.clear();
        for(int i=1;i<=Mn;i++)
            for(int j=1;j<=Mn;j++)
                tmp.a[i][j]=(a[i][j]+b.a[i][j])%mod;
        return tmp;
    }
    matrix operator +=(const matrix &b){
        return *this=*this+b;
    }
    inline void clear(){
        for(int i=1;i<=Mn;i++)
            for(int j=1;j<=Mn;j++)a[i][j]=0;
    }
    inline void build(){
        for(int i=1;i<=Mn;i++)
            for(int j=1;j<=Mn;j++)
                a[i][j]=(i==j?1:0);
    }
    inline bool isE(){
        for(int i=1;i<=Mn;i++)
            for(int j=1;j<=Mn;j++)
                if((a[i][j]&&i!=j)||(a[i][j]!=1&&i==j))return 0;
        return 1;
    }
    inline void qp(long long x){
        matrix res;res.build();
        while(x){
            if(x&1)res*=*this;
            *this*=*this;
            x>>=1;
        }
        for(int i=1;i<=Mn;i++)
            for(int j=1;j<=Mn;j++)
                a[i][j]=res.a[i][j];
    }
    inline void print(){
        for(int i=1;i<=Mn;i++,cout<<'\n')
            for(int j=1;j<=Mn;j++)cout<<a[i][j]<<' ';
    }
};
const int N=2e5+5;
#define ls k<<1
#define rs k<<1|1
matrix a[N];
struct node{
    int l,r;
    matrix s,lazy;
}tr[N<<2];
void PushUp(node& x,node& l,node& r){
    x.s=l.s*r.s;
}
void UpData(node& x,matrix& v){
    x.lazy*=v;x.s*=v;
}
void PushDown(node& x,node& l,node& r){
    if(x.lazy.isE())return;
    UpData(l,x.lazy);UpData(r,x.lazy);x.lazy.build();
}
void PushUp(int k){PushUp(tr[k],tr[ls],tr[rs]);}
void PushDown(int k){PushDown(tr[k],tr[ls],tr[rs]);}
void build(int k,int l,int r){
    if(l==r)tr[k]={l,r,a[l]},tr[k].lazy.build();
    else{
        tr[k]={l,r};
        tr[k].lazy.build();
        int m=l+((r-l)>>1);
        build(ls,l,m);build(rs,m+1,r);
        PushUp(k);
    }
}
node Query(int L,int R,int l,int r,int k){
    if(L<=l&&r<=R)return tr[k];
    PushDown(k);
    int m=l+((r-l)>>1);
    if(R<=m)return Query(L,R,l,m,ls);
    if(L>=m+1)return Query(L,R,m+1,r,rs);
    node res,left=Query(L,R,l,m,ls),right=Query(L,R,m+1,r,rs);
    PushUp(res,left,right);
    return res; 
}
void Change(int L,int R,matrix v,int l,int r,int k){
    if(L<=l&&r<=R){
        UpData(tr[k],v);
    }
    else{
        PushDown(k);
        int m=l+((r-l)>>1);
        if(R<=m)return Change(L,R,v,l,m,ls),PushUp(k);
        if(L>=m+1)return Change(L,R,v,m+1,r,rs),PushUp(k);
        Change(L,R,v,l,m,ls),Change(L,R,v,m+1,r,rs),PushUp(k);
    }
}