#define LL long long
struct Point {
    LL x, y;
    Point(LL x = 0, LL y = 0) : x(x), y(y) {}
    Point operator - (const Point &rhs) const {
        return Point(x - rhs.x, y - rhs.y);
    }
};
inline LL Det(Point A, Point B) {
    return A.x * B.y - B.x * A.y;
}
struct ConvexHull {
    Point P[N];
    int be=1, ed=0;
    void init() {
        be = 1, ed = 0;
    }
    void add(LL x, LL y) {
        Point cur(x, y);
        while(be < ed && Det(cur - P[ed], P[ed] - P[ed - 1]) <= 0) ed--;//上凸包
        //while(be < ed && Det(cur - P[ed], P[ed] - P[ed - 1]) >= 0) ed--;//下凸包
        P[++ed] = Point(x, y);
    }
    LL query(LL k) {//k为斜率 y=kx+c  且 k在询问过程中一直大
        Point cur(1, k);
        while(be < ed && Det(cur, P[be + 1] - P[be]) >= 0) be++;//上凸包
        //while(be < ed && Det(cur, P[be + 1] - P[be]) <= 0) be++;//下凸包
        return P[be].y - k * P[be].x;
    }
    LL query2(LL k) {//k为斜率 y=kx+c 无脑用法 
        Point cur(1, k);
        int low = be + 1, high = ed, mid, pos = be;
        while(low <= high) {
            mid = low + high >> 1;
            if(Det(cur, P[mid] - P[mid - 1]) >= 0) pos = mid, low = mid + 1;//上凸包
            // if(Det(cur, P[mid] - P[mid - 1]) <= 0) pos = mid, low = mid + 1;//下凸包
            else high = mid - 1;
        }
        return P[pos].y - k * P[pos].x;
    }
};