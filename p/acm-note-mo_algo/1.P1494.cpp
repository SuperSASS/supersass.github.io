#include <bits/stdc++.h>
#define ALL(NAME_i, BEGIN, TO) \
    int NAME_i = BEGIN;        \
    NAME_i <= TO;              \
    NAME_i++
#define ALL_invert(NAME_i, BEGIN, TO) \
    int NAME_i = BEGIN;               \
    NAME_i >= TO;                     \
    NAME_i--
typedef long long LL;
using namespace std;

#define MAX_N 50000
#define MAX_M 50000

int color[MAX_N + 5], cnt[MAX_M + 5], BLOCK_SIZE;
LL nume[MAX_M + 5], deno[MAX_M + 5];

struct queryType
{
    int l, r, id;

    //bool operator<(const queryType &a) const { return l == a.l ? r < a.r : l < a.l; } //直接排序
    //bool operator<(const queryType &a) const { return l / BLOCK_SIZE == a.l / BLOCK_SIZE ? r < a.r : l < a.l; } //分块排序
    bool operator<(const queryType &a) const { return l / BLOCK_SIZE == a.l / BLOCK_SIZE ? (l / BLOCK_SIZE & 1) ^ (r < a.r) : l < a.l; } //分块排序+奇偶性优化

} query[MAX_M + 5];

inline LL C(const int &n, const int &m)
{
    LL ans = 1;
    for (int i = n; i >= n - m + 1; i--)
        ans *= i;
    for (int i = 2; i <= m; i++)
        ans /= i;
    return ans;
}
inline LL GCD(const LL &a, const LL &b) { return b ? GCD(b, a % b) : a; }
inline int intRead()
{
    int f = 1, num = 0;
    char t = getchar();
    while (t < '0' || t > '9')
        if (t == '-')
            f = -1, t = getchar();
        else
            t = getchar();
    while (t >= '0' && t <= '9')
        num = num * 10 + t - '0', t = getchar();
    return f * num;
}

inline void add(const int &color, LL &ans) { ans += cnt[color]++; }
inline void dec(const int &color, LL &ans) { ans -= --cnt[color]; }

int main()
{
    int n = intRead(), m = intRead();
    BLOCK_SIZE = sqrt(n);
    for (ALL(i, 1, n))
        color[i] = intRead();
    for (ALL(i, 1, m))
        query[i].l = intRead(), query[i].r = intRead(), query[i].id = i;
    sort(query + 1, query + m + 1);
    /* 排序的原因：
	使得每次区间的差距不那么大，因此move的操作便会大大减少。

	e.g.
	1 100
	49 51
	2 99
	48 52
	3 97

	对于这组数据，如果不排序直接莫队，  
	便会进行大量重复的增减区间操作。

	---

	若简单排序为：
	1 100
	2 99
	3 97
	48 52
	49 51

	则会使增减区间操作大大减少。
	*/
    /* 如何排序：
    1. 直接按照l和r的大小来排序

    l为升序，最坏情况为$O(n)$，  
    r最坏情况为反复在最大最小移动，则为$O(n^2)$。
    > e.g.
    >
    > 1 100
    > 2 2
    > 3 100
    > 4 4
    > 5 100
    > 6 6

    故最坏情况复杂度为$O(n^2)$，会TLE。

    ---

    2. 分块

    定一个块大小`BLOCK_SIZE`为$sqrt(n)$，  
    以l来划分块。

    对于不同块，则按照块大小排序；  
    对于相同块(`a.l/BLOCK_SIZE == b.l/BLOCK_SIZE`)，则按照`r`大小排序。

    这样划分之后，  
    在同一块内，`l`在`BLOCK_SIZE`范围内振荡，`r`为升序，  
    不同块，最坏情况为`r`从一极点移动到另一极点，复杂度为$O(n)$。

    这样下来复杂度为$O(n\sqrt{n})$。

    > OI-Wiki上的证明太复杂懒得看了x_(:з」∠)_……  
    > 这里简单证明一下。
    >
    > 同一块中，长度为$\sqrt{n}$，  
    > `l`最坏情况为“每次从最大振荡到最小，再振荡到最大”，则移动次数为$\sqrt{n}*\sqrt{n}=n$，  
    > `r`为递增，所以最坏情况移动次数为$n$，  
    >
    > 跨块的时候，  
    > `l`最坏移动$\sqrt{n}$次，  
    > `r`最坏移动$n$次，
    >
    > 所以每一块（同时算上同一块和跨块的移动操作）移动次数为$3n+\sqrt{n}$，  
    > 一共$\sqrt{n}$块，  
    > 则最坏情况，总移动次数为$3n\sqrt{n}+n$。
    >
    > 即复杂度为$O(n\sqrt{n})$。

    ---

    3. 分块优化——奇偶化排序

    对于这组已排好序的数据：
    （令：`n`为`100`，即`BLOCK_SIZE`为$10$）
    > 1 1
    > 2 100
    > 10 3
    > 11 100

    如果按照这样的顺序进行操作，  
    在第二步`r`为$100$后，  
    执行第三步会跳到$3$，执行第四步又会跳到$100$。

    而将顺序改为：
    > 1 1
    > 2 100
    > 11 100
    > 10 3
    则能减少一次从一极值跳到另一极值的情况。

    也就是说，对于第二种“分块”排序方法：
    在执行完某一块跳到下一块的时候，  
    `r`会从当前块的最大值，唐突移动到下一块的最小值，  
    从则造成多余的移动操作。

    而如果将奇数块改为从小到大排序，偶数块改为从大到小排序，  
    则在跳块的时候，能很平滑的从这一块最大过渡到下一块最大。

    这种优化能使程序快$30%$。
    */

    int now_l = 1, now_r = 0; //这里初值l=1,r=0
    LL now_nume = 0;

#define L query[i].l
#define R query[i].r
#define ID query[i].id
    for (ALL(i, 1, m))
        if (L == R)
            nume[ID] = 0, deno[ID] = 1;
        else
        {
            while (now_l > L)
                add(color[--now_l], now_nume);
            while (now_r < R)
                add(color[++now_r], now_nume);
            while (now_l < L)
                dec(color[now_l++], now_nume);
            while (now_r > R)
                dec(color[now_r--], now_nume);

            nume[ID] = now_nume;
            if (now_nume)
            {
                deno[ID] = C(R - L + 1, 2);
                LL gcd = GCD(nume[ID], deno[ID]);
                nume[ID] /= gcd, deno[ID] /= gcd;
            }
            else
                deno[ID] = 1;
        }

    for (ALL(i, 1, m))
        printf("%lld/%lld\n", nume[i], deno[i]);
}
/*
10 15
1 1 1 1 1 1 1 1 1 1 
5 10
1 8
6 9
6 9
9 10
3 10
1 4
3 9
5 9
4 9
1 4
1 8
7 8
3 9
1 3

分块反而多
*/