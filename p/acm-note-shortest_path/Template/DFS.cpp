struct typeNode
{
	int cnt;
	struct typeEdge
	{
		int to, val;
	} edge[N + 5];
} node[N + 5];

bool instack[N + 5]; //用以记录当前入栈状态
bool SPFA(int u)
{
	int flag = 1;						   //记录是否找到环，默认为1即没找到（找出最小路）
	instack[u] = true;					   //节点入栈
	for (int i = 1; i <= node[u].cnt; i++) //遍历u的边
	{
		int v = node[u].edge[i].to, val = node[u].edge[i].val;
		if (dist[u] + val < dist[v]) //relax判断
		{
			dist[v] = dist[u] + val; //更新答案
			if (!instack[v])		 //如果终点不在栈内
				flag = SPFA(v);		 //深搜
			else					 //否则
				return 0;			 //有负环
		}
	}
	instack[u] = false; //将当前结点退栈
	return flag;
}
