#include <bits/stdc++.h>
using namespace std;
using ll = long long;

vector<int> adj[300005];

int d[300005], e = 1;
int cnt[300005];

//단절점을 만드는 로직인데 공부가 필요함
int dfs(int i)
{
	d[i] = e;
	int ret = e++;

	for (int j : adj[i])
	{
		if (!d[j])
		{
			int o = dfs(j);
			if (o >= d[i])
				cnt[i]++;
			ret = min(ret, o);
		} else
			ret = min(ret, d[j]);
	}
	return ret;
}

int main()
{
	ios::sync_with_stdio(false);
	cin.tie(0);

	int n, m, i;
	cin >> n >> m;
	for (i = 0; i < m; i++)
	{
		int a, b;
		cin >> a >> b;
		adj[a].push_back(b);
		adj[b].push_back(a);
	}
	dfs(1);
	cnt[1]--;
	ll ans = 0;

	//n개의 정점, k개의 컴포넌트일 때 간선의 수가 n - k이면 포레스트
	//n개의 정점, 하나의 컴포넌트, 간선의 수가 n - 1개이면 트리
	//m개의 간선(전체 간선 수)에서 i번째 정점의 간선 수을 뺀 것이 (전체 정점 - 1) - (cnt[i] + 1) 이 되어야 한다.
	//처음에 컴포넌트 1개
	//i번째 정점을 지우면 cnt[i] + 1개의 컴포넌트
	//i번째 정점을 지우면 정점의 수가 n - 1개
	//(n - 1) - (cnt[i] + 1) == m - (int)adj[i].size()
	for (i = 1; i <= n; i++)
		if (m - (int)adj[i].size() == n - cnt[i] - 2)
			ans += i;
	cout << ans;
}