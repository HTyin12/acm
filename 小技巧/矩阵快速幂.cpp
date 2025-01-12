const int matrixN=2,Mn=2;
const int mod=1e9+7,N=1e7+5;
struct matrix{
	long long a[matrixN][matrixN];
	matrix operator *(const matrix &b)const{
		matrix tmp;
		tmp.clear();
		for(int k=0;k<Mn;k++)
			for(int i=0;i<Mn;i++)
				for(int j=0;j<Mn;j++)
					tmp.a[i][j]=(tmp.a[i][j]+a[i][k]*b.a[k][j])%mod;
		return tmp;
	}
	matrix operator *=(const matrix &b){
		return *this=*this*b;
	}
	matrix operator +(const matrix &b)const{
		matrix tmp;
		tmp.clear();
		for(int i=0;i<Mn;i++)
			for(int j=0;j<Mn;j++)
				tmp.a[i][j]=(a[i][j]+b.a[i][j])%mod;
		return tmp;
	}
	matrix operator +=(const matrix &b){
		return *this=*this+b;
	}
	inline void clear(){
		for(int i=0;i<Mn;i++)
			for(int j=0;j<Mn;j++)a[i][j]=0;
	}
	inline void build(){
		for(int i=0;i<Mn;i++)
			for(int j=0;j<Mn;j++)
				a[i][j]=(i==j?1:0);
	}
	inline bool isE(){
		for(int i=0;i<Mn;i++)
			for(int j=0;j<Mn;j++)
				if((a[i][j]&&i!=j)||(a[i][j]!=1&&i==j))return 0;
		return 1;
	}
	inline void qp(long long x){
		matrix res;res.build();
		while(x){
			if(x&1)res*=*this;
			*this*=*this;
			x>>=1;
		}
		for(int i=0;i<Mn;i++)
			for(int j=0;j<Mn;j++)
				a[i][j]=res.a[i][j];
	}
	inline void print(){
		for(int i=0;i<Mn;i++,cout<<'\n')
			for(int j=0;j<Mn;j++)cout<<a[i][j]<<' ';
	}
};
