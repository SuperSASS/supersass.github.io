//P4343 [自动刷题机](https://www.luogu.com.cn/problem/P4343)
/*算法——1.3. 二分：
二分一般指二分查找算法……
* 满足条件
1. 所查找的值明确属于某个区间……
2. 具有单调性……（会有过小、相等、过大三种判断情况……
	【来自OI-WiKi】这里的有序是广义的有序，如果一个数组中的左侧或者右侧都满足某一种条件，而另一侧都不满足这种条件，也可以看作是一种有序
	（如果把满足条件看做1，不满足看做0，至少对于这个条件的这一维度是有序的）。换言之，二分搜索法可以用来查找~满足某种条件的最大（最小）的值~。
(3.)可能找出这个值很不容易（比如只能遍历），但能很容易判断是否满足条件……
*/

/*题目分析：
一看题，确实感觉有明显的二分思维【可能是因为刚做了道二分日常题的原因x……

* 模板化：
1. 求一个n，明确属于某个范围（如这道题就是n∈(1,2*10e14)）……
2. 加上有单调性（本题中如果n<ans(i,j)，则必定会导致sum<numAC，反之则会大于……
则是标准的二分查找的题……

* 二分的两种类：
1. 普通二分查找——n为确值【见 [P2218 覆盖问题](file:///F:\Code%20Files\OI%20Practice\Practice\Daily\11.11_P2218.cpp)……
2. 区间二分查找——n为区间，找最大最小值。即为本题……
而找最小最大的区别也不大，可以看下方具体实现……
*/
#include <bits/stdc++.h>
#define log_MAX 100000
#define span_MAX 20000000000000
#define ALL          \
	long long i = 1; \
	i <= numLog;     \
	i++
using namespace std;
long long cmd[log_MAX + 5], numLog, numAC;
inline long long intRead()
{
	long long f = 1, num = 0;
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
long long check(long long ans) //-1代表sum<k——需要R左移过来；0代表sum==k——根据求最大还是最小移；1代表sum>k——需要L右移过来
{
	long long sum = 0, ques = 0;
	for (ALL) //遍历计算sum，即这种情况的AC数
	{
		ques = ques + cmd[i] > 0 ? ques + cmd[i] : 0;
		if (ques >= ans)
			sum++, ques = 0;
	}
	if (sum < numAC)
		return -1;
	else if (sum == numAC)
		return 0;
	else
		return 1;
}
long long min_binSearch()
{
	long long L = 1, R = span_MAX;
	while (L <= R)
	{
		long long mid = (L + R) >> 1, re = check(mid);
		if (re == -1)
			R = mid - 1; //因为sum<numAC，故这个mid值肯定不是正确答案，直接R=mid-1
		if (re == 0)
		{
			R = mid;	//这里是正确答案，所以R=mid而不是R=mid-1
			if (L == R) //如果是正确答案并且L、R相等，则找到最值
				break;
		}
		if (re == 1)
			L = mid + 1; //与上同理
	}
	return L == R ? R : -1;
}
long long max_binSearch()
{
	long long L = 1, R = span_MAX;
	while (L <= R)
	{
		long long mid = ((L + R) >> 1) + ((L + R) % 2 ? 1 : 0), re = check(mid); //！这里也是重要的区别，我这种写法找左侧（最小）有余数的话取左，找右侧（最大）有余数的话取右，故要加1……
		if (re == -1)
			R = mid - 1;
		if (re == 0)
		{
			L = mid; //找最小最大的区别点
			if (L == R)
				break;
		}
		if (re == 1)
			L = mid + 1;
	}
	return L == R ? R : -1;
}
int main()
{
	numLog = intRead(), numAC = intRead();
	for (ALL)
		cmd[i] = intRead();
	long long minAns = min_binSearch();
	if (minAns == -1)
		printf("-1");
	else
		printf("%lld %lld", minAns, max_binSearch());
	return 0;
}

/*WA记录：
0. 数组没多开啊，没开longlong啊什么的orz……

0.1. 这里的n的范围是0-10e14！……并不是10e9！……span_MAX给我往高里开就完事了嗷！【但不要超过两倍啊kora！……

总结：不开longlong见祖宗！……
反正看到数据过10e9还是考虑考虑long long吧_(:з」∠)_……
*/