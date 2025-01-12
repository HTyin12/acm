template<class T> bool ckmax(T& a, T b) { return a < b ? (a = b, 1) : 0; }
template<class T> bool ckmin(T& a, T b) { return a > b ? (a = b, 1) : 0; }
template<class T> vector<T> & operator + (vector<T> & a, vector<T> & b) { a.insert(a.end(), b.begin(), b.end()); return a; }
template<class T> vector<T> & operator += (vector<T> & a, vector<T> & b) { return a = a + b; }
 
using point_t = long double;  //全局数据类型，可修改为 long long 等
 
constexpr point_t eps = 1e-8;
constexpr long double PI = acosl(-1);
 
// 点与向量
template<typename T> struct point
{
    T x, y;
 
    bool operator == (const point & a) const { return abs(x - a.x) <= eps && abs(y - a.y) <= eps; }
    bool operator < (const point & a) const { if(abs(x - a.x) > eps) return x < a.x - eps; return y < a.y - eps; }
    bool operator > (const point & a) const { return !((*this) < a || (*this) == a); }
    point operator + (const point & a) const { return {x + a.x, y + a.y}; }
    point operator - (const point & a) const { return {x - a.x, y - a.y}; }
    point operator - () const { return {-x, -y}; }
    point operator * (const T k) const { return {x * k, y * k}; }
    point operator / (const T k) const { return {x / k, y / k}; }
    T operator * (const point & a) const { return x * a.x + y * a.y; }
    T operator ^ (const point & a) const { return x * a.y - y * a.x; }
    int toleft (const point & a) const { const auto t = (*this) ^ a; return (t > eps) - (t < -eps); } // a 向量在该向量的左半平面 / 上 / 右半平面
    T len2 () const { return x * x + y * y; }
    T dis2 (const point & a) const { return ((*this) - a).len2(); }
 
    // 涉及浮点数
    long double len () const { return sqrtl(len2()); }
    long double dis (const point & a) const { return sqrtl(dis2(a)); }
    long double ang (const point & a) const { return acosl(max(-1.0l, min(1.0l, ((*this) * a) / (len() * a.len())))); }
    long double toang (const point & a) const { const auto t = ang(a); return (*this ^ a) > 0 ? t : 2 * PI - t; }
    point rot () const { return {-y, x}; }
    point rot (const long double rad) const { return {x * cosl(rad) - y * sinl(rad), x * sinl(rad) + y * cosl(rad)}; }
    point rot (const long double cosr, const long double sinr) const { return {x * cosr - y * sinr, x * sinr + y * cosr}; }
};
 
using Point = point<point_t>;
 
 
// 极角排序
struct argcmp
{
    bool operator () (const Point & a, const Point & b) const
    {
        const auto quad = [] (const Point & a)
        {
            if(a.y < -eps) return 1;
            if(a.y > eps) return 4;
            if(a.x < -eps) return 5;
            if(a.x > eps) return 3;
            return 2;
        };
        const int qa = quad(a), qb = quad(b);
        if(qa != qb) return qa < qb;
        const auto t = a ^ b;
        // if(abs(t) <= eps) return a * a < b * b - eps;  // 不同长度的向量需要分开
        return t > eps;
    }
};
 
// 直线
template<typename T> struct line
{
    point<T> p, v;
     
    bool operator == (const line & a) const { return v.toleft(a.v) == 0 && v.toleft(p - a.p) == 0; }
    int toleft (const point<T> & a) const { return v.toleft(a - p); } // 点 a 在该直线的左半平面 / 上 / 右半平面
 
    // 涉及浮点数
    long double dis (const point<T> & a) const { return abs(v ^ (a - p)) / v.len(); }
    point<T> inter (const line & a) const { return p + v * ( (a.v ^ (p - a.p)) / (v ^ a.v) ); }
    long double inter_dis (const line & a) const { return v.len() * (a.v ^ (p - a.p)) / (v ^ a.v); }
    point<T> proj (const point<T> & a) const { return p + v * ( (v * (a - p)) / (v * v) ); }
    long double proj_dis (const point<T> & a) const { return v * (a - p) / v.len(); }
};
 
using Line = line<point_t>;
 
 
// 线段
template<typename T> struct segment
{
    point<T> a, b;
     
    bool operator < (const segment & s) const { return make_pair(a, b) < make_pair(s.a, s.b) ; }
 
    // 判定性函数建议在整数域使用
 
    // 判断点是否在线段上
    // -1 点在线段端点 | 0 点不在线段上 | 1 点严格在线段上
    int is_on (const point<T> & p) const
    {
        if(p == a || p == b) return -1;
        return (p - a).toleft(p - b) == 0 && (p - a) * (p - b) < -eps;
    }
 
    // 判断线段直线是否相交
    // -1 直线经过线段端点 | 0 线段和直线不相交 | 1 线段和直线严格相交
    int is_inter (const line<T> & l) const
    {
        if(l.toleft(a) == 0 || l.toleft(b) == 0) return -1;
        return l.toleft(a) != l.toleft(b);
    }
 
    // 判断两线段是否相交
    // -1 在某一线段端点处相交 | 0 两线段不相交 | 1 两线段严格相交
    int is_inter (const segment & s) const
    {
        if(is_on(s.a) || is_on(s.b) || s.is_on(a) || s.is_on(b)) return -1;
        const line<T> l = {a, b - a}, ls = {s.a, s.b - s.a};
        return l.toleft(s.a) * l.toleft(s.b) == -1 && ls.toleft(a) * ls.toleft(b) == -1;
    }
 
    // 点到线段距离
    long double dis (const point<T> & p) const
    {
        if((b - a) * (p - a) < -eps || (a - b) * (p - b) < -eps) return min(p.dis(a), p.dis(b));
        const line<T> l = {a, b - a};
        return l.dis(p);
    }
 
    // 两线段间距离
    long double dis (const segment & s) const
    {
        if(is_inter(s)) return 0;
        return min({dis(s.a), dis(s.b), s.dis(a), s.dis(b)});
    }
};
 
using Segment = segment<point_t>;
 
 
// 射线
template<typename T> struct ray
{
    point<T> p, v;
 
    // 判定性函数建议在整数域使用
 
    // 判断点是否在射线上
    // -1 点在射线端点 | 0 点不在射线上 | 1 点严格在射线上
    int is_on (const point<T> & a) const
    {
        if(p == a) return -1;
        return v.toleft(a - p) == 0 && v * (a - p) > eps;
    }
 
    // 判断射线直线是否相交
    // -1 直线经过射线端点 | 0 射线和直线不相交 | 1 射线和直线严格相交
    int is_inter (const line<T> & l) const
    {
        if(l.toleft(p) == 0) return -1;
        return l.v.toleft(p - l.p) * l.v.toleft(v) == -1;
    }
 
    // 判断射线线段是否相交
    // -1 在线段端点或射线端点处相交 | 0 射线和线段不相交 | 1 射线和线段严格相交
    int is_inter (const segment<T> & s) const
    {
        if(is_on(s.a) || is_on(s.b) || s.is_on(p)) return -1;
        const point<T> sv = s.b - s.a;
        return v.toleft(s.a - p) * v.toleft(s.b - p) == -1 && sv.toleft(p - s.a) * sv.toleft(v) == -1;
    }
 
    // 判断两射线是否相交
    // -1 在某一射线端点处相交 | 0 两射线不相交 | 1 两射线严格相交
    int is_inter (const ray & r) const
    {
        if(is_on(r.p) || r.is_on(p)) return -1;
        const line<T> l = {p, v}, lr = {r.p, r.v};
        return is_inter(lr) && r.is_inter(l);
    }
 
    // 点到射线距离
    long double dis (const point<T> & a) const
    {
        if(v * (a - p) < -eps) return a.dis(p);
        const line<T> l = {p, v};
        return l.dis(a);
    }
 
    // 线段到射线距离
    long double dis (const segment<T> & s) const
    {
        if(is_inter(s)) return 0;
        return min({dis(s.a), dis(s.b), s.dis(p)});
    }
 
    // 射线到射线距离
    long double dis (const ray & r) const
    {
        if(is_inter(r)) return 0;
        return min(dis(r.p), r.dis(p));
    }
 
    // 射线从点 p 沿着方向 v 到达 直线/线段/射线 的距离
    // 1. 直线
    long double dis_from_p_in_v (const line<T> & l) const
    {
        const int t = is_inter(l);
        if(t <= 0) return t ? 0 : -1;
        return line<T>{p, v}.inter_dis(l);
    }
 
    // 2. 线段
    long double dis_from_p_in_v (const segment<T> & s) const
    {
        const int t = is_inter(s);
        if(t == 0) return -1;
        if(t == -1) {
            if(s.is_on(p)) return 0;
            else if(is_on(s.a) && is_on(s.b)) return min(p.dis(s.a), p.dis(s.b));
        }
        return line<T>{p, v}.inter_dis(line<T>{s.a, s.b - s.a});
    }
 
    // 3. 射线
    long double dis_from_p_in_v (const ray & r) const
    {
        const int t = is_inter(r);
        if(t == 0) return -1;
        if(t == -1) return r.is_on(p) ? 0 : p.dis(r.p);
        return line<T>{p, v}.inter_dis(line<T>{r.p, r.v});
    }
};
 
using Ray = ray<point_t>;
 
 
// 多边形
template<typename T> struct polygon
{
    vector<point<T>> p;  // 以逆时针顺序存储
 
    size_t nxt (const int i) const { return i == p.size() - 1 ? 0 : i + 1; }
    size_t pre (const int i) const { return i == 0 ? p.size() - 1 : i - 1; }
 
    // 回转数
    // 返回值第一项表示点是否在多边形边上
    // 对于狭义多边形，回转数为 0 表示点在多边形外，否则点在多边形内
    pair<bool, int> winding (const point<T> & a) const
    {
        int cnt = 0;
        for(size_t i = 0; i < p.size(); i ++ )
        {
            const point<T> u = p[i], v = p[nxt(i)];
            if(abs((a - u) ^ (a - v)) <= eps && (a - u) * (a - v) <= eps) return {true, 0};
            if(abs(u.y - v.y) <= eps) continue;
            const line<T> uv = {u, v - u};
            if(u.y < v.y - eps && uv.toleft(a) <= 0) continue;
            if(u.y > v.y + eps && uv.toleft(a) >= 0) continue;
            if(u.y < a.y - eps && v.y >= a.y - eps) cnt ++ ;
            if(u.y >= a.y - eps && v.y < a.y - eps) cnt -- ;
        }
        return {false, cnt};
    }
 
    // 多边形面积的两倍
    // 可用于判断点的存储顺序是顺时针或逆时针
    T area () const
    {
        T sum = 0;
        for(size_t i = 0; i < p.size(); i ++ ) sum += p[i] ^ p[nxt(i)];
        return sum;
    }
 
    long double circ() const
    {
        long double sum = 0;
        for(size_t i = 0; i < p.size(); i ++ ) sum += p[i].dis(p[nxt(i)]);
        return sum;
    }
};
 
using Polygon = polygon<point_t>;
 
 
// 凸多边形
template<typename T> struct convex : polygon<T>
{
    // 多边形的邻点叉积前缀和，用于计算凸多边形的凸壳的面积
    // 注意：如果是顺时针储存，sum 储存的面积为负数
    vector<T> sum;
 
    void get_sum ()
    {
        const auto & p = this -> p;
        vector<T> a(p.size());
        for(size_t i = 0; i < p.size(); i ++ ) a[i] = p[this -> pre(i)] ^ p[i];
        sum.resize(p.size());
        partial_sum(a.begin(), a.end(), sum.begin());
    }
 
    T query_sum (const size_t l, const size_t r) const
    {
        const auto & p = this -> p;
        if(l <= r) return sum[r] - sum[l] + (p[r] ^ p[l]);
        return sum.back() - sum[l] + sum[r] + (p[r] ^ p[l]);
    }
    T query_sum () const { return sum.back(); }
 
 
    // 闵可夫斯基和
    // 复杂度 O(n)
    convex operator + (const convex & c) const
    {
        const auto & p = this -> p;
        if(!p.size()) return c; if(!c.p.size()) return *this;
        vector<segment<T>> e1(p.size()), e2(c.p.size()), edge(p.size() + c.p.size());
        vector<point<T>> res; res.reserve(p.size() + c.p.size());
        const auto cmp = [] (const segment<T> & u, const segment<T> & v) {
            return argcmp() (u.b - u.a, v.b - v.a);
        };
        for(size_t i = 0; i < p.size(); i ++ ) e1[i] = {p[i], p[this -> nxt(i)]};
        for(size_t i = 0; i < c.p.size(); i ++ ) e2[i] = {c.p[i], c.p[c.nxt(i)]};
        rotate(e1.begin(), min_element(e1.begin(), e1.end(), cmp), e1.end());
        rotate(e2.begin(), min_element(e2.begin(), e2.end(), cmp), e2.end());
        merge(e1.begin(), e1.end(), e2.begin(), e2.end(), edge.begin(), cmp);
        const auto check = [] (const vector<point<T>> & res, const point<T> & u)
        {
            const auto v = *prev(res.end(), 2), w = res.back();
            return (w - v).toleft(u - w) == 0 && (w - v) * (u - w) >= -eps;
        };
        auto u = e1[0].a + e2[0].a;
        for(const auto & v : edge)
        {
            while(res.size() > 1 && check(res, u)) res.pop_back();
            res.push_back(u);
            u = u + v.b - v.a;
        }
        if(res.size() > 1 && check(res, res[0])) res.pop_back();
        return {res};
    }
 
    // 旋转卡壳
    // func 为更新答案的函数，可以根据题目调整位置
    template<typename F> void rotcaliper (const F & func) const
    {
        const auto & p = this -> p;
        const auto area = [] (const point<T> & u, const point<T> & v, const point<T> & w) { return (w - v) ^ (u - v); };
        for(size_t i = 0, j = 1; i < p.size(); i ++ )
        {
            const auto nxti = this -> nxt(i);
            while(area(p[this -> nxt(j)], p[i], p[nxti]) >= area(p[j], p[i], p[nxti]))
            {
                j = this -> nxt(j);
            }
            func(p[j], p[i], p[nxti]);
        }
    }
 
    // 凸多边形的直径的平方
    T diameter2 () const
    {
        const auto & p = this -> p;
        if(p.size() <= 2) return 0;
        T ans = 1e18;
        const auto func = [&] (const point<T> & u, const point<T> & v, const point<T> & w) {
            ans = min(ans, Line{v, w - v}.dis(u));
        };
        rotcaliper(func);
        return ans;
    }
     
    // 判断点是否在凸多边形内
    // 复杂度 O(logn)
    // -1 点在多边形边上 | 0 点在多边形外 | 1 点在多边形内
    int is_in (const point<T> & a) const
    {
        const auto & p = this -> p;
        if(p.size() == 1) return a == p[0] ? -1 : 0;
        if(p.size() == 2) return segment<T>{p[0], p[1]}.is_on(a) ? -1 : 0;
        if(a == p[0]) return -1;
        if((p[1] - p[0]).toleft(a - p[0]) == -1 || (p.back() - p[0]).toleft(a - p[0]) == 1) return 0;
        const auto cmp = [&] (const point<T> & u, const point<T> & v) {
            return (u - p[0]).toleft(v - p[0]) == 1;
        };
        const size_t i = lower_bound(p.begin() + 1, p.end(), a, cmp) - p.begin();
        if(i == 1) return segment<T>{p[0], p[1]}.is_on(a) ? -1 : 0;
        if(i == p.size() - 1 && segment<T>{p[0], p.back()}.is_on(a)) return -1;
        if(segment<T>{p[i - 1], p[i]}.is_on(a)) return -1;
        return (p[i] - p[i - 1]).toleft(a - p[i - 1]) > 0;
    }
     
    // 凸多边形关于某一方向的极点
    // 复杂度 O(logn)
    // 参考资料：https://codeforces.com/blog/entry/48868
    template<typename F> size_t extreme (const F & dir) const
    {
        const auto & p = this -> p;
        const auto check = [&] (const size_t i) {
            return dir(p[i]).toleft(p[this -> nxt(i)] - p[i]) >= 0;
        };
        const auto dir0 = dir(p[0]); const auto check0 = check(0);
        if(!check0 && check(p.size() - 1)) return 0;
        const auto cmp = [&] (const point<T> & v)
        {
            const size_t vi = &v - p.data();
            if(vi == 0) return 1;
            const auto checkv = check(vi);
            const auto t = dir0.toleft(v - p[0]);
            if(vi == 1 && checkv == check0 && t == 0) return 1;
            return checkv ^ (checkv == check0 && t <= 0);
        };
        return partition_point(p.begin(), p.end(), cmp) - p.begin();
    }
 
    // 过凸多边形外一点求凸多边形的切线，返回切点下标
    // 复杂度 O(logn)
    // 必须保证点在多边形外
    // 必须保证凸多边形点数大于等于 3，点数小于等于 2 的 case 需要特判
    pair<size_t, size_t> tangent (const point<T> & a) const
    {
        const size_t i = extreme([&] (const point<T> & u) { return u - a; });
        const size_t j = extreme([&] (const point<T> & u) { return a - u; });
        return {i, j};
    }
 
    // 求平行于给定直线的凸多边形的切线，返回切点下标
    // 复杂度 O(logn)
    // 必须保证凸多边形点数大于等于 3，点数小于等于 2 的 case 需要特判
    pair<size_t, size_t> tangent (const line<T> & a) const
    {
        const size_t i = extreme([&] (...) { return a.v; });
        const size_t j = extreme([&] (...) { return -a.v; });
        return {i, j};
    }
};
 
using Convex = convex<point_t>;
 
// 圆
struct Circle
{
    Point c;
    long double r;
 
    bool operator == (const Circle & a) const { return c == a.c && abs(r - a.r) <= eps; }
    long double circ () const { return 2 * PI * r; }  // 周长
    long double area () const { return PI * r * r; }  // 面积
 
    // 点与圆的关系
    // -1 圆上 | 0 圆外 | 1 圆内
    int is_in (const Point & p) const
    {
        const long double d = p.dis(c);
        if(abs(d - r) <= eps) return -1;
        return d < r - eps;
    }
 
    // 直线与圆关系
    // 0 相离 | 1 相切 | 2 相交
    int relation (const Line & l) const
    {
        const long double d = l.dis(c);
        if(d < r - eps) return 2;
        return abs(d - r) <= eps;
    }
 
    // 圆与圆关系
    // -1 相同 | 0 相离 | 1 外切 | 2 相交 | 3 内切 | 4 内含
    int relation (const Circle & a) const
    {
        if((*this) == a) return -1;
        const long double d = c.dis(a.c);
        if(d > r + a.r + eps) return 0;
        if(abs(d - r - a.r) <= eps) return 1;
        if(abs(d - abs(r - a.r)) <= eps) return 3;
        if(d < abs(r - a.r) - eps) return 4;
        return 2;
    }
 
    // 直线与圆的交点
    vector<Point> inter (const Line & l) const
    {
        const long double d = l.dis(c);
        const Point p = l.proj(c);
        const int t = relation(l);
        if(t == 0) return {};
        if(t == 1) return {p};
        const long double k = sqrt(r * r - d * d);
        return {p - l.v * k / l.v.len(), p + l.v * k / l.v.len()};
    }
 
    // 圆与圆交点
    vector<Point> inter (const Circle & a) const
    {
        const long double d = c.dis(a.c);
        const int t = relation(a);
        if(t == -1 || t == 0 || t == 4) return {};
        Point e = a.c - c; e = e * r / e.len();
        if(t == 1 || t == 3)
        {
            if(r * r + d * d - a.r * a.r >= -eps) return {c + e};
            return {c - e};
        }
        const long double costh = (r * r + d * d - a.r * a.r) / (2 * d * r), sinth = sqrt(1 - costh * costh);
        return {c + e.rot(costh, -sinth), c + e.rot(costh, sinth)};
    }
 
    // 圆与圆交面积
    long double inter_area (const Circle & a) const
    {
        const long double d = c.dis(a.c);
        const int t = relation(a);
        if(t == -1) return area();
        if(t <= 1) return 0;
        if(t >= 3) return min(area(), a.area());
        const long double costh1 = (r * r + d * d - a.r * a.r) / (2 * r * d), costh2 = (a.r * a.r + d * d - r * r) / (2 * a.r * d);
        const long double sinth1 = sqrt(1 - costh1 * costh1), sinth2 = sqrt(1 - costh2 * costh2);
        const long double th1 = acos(costh1), th2 = acos(costh2);
        return r * r * (th1 - costh1 * sinth1) + a.r * a.r * (th2 - costh2 * sinth2);
    }
 
    // 过圆外一点圆的切线
    vector<Line> tangent (const Point & a) const
    {
        const int t = is_in(a);
        if(t == 1) return {};
        if(t == -1) return {{a, (a - c).rot()}};
        Point e = a - c; e = e * r / e.len();
        const long double costh = r / c.dis(a), sinth = sqrt(1 - costh * costh);
        const Point t1 = c + e.rot(costh, -sinth), t2 = c + e.rot(costh, sinth); // t1, t2 对应为切点
        return {{a, t1 - a}, {a, t2 - a}};
    }
 
    // 两圆的公切线
    vector<Line> tangent (const Circle & a) const
    {
        const int t = relation(a);
        if(t == -1 || t == 4) return {};
        vector<Line> lines;
        if(t == 1 || t == 3)
        {
            const Point p = inter(a)[0], v = (a.c - c).rot();
            lines.push_back({p, v}); // t = 1: 内切线; t = 3: 外切线
        }
        const long double d = c.dis(a.c);
        const Point e = (a.c - c) / (a.c - c).len();
        const auto add = [&] (int sign)
        {
            const long double costh = (r - a.r * sign) / d, sinth = sqrt(1 - costh * costh);
            const Point d1 = e.rot(costh, -sinth), d2 = e.rot(costh, sinth);
            const Point u1 = c + d1 * r, u2 = c + d2 * r, v1 = a.c + d1 * sign * a.r, v2 = a.c + d2 * sign * a.r;
            lines.push_back({u1, v1 - u1}), lines.push_back({u2, v2 - u2});
        };
        if(t <= 2) add(1); // 外切线
        if(t == 0) add(-1); // 内切线
        return lines;
    }
 
    // 圆上反演
    tuple<bool, Point> inverse (const Point & a) const
    {
        if(a == c) return {0, {}};
        const Point v = a - c;
        const long double d = r * r / c.dis(a);
        return {1, c + v * d / v.len()};
    }
 
    tuple<int, Circle, Line> inverse (const Line & l) const
    {
        if(l.toleft(c) == 0) return {2, {}, l};
        const Point v = l.toleft(c) == 1 ? -l.v.rot() : l.v.rot();
        const long double d = r * r / l.dis(c);
        const Point p = c + v * d / v.len();
        return {1, {(c + p) / 2, d / 2}, {}};
    }
 
    tuple<int, Circle, Line> inverse (const Circle & a) const
    {
        const Point v = a.c - c;
        if(a.is_in(c) == -1)
        {
            const long double d = r * r / (a.r + a.r);
            const Point p = c + v * d / v.len();
            return {2, {}, {p, v.rot()}};
        }
        if(c == a.c) return {1, {c, r * r / a.r}, {}};
        const long double d1 = r * r / (c.dis(a.c) - a.r), d2 = r * r / (c.dis(a.c) + a.r);
        const Point p = c + v * d1 / v.len(), q = c + v * d2 / v.len();
        return {1, {(p + q) / 2, p.dis(q) / 2}, {}};
    }
};
 
 
// 点集的凸包
// Andrew 算法，复杂度 O(nlogn)
Convex convexhull (vector<Point> p)
{
    vector<Point> st;
    if(!p.size()) return Convex{st};
    sort(p.begin(), p.end());
    const auto check = [] (const vector<Point> & st, const Point & u)
    {
        const auto v = *prev(st.end(), 2), w = st.back();
        return (w - v).toleft(u - w) <= 0;
    };
    for(const Point & u : p)
    {
        while(st.size() > 1 && check(st, u)) st.pop_back();
        st.push_back(u);
    }
    size_t k = st.size();
    p.pop_back(); reverse(p.begin(), p.end());
    for(const Point & u : p)
    {
        while(st.size() > k && check(st, u)) st.pop_back();
        st.push_back(u);
    }
    st.pop_back();
    return Convex{st};
}
 
// 半平面交
// 排序增量法，复杂度 O(nlogn)
// 输入与返回值都是用直线表示的半平面集合。返回为空表示无解
vector<Line> halfinter_get_lines (vector<Line> l, const point_t lim = 1e9)
{
    const auto check = [] (const Line & a, const Line & b, const Line & c) { return a.toleft(b.inter(c)) < 0; };
    // 无精度误差的方法，但注意取值范围会扩大到三次方
    // const auto check = [] (const Line & a, const Line & b, const Line & c)
    // {
    //  const Point p = a.v * (b.v ^ c.v), q = b.p * (b.v ^ c.v) + b.v * (c.v ^ (b.p - c.p)) - a.p * (b.v ^ c.v);
    //  return p.toleft(q) < 0;
    // };
    l.push_back({{lim, 0}, {0, 1}}), l.push_back({{-lim, 0}, {0, -1}});
    l.push_back({{0, lim}, {-1, 0}}), l.push_back({{0, -lim}, {1, 0}});
    sort(l.begin(), l.end(), [] (const Line & a, const Line & b) {
        if(a.v.toleft(b.v) == 0 && a.v * b.v >= -eps) return a.toleft(b.p) == -1;
        return argcmp() (a.v, b.v);
    });
    deque<Line> q;
    for(size_t i = 0; i < l.size(); i ++ )
    {
        if(i > 0 && l[i - 1].v.toleft(l[i].v) == 0 && l[i - 1].v * l[i].v >= -eps) continue;
        while(q.size() > 1 && check(l[i], q.back(), q[q.size() - 2])) q.pop_back();
        while(q.size() > 1 && check(l[i], q[0], q[1])) q.pop_front();
        if(q.size() && q.back().v.toleft(l[i].v) <= 0) return {};
        q.push_back(l[i]);
    }
    while(q.size() > 1 && check(q[0], q.back(), q[q.size() - 2])) q.pop_back();
    while(q.size() > 1 && check(q.back(), q[0], q[1])) q.pop_front();
    return vector<Line>(q.begin(), q.end());
}
 
// 输入是用直线表示的半平面集合，返回是半平面交在框架内形成的凸包。返回为空表示无解
Convex halfinter_get_convex (vector<Line> & l, const point_t lim = 1e9)
{
    const auto lines = halfinter_get_lines(l, lim);
    Convex poly; poly.p.resize(lines.size());
    if(!lines.size()) return poly;
    for(size_t i = 0; i < lines.size(); i ++ )
    {
        const size_t j = (i == lines.size() - 1 ? 0 : i + 1);
        poly.p[i] = lines[i].inter(lines[j]);
    }
    // 如果重点不影响答案，则不需要去重
    // poly.p.erase(unique(poly.p.begin(), poly.p.end()), poly.p.end());
    // if(poly.p.front() == poly.p.back()) poly.p.pop_back();
    return poly;
}
 
// 平面旋转 + 动态维护排名，解决平面旋转上关键事件更新答案的问题，复杂度 O(n^2 logn)
// 以 (点集形成的最小最大三角形) 问题为例
// 最大三角形问题可以使用凸包与旋转卡壳做到 O(n^2)
pair<point_t, point_t> minmax_triangle (vector<Point> p)
{
    int n = p.size();
    if(n <= 2) return {0, 0};
    vector<int> rk(n), id(n);
    vector<pair<int, int>> vec; vec.reserve(n * n);
 
    auto cal = [&] (const int i, const int j) -> pair<point_t, point_t> {
        point_t mn = 1e18, mx = 0;
        int rkn = rk[i];
        for(int k = max(0, rkn - 2); k <= min(n - 1, rkn + 2); k ++ ) if(k != rk[i] && k != rk[j])
            mn = min(mn, abs( (p[i] - p[j]) ^ ( p[id[k]] - p[j] ) ));
        if(rk[i] != 0 && rk[j] != 0)
            mx = max(mx, abs( (p[i] - p[j]) ^ ( p[id[0]] - p[j] ) ));
        if(rk[i] != n - 1 && rk[j] != n - 1)
            mx = max(mx, abs( (p[i] - p[j]) ^ ( p[id[n - 1]] - p[j] ) ));
        return {mn, mx};
    };
 
    sort(p.begin(), p.end(), [] (const Point & a, const Point & b) {
        if(a.y != b.y) return a.y < b.y;
        return a.x > b.x;
    });
    for(int i = 0; i < p.size(); i ++ )
    {
        rk[i] = id[i] = i;
        for(int j = 0; j < p.size(); j ++ ) if(i != j) vec.push_back({i, j});
    }
    sort(vec.begin(), vec.end(), [&] (const pair<int, int> & a, const pair<int, int> & b) {
        return argcmp() (p[a.second] - p[a.first], p[b.second] - p[b.first]);
    });
    point_t minans = 1e18, maxans = 0;
    for(auto [i, j] : vec)
    {
        auto [mn, mx] = cal(i, j);
        minans = min(minans, mn), maxans = max(maxans, mx);
        swap(rk[i], rk[j]), swap(id[rk[i]], id[rk[j]]);
    }
    return {minans, maxans};
}
 
// 判断多条线段是否有交点
// 扫描线，复杂度 O(nlogn)
bool segs_is_inter (const vector<Segment> & segs)
{
    if(!segs.size()) return false;
    using seq_t = tuple<point_t, int, Segment>;
    const auto seqcmp = [] (const seq_t & u, const seq_t & v)
    {
        const auto [u0, u1, u2] = u;
        const auto [v0, v1, v2] = v;
        if(abs(u0 - v0) <= eps) return make_pair(u1, u2) < make_pair(v1, v2);
        return u0 < v0 - eps;
    };
    vector<seq_t> seq;
    for(auto seg : segs)
    {
        if(seg.a.x > seg.b.x + eps) swap(seg.a, seg.b);
        seq.push_back({seg.a.x, 0, seg});
        seq.push_back({seg.b.x, 1, seg});
    }
    sort(seq.begin(), seq.end(), seqcmp);
    point_t x_now;
    auto cmp = [&] (const Segment & u, const Segment & v)
    {
        if(abs(u.a.x - u.b.x) <= eps || abs(v.a.x - v.b.x) <= eps) return u.a.y < v.a.y - eps;
        return ((x_now - u.a.x) * (u.b.y - u.a.y) + u.a.y * (u.b.x - u.a.x)) * (v.b.x - v.a.x) < ((x_now - v.a.x) * (v.b.y - v.a.y) + v.a.y * (v.b.x - v.a.x)) * (u.b.x - u.a.x) - eps;
    };
    multiset<Segment, decltype(cmp)> s{cmp};
    for(const auto [x, o, seg] : seq)
    {
        x_now = x;
        const auto it = s.lower_bound(seg);
        if(o == 0){
            if(it != s.end() && seg.is_inter(*it)) return 1;
            if(it != s.begin() && seg.is_inter(*prev(it))) return 1;
            s.insert(seg);
        }else{
            if(next(it) != s.end() && it != s.begin() && (*prev(it)).is_inter(*next(it))) return 1;
            s.erase(it);
        }
    }
    return 0;
}
 
// 多边形面积并
// 轮廓积分，复杂度 O(n^2logn)，n为边数
// ans[i] 表示被至少覆盖了 i+1 次的区域的面积
vector<long double> area_union (const vector<Polygon> & polys)
{
    const size_t siz = polys.size();
    vector<vector<pair<Point,Point>>> segs(siz);
    const auto check = [] (const Point & u, const Segment & e) {return !((u < e.a && u < e.b) || (u > e.a && u > e.b)); };
 
    auto cut_edge = [&] (const Segment & e, const size_t i)
    {
        const Line le{e.a, e.b - e.a};
        vector<pair<Point,int>> evt;
        evt.push_back({e.a, 0}); evt.push_back({e.b, 0});
        for(size_t j = 0; j < polys.size(); j ++ )
        {
            if(i == j) continue;
            const auto & pj = polys[j];
            for(size_t k = 0; k < pj.p.size(); k ++ )
            {
                const Segment s = {pj.p[k], pj.p[pj.nxt(k)]};
                if(le.toleft(s.a) == 0 && le.toleft(s.b) == 0)
                {
                    evt.push_back({s.a, 0});
                    evt.push_back({s.b, 0});
                }
                else if(s.is_inter(le))
                {
                    const Line ls{s.a, s.b - s.a};
                    const Point u = le.inter(ls);
                    if(le.toleft(s.a) < 0 && le.toleft(s.b) >= 0) evt.push_back({u, -1});
                    else if(le.toleft(s.a) >= 0 && le.toleft(s.b) < 0) evt.push_back({u, 1});
                }
            }
        }
        sort(evt.begin(), evt.end());
        if(e.a > e.b) reverse(evt.begin(), evt.end());
        int sum = 0;
        for(size_t i = 0; i < evt.size(); i ++ )
        {
            sum += evt[i].second;
            const Point u = evt[i].first, v = evt[i + 1].first;
            if(!(u == v) && check(u, e) && check(v, e)) segs[sum].push_back({u, v});
            if(v == e.b) break;
        }
    };
     
    for(size_t i = 0; i < polys.size(); i ++ )
    {
        const auto & pi = polys[i];
        for(size_t k = 0; k < pi.p.size(); k ++ )
        {
            const Segment ei = {pi.p[k], pi.p[pi.nxt(k)]};
            cut_edge(ei, i);
        }
    }
    vector<long double> ans(siz);
    for(size_t i = 0; i < siz; i ++ )
    {
        long double sum = 0;
        sort(segs[i].begin(), segs[i].end());
        int cnt = 0;
        for(size_t j = 0; j < segs[i].size(); j ++ )
        {
            if(j > 0 && segs[i][j] == segs[i][j - 1]) segs[i + ( ++ cnt)].push_back(segs[i][j]);
            else cnt = 0, sum += segs[i][j].first ^ segs[i][j].second;
        }
        ans[i] = sum / 2;
    }
    return ans;
}
 
// 圆面积并
// 轮廓积分，复杂度 O(n^2logn)
// ans[i] 表示被至少覆盖了 i+1 次的区域的面积
// x_0 * r * ( sin(thr) - sin(thl) ) - y_0 * r * ( cos(thr) - cos(thl) ) + r * r * ( thr - thl )
vector<long double> area_union (const vector<Circle> & circs)
{
    const size_t siz = circs.size();
    using arc_t = tuple<Point, long double, long double, long double>;
    vector<vector<arc_t>> arcs(siz);
    const auto eq = [] (const arc_t & u, const arc_t & v)
    {
        const auto [u1, u2, u3, u4] = u;
        const auto [v1, v2, v3, v4] = v;
        return u1 == v1 && abs(u2 - v2) <= eps && abs(u3 - v3) <= eps && abs(u4 - v4) <= eps;
    };
 
    auto cut_circ = [&] (const Circle & ci, const size_t i)
    {
        vector<pair<long double,int>> evt;
        evt.push_back({-PI, 0}); evt.push_back({PI, 0});
        int init = 0;
        for(size_t j = 0; j < circs.size(); j ++ )
        {
            if(i == j) continue;
            const Circle & cj = circs[j];
            if(ci.r < cj.r - eps && ci.relation(cj) >= 3) init ++ ;
            const auto inters = ci.inter(cj);
            if(inters.size() == 1) evt.push_back({atan2l((inters[0] - ci.c).y, (inters[0] - ci.c).x), 0});
            if(inters.size() == 2)
            {
                const Point dl = inters[0] - ci.c, dr = inters[1] - ci.c;
                long double argl = atan2l(dl.y, dl.x), argr = atan2l(dr.y, dr.x);
                if(abs(argl + PI) <= eps) argl = PI;
                if(abs(argr + PI) <= eps) argr = PI;
                if(argl > argr + eps)
                {
                    evt.push_back({argl, 1}); evt.push_back({PI, -1});
                    evt.push_back({-PI, 1}); evt.push_back({argr, -1});
                }else
                {
                    evt.push_back({argl, 1});
                    evt.push_back({argr, -1});
                }
            }
        }
        sort(evt.begin(), evt.end());
        int sum = init;
        for(size_t i = 0; i < evt.size(); i ++ )
        {
            sum += evt[i].second;
            if(abs(evt[i].first - evt[i + 1].first) > eps) arcs[sum].push_back({ci.c, ci.r, evt[i].first, evt[i + 1].first});
            if(abs(evt[i + 1].first - PI) <= eps) break;
        }
    };
 
    const auto oint = [] (const arc_t & arc)
    {
        const auto [cc, cr, l, r] = arc;
        if(abs(r - l - PI - PI) <= eps) return 2.0l * PI * cr * cr;
        return cr * cr * (r - l) + cc.x * cr * (sin(r) - sin(l)) - cc.y * cr * (cos(r) - cos(l));
    };
 
    for(size_t i = 0; i < circs.size(); i ++ )
    {
        const auto & ci = circs[i];
        cut_circ(ci, i);
    }
    vector<long double> ans(siz);
    for(size_t i = 0; i < siz; i ++ )
    {
        long double sum = 0;
        sort(arcs[i].begin(), arcs[i].end());
        int cnt = 0;
        for(size_t j = 0; j < arcs[i].size(); j ++ )
        {
            if(j > 0 && eq(arcs[i][j], arcs[i][j - 1])) arcs[i + ( ++ cnt)].push_back(arcs[i][j]);
            else cnt = 0, sum += oint(arcs[i][j]);
        }
        ans[i] = sum / 2;
    }
    return ans;
}
 
// 圆与多边形面积交
long double inter_area (const Circle & circ, const Polygon & poly)
{
    const auto cal = [] (const Circle & circ, const Point & a, const Point & b)
    {
        if((a - circ.c).toleft(b - circ.c) == 0) return 0.0l;
        const auto ina = circ.is_in(a), inb = circ.is_in(b);
        const Line ab = {a, b - a};
        if(ina && inb) return ((a - circ.c) ^ (b - circ.c)) / 2;
        if(ina && !inb)
        {
            const auto t = circ.inter(ab);
            const Point p = t.size() == 1 ? t[0] : t[1];
            const long double ans = ((a - circ.c) ^ (p - circ.c)) / 2;
            const long double th = (p - circ.c).ang(b - circ.c);
            const long double d = circ.r * circ.r * th / 2;
            if((a - circ.c).toleft(b - circ.c) == 1) return ans + d;
            return ans - d;
        }
        if(!ina && inb)
        {
            const Point p = circ.inter(ab)[0];
            const long double ans = ((p - circ.c) ^ (b - circ.c)) / 2;
            const long double th = (a - circ.c).ang(p - circ.c);
            const long double d = circ.r * circ.r * th / 2;
            if((a - circ.c).toleft(b - circ.c) == 1) return ans + d;
            return ans - d;
        }
        const auto p = circ.inter(ab);
        if(p.size() == 2 && Segment{a, b}.dis(circ.c) <= circ.r + eps)
        {
            const long double ans = ((p[0] - circ.c) ^ (p[1] - circ.c)) / 2;
            const long double th1 = (a - circ.c).ang(p[0] - circ.c), th2 = (b - circ.c).ang(p[1] - circ.c);
            const long double d1 = circ.r * circ.r * th1 / 2, d2 = circ.r * circ.r * th2 / 2;
            if((a - circ.c).toleft(b - circ.c) == 1) return ans + d1 + d2;
            return ans - d1 - d2;
        }
        const long double th = (a - circ.c).ang(b - circ.c);
        if((a - circ.c).toleft(b - circ.c) == 1) return circ.r * circ.r * th / 2;
        return -circ.r * circ.r * th / 2;
    };
 
    long double ans = 0;
    for(size_t i = 0; i < poly.p.size(); i ++ )
    {
        const Point a = poly.p[i], b = poly.p[poly.nxt(i)];
        ans += cal(circ, a, b);
    }
    return abs(ans);
}