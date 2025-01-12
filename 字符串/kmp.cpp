const int N=4e6+5;
string ch1,ch2;
int nxt[N];
int kmp(){
    int n=ch1.size(),m=ch2.size();
    string ch=" ";
    ch+=ch1;ch+=" ";ch+=ch2;
    nxt[1]=0;
    int j=0;
    for(int i=2;i<=n+m+1;i++){
        while(j&&ch[j+1]!=ch[i])j=nxt[j];
        if(ch[j+1]==ch[i])j++;
        nxt[i]=j;
    }
    int ans=0;
    for(int i=n+2;i<=n+m+1;i++){
        if(nxt[i]==n)ans++;
    }
    return ans;
}