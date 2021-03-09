struct typeNode
{
	int cnt;
	struct typeEdge
	{
		int to, val;
	} edge[N + 5];
} node[N + 5];

int vis[N + 5];	//用以记录某一点是否被访问
int cnt[N + 5]; //用以记录某一点的入队次数
while (!que.empty())
{
	u = q.front();
	q.pop();
	vis[u] = 0;
	for (int i = 1; i <= node[u].cnt; i++)
	{
		int v = node[u].edge[i].to, val = node[u].edge[i].val;
		if (dist[u] + val < dist[v]) //relax判断
		{
			dist[v] = dist[u] + val; //更新dist
			if (!vis[v])		   //如果未在队列里
			{
				if (++cnt[v] >= n) //区别点：注意就是这个位置的判断。一定要保证在判vis之后，即判入队次数；而不是在判vis之前，即判松弛次数！！！
				{
					printf("YES\n");
					return;
				}
				vis[v] = 1;
				q.push(v);
			}
		}
	}
}