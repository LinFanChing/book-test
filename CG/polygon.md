多边形
======

## 简单多边形

简单多边形是边不相交的多边形，大部分我们在编程竞赛中的计算几何题目中的多边形都是简单多边形，所以在这个手册中所提到的多边形都是简单多边形。

## 判断点在多边形内

### 判断方法

判断点在多边形内：从该点做一条水平向右的射线，统计射线与多边形相交的情况，若相交次数为偶数，则说明该点在形外，否则在形内。为了便于交点在定点或射线与某些边重合时的判断，可以将每条边看成左开右闭的线段，即若交点为左端点就不计算。

### 示例代码

```cpp
#define nxt(x) ((x+1)%n)

int PtInPolygon(Pt p, Polygon &a) {
	int num = 0, d1, d2, k, n = size(a);
	for (int i = 0; i < n; ++i) {
		if (PtOnSegment(p, a[i], a[nxt(i)])) {
			return 2;
		}
		k = sgn(det(a[nxt(i)]-a[i], p-a[i]));
		d1 = sgn(a[i].y - p.y);
		d2 = sgn(a[nxt(i)] - p.y);
		if (k > 0 && d1 <= 0 && d2 > 0) num++;
		if (k < 0 && d2 <= 0 && d1 > 0) num--;
	}
	return num != 0;
}
```

## 多边形的面积

### 求法

多边形的面积可以靠三角剖分求得。对多边形的每一条边和原点$$O$$所组成的三角形通过叉积求有向面积并简单求和，就可以求得多边形的有向面积。而且通过求得的有向面积能判断出多边形中点的方向。如果输入多边形点的方向是按照逆时针给出的话，求得的面积就是正数，如果输入的多边形的点是按照顺时针给出的话，求得的面积就是负数。

#### 示例代码

```cpp
#define nxt(x) ((x+1)%n)

double polygon_area(const Polygon &p) {
    double ans = 0.0;
    int n = p.size();
    for (int i = 0; i < n; ++i)
        ans += det(p[i], p[nxt(i)]);
    return ans / 2.0;
}
```

## 多边形的重心

### 算法

将多边形分割为三角形的并，并对每个三角形求重心，然后以三角形的有向面积为权值将所有面积加权求和即可。

#### 示例代码

```cpp
#define nxt(x) ((x+1)%n)

Pt polygon_mass_center(const Polygon &p) {
    Pt ans = Pt(0, 0);
    double area = polygon_area(p);
    if (sgn(area) == 0) return ans;
    int n = p.size();
    for (int i = 0; i < n; ++i)
        ans = ans + (p[i]+p[nxt(i)]) * det(p[i], p[nxt(i)]);
    return ans / area / 6.0;
}
```

## 多边形内的格点数

### Pick公式

给定顶点坐标均是整点的简单多边形，有：

```
面积 = 内部格点数 + 边上格点数 / 2 - 1
```

### 边界的格点数

把每条边当作左开右闭的区间避免重复，一条左开右闭的线段$$AB$$上的格点数为$$gcd(B_x-A_x,B_y-A_y)$$。

```cpp
int polygon_border_point_cnt(const Polygon &p) {
    int ans = 0;
    int n = p.size();
    for (int i = 0; i < n; ++i)
        ans += gcd(Abs(int(p[next(i)].x-p[i].x)), Abs(int(p[next(i)].y-p[i].y)));
    return ans;
}

int polygon_inside_point_cnt(const Polygon &p) {
    return int(polygon_area(p)) + 1 - polygon_border_point_cnt(p) / 2;
}
```

