struct typeNode
{
	int cnt;
	struct typeEdge
	{
		int to, val;
	} edge[N + 5];
} node[N + 5];

int vis[N + 5]; //用以记录某一点是否被访问
int cnt[N + 5]; //用以记录某一点的入队次数
while (!que.empty())
{
	int u = q.front();
	q.pop();
	vis[u] = 0;
	for (int i = 1; i <= node[u].cnt; i++) //遍历u节点的边
	{
		int v = node[u].edge[i].to, val = node[u].edge[i].val;
		if (dist[u] + val < dist[v]) //relax判断
		{
			dist[v] = dist[u] + val; //更新dist
			if (++cnt[v] >= n)		 //区别点：松弛次数加一后判断是否大于n-1
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