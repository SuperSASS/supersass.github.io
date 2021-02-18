//P1908 [逆序对](https://www.luogu.com.cn/problem/P1908)
/*题目分析：
采用归并排序来计算逆序对……
因为分治后会使左右两部分分别有序，在归并时，如果选择了右半部分，证明这个数肯定比左半部分剩余的数都小，即逆序对数目sum+=mid-merge_l+1……
*/
/*归并排序：
[之前笔记](https://blog.csdn.net/qq_31029725/article/details/78073131)
*/
#include <bits/stdc++.h>
using namespace std;
#define N_MAX 500000
long long num[N_MAX + 5], t[N_MAX + 5];
long long sortMerge(int l, int r)
{
	long long sum = 0;
	if (l == r)
		return 0;
	int mid = (l + r) >> 1;
	sum += sortMerge(l, mid);
	sum += sortMerge(mid + 1, r);
	int merge_l = l, merge_r = mid + 1, index_t = l;
	while (index_t <= r)
	{
		if ((num[merge_l] <= num[merge_r] || merge_r > r) && merge_l < mid + 1)	//WA.1 极其注意这里是小于等于！！！……
			t[index_t++] = num[merge_l++];
		else
			sum += mid - merge_l + 1, t[index_t++] = num[merge_r++];
	}
	/*清晰写法：
	while (merge_l <= mid && merge_r <= r)
		if (num[merge_l] <= num[merge_r])
			t[index_t++] = num[merge_l++];
		else
			t[index_t++] = num[merge_r++], sum += mid - merge_l + 1; //选择a和b中最小的存入Temp中
	while (merge_l <= mid)
		t[index_t++] = num[merge_l++]; //处理a中剩余
	while (merge_r <= r)
		t[index_t++] = num[merge_r++]; //处理b中剩余
	*/
	for (int i = l; i <= r; i++)
		num[i] = t[i];
	return sum;
}
int main()
{
	int N;
	scanf("%d", &N);
	for (int i = 1; i <= N; i++)
		scanf("%lld", &num[i]);
	printf("%lld", sortMerge(1, N));
	/*for (int i = 1; i <= N; i++)
		printf("%d ", num[i]);*/
}
/*WA记录：
⭐1. 之前if ((num[merge_l] <= num[merge_r] ... 这里写的是 num[merge_l] < num[merge_r]。如果用小于的话，会导致等于的情况也当作逆序对计算……
*/