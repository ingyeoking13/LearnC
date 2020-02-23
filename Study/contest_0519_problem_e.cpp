#include<bits/stdc++.h>
#define endl "\n"
using namespace std;
using ll = long long;
struct TREE
{
	int vn, sidx;
	vector<vector<int>>elist, p;
	vector<int>size, depth;
	TREE(int a) : vn(a), sidx(1)
	{
		size.resize(vn + 1, 0);
		depth.resize(vn + 1, -1);
		elist.resize(vn + 1);
		p.resize(vn + 1);
		for (; (1 << (sidx)) < vn + 2; sidx++);
		for (int i = depth[1] = 0; i <= vn; i++)
		{
			p[i].resize(sidx, 0);
		}
	}
	void pb(int a, int b)
	{
		elist[a].push_back(b);
	}
	int go(int c, int pa)
	{
		size[c] = 1;
		p[c][0] = pa;
		for (auto& nx : elist[c])
		{
			if (depth[nx] == -1)
			{
				depth[nx] = depth[c] + 1;
				size[c] += go(nx, c);
			}
		}
		return size[c];
	}
	void prepare()
	{
		int i, j;
		for (j = 1; j < sidx; j++)
		{
			for (i = 1; i <= vn; i++)
			{
				p[i][j] = p[p[i][j - 1]][j - 1];
			}
		}
	}
	int lca(int a, int b)
	{
		int po, diff;
		if (depth[a] > depth[b])
		{
			po = a;
			a = b;
			b = po;
		}
		diff = depth[b] - depth[a];
		for (po = sidx - 1; po >= 0; po--)
		{
			if (diff & (1 << po))
			{
				b = p[b][po];
			}
		}
		if (a == b)
		{
			return a;
		}
		for (po = sidx - 1; po >= 0; po--)
		{
			if (p[b][po] != p[a][po])
			{
				b = p[b][po];
				a = p[a][po];
			}
		}
		return p[a][0];
	}
	int kup(int a, int diff)
	{
		int po;
		for (po = sidx - 1; po >= 0; po--)
		{
			if (diff & (1 << po))
			{
				a = p[a][po];
			}
		}
		return a;
	}
	int get_dis(int a, int b, int l)
	{
		return depth[a] + depth[b] - depth[l] - depth[l];
	}
	int get_deep(int a, int b)
	{
		return depth[a] > depth[b] ? a : b;
	}
};
struct SOLUTION
{
	int vn;
	TREE tree;
	SOLUTION(int a) : vn(a), tree(a)
	{
		input();
		tree.go(1, 0);
		tree.prepare();
		proc();
	}
	void input()
	{
		int i, a, b;
		for (i = 0; i < vn - 1; i++)
		{
			cin >> a >> b;
			tree.pb(a, b);
			tree.pb(b, a);
		}
	}
	void proc()
	{
		int qn, a, b;
		cin >> qn;
		while (qn--)
		{
			cin >> a >> b;
			cout << query(a, b) << endl;
		}
	}
	int query(int a, int b)
	{
		int l, dis, u, deep, s1, s2, c;
		if (a == b)
		{
			return vn;
		}
		l = tree.lca(a, b);
		dis = tree.get_dis(a, b, l);
		if (dis & 1)
		{
			return 0;
		}
		deep = tree.get_deep(a, b);
		u = tree.kup(deep, dis >> 1);
		if (u == l)
		{
			s1 = tree.kup(a, (dis >> 1) - 1);
			s2 = tree.kup(b, (dis >> 1) - 1);
			return vn - tree.size[s1] - tree.size[s2];
		} else
		{
			c = tree.kup(deep, (dis >> 1));
			s1 = tree.kup(deep, (dis >> 1) - 1);
			return tree.size[c] - tree.size[s1];
		}
	}
};
void make_answer();
int main(void)
{
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	make_answer();
	return 0;
}
void make_answer()
{
	int vn;
	cin >> vn;
	SOLUTION sol(vn);
}