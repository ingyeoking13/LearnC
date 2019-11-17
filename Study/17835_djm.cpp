//#include <bits/stdc++.h>
#include <iostream>
#include <queue>
#include <vector>
#include <algorithm>
using namespace std;
using ll = long long;

struct A {
	int i;
	ll x;
	bool operator<(const A& o) const {
		return x > o.x;
	}
};

vector<A> adj[100001];
ll d[100001];
const ll inf = (ll)1e18;

int main()
{
	ios::sync_with_stdio(false);
	cin.tie(0);

	int n, m, k, i;
	cin >> n >> m >> k;
	for (i = 0; i < m; i++)
	{
		int a, b, c;
		cin >> a >> b >> c;
		adj[b].push_back({ a, c });
	}
	fill(d, d + n + 1, inf);
	priority_queue<A> pq;
	for (i = 0; i < k; i++)
	{
		int x;
		cin >> x;
		d[x] = 0;
		pq.push({ x, 0 });
	}
	while (pq.size())
	{
		A cur = pq.top();
		pq.pop();
		if (cur.x != d[cur.i])
			continue;
		for (A nxt : adj[cur.i])
		{
			if (cur.x + nxt.x < d[nxt.i])
			{
				d[nxt.i] = cur.x + nxt.x;
				pq.push({ nxt.i, cur.x + nxt.x });
			}
		}
	}
	int ans = 1;
	for (i = 2; i <= n; i++)
		if (d[i] > d[ans])
			ans = i;
	cout << ans << '\n' << d[ans];
}