long long ex_gcd(long long a,long long b,long long &x,long long &y){
	if(!b){x=1;y=0;return a;}
	long long d=ex_gcd(b,a%b,y,x);
	y-=a/b*x;
	return d;
}
// dx=b/d  dy=a/d
// x*=c/d  y*=c/d
// x=x0+k*dx,y=y0-k*dy
// x最小正整数解 (x%dx+dx)%dx dx>0
// x y 为正整数  解方程确定k的范围
int gcd(int x,int y)
{
	if(!x) return y;
	if(!y) return x;
	int t=__builtin_ctzll(x|y);
	x>>=__builtin_ctzll(x);
	do{
		y>>=__builtin_ctzll(y);
		if(x>y) swap(x,y);
		y-=x;
	}while(y);
	return x<<t;
}
