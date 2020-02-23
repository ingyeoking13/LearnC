#include <bits/stdc++.h>
using namespace std;
using pii = pair<int, int>;

const int N = 100005;

struct Query {
	int a, b, t;

	bool operator<(const Query &o) const {
		return t < o.t;
	}
};

vector<Query> q;

struct Edge {
	int a, b, s, e;

	bool operator<(const Edge &o) const {
		return a == o.a ? b < o.b : a < o.a;
	}
};

int p[N], r[N];

struct Info {
	int x, y, k;
};

stack<Info> st;

inline int f(int x)
{
	while (x != p[x])
		x = p[x];
	return x;
}

inline void merge(int x, int y)
{
	x = f(x);
	y = f(y);
	if (x == y)
		return;
	if (r[x] > r[y])
		swap(x, y);
	p[x] = y;
	int k = 0;
	if (r[x] == r[y])
	{
		r[y]++;
		k = 1;
	}
	st.push({ x, y, k });
}

inline void split(Info info)
{
	p[info.x] = info.x;
	r[info.y] -= info.k;
}

void solve(int s, int e, const vector<Edge> &v)
{
	int t = q[s].t, tt = q[e].t;
	size_t sz = st.size();
	vector<Edge> left, right;
	int mid = q[(s + e) / 2].t;
	for (Edge edge : v)
	{
		if (edge.s <= t && tt <= edge.e)
		{
			merge(edge.a, edge.b);
			continue;
		}
		if (edge.s <= mid)
			left.push_back(edge);
		if (edge.e >= mid + 1)
			right.push_back(edge);
	}
	if (s == e)
		cout << int(f(q[s].a) == f(q[s].b)) << '\n';
	else
	{
		int m = (s + e) / 2;
		solve(s, m, left);
		solve(m + 1, e, right);
	}
	while (st.size() > sz)
	{
		split(st.top());
		st.pop();
	}
}

int main()
{
	ios::sync_with_stdio(false);
	cin.tie(0);

	int n, m, i;
	cin >> n >> m;
	set<Edge> s;
	vector<Edge> v;
	for (i = 1; i <= n; i++)
	{
		p[i] = i;
		r[i] = 1;
	}
	for (i = 1; i <= m; i++)
	{
		int t, a, b;
		cin >> t >> a >> b;
		if (a > b)
			swap(a, b);
		if (t == 1)
			s.insert({ a, b, i });
		else if (t == 2)
		{
			Edge e = *s.find({ a, b });
			s.erase(e);
			e.e = i;
			v.push_back(e);
		} else
			q.push_back({ a, b, i });
	}
	while (s.size())
	{
		Edge e = *s.begin();
		s.erase(s.begin());
		e.e = m + 1;
		v.push_back(e);
	}

	solve(0, (int)q.size() - 1, v);
}