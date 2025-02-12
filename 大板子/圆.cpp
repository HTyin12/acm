
#define eps 1e-8
struct point
{
    double x, y;
};
double xmult(point p1, point p2, point p0)
{
    return (p1.x - p0.x) * (p2.y - p0.y) - (p2.x - p0.x) * (p1.y - p0.y);
}
double distance(point p1, point p2)
{
    return sqrt((p1.x - p2.x) * (p1.x - p2.x) + (p1.y - p2.y) * (p1.y - p2.y));
}
double disptoline(point p, point l1, point l2)
{
    return fabs(xmult(p, l1, l2)) / distance(l1, l2);
}
point intersection(point u1, point u2, point v1, point v2)
{
    point ret = u1;
    double t = ((u1.x - v1.x) * (v1.y - v2.y) - (u1.y - v1.y) * (v1.x - v2.x)) / ((u1.x - u2.x) * (v1.y - v2.y) - (u1.y - u2.y) * (v1.x - v2.x));
    ret.x += (u2.x - u1.x) * t;
    ret.y += (u2.y - u1.y) * t;
    return ret;
}
// 判直线和圆相交,包括相切
int intersect_line_circle(point c, double r, point l1, point l2)
{
    return disptoline(c, l1, l2) < r + eps;
}
// 判线段和圆相交,包括端点和相切
int intersect_seg_circle(point c, double r, point l1, point l2)
{
    double t1 = distance(c, l1) - r, t2 = distance(c, l2) - r;
    point t = c;
    if (t1 < eps || t2 < eps)
        return t1 > -eps || t2 > -eps;
    t.x += l1.y - l2.y;
    t.y += l2.x - l1.x;
    return xmult(l1, c, t) * xmult(l2, c, t) < eps && disptoline(c, l1, l2) - r < eps;
}
// 判圆和圆相交,包括相切
int intersect_circle_circle(point c1, double r1, point c2, double r2)
{
    return distance(c1, c2) < r1 + r2 + eps && distance(c1, c2) > fabs(r1 - r2) - eps;
}
// 计算圆上到点 p 最近点,如 p 与圆心重合,返回 p 本身
point dot_to_circle(point c, double r, point p)
{
    point u, v;
    if (distance(p, c) < eps)
        return p;
    u.x = c.x + r * fabs(c.x - p.x) / distance(c, p);
    u.y = c.y + r * fabs(c.y - p.y) / distance(c, p) * ((c.x - p.x) * (c.y - p.y) < 0 ? -1 : 1);
    v.x = c.x - r * fabs(c.x - p.x) / distance(c, p);
    v.y = c.y - r * fabs(c.y - p.y) / distance(c, p) * ((c.x - p.x) * (c.y - p.y) < 0 ? -1 : 1);
    return distance(u, p) < distance(v, p) ? u : v;
}
// 计算直线与圆的交点,保证直线与圆有交点
// 计算线段与圆的交点可用这个函数后判点是否在线段上
void intersection_line_circle(point c, double r, point l1, point l2, point &p1, point &p2)
{
    point p = c;
    double t;
    p.x += l1.y - l2.y;
    p.y += l2.x - l1.x;
    p = intersection(p, c, l1, l2);
    t = sqrt(r * r - distance(p, c) * distance(p, c)) / distance(l1, l2);
    p1.x = p.x + (l2.x - l1.x) * t;
    p1.y = p.y + (l2.y - l1.y) * t;
    p2.x = p.x - (l2.x - l1.x) * t;
    p2.y = p.y - (l2.y - l1.y) * t;
}
// 计算圆与圆的交点,保证圆与圆有交点,圆心不重合
void intersection_circle_circle(point c1, double r1, point c2, double r2, point &p1, point &p2)
{
    point u, v;
    double t;
    t = (1 + (r1 * r1 - r2 * r2) / distance(c1, c2) / distance(c1, c2)) / 2;
    u.x = c1.x + (c2.x - c1.x) * t;
    u.y = c1.y + (c2.y - c1.y) * t;
    v.x = u.x + c1.y - c2.y;
    v.y = u.y - c1.x + c2.x;
    intersection_line_circle(c1, r1, u, v, p1, p2);
}