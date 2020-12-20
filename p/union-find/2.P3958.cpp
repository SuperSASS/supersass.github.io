/*
并查集算法
用father数组记录每个节点的父节点，数据结构类似于树
关键操作：合并、查询
详细介绍: https://zhuanlan.zhihu.com/p/93647900
*/
//P3958 奶酪: https://www.luogu.com.cn/problem/P3958
#include <bits/stdc++.h>
#define N 1005
using namespace std;
inline int quickRead()
{
    int f = 1, num = 0;
    char t = getchar();
    while (t < '0' || t > '9')
        f = t == '-' ? -1 : 1, t = getchar();
    while (t >= '0' && t <= '9')
        num = num * 10 + t - '0', t = getchar();
    return f * num;
}
struct typeUnionFind
{
    int num, father[N], rank[N]; //这里rank作用是记录节点深度（真实为深度-1），采用了按秩合并的优化
    /*
    按秩合并指将深度小的合并到深度大的树上，这样可以减少查询次数。
    这里按秩合并与路径压缩一起使用时，rank可能会因路径压缩操作而变得不准确。
    因此这里rank只是相对的判断标准，并不一定绝对会将深度小的合并到深度大的
    */

    void init(int n)
    {
        num = n;
        for (int i = 1; i <= num; i++)
            father[i] = i;
    }
    inline int find(int node)
    {
        return father[node] == node ? node : (father[node] = find(father[node])); //这里使用了路径压缩优化
    }
    inline void merge(int node1, int node2)
    {
        int father1 = find(node1), father2 = find(node2);
        if (rank[father1] < rank[father2])
            father[father1] = father2;
        else if (rank[father1] > rank[father2])
            father[father2] = father1;
        else if (father1 != father2)
            father[father1] = father2, rank[father2]++; //如果深度一样且父节点不一样（不为一棵树），合并后新树深度会加一
    }
} UnionFind;

struct typeHole
{
    long long x, y, z;
} hole[N];
bool ifIntersect(typeHole hole1, typeHole hole2, long long r)
{
    return (hole1.x - hole2.x) * (hole1.x - hole2.x) + (hole1.y - hole2.y) * (hole1.y - hole2.y) + (hole1.z - hole2.z) * (hole1.z - hole2.z) <= 4 * r * r;
}
int main()
{
    long long T, n, h, r;
    scanf("%lld", &T);
    while (T--)
    {
        scanf("%d%lld%lld", &n, &h, &r);
        UnionFind.init(n);
        UnionFind.father[1001] = 1001, UnionFind.father[1002] = 1002; //这里用特殊的两个节点，1001代表底，1002代表顶。如果father[1001]==father[1002]则证明连通。
        for (int i = 1; i <= UnionFind.num; i++)
        {
            scanf("%lld%lld%lld", &hole[i].x, &hole[i].y, &hole[i].z);
            if (hole[i].z <= r)
                UnionFind.merge(1001, i);
            if (hole[i].z >= h - r)
                UnionFind.merge(1002, i);
        }
        for (int i = 1; i <= UnionFind.num; i++)
            for (int j = 1; j <= UnionFind.num && i != j; j++)
                if (ifIntersect(hole[i], hole[j], r))
                    UnionFind.merge(i, j);
        if (UnionFind.find(1001) == UnionFind.find(1002))
            printf("Yes\n");
        else
            printf("No\n");
    }
}

/*
WA 1st:
没考虑到只有一个洞以及贯穿的情况……
修改:
1. merge(i,1001) ---> mergr(1001,i)
    实际上完全没必要，因为无论前并后还是后并前，最终都是父节点合并……
2. if (hole.z<=r) ... else if (hole.z>=h-r) ...; ---> if ...; if ...;
    当时想着要么是底部相交要么是顶部相交，导致用了个else if，没考虑到直接贯穿的情况……

WA 2nd:
long long！！！！……
*/