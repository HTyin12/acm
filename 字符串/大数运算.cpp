namespace tinybuint{
#define YZLF(i,x) for(int i=48<<x;i<58<<x;i+=1<<x)
	constexpr auto ot4=[]{std::array<int,10000> n;int z=0;YZLF(i,0)YZLF(j,8)YZLF(k,16)YZLF(w,24)n[z++]=i^j^k^w;return n;}();
#undef YZLF
	inline auto stou_8(const char*s){
		return (((*(uint64_t*)s^0x3030303030303030)*0xa01>>8&0x00ff00ff00ff00ff)*0x640001>>16&0x0000ffff0000ffff)*0x271000000001>>32;
	}
	using Cp=std::complex<double>;
	std::vector<Cp> w{1.},F,G;
#define btw for(Cp*k=f,x,y;k!=f+l;++k){x=*k,y=k[l],*k=x+y,k[l]=x-y;}for(Cp*j=f+r,*o=w.data()+1,x,y;j!=f+L;j+=r,++o)for(Cp*k=j;k!=j+l;++k)x=*k,y=k[l],
	void dif(Cp*f,int L){for(int l=L>>1,r=L;l;l>>=1,r>>=1){btw y*=*o,*k=x+y,k[l]=x-y;}}
	void fconv(Cp*f,Cp*g,int L){
		int z=w.size();
		if(L>(z<<1)){
			int l=L>>1,i=z;
			w.resize(l);for(;z<l;z<<=1)w[z]=std::polar(1.,acos(-1)/(z<<1));for(;i<l;++i)w[i]=w[i&(i-1)]*w[i&-i];
		}
		dif(f,L),dif(g,L);
		auto v=1./L,u=v/4;
		*f=(*f**g+2*f->imag()*g->imag())*v,f[1]*=g[1]*v;
		for(int k=2,m=3;k<L;k<<=1,m<<=1)for(int i=k,j=i+k-1;i<m;++i,--j){
			Cp o=f[i]+std::conj(f[j]),h=f[i]-std::conj(f[j]),O=g[i]+std::conj(g[j]),H=g[i]-std::conj(g[j]),r=o*O-h*H*((i&1)?-w[i>>1]:w[i>>1]),R=O*h+o*H;
			f[i]=(r+R)*u,f[j]=std::conj(r-R)*u;
		}
		for(int l=1,r=2;l<L;l<<=1,r<<=1){btw *k=x+y,k[l]=(x-y)*std::conj(*o);}
	}
#undef btw
	constexpr uint32_t B=1E8;
	class Bi{
		std::vector<uint32_t> a;
		void shr(){while(!a.empty()&&a.back()==0)a.pop_back();}
		auto sz()const{return a.size();}
	public:
		Bi()=default;
		Bi(uint64_t x){while(x)a.emplace_back(x%B),x/=B;}
		auto operator<=>(const Bi&b)const{
			if(sz()!=b.sz()){return sz()<=>b.sz();}for(int n=sz()-1;~n;--n)if(a[n]!=b.a[n])return a[n]<=>b.a[n];return 0<=>0;
		}
		auto operator==(const Bi&b)const{return (*this<=>b)==0;}
		static std::string to_str(const Bi&x){
			if(x.a.empty())return "0";
			auto r=std::to_string(x.a.back());
			for(int i=x.sz()-2;~i;--i)r.append((char*)&ot4[x.a[i]/10000],4).append((char*)&ot4[x.a[i]%10000],4);
			return r;
		}
		static void fr_str(std::string_view s,Bi&r){
			if(s.empty()){return;}
			int n=s.size(),sz=(n+7)>>3,p=(n&7)?(n&7):8;
			auto y=s.data();
			r.a.resize(sz),std::from_chars(y,y+p,r.a[sz-1]);
			for(int i=sz-2;~i;--i)r.a[i]=stou_8(y+p),p+=8;
			r.shr();
		}
		Bi&operator-=(const Bi&b){
			assert((*this)>=b);
			int i=0,n=b.sz(),c=0;
			for(;i<n;++i)(a[i]-=b.a[i]+c)>B?(a[i]+=B,c=1):c=0;
			for(;c;++i)(a[i]-=c)>B?(a[i]+=B,c=1):c=0;
			shr();
			return *this;
		}
		Bi&operator+=(const Bi&b){
			if(sz()<b.sz())a.resize(b.sz());
			int i=0,n=sz(),m=b.sz(),c=0;
			for(;i<m;++i)(a[i]+=b.a[i]+c)>=B?(a[i]-=B,c=1):c=0;
			for(;c&&i<n;++i)(a[i]+=c)>=B?(a[i]-=B,c=1):c=0;
			if(c)a.emplace_back(1);
			return *this;
		}
		Bi operator-(const Bi&b)const{return Bi(*this)-=b;}
		Bi operator+(const Bi&b)const{return Bi(*this)+=b;}
		Bi operator*(const Bi&b)const{return sz()<b.sz()?b.rmul(*this):rmul(b);}
		Bi&operator*=(const Bi&b){return *this=*this*b;}
		Bi operator/(const Bi&b)const{return div_mod(b).first;}
		Bi operator%(const Bi&b)const{return div_mod(b).second;}
		Bi&operator/=(const Bi&b){return *this=*this/b;}
		Bi&operator%=(const Bi&b){return *this=*this%b;}
		Bi rshiftr(int d)const{
			int n=sz();
			if(d>=n)return 0;
			Bi r;r.a={a.begin()+d,a.end()};
			return r;
		}
		Bi&shiftr(int d){
			int n=sz();
			if(d>=n)a.clear();
			else std::copy(a.begin()+d,a.end(),a.begin()),a.resize(n-d);  
			return *this;
		}
		Bi rshiftl(int d)const{
			if(a.empty())return 0;
			int n=sz();
			Bi r;r.a.reserve(n+d),r.a.resize(d),r.a.insert(r.a.end(),a.begin(),a.end());
			return r;
		}
		Bi&shiftl(int d){
			int n=sz();
			if(!a.empty())a.resize(n+d),std::copy_backward(a.begin(),a.begin()+n,a.end()),std::fill_n(a.begin(),d,0);
			return*this;
		}
		std::pair<Bi,Bi> div_mod(const Bi&b)const{
			if(*this<b)return {{},*this};
			return std::min(b.sz(),sz()-b.sz())<=100?rdiv_bf(b):rdiv_nwt(b);
		}
	private:
		Bi rmul(const Bi&b)const{
			if(b.sz()==0)return 0;
			int n=sz(),m=b.sz(),u=n+m-1;
			Bi r;r.a.resize(n+m);
			uint64_t t=0;
			if(b.sz()<=32){
				for(int i=0;i<u;++i){
					for(int j=((i>=n)?i-n+1:0);j<=std::min(i,m-1);++j)t+=b.a[j]*uint64_t(a[i-j]);
					r.a[i]=t%B,t/=B;
				}
				r.a[u]=t;
			}
			else{
				int lm=2<<std::__lg(u);
				F.assign(lm,0),G.assign(lm,0);
				for(int i=0;i<n;++i)F[i]=Cp(a[i]%10000,a[i]/10000);
				for(int i=0;i<m;++i)G[i]=Cp(b.a[i]%10000,b.a[i]/10000);
				fconv(F.data(),G.data(),lm);
				for(int i=0;i<=u;++i)t+=int64_t(F[i].real()+0.5)+int64_t(F[i].imag()+0.5)*10000,r.a[i]=t%B,t/=B;
			}
			r.shr();
			return r;
		}
		std::pair<Bi,Bi> rdiv_bf(const Bi&b)const{
			Bi q,r=*this;
			int n=sz(),m=b.sz(),p=0;
			q.a.resize(n-m+1);
			auto get_v=[](auto&A,int y,int z){return 10*(B*uint64_t((y+1)<z?A[y+1]:0)+A[y])+(y>=1?A[y-1]:0)/(B/10);};
			for(int i=n-m;~i;--i){
				auto subt=[&](){
					int64_t k=0;
					for(int j=0;j<m;++j){k-=int64_t(p)*b.a[j]-r.a[i+j],r.a[i+j]=k%B,k/=B;if(r.a[i+j]>B){r.a[i+j]+=B,--k;}}
					if(k){r.a[i+m]+=k;}q.a[i]+=p;
				};
				q.a[i]=0;while((p=get_v(r.a,i+m-1,n)/(get_v(b.a,m-1,m)+1))){subt();}p=1;
				for(int j=m-1;~j;--j)if(b.a[j]!=r.a[i+j]){p=b.a[j]<r.a[j+i];break;}
				if(p)subt();
			}
			q.shr(),r.shr();
			return {q,r};
		}
		Bi __inv(int p)const{
			int n=sz();
			if(std::min(n,p-n)<=64){
				Bi A;A.a.resize(p+1),A.a[p]=1;
				return A.rdiv_bf(*this).first;
			}
			int k=(p-n+5)>>1,kk=k>n?0:n-k,nn=n-kk+k;
			auto x=rshiftr(kk),y=x.__inv(nn),b=(*this)*y*y;
			y+=y,y.shiftl(p-nn-kk)-=b.shiftr(2*(nn+kk)-p),y-=1;
			return y;
		}
		std::pair<Bi,Bi> rdiv_nwt(const Bi&b)const{
			int n=sz(),m=b.sz(),k=n-m+5,kk=k>m?0:m-k,nn=k+m-kk;
			auto xx=b.rshiftr(kk);
			if(kk)xx+=1;
			auto q=*this*xx.__inv(nn),r=*this-q.shiftr(nn+kk)*b;
			if(r>=b)q+=1,r-=b;
			assert(r<b);
			return {q,r};
		}
	};
	auto&operator>>(auto&is,Bi&x){std::string s;return is>>s,Bi::fr_str(s,x),is;}
	auto&operator<<(auto&os,const Bi&x){return os<<Bi::to_str(x);}
}
using bigint=tinybuint::Bi;
