半平面
======

## 简介

1. 什么是半平面？顾名思义，半平面就是指平面的一半，我们知道，一条直线可以将平面分为两个部分，那么这两个部分就叫做两个半平面。
2. 半平面怎么表示呢？二维坐标系下，直线可以表示为 ax + by + c = 0，那么两个半平面则可以表示为 ax + by + c >= 0 和 ax + by + c < 0，这就是半平面的表示方法。
3. 半平面的交是什么？ 其实就是一个方程组，让你画出满足若干个式子的坐标系上的区域（类似于线性规划的可行域），方程组就是由类似于上面的这些不等式组成的。
4. 半平面交可以干什么？ 半平面交虽然说是半平面的问题，但它其实就是关于直线的问题。一个一个的半平面其实就是一个一个有方向的直线而已。

## 半平面交求法

我们用一个向量$$(x_1,y_1)\rightarrow(x_x,y_x)$$的左侧来描述一个半平面。首先将半平面按照极角排序，极角相同的则只保留最左侧的一个。然后用一个双端队列维护这些半平面：按照顺序插入，在插入半平面$$p_i$$之前判断双端队列尾部的两个半平面的交点是否在半平面$$p_i$$内，如果不是则删除最后一个半平面；判断双端队列尾部的两个半平面交是否在半平面$$p_i$$内，如果不是则删除第一个半平面。插入完毕之后再处理一下双端队列两端多余的半平面，最后求出尾端和顶端的两个半平面的交点即可。

### 模板代码

```cpp
// 计算半平面交
void halfplane_intersect(vector<HP> &v, Convex &output) {
    sort(v.begin(), v.end(), cmp_HP);
    deque<HP> q;
    deque<Pt> ans;
    q.push_back(v[0]);
    int n = v.size();
    for (int i = 1; i < n; ++i) {
        if (sgn(arg(v[i].t-v[i].s) - arg(v[i-1].t-v[i-1].s)) == 0)
            continue;
        while (ans.size() > 0 && !satisfy(ans.back(), v[i])) {
            ans.pop_back();
            q.pop_back();
        }
        while (ans.size() > 0 && !satisfy(ans.front(), v[i])) {
            ans.pop_front();
            q.pop_front();
        }
        ans.push_back(crosspoint(q.back(), v[i]));
        q.push_back(v[i]);
    }
    while (ans.size() > 0 && !satisfy(ans.back(), q.front())) {
        ans.pop_back();
        q.pop_back();
    }
    while (ans.size() > 0 && !satisfy(ans.front(), q.back())) {
        ans.pop_front();
        q.pop_front();
    }
    ans.push_back(crosspoint(q.back(), q.front()));
	output = vector<Pt>(ans.begin(), ans.end());
}
```

## 凸多边形交

```cpp
// 凸多边形交
void convex_intersection(const Convex &v1, const Convex &v2, Convex &out) {
    vector<HP> h;
    for (int i = 0, n = v1.size(); i < n; ++i)
        h.push_back(HP(v1[i], v1[nxt(i)]));
    for (int i = 0, n = v2.size(); i < n; ++i)
        h.push_back(HP(v2[i], v2[nxt(i)]));
    halfplane_intersect(h, out);
}
```

