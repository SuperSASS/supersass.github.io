//P1774 [最接近神的人](https://www.luogu.com.cn/problem/P1774)
/* 题目分析：
很明显找逆序对……
即便加了限制只能交换相邻的两个数，也因为交换一次实际上就减且仅减少一个逆序对……
所以仍为找逆序对……
*/
#include <bits/stdc++.h>
using namespace std;
#define MAX_LENGTH 500000
#define ALL(NAME_i, BEGIN, TO) \
	int NAME_i = BEGIN;        \
	NAME_i <= TO;              \
	NAME_i++
int tmpArray[MAX_LENGTH + 5];
long long sortMerge(int *rawArray, int indexLeft, int indexRight)
{
	long long sum = 0; //WA.2.
	if (indexLeft == indexRight)
		return 0;
	int mid = (indexLeft + indexRight) >> 1, indexTmpArray = indexLeft, indexLeftMerge = indexLeft, indexRightMerge = mid + 1;
	sum += sortMerge(rawArray, indexLeft, mid);
	sum += sortMerge(rawArray, mid + 1, indexRight);
	while (indexTmpArray <= indexRight)
	{
		if (indexLeftMerge <= mid && (rawArray[indexLeftMerge] <= rawArray[indexRightMerge] || indexRightMerge > indexRight)) //WA.1.
			tmpArray[indexTmpArray++] = rawArray[indexLeftMerge++];
		else
			tmpArray[indexTmpArray++] = rawArray[indexRightMerge++], sum += mid - indexLeftMerge + 1;
	}
	for (ALL(i, indexLeft, indexRight))
		rawArray[i] = tmpArray[i];
	return sum;
}
int main()
{
	int n, array[MAX_LENGTH + 5];
	scanf("%d", &n);
	for (ALL(i, 1, n))
		scanf("%d", &array[i]);
	printf("%lld", sortMerge(array, 1, n));
}
/*WA 记录：
nima做过了还在WA！……
1st. 注意是<=不是<！！！！！！！！……

2nd. long long！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！……
*/