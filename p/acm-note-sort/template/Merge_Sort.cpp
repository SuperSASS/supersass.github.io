//归并排序
/* 特殊用途：
利用归并排序求逆序对，并可求出全排列的Hash
*/
/* 参数说明：
sortMerge_inv(T,int,int)
1. T: 需要排序的数组（支持自定义<=运算的结构体）
2. int: 开始排序的位置
3. int: 结束排序的位置

sortMerge_hash(T,int,int,int&)
1. T: 需要排序的数组（支持自定义<=运算的结构体）
2. int: 开始排序的位置
3. int: 结束排序的位置
4. int: 排序的长度（需要用个实际变量传递）
*/
#include <bits/stdc++.h>
using namespace std;
#define MAX_LENGTH 10 //5000000
#define ALL(NAME_i, BEGIN, TO) \
    int NAME_i = BEGIN;        \
    NAME_i <= TO;              \
    NAME_i++

long long inver[MAX_LENGTH];
template <typename T>
long long sortMerge_inv(T *rawArray, int indexLeft, int indexRight) //求逆序对版
{
    vector<T> tmpArray;
    long long sum = 0;
    if (indexLeft == indexRight)
        return 0;
    int mid = (indexLeft + indexRight) >> 1, indexTmpArray = 0, indexLeftMerge = indexLeft, indexRightMerge = mid + 1;
    sum += sortMerge_inv(rawArray, indexLeft, mid);
    sum += sortMerge_inv(rawArray, mid + 1, indexRight);
    while (indexLeftMerge <= mid || indexRightMerge <= indexRight)
    {
        if (indexLeftMerge <= mid && (rawArray[indexLeftMerge] <= rawArray[indexRightMerge] || indexRightMerge > indexRight))
            tmpArray.push_back(rawArray[indexLeftMerge++]);
        else
        {
            tmpArray.push_back(rawArray[indexRightMerge++]), sum += mid - indexLeftMerge + 1;
            for (ALL(i, indexLeftMerge, mid)) //这里为注意点：为左部分的剩余所有数的逆序对个数++
                inver[i]++;
        }
    }
    for (ALL(i, indexLeft, indexRight))
        rawArray[i] = tmpArray[indexTmpArray++];
    return sum;
}

int hash_index[10];
long long fact(int num)
{
    long long ans = 1;
    for (ALL(i, 1, num))
        ans *= i;
    return ans;
}
void hash_init(int len)
{
    for (ALL(i, 1, len))
        hash_index[i] = len - i;
}
template <typename T>
long long sortMerge_hash(T *rawArray, int indexLeft, int indexRight, const int &length) //求全排列的Hash
{
    if (indexLeft == indexRight)
        return 0;
    vector<T> tmpArray;
    vector<T> tmpFact; //用来swap后对位权的swap
    long long hashArr = 0;
    int mid = (indexLeft + indexRight) >> 1, indexTmpArray = 0, indexLeftMerge = indexLeft, indexRightMerge = mid + 1;
    hashArr += sortMerge_hash(rawArray, indexLeft, mid, length);
    hashArr += sortMerge_hash(rawArray, mid + 1, indexRight, length);
    while (indexLeftMerge <= mid || indexRightMerge <= indexRight)
    {
        if (indexLeftMerge <= mid && (rawArray[indexLeftMerge] <= rawArray[indexRightMerge] || indexRightMerge > indexRight))
            tmpArray.push_back(rawArray[indexLeftMerge++]), tmpFact.push_back(hash_index[indexLeftMerge - 1]);
        else
        {
            tmpArray.push_back(rawArray[indexRightMerge++]), tmpFact.push_back(hash_index[indexRightMerge - 1]);
            for (ALL(i, indexLeftMerge, mid)) //这里为注意点：为左部分的剩余所有数的逆序对个数++
            {
                hashArr += fact(hash_index[i]); //hash计算
            }
        }
    }
    for (ALL(i, indexLeft, indexRight))
        rawArray[i] = tmpArray[indexTmpArray++], hash_index[i] = tmpFact[indexTmpArray - 1]; //补了交换权重【这样也可以准确算出每一位的逆序对
    return hashArr;
}

int arr[MAX_LENGTH], arr_hash[MAX_LENGTH];
int main()
{
    int n;
    scanf("%d", &n);
    for (ALL(i, 1, n))
        scanf("%d", &arr[i]), arr_hash[i] = arr[i];

    printf("Each inversion:\n"); //输出每一位的逆序对个数
    cout << setw(7) << "---Top:";
    for (ALL(i, 1, n))
        cout << setw(7) << i;
    cout << endl
         << setw(7) << "---Num:";
    for (ALL(i, 1, n))
        cout << setw(7) << arr[i];
    cout << endl
         << setw(7) << "";
    for (ALL(i, 1, n))
        cout << setw(8) << "↓";
    cout << endl
         << setw(7) << "---CNT:";
    long long inverSum = sortMerge_inv(arr, 1, n);
    for (ALL(i, 1, n))
        cout << setw(7) << inver[i];
    printf("\nInversions conut: %lld\n", inverSum); //输出逆序对和

    hash_init(n);
    printf("Hash: %lld\n", sortMerge_hash(arr_hash, 1, n, n)); //输出全排列hash值

    printf("Sort: "); //输出归并排序后结果。
    for (ALL(i, 1, n))
        printf("%d ", arr[i]);
}