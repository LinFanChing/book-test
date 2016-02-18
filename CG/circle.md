圆
==

## 圆与线求交

将线段AB写成参数方程P=A+t(B-A)，带入圆的方程，得到一个一元二次方程。解出t就可以求得线段所在直线与圆的交点。如果0<=t<=1则说明点在线段上。

```cpp
void circle_cross_line(Pt a, Pt b, Pt o, double r, Pt ret[], int &num) {
    double ox = o.x, oy = o.y, ax = a.x, ay = a.y, bx = b.x, by = b.y;
    double dx = bx-ax, dy = by-ay;
    double A = dx*dx + dy*dy;
    double B = 2*dx*(ax-ox) + 2*dy*(ay-oy);
    double C = sqr(ax-ox) + sqr(ay-oy) - sqr(r);
    double delta = B*B - 4*A*C;
    num = 0;
    if (sgn(delta) >= 0) {
        double t1 = (-B - Sqrt(delta)) / (2*A);
        double t2 = (-B + Sqrt(delta)) / (2*A);
        if (sgn(t1-1) <= 0 && sgn(t1) >= 0)
            ret[num++] = Pt(ax + t1*dx, ay + t1*dy);
        if (sgn(t2-1) <= 0 && sgn(t2) >= 0)
            ret[num++] = Pt(ax + t2*dx, ay + t2*dy);
    }
}
```

## 圆与圆求交

```cpp
// 计算圆a和圆b的交点，注意要先判断两圆相交
void circle_circle_cross(Pt ap, double ar, Pt bp, double br, Pt p[]) {
    double d = (ap - bp).norm();
    double cost = (ar*ar + d*d - br*br) / (2*ar*d);
    double sint = sqrt(1.0 - cost*cost);
    Pt v = (bp - ap) / (bp - ap).norm() * ar;
    p[0] = ap + rotate(v, cost, -sint);
    p[1] = ap + rotate(v, cost, sint);
}
```

## 圆与多边形交

## 圆的面积并

