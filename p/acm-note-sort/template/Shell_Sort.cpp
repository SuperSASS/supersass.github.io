#include <bits/stdc++.h>
using namespace std;

#define MAX_N 100000

template <typename T>
void shell_sort(T array[], int begin, int end) //希尔排序（优化的插入）
{
	int h = 1, length = end - begin + 1;
	while (h < length / 3)
	{
		h = 3 * h + 1;
	}
	while (h >= 1)
	{
		for (int i = h + begin; i <= end; i++)
		{
			for (int j = i; j >= h && array[j] < array[j - h]; j -= h)
			{
				std::swap(array[j], array[j - h]);
			}
		}
		h = h / 3;
	}
}

int a[MAX_N];

int main()
{
	int n;
	scanf("%d", &n);
	for (int i = 1; i <= n; ++i)
		scanf("%d", &a[i]);
	shell_sort(a, 1, n);
	for (int i = 1; i <= n; ++i)
		printf("%d ", a[i]);
	return 0;
}
