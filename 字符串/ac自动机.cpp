const int N=1e6+5;
int ch[N][26],cnt[N],idx,nxt[N];
void insert(string s){
    int p=0;
    for(int i=0;i<s.size();i++){
        int j=s[i]-'a';
        if(!ch[p][j])ch[p][j]=++idx;
        p=ch[p][j];
    }
    cnt[p]++;
}
void build(){
    queue<int>q;
    for(int i=0;i<26;i++){
        if(ch[0][i])q.push(ch[0][i]);
    }
    while(q.size()){
        int u=q.front();q.pop();
        for(int i=0;i<26;i++){
            int v=ch[u][i];
            if(v)nxt[v]=ch[nxt[u]][i],q.push(v);
            else ch[u][i]=ch[nxt[u]][i];
        }
    }
}
//询问出现几种
int query(string s){
    int ans=0;
    for(int k=0,i=0;k<s.size();k++){
        i=ch[i][s[k]-'a'];
        for(int j=i;j&&~cnt[j];j=nxt[j]){
            ans+=cnt[j],cnt[j]=-1;
        }
    }
    return ans;
}