#define eps 1e-8
#define zero(x) (((x) > 0 ? (x) : -(x)) < eps)
const int N=2e5+5;
struct point{double x,y;}p[N],sta[N];
struct line{point a,b;};
// 计算 cross product (P1-P0)x(P2-P0) 三角形面积两倍
double xmult(point p0,point p1,point p2){
    return (p1.x-p0.x)*(p2.y-p0.y)-(p2.x-p0.x)*(p1.y-p0.y);
}
// 计算 dot product (P1-P0).(P2-P0)
double dmult(point p0,point p1,point p2){
    return (p1.x-p0.x)*(p2.x-p0.x)+(p1.y-p0.y)*(p2.y-p0.y);
}
// 两点距离
double distance(point p1,point p2){
	return ((p1.x-p2.x)*(p1.x-p2.x)+(p1.y-p2.y)*(p1.y-p2.y));
}
//点到直线距离
double dispointtoline(point p,line l){
	point p1={p.x-l.a.x,p.y-l.a.y};
	point p2={l.b.x-l.a.x,l.b.y-l.a.y};
	return fabs(xmult(p1,p2,{0,0}))/sqrt(distance(l.a,l.b));
}
//得到凸包
int Andrew(int n){
    sort(p+1,p+1+n,[&](point a,point b){
        return a.x!=b.x?a.x<b.x:a.y<b.y;
    });
    int top=0;
    for(int i=1;i<=n;i++){
        while(top>1&&xmult(sta[top-1],sta[top],p[i])<=0)top--;
        sta[++top]=p[i];
    }
    int tmp=top;
    for(int i=n-1;i>=1;i--){
        while(top>tmp&&xmult(sta[top-1],sta[top],p[i])<=0)top--;
        sta[++top]=p[i];
    }
    // double res=0;//凸包周长
    // for(int i=1;i<top;i++){
    //     res+=distance(sta[i],sta[i+1]);
    // }
    // cout<<fixed<<setprecision(2)<<res;
    return top-1;
}
//两点最远距离(多边形最小宽度)
double rotating_cailpers(int n){
    double res=0;
//	double res=1e9;
    for(int i=1,j=2;i<=n;i++){
        while(xmult(sta[i],sta[i+1],sta[j])<xmult(sta[i],sta[i+1],sta[j+1]))j=j%n+1;
        res=max(res,max(distance(sta[i],sta[j]),distance(sta[i+1],sta[j])));
//		res=min(res,dispointtoline(sta[j],{sta[i],sta[i+1]}));
    }
    return res;
}

