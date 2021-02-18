#include <bits/stdc++.h>
using namespace std;
const int N = 5;
const int W = 10;

int n=N, w=W, a[N+1], cnt[W+1], b[N+1];

void counting_sort() {
  memset(cnt, 0, sizeof(cnt));
  for (int i = 1; i <= n; ++i) ++cnt[a[i]];
  for (int i = 1; i <= w; ++i) cnt[i] += cnt[i - 1];
  for (int i = n; i >= 1; --i)
  	b[cnt[a[i]]--] = a[i];
}

int main()
{
	a[1] = 5, a[2] = 3, a[3] = 10, a[4] = 1, a[5] = 3;

	counting_sort();
	
	for (int i = 1; i <= 5; i++)
		printf("%d ", b[i]);
}