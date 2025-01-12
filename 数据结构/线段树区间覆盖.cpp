#define int long long
const int N=2e6+5;
#define ls k<<1
#define rs k<<1|1
long long a[N];
struct node{
    int l,r;
    long long s,mx,mn,lazy,tag;
}tr[N<<2];
void PushUp(node& x,node& l,node& r){
    x.mx=max(l.mx,r.mx);
    x.mn=min(l.mn,r.mn);
    x.s=l.s+r.s;
}
void UpData(node& x,long long v,int op){
    if(op==1){
        x.tag=v;x.mx=x.mn=v;x.s=(x.r-x.l+1)*v;
    }else{
        x.mx+=v;x.mn+=v;x.s+=(x.r-x.l+1)*v;
        if(x.tag!=1e18){
            x.tag+=v;
        }
        else x.lazy+=v;
    }
}
void PushDown(node& x,node& l,node& r){
    if(x.tag!=1e18){
        UpData(l,x.tag,1);
        UpData(r,x.tag,1);
        x.tag=1e18;x.lazy=0;
    }else if(x.lazy){
        UpData(l,x.lazy,0);
        UpData(r,x.lazy,0);
        x.lazy=0;
    }
}
void PushUp(int k){PushUp(tr[k],tr[ls],tr[rs]);}
void PushDown(int k){PushDown(tr[k],tr[ls],tr[rs]);}
void build(int k,int l,int r){
    if(l==r)tr[k]={l,r,a[l],a[l],a[l],0,(int)1e18};
    else{
        tr[k]={l,r,0,0,0,0,(int)1e18};
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
void Change(int L,int R,long long v,int l,int r,int k,int op){
    if(L<=l&&r<=R){
        UpData(tr[k],v,op);
    }
    else{
        PushDown(k);
        int m=l+((r-l)>>1);
        if(R<=m)return Change(L,R,v,l,m,ls,op),PushUp(k);
        if(L>=m+1)return Change(L,R,v,m+1,r,rs,op),PushUp(k);
        Change(L,R,v,l,m,ls,op),Change(L,R,v,m+1,r,rs,op),PushUp(k);
    }
}