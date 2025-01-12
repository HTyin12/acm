const int N=2e5+5;
long long t[N];
#define lowbit(x) ((x)&(-x))
void add(int x,long long k){while(x<N)t[x]+=k,x+=lowbit(x);}
long long ask(int x){long long ans=0;while(x)ans+=t[x],x-=lowbit(x);return ans;}



const int N=1e6+5;
#define lowbit(x) ((x)&(-x))
int a[N],h[N],l[N];long long s[N];
int querymax(int x, int y){int ans=0;while(y>=x){ans=max(a[y],ans);y--;for(;y-lowbit(y)>=x;y-=lowbit(y))ans=max(h[y],ans);}return ans;}
int querymin(int x, int y){int ans=1e9;while(y>=x){ans=min(a[y],ans);y--;for(;y-lowbit(y)>=x;y-=lowbit(y)) ans=min(l[y],ans);}return ans;}
long long ask(long long x){long long ans=0;while(x)ans+=s[x],x-=lowbit(x);return ans;}
long long querysum(int l,int r){return ask(r)-ask(l-1);}
void updata(int x){int lx,i;while(x<=n){h[x]=l[x]=s[x]=a[x];lx=lowbit(x);for(i=1;i<lx;i<<=1)h[x]=max(h[x],h[x-i]),l[x]=min(l[x],l[x-i]),s[x]=s[x]+s[x-i];x+=lowbit(x);}}


struct Fenwick{
	int n;
	vector<int>f;
	void reset(int m){
		n=m+1;f.assign(n+1,0);
	}
	void modify(int u, int x=1){
		for(int i=u+1;i<=n;i+=i&-i)
			f[i]+=x;
	}
	auto query(int u){
		int x=0;
		for(int i=u+1;i>=1;i^=i&-i)
			x+=f[i];
		return x;
	}
	auto query(int l, int r){
		return query(r)-query(l-1);
	}
	int select(int k){
        int x=0,cur=0;
        for(int i=1<<__lg(n);i;i/=2)
			if(x+i<=n&&cur+f[x+i]<k)
                x+=i,cur=cur+f[x];
        return x;
    }
}tr;
