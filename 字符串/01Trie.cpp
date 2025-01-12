const int N=2e5+5;
int ch[N<<5][2],idx;
void insert(int x){
    int p=0;
    for(int i=30;i>=0;i--){
        int j=x>>i&1;
        if(!ch[p][j])ch[p][j]=++idx;
        p=ch[p][j];
    }
}
int query(int x){
    int p=0,res=0;
    for(int i=30;i>=0;i--){
        int j=x>>i&1;
        if(ch[p][!j]){
            res+=1<<i;
            p=ch[p][!j];
        }else p=ch[p][j];
    }
    return res;
}//注意p=0要不要退出
//可持续化
const int N=6e5+5;
int ch[N<<5][2],idx,ver[N<<5],root[N];
void insert(int x,int &y,int s,int t){
    y=++idx;ver[y]=t;int fy=y;
    for(int k=30;k>=0;k--){
        int c=s>>k&1;
        ch[fy][!c]=ch[x][!c];
        ch[fy][c]=++idx;
        x=ch[x][c],fy=ch[fy][c];
        ver[fy]=t;
    }
}
int query(int l,int r,int s){
    int x=root[r];
    int res=0;
    for(int k=30;k>=0;k--){
        int c=s>>k&1;
        if(ver[ch[x][!c]]>=l){
            x=ch[x][!c],res+=1<<k;
        }else x=ch[x][c];
    }
    return res;
}
void init(){
    ver[0]=-1;
    insert(0,root[0],0,0);
}