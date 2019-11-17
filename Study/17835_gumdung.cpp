//#include <bits/stdc++.h>
#include <iostream>
#include <queue>
#include <vector>
#include <algorithm>

#define SIZE 100001

using namespace std;
using ll = long long;

struct info {
	ll to, weight;
	bool operator<(const info &in) const {
		return weight > in.weight;
	}
};

ll n, m, k;
ll dist[SIZE], meet[SIZE];
vector<info> graph[SIZE];

void dijk(int s);

int main()
{
	ios::sync_with_stdio(false);
	cin.tie(0);

	ll x, y, w;
	cin >> n >> m >> k;
	//list 생성 및 연결
	for (int i = 0; i < m; i++)
	{
		cin >> x >> y >> w;
		graph[y].push_back({ x, w });
	}
	//면접장
	for (int i = 0; i < k; i++)
	{
		cin >> x;
		meet[x] = 1;
	}
	for (int i = 1; i <= n; i++)
		dist[i] = LONG_MAX;
	ll v, Max = -1;
	for (int i = 1; i <= n; i++)
	{
		if (meet[i] == 1)
			dijk(i);
	}
	for (int i = 1; i <= n; i++)
	{
		if (meet[i] != 1) {
			if (dist[i] > Max) {
				v = i;
				Max = dist[i];
			}
		}
	}
	cout << v << "\n" << Max;
	return 0;
}
void dijk(int s)
{
	priority_queue<info> pq;

	dist[s] = 0;
	pq.push({ s, 0 });

	while (!pq.empty())
	{
		info cur = pq.top();
		pq.pop();

		if (cur.weight > dist[cur.to])continue;

		for (int i = 0; i < graph[cur.to].size(); i++)
		{
			ll next = graph[cur.to][i].to;
			ll next_dist = graph[cur.to][i].weight;

			if (dist[next] > dist[cur.to] + next_dist)
			{
				dist[next] = dist[cur.to] + next_dist;
				pq.push({ next, dist[next] });
			}
		}
	}
}