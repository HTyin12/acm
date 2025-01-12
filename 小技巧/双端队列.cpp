deque<array<int,2>> dq;
vector l(1,vector(2005,0)),r(1,vector(2005,0));
auto add=[&](vector<int> a,int v,int w){
    for(int i=2000;i>=v;i--)a[i]=max(a[i],a[i-v]+w);
    return a;
};
auto pb=[&](int v,int w)->void{
    dq.push_back({v,w});
    r.push_back(add(r.back(),v,w));
};
auto pf=[&](int v,int w)->void{
    dq.push_front({v,w});
    l.push_back(add(l.back(),v,w));
};
auto rebuild=[&]{//<-l r->
    int m=dq.size(),mid=m>>1;
    l.assign(mid+1,vector(2005,0));
    r.assign(m-mid+1,vector(2005,0));
    for(int i=1;i<=mid;i++){
        l[i]=add(l[i-1],dq[mid-i][0],dq[mid-i][1]);
    }
    for(int i=1;i<=m-mid;i++){
        r[i]=add(r[i-1],dq[mid+i-1][0],dq[mid+i-1][1]);
    }
};
auto ppb=[&]{
    dq.pop_back();
    if(r.size()>1){
        r.pop_back();
    }else rebuild();
};
auto ppf=[&]{
    dq.pop_front();
    if(l.size()>1){
        l.pop_back();
    }else rebuild();
};
auto query=[&](int x)->int{
    int res=0;
    for(int i=0;i<=x;i++){
        res=max(res,l.back()[i]+r.back()[x-i]);
    }
    return res;
};