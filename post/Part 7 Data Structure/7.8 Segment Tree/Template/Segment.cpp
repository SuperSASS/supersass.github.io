#include <bits/stdc++.h>

#define N 100000

#define NOW_Node node[index]	  //代表当前节点
#define NOW_LSon node[index].sonL //代表当前节点左儿子下标
#define NOW_RSon node[index].sonR //代表当前节点右儿子下标
using namespace std;
long long arr[N + 5];
struct typeSegment
{
	int cnt = 0; //记录node节点的数量，便可实现按顺序建树

	struct typeNode
	{
		long long val;
		int L, R, len, mid, sonL = 0, sonR = 0, lazy = 0;

		void pushdown(typeSegment &Segment) //下放也不用太彻底，左右儿子仍加到lazy里。【能摸一层是一层xd……
		{
			val += len * lazy;
			if (sonL)
				Segment.modify(sonL, L, mid, lazy); //存在子节点才下放【不然我这种结构就会无限下放
			if (sonR)
				Segment.modify(sonR, mid + 1, R, lazy);
			lazy = 0; //lazy注意清零。
		}
	} node[N * 2];

	void build(int &index, int L, int R) //对区间[l,r]建立节点，下标为index
	{
		index = ++cnt;
		//引用原因：
		//这里因为引用index的原因，在递归时会直接把seg[index].lson赋值为左儿子的index。
		NOW_Node.L = L, NOW_Node.R = R,
		NOW_Node.mid = (L + R) >> 1, NOW_Node.len = R - L + 1;
		//节点基本信息
		if (L == R)
			NOW_Node.val = arr[R]; //为递归边界，直接为对应区间的值
		else
		{
			build(NOW_LSon, L, NOW_Node.mid);
			//划分建立左区间，注意这里传的index是sed[index].lson
			build(NOW_RSon, NOW_Node.mid + 1, R);
			//划分建立右区间
			NOW_Node.val = node[NOW_LSon].val + node[NOW_RSon].val;
			//计算该区间信息
		}
	}

	void modify(int index, const int &m_L, const int &m_R, const int &m_val)
	{
		if (m_L <= NOW_Node.L && NOW_Node.R <= m_R)
			NOW_Node.lazy += m_val; //当前区间完全在范围里，直接偷懒。
		else
		{
			NOW_Node.val += (min(m_R, NOW_Node.R) - max(m_L, NOW_Node.L) + 1) * m_val;
			/*
			这里是修改所包含区间的值
			如要修改[4,9]，当前节点区间是(1,6)	//这里为了区分用的小括号，实际上包含端点
			则只会修改[4,6)，也就是val += (6 - 4 + 1) * 2
			*/
			if (m_L <= NOW_Node.mid)
				modify(NOW_LSon, m_L, m_R, m_val);
			if (m_R > NOW_Node.mid)
				modify(NOW_RSon, m_L, m_R, m_val);
		}
	}

	long long query(int index, const int &q_L, const int &q_R)
	{
		if (NOW_Node.lazy) //注意查询的时候，只要有懒标记就必下放【别人都来查岗了你还摸鱼.jpg……
			NOW_Node.pushdown(*this);
		if (q_L <= NOW_Node.L && NOW_Node.R <= q_R)
			return NOW_Node.val;
		//当前区间直接在查询区间里，直接返回值//【我查了，一句返回了，有什么好说的……

		//↓ 不完全包含于查询区间里，就要查询两子区间的值计算
		long long tmpAns = 0;
		if (q_L <= NOW_Node.mid)
			tmpAns += query(NOW_LSon, q_L, q_R);
		//如果要查询区间左端点，比当前区间的中点还大，证明左儿子区间完全不在
		if (q_R > NOW_Node.mid)
			tmpAns += query(NOW_RSon, q_L, q_R);
		return tmpAns;
	}
} Segment; //直接用个大的结构体，便于模板化。

int main()
{
	int n, m, tmp, w, l, r, i;
	cin >> n >> m;
	for (int i = 1; i <= n; i++)
		scanf("%lld", &arr[i]);
	Segment.build(tmp, 1, n);
	//Segment.test(1);
	while (m--)
	{
		scanf("%d", &w);
		if (w == 1)
		{
			scanf("%d%d%d", &l, &r, &i);
			Segment.modify(1, l, r, i);
		}
		else
		{
			scanf("%d%d", &l, &r);
			printf("%lld\n", Segment.query(1, l, r));
		}
	}
}