#define int long long
#define ntt_bit(x) (__lg(x)+1)
const int P=998244353;
using poly=vector<int>;
namespace Poly{
	const int G=3;
	vector<int>gen,igen,inv,rev;
	int qp(int x,int y){int s=1;while(y){if(y&1)s=s*x%P;x=x*x%P;y>>=1;}return s;}
	int w;
	struct Complex{
		int x,y;
		Complex(int _x=0,int _y=0):x(_x),y(_y){}
		friend Complex operator *(const Complex a,const Complex b){
			return Complex((a.x*b.x%P+w*a.y%P*b.y%P)%P,(a.x*b.y%P+a.y*b.x%P)%P);
		}
	};
	int fastpow(Complex a,int b){Complex ans(1,0);while(b){if(b&1)ans=ans*a;a=a*a;b>>=1;}return ans.x;}
	int Cipolla(int x){
		if(x<=1)return x;if(fastpow(x,(P-1)>>1)==P-1)return -1;srand(time(0));
		while(1){
			int a=(1ll*rand()<<15|rand())%P;w=(a*a%P+P-x)%P;
			if(fastpow(w,(P-1)>>1)==P-1){int res=fastpow(Complex(a,1),(P+1)>>1);return min(res,P-res);}
		}
	}
	void init(int dig=21){
		int n=(1<<dig)+1;dig+=1;
		gen.resize(dig); igen.resize(dig);inv.resize(n);rev.resize(n);
		for(int i=0;i<dig;i++){gen[i]=qp(G,(P-1)/(1<<i));igen[i]=qp(gen[i],P-2);}
		inv[1]=1;for(int i=2;i<n;i++)inv[i]=(P-inv[P % i])*(P/i)%P;
	}
	void ntt_init(int bit,int tot){for(int i=0;i<tot;i++)rev[i]=(rev[i>>1]>>1)|((i&1)<<(bit-1));}
	void NTT(poly &a,int op,int tot){
		a.resize(tot);
		for(int i=0;i<tot;i++)if(i<rev[i])swap(a[i],a[rev[i]]);
		for(int o=1,bt=0,w;o<tot;o<<=1,bt++){
			w=(op==1?gen[bt+1]:igen[bt+1]);
			for(int i=0;i<tot;i+=o+o)for(int j=i,x,y,W=1;j<i+o;j++,W=W*w%P){
				x=a[j];y=a[j+o],a[j]=(x+W*y)%P,a[j+o]=(x+P-W*y%P)%P;
				if(a[j+o]>=P)a[j+o]-=P;
			}
		}
		if(op==1)return;for(int i=0;i<tot;i++)a[i]=a[i]*inv[tot]%P;
	}
	poly operator *(poly a,poly b){
		int deg=a.size()+b.size()-1,bit=ntt_bit(deg),tot=(1<<bit);
		ntt_init(bit,tot);poly c(tot);NTT(a,1,tot);NTT(b,1,tot);
		for(int i=0;i<tot;i++)c[i]=a[i]*b[i]%P;
		NTT(c,-1,tot);c.resize(deg);return c;
	}
	poly poly_inv(poly &f,int deg){
		if(deg==1){poly q;q.push_back(qp(f[0],P-2));return q;}
		poly B=poly_inv(f,(deg+1)>>1);
		int bit=ntt_bit(deg<<1),tot=1<<bit;
		ntt_init(bit,tot);poly A(tot);for(int i=0;i<deg;i++)A[i]=f[i];NTT(A,1,tot);NTT(B,1,tot);
		for(int i=0;i<tot;i++)A[i]=B[i]*(2+P-A[i]*B[i]%P)%P;
		NTT(A,-1,tot);A.resize(deg); return A;
	}
	poly diff(int n,poly &a){poly b(n);for(int i=1;i<n;i++)b[i-1]=a[i]*i%P;b[n-1]=0;return b;}
	poly ieteg(int deg,poly &a){poly b(deg);b[0]=0;for(int i=0;i<deg-1;i++)b[i+1]=a[i]*inv[i+1]%P;return b;}
	poly poly_ln(poly &a,int n){poly b(n),L1(n),L2(n),L3(n);L1=diff(n,a);for(int i=0;i<n;i++)L2[i]=0;L2=poly_inv(a,n);L3=L1*L2;b=ieteg(n,L3);return b;}
	poly poly_exp(poly &a,int n){
		if(n==1){poly q;q.push_back(1);return q;}
		poly B=poly_exp(a,(n+1)>>1);B.resize(n);poly E1=poly_ln(B,n);
		int bit=ntt_bit(n<<1),tot=1<<bit;ntt_init(bit, tot);
		E1.resize(tot);B.resize(tot);for(int i=0;i<n;i++)E1[i]=(a[i]+P-E1[i])%P;
		for(int i=n;i<tot;i++)E1[i]=B[i]=0;E1[0]++;
		NTT(E1,1,tot);NTT(B,1,tot);for(int i=0;i<tot;i++)B[i]=B[i]*E1[i]%P;
		NTT(B,-1,tot);for(int i=n;i<tot;i++)B[i]=0;B.resize(n);return B;
	}
	poly poly_qp(poly &a,int n,int k){
        int p=0;while(p<n){if(a[p])break;p++;}
        if(p==n){poly b(n);return b;}n-=p;
        int res=qp(a[p],P-2);poly aa(n);for(int i=0;i<n;i++)aa[i]=a[i+p]*res%P;
        poly b=poly_ln(aa,n),ans(n+p);
        for(int i=0;i<n;i++)b[i]=b[i]*k%P;
        poly c=poly_exp(b,n);res=qp(a[p],k);n+=p;p=min(n,p*k);
        for(int i=0;i<n-p;i++)ans[i+p]=c[i]*res%P;
        return ans;
    }
	poly poly_sqrt(poly &a,int n){//前面有奇数个0无解
		int p=0,k=qp(2,P-2);while(p<n){if(a[p])break;p++;}
        if(p==n){poly b(n);return b;}n-=p;
        int res=qp(a[p],P-2);poly aa(n);for(int i=0;i<n;i++)aa[i]=a[i+p]*res%P;
        poly b=poly_ln(aa,n),ans(n+p);
        for(int i=0;i<n;i++)b[i]=b[i]*k%P;
        poly c=poly_exp(b,n);res=Cipolla(a[p]);n+=p;p>>=1;
        for(int i=0;i<n-p;i++)ans[i+p]=c[i]*res%P;
        return ans;
	}
}
using namespace Poly;