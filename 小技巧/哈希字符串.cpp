template<long long BASE,long long MOD,long long SZ>
struct Hash {
public:
	static constexpr long long ERR=-1;
	long long sz;
	void build(string &s){
		sz=s.size();s=" "+s;
		hs[0]=hsr[0]=0;p[0]=1;
		for(int i=1;i<=sz;i++){
			p[i]=p[i-1]*BASE%MOD;
			hs[i]=hs[i-1]*BASE%MOD+s[i],hs[i]%=MOD;
			hsr[i]=hsr[i-1]*BASE%MOD+s[sz+1-i],hsr[i]%=MOD;
		}
		return;
	}
	long long qry(int l,int r){
		if(r<l)return ERR;
		if(l<1||sz<r)return ERR;
		return (hs[r]-hs[l-1]*p[r-l+1]%MOD+MOD)%MOD;
	}
	long long qryr(int L,int R){
		if(R<L)return ERR;
		if(L<1||sz<R)return ERR;
		long long l=sz+1-R;
		long long r=sz+1-L;
		return (hsr[r]-hsr[l-1]*p[r-l+1]%MOD+MOD)%MOD;
	}
	
protected:
	long long p[SZ+1],hs[SZ+1],hsr[SZ+1];
};
const long long SZ=2e5+10;
constexpr long long BASE1=521,MOD1=1004535809;
constexpr long long BASE2=239,MOD2=2013265921;
Hash<BASE1,MOD1,SZ>h1;
Hash<BASE2,MOD2,SZ>h2;

struct custom_hash{
	static uint64_t splitmix64(uint64_t x){
		x^=x<<13;
		x^=x>>7;
		x^=x<<17;
		return x; 
	}
	size_t operator()(uint64_t x) const {
		static const uint64_t FIXED_RANDOM=chrono::steady_clock::now().time_since_epoch().count(); // 时间戳
		return splitmix64(x+FIXED_RANDOM);
	}
};