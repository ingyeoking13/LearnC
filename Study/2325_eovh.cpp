#include<bits/stdc++.h>
#define endl "\n"
using namespace std;
struct node
{
	int num;
	long long cost;
	//참조자를 써서 node를 deep copy 하는 일이 없도록 주의한다.
	//소스는 돌아가지만 성능 면에서 새로 객체를 만드는 일이 없도록 주의한다.
	bool operator < (node & a)const
	{
		return cost > a.cost;
	}
};
long long answer;
priority_queue<node> pq;
vector<vector<node>>elist;
long long memo[1001];
int parent[1001];
int vn, en;
long long di1();
long long di2(int, int);
long long make_answer();
int main(void)
{
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	answer = make_answer();
	cout << answer << endl;
	return 0;
}
long long make_answer()
{
	int i, a, b;
	long long c, ans, t, origin, gap;
	cin >> vn >> en;
	elist.resize(vn + 1);
	while (en--)
	{
		cin >> a >> b >> c;
		elist[a].push_back({ b, c });
		elist[b].push_back({ a, c });
	}
	ans = di1();
	a = vn;
	while (1)
	{
		b = parent[a];
		if (b == 0)
		{
			break;
		}
		t = di2(a, b);
		a = b;
		ans = max(ans, t);
	}
	return ans;
}
long long di1()
{
	int d, next, cur;
	long long ncost;
	for (d = 1; d <= vn; d++)
	{
		memo[d] = LLONG_MAX;
	}
	memo[1] = 0;
	pq.push({ 1, 0 });
	while (!pq.empty())
	{
		cur = pq.top().num;
		pq.pop();
		for (d = 0; d < elist[cur].size(); d++)
		{
			next = elist[cur][d].num;
			ncost = elist[cur][d].cost;
			if (memo[next] > memo[cur] + ncost)
			{
				parent[next] = cur;
				memo[next] = memo[cur] + ncost;
				pq.push({ next, memo[next] });
			}
		}
	}
	return memo[vn];
}
long long di2(int a, int b)
{
	int d, next, cur;
	long long ncost;
	for (d = 1; d <= vn; d++)
	{
		memo[d] = LLONG_MAX;
	}
	memo[1] = 0;
	pq.push({ 1, 0 });
	while (!pq.empty())
	{
		cur = pq.top().num;
		pq.pop();
		for (d = 0; d < elist[cur].size(); d++)
		{
			next = elist[cur][d].num;
			ncost = elist[cur][d].cost;
			if (memo[next] > memo[cur] + ncost && !((cur == a && next == b) || (cur == b && next == a)))
			{
				parent[next] = cur;
				memo[next] = memo[cur] + ncost;
				pq.push({ next, memo[next] });
			}
		}
	}
	return memo[vn];
}