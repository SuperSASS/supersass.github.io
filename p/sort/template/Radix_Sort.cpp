//基数排序
/* 使用要求：
必须为整形数组。

对于无法定义关键字的结构体，是无法使用基数排序的。
*/
/* 参数说明：
radixsort(T,int,int)
1. T: 需要排序的整形数组
2. int: 开始排序的位置
3. int: 结束排序的位置
*/
int maxbit(int data[], int begin, int n) //求最大位数
{
	int d = 1; //保存最大的位数
	int p = 10;
	for (int i = begin; i <= begin + n - 1; i++)
		while (data[i] >= p)
		{
			p *= 10;
			++d;
		}
	return d;
}
void radixsort(int data[], int begin, int end) //基数排序
{
	int n = end - begin + 1, //数组长度
		d = maxbit(data, begin, n),
		tmp[n+1],
		count[10], //计数器
		radix = 1, //基数
		i, j, k;
	for (i = 1; i <= d; i++) //进行d次排序
	{
		for (j = 0; j < 10; j++)
			count[j] = 0; //每次分配前清空计数器
		for (j = begin; j <= end; j++)
		{
			k = (data[j] / radix) % 10; //统计每个桶中的记录数
			count[k]++;
		}
		for (j = 1; j < 10; j++)
			count[j] = count[j - 1] + count[j]; //将tmp中的位置依次分配给每个桶
		for (j = end; j >= begin; j--)			//将所有桶中记录依次收集到tmp中
		{
			k = (data[j] / radix) % 10;
			tmp[count[k]] = data[j];
			count[k]--;
		}
		for (j = begin; j <= end; j++) //将临时数组的内容复制到data中
			data[j] = tmp[j];
		radix = radix * 10;
	}
}
//使用例
#include <iostream>
using namespace std;
int main()
{
	int n;
	cin >> n;
	int array[n+1];
	for (int i = 1; i <= n; i++)
		cin >> array[i];
	radixsort(array, 1, n);
	for (int i = 1; i <= n; i++)
		printf("%d ", array[i]);
	return 0;
}