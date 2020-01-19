#include <bits/stdc++.h>
using namespace std;

int d[1005];
const int inf = (int)1e9;

int adj[1005][1005];
int f[500005], s[500005];
bool ok[1005][1005];
bool v[1005];
int p[1005];

int main()
{
	ios::sync_with_stdio(false);
	cin.tie(0);

	int n, m, i, j;
	cin >> n >> m;
	for (i = 1; i <= n; i++)
		fill(adj[i], adj[i + 1], inf);
	for (i = 1; i <= m; i++)
	{
		int a, b, w;
		cin >> a >> b >> w;
		f[i] = a;
		s[i] = b;
		if (w < adj[a][b])
			adj[a][b] = adj[b][a] = w;
	}

	int ans = 0;
	for (i = 0; i <= m; i++)
	{
		if (i != 0 && !ok[f[i]][s[i]])
			continue;
		fill(d, d + n + 1, inf);
		memset(v, 0, sizeof v);
		d[1] = 0;

		//while에서 다익스트라를 돌리되 v^2으로 돌리는 다익스트라다.
		while (true)
		{
			//아직 줄일 수 있다고 생각되는 것을 하나 잡고
			int cur = 0;
			for (j = 1; j <= n; j++)
				if (!v[j] && d[j] < d[cur])
					cur = j;
			if (cur == 0)
				break;
			v[cur] = true;
			//run!
			for (j = 1; j <= n; j++)
			{
				if (min(cur, j) == f[i] && max(cur, j) == s[i])
					continue;
				int w = d[cur] + adj[cur][j];
				if (w < d[j])
				{
					d[j] = w;
					p[j] = cur;
				}
			}
		}
		if (i == 0)
			for (int j = n; j != 1; j = p[j])
				ok[j][p[j]] = ok[p[j]][j] = true;
		else
			ans = max(ans, d[n]);
	}
	cout << ans;
	return 0;
}