#define eps 1e-8
#define zero(x) (((x) > 0 ? (x) : -(x)) < eps)
const int N=2e5+5;
struct point{double x,y;}p[N],sta[N];
struct line{point a,b;};
// 计算 cross product (P1-P0)x(P2-P0)
double xmult(point p0,point p1,point p2){
    return (p1.x-p0.x)*(p2.y-p0.y)-(p2.x-p0.x)*(p1.y-p0.y);
}
// 计算 dot product (P1-P0).(P2-P0)
double dmult(point p0,point p1,point p2){
    return (p1.x-p0.x)*(p2.x-p0.x)+(p1.y-p0.y)*(p2.y-p0.y);
}
// 两点距离
double distance(point p1,point p2){
    return sqrt((p1.x-p2.x)*(p1.x-p2.x)+(p1.y-p2.y)*(p1.y-p2.y));
}
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