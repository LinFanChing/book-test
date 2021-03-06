凸包
====

## 点的有序化

凸包算法多要先对点进行排序。点排序的主要方法有两种——极角排序和水平排序。

### 极角排序

极角排序一般选择一个点做极点，然后以这个点为中心建立极坐标，将输入的点按照极角从小到大排序，如果两个点的极角相同，那么将距离极点较远的点排在前面。

### 水平排序

水平排序将所有点按照$$y$$坐标从小到大排列，$$y$$坐标相同的则按照$$x$$坐标从小到大排序。选取排序后最前面的$$A$$点和最后面的$$B$$点，将$$\vec{AB}$$右边的点按照次序取出，再将左侧的点按照次序逆序取出后连起来就是最终的结果。

### 比较

虽然水平排序比较复杂，但水平排序因为不涉及三角函数操作，精度较高，在条件相同时，最好选择水平排序。

## 凸包求法

### Graham 扫描法

Graham 算法是在某种意义上来说求解二维静态凸包的一种最优的算法，这种算法目前被广泛的应用于对各种以二维静态凸包为基础的 ACM 题目的求解。Graham 算法的时间复杂度大约是 nlogn，因此在求解二维平面上几万个点构成的凸包时，消耗的时间相对较少。

#### 算法描述

这里描述的 Graham 算法是经过改进后的算法而不是原始算法，因为改进之后的算法更易于对算法进行编码。

1. 已知有 n 个点的平面点集 p（p[0]~p[n-1]），找到二维平面中最下最左的点，即 y 坐标最小的点。若有多个 y 值最小的点，取其中 x 值最小的点。
2. 以这个最下最左的点作为基准点（即 p[0]），对二维平面上的点进行极角排序。
3. 将 p[0]、p[1]、p[2]三个点压入栈中（栈用 st 表示，top 表示栈顶指针的位置）。并将 p[0]的值赋给 p[n]。
4. 循环遍历平面点集 p[3]到 p[n]。对于每个 p[i]（ 3<=i<=n）若存在 p[i]在向量st[top-1]st[top]的顺时针方（包括共线）向且栈顶元素不多于 2 个时，将栈顶元素出栈，直到 p[i]在向量 st[top-1]st[top]的逆时针方向或栈中元素个数小于 3 时将 p[i]入栈。
5. 循环结束后，栈 st 中存储的点正好就是凸包的所有顶点，且这些顶点以逆时针的顺序存储在栈中（st[0]~st[top-1]）。注意：由于第三步中，将 p[0]的值赋给了 p[n]，此时栈顶元素 st[top]和 st[0]相同，因为最后入栈的点是 p[n]。

由于 Graham 算法是基于极角排序的，对平面上所有点极角排序的时间复杂度是nlogn，而之后逐点扫描的过程的时间复杂度是 n，因此整个 Graham 算法的时间复杂度接近 nlogn。

#### 实现细节的注意事项

##### 极角大小问题

实际实现 Graham 算法的极角排序并不是真正的按照极角大小排序，因为计算机在表示和计算浮点数时会有一定的误差。一般会利用叉积判断两个点的相对位置来实现极角排序的功能。假设以确定平面中最下最左的点（基准点）P，并已知平面上其它两个不同的点 A B。若点 A 在向量 PB 的逆时针方向，那么我们认为 A 的极角大于 B 的极角，反之 A 的极角小于 B 的极角（具体实现应借助叉积）。

##### 极角相同点的处理
在 Graham 算法中，经常会出现两个点极角相同的情况。对于具有相同极角的两个不同点 A B，那么我们应该把 A B 两点的按照距离基准点距离的降序排列。而对于完全重合的两点，可以暂不做处理。

### 模板代码

```cpp
typedef vector<Pt> Convex;

// 排序比较函数，水平序
bool comp_less(Pt a, Pt b) {
    return sgn(a.x-b.x) < 0 || (sgn(a.x-b.x) == 0 && sgn(a.y-b.y) < 0);
}

// 返回a中点计算出的凸包，结果存在res中
void convex_hull(Convex &res, vector<Pt> a) {
    res.resize(2 * a.size() + 5);
    sort(a.begin(), a.end(), comp_less);
    a.erase(unique(a.begin(), a.end()), a.end());
    int m = 0;
    for (int i = 0; i < int(a.size()); ++i) {
        while (m>1 && sgn(det(res[m-1] - res[m-2], a[i] - res[m-2])) <= 0)
            --m;
        res[m++] = a[i];
    }
    int k = m;
    for (int i = int(a.size()) - 2; i >= 0; --i) {
        while (m>k && sgn(det(res[m-1] - res[m-2], a[i] - res[m-2])) <= 0)
            --m;
        res[m++] = a[i];
    }
    res.resize(m);
    if (a.size() > 1) res.resize(m-1);
}
```

### Jarvis 步进法

Jarvis 步进法运用了一种称为打包的技术来计算一个点集 Q 的凸包。算法的运行时间
为 O(nh)，其中 h 为凸包 CH(Q)的顶点数。 当 h 为 O(lg(n))，Jarvis 步进法在渐进意义上
比 Graham 算法的速度快一点。
从直观上看，可以把 Jarvis 步进法相像成在集合 Q 的外面紧紧的包了一层纸。开始
时，把纸的末端粘在集合中最低的点上，即粘在与 Graham 算法开始时相同的点 p0 上。该
点为凸包的一个顶点。把纸拉向右边使其绷紧，然后再把纸拉高一些，知道碰到一个点。
该点也必定为凸包中的一个顶点。使纸保持绷紧状态，用这种方法继续围绕顶点集合，直
到回到原始点 p0。
更形式的说，Jarvis 步进法构造了 CH(Q)的顶点序列 H=(P0,P1,…,Ph-1)，其中 P0 为
原始点。如图所示，下一个凸包顶点 P1 具有相对与 P0 的最小极角。（如果有数个这样的
点，选择最远的那个点作为 P1。）类似地，P2 具有相对于 P1 的最小的极角，等等。当达
到最高顶点，如 Pk（如果有数个这样的点，选择最远的那个点）时，我们构造好了 CH(Q)
的右链了，为了构造其左链，从 Pk 开始选取相对于 Pk 具有最小极角的点作为 Pk+1，这时
的 x 轴是原 x 轴的反方向，如此继续，根据负 x 轴的极角逐渐形成左链，知道回到原始点
P0。

## 旋转卡壳

### 模板代码

```cpp
// 计算凸包a的直径
double convex_diameter(const Convex &a, int &first, int &second) {
    int n = a.size();
    double ans = 0.0;
	first = second = 0;
    if (n == 1) return ans;
    for (int i = 0, j = 1; i < n; ++i) {
        while (sgn(det(a[nxt(i)]-a[i], a[j]-a[i]) - det(a[nxt(i)]-a[i], a[nxt(j)]-a[i])) < 0)
            j = nxt(j);
        double d = max((a[i]-a[j]).norm(), (a[nxt(i)]-a[nxt(j)]).norm());
        if (d > ans) ans=d, first=i, second=j;
    }
    return ans;
}
```
