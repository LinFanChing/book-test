三角形
======

## 三角形的面积

三角形的面积可以由叉积直接求出。

$$
S_{\triangle ABC} = |\frac{1}{2} \vec{AB} \times \vec{AC}|
$$

## 判断点在三角形内

判断点$$P$$在三角形 ABC 内部常用的又两种方法，面积法和叉积法。

### 面积法

$$
S_{\triangle PAB} + S_{\triangle PAC} + S_{\triangle PBC} = S_{\triangle ABC}
$$

### 叉积法

利用叉积的正负号判断，如图所示，AP在向量AC的顺时针方向，CP在向量BC的顺时针方向，BP在向量BC的顺时针方向，利用这一性质推广，那么可以利用叉积的正负号来判断一个点是否在一个凸多边形内部。

## 三角形的重心

三角形三条中线的交点叫做三角形重心。

### 性质

设三角形重心为$$O$$，$$BC$$边中点为$$D$$，则有$$AO = 2OD$$。

### 求重心的方法

三角形的重心是三角形三个顶点的坐标的平均值。

## 三角形的外心

三角形三边的垂直平分线的交点，称为三角形外心。

### 性质

外心到三顶点距离相等。过三角形各顶点的圆叫做三角形的外接圆，外接圆的圆心即三角形外心，这个三角形叫做这个圆的内接三角形。

## 三角形的内心

三角形内心为三角形三条内角平分线的交点。

### 性质

与三角形各边都相切的圆叫做三角形的内切圆，内切圆的圆心即是三角形内心，内心到三角形三边距离相等。这个三角形叫做圆的外切三角形。

## 三角形的垂心

三角形三边上的三条高线交于一点，称为三角形垂心。

### 性质

锐角三角形的垂心在三角形内；直角三角形的垂心在直角的顶点；钝角三角形的垂心在三角形外。

## 费马点

费马点是在一个三角形中，到3个顶点距离之和最小的点。

### 计算方法

1. 若三角形ABC的3个内角均小于120度，那么3条距离连线正好平分费马点所在的周角。所以三角形的费马点也称为三角形的等角中心。
2. 若三角形有一内角不小于120度，则此钝角的顶点就是距离和最小的点。

#### 等角中心的计算方法

做任意一条边的外接等边三角形，得到另一点，将此点与此边在三角形中对应的点相连。如此再取另一边作同样的连线，相交点即费马点。

```cpp
#include <math.h>
struct point{double x,y;};
struct line{point a,b;};

double distance(point p1,point p2){
	return sqrt((p1.x-p2.x)*(p1.x-p2.x)+(p1.y-p2.y)*(p1.y-p2.y));
}

//已知两条直线求出交点
point intersection(line u,line v){
	point ret=u.a;
	double t=((u.a.x-v.a.x)*(v.a.y-v.b.y)-(u.a.y-v.a.y)*(v.a.x-v.b.x))
		/((u.a.x-u.b.x)*(v.a.y-v.b.y)-(u.a.y-u.b.y)*(v.a.x-v.b.x));
	ret.x+=(u.b.x-u.a.x)*t;
	ret.y+=(u.b.y-u.a.y)*t;
	return ret;
}

//外心
point circumcenter(point a,point b,point c){
	line u,v;
	u.a.x=(a.x+b.x)/2;
	u.a.y=(a.y+b.y)/2;
	u.b.x=u.a.x-a.y+b.y;
	u.b.y=u.a.y+a.x-b.x;
	v.a.x=(a.x+c.x)/2;
	v.a.y=(a.y+c.y)/2;
	v.b.x=v.a.x-a.y+c.y;
	v.b.y=v.a.y+a.x-c.x;
	return intersection(u,v);
}

//内心
point incenter(point a,point b,point c){
	line u,v;
	double m,n;
	u.a=a;
	m=atan2(b.y-a.y,b.x-a.x);
	n=atan2(c.y-a.y,c.x-a.x);
	u.b.x=u.a.x+cos((m+n)/2);
	u.b.y=u.a.y+sin((m+n)/2);
	v.a=b;
	m=atan2(a.y-b.y,a.x-b.x);
	n=atan2(c.y-b.y,c.x-b.x);
	v.b.x=v.a.x+cos((m+n)/2);
	v.b.y=v.a.y+sin((m+n)/2);
	return intersection(u,v);
}

//垂心
point perpencenter(point a,point b,point c){
	line u,v;
	u.a=c;
	u.b.x=u.a.x-a.y+b.y;
	u.b.y=u.a.y+a.x-b.x;
	v.a=b;
	v.b.x=v.a.x-a.y+c.y;
	v.b.y=v.a.y+a.x-c.x;
	return intersection(u,v);
}

//重心
//到三角形三顶点距离的平方和最小的点
//三角形内到三边距离之积最大的点
point barycenter(point a,point b,point c){
	line u,v;
	u.a.x=(a.x+b.x)/2;
	u.a.y=(a.y+b.y)/2;
	u.b=c;
	v.a.x=(a.x+c.x)/2;
	v.a.y=(a.y+c.y)/2;
	v.b=b;
	return intersection(u,v);
}

//费马点（模拟退火）
point fermentpoint(point a,point b,point c){
	point u,v;
	double step=fabs(a.x)+fabs(a.y)+fabs(b.x)+fabs(b.y)+fabs(c.x)+fabs(c.y);
	int i,j,k;
	u.x=(a.x+b.x+c.x)/3;
	u.y=(a.y+b.y+c.y)/3;
	while (step>1e-10) for (k=0;k<10;step/=2,k++)
	for (i=-1;i<=1;i++)
		for (j=-1;j<=1;j++){
			v.x=u.x+step*i;
			v.y=u.y+step*j;
			if(distance(u,a)+distance(u,b)+distance(u,c) >
			distance(v,a)+distance(v,b)+distanc
					e(v,c))
				u=v;
		}
	return u;
}
```
