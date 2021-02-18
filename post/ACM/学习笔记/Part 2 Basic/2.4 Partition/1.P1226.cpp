/*
纯快速幂
详细介绍：https://zhuanlan.zhihu.com/p/95902286
*/
#include <bits/stdc++.h>
using namespace std;
int quickPow(long long x, long long pow, long long k)
{
    long long ans = 1;
    while (pow)
    {
        if (pow & 1)
            ans = (ans % k) * (x % k) % k;
        x = (x % k) * (x % k) % k;
        pow >>= 1;
    }
    return ans % k;
}
int main()
{
    long long n, p, m;
    cin >> n >> p >> m;
    printf("%lld^%lld mod %lld=%d", n, p, m, quickPow(n, p, m));
}