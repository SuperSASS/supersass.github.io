struct typeNode
{
	int cnt;
	struct typeEdge
	{
		int to, val;
	} edge[N + 5];
} node[N + 5];

int vis[N + 5];	//用以记录某一点是否被访问
int cnt[N + 5]; //用以记录到某一点所经过的边的个数
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
			if ((cnt[v] = cnt[u] + 1) > n)	//变为按边的个数判断
			{
				printf("YES\n");
				return;
			}
			if (!vis[v]) //如果未在队列里
			{
				vis[v] = 1;
				q.push(v);
			}
		}
	}
}