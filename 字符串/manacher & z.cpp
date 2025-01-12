const int N=4e7+5;
#define int long long
int d[N],z[N];
string make_s(string s){
    string res="#";
    for(auto it:s){
        res+=it;res+='#';
    }
    return res;
}
int get_d(string s){
    int n=s.size(),mx=1;
	for(int i=1;i<=n;i++)d[i]=0;
    d[1]=1;s=" "+s;
    for(int i=2,l,r=1;i<=n;i++){
        if(i<=r)d[i]=min(d[l+r-i],r-i+1);
        while(s[i-d[i]]==s[i+d[i]])d[i]++;
        if(i+d[i]-1>r)l=i-d[i]+1,r=i+d[i]-1;
        mx=max(mx,d[i]);
    }
    return mx-1;
}
void get_z(string s){
    int n=s.size();
	for(int i=1;i<=n;i++)z[i]=0;
    s=" "+s;z[1]=n;
    for(int i=2,l,r=0;i<=n;i++){
        if(i<=r)z[i]=min(z[i-l+1],r-i+1);
        while(s[z[i]+1]==s[i+z[i]])z[i]++;
        if(i+z[i]-1>r)l=i,r=i+z[i]-1;
    }
}
