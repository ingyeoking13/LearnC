#include<stdio.h>
#include<malloc.h>
struct e
{
	int num, cost;
};
struct node
{
	int num;
	struct node* next;
};
struct node* f, *r;
int vn;
struct e* elist[50010];
int eindex[50010];
int root, cost[50010], depth[50010], tail;
int tp[50010], max_depth, sidx, **p;
int ans[50010];
void input();
void pb(int, int, int);
int get_root();
void push(int);
struct node pop();
void pre();
void build();
void calc();
int lca(int, int);
void show();
void fin();
void make_answer();
int main(void)
{
	make_answer();
	return 0;
}
void make_answer()
{
	input();
	root = get_root();
	pre();
	build();
	calc();
	show();
	fin();
}
void input()
{
	int i, a, b, c;
	scanf("%d", &vn);
	for (i = 0; i < vn - 1; i++)
	{
		scanf("%d %d %d", &a, &b, &c);
		pb(a, b, c);
		pb(b, a, c);
		depth[a] = depth[b] = -1;
	}
}
void pb(int a, int b, int c)
{
	elist[a] = (struct e*)realloc(elist[a], sizeof(struct e) * (eindex[a] + 1));
	elist[a][eindex[a]].cost = c;
	elist[a][eindex[a]++].num = b;
}
int get_root()
{
	int d, next, ncost, st, cur;
	struct node pnode;
	push(1);
	cost[1] = 0;
	depth[1] = 0;
	while (f)
	{
		pnode = pop();
		for (d = 0; d < eindex[pnode.num]; d++)
		{
			next = elist[pnode.num][d].num;
			if (depth[next] == -1)
			{
				ncost = elist[pnode.num][d].cost;
				depth[next] = depth[pnode.num] + 1;
				cost[next] = cost[pnode.num] + ncost;
				push(next);
			}
		}
	}
	for (d = cur = 1, st = -1; d <= vn; d++)
	{
		if (st < cost[d])
		{
			st = cost[d];
			cur = d;
		}
		cost[d] = 0;
		depth[d] = -1;
	}
	return cur;
}
void push(int num)
{
	struct node ret, *temp;
	temp = (struct node*)malloc(sizeof(struct node));
	temp->next = 0;
	temp->num = num;
	if (!f)
	{
		f = temp;
	} else
	{
		r->next = temp;
	}
	r = temp;
}
struct node pop()
{
	struct node ret, *temp;
	temp = f;
	ret = *f;
	f = f->next;
	free(temp);
	return ret;
}
void pre()
{
	int d, next, ncost, st = -1;
	struct node pnode;
	push(root);
	depth[root] = 0;
	cost[root] = 0;
	while (f)
	{
		pnode = pop();
		if (st < cost[pnode.num])
		{
			st = cost[pnode.num];
			tail = pnode.num;
		}
		max_depth = max_depth > depth[pnode.num] ? max_depth : depth[pnode.num];
		for (d = 0; d < eindex[pnode.num]; d++)
		{
			next = elist[pnode.num][d].num;
			if (depth[next] == -1)
			{
				ncost = elist[pnode.num][d].cost;
				depth[next] = depth[pnode.num] + 1;
				cost[next] = cost[pnode.num] + ncost;
				tp[next] = pnode.num;
				push(next);
			}
		}
	}

}
void build()
{
	int i, j;
	for (; (1 << sidx) < max_depth; sidx++);
	p = (int**)calloc(vn + 1, sizeof(int*));
	for (i = 0; i <= vn; i++)
	{
		p[i] = (int*)calloc(sidx, sizeof(int));
	}
	for (i = 1; i <= vn; i++)
	{
		p[i][0] = tp[i];
	}
	for (j = 1; j < sidx; j++)
	{
		for (i = 1; i <= vn; i++)
		{
			p[i][j] = p[p[i][j - 1]][j - 1];
		}
	}
}
void calc()
{
	int a, l, up, down;
	for (a = 1; a <= vn; a++)
	{
		l = lca(a, tail);
		up = cost[l];
		down = cost[tail] - cost[l];
		ans[a] = (up > down ? up : down) + cost[a] - cost[l];
	}
}
int lca(int a, int b)
{
	int po, diff, temp;
	if (depth[a] > depth[b])
	{
		temp = a;
		a = b;
		b = temp;
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
		if (p[a][po] != p[b][po])
		{
			b = p[b][po];
			a = p[a][po];
		}
	}
	return p[a][0];
}
void show()
{
	int i;
	for (i = 1; i <= vn; i++)
	{
		printf("%d\n", ans[i]);
	}
}
void fin()
{
	int i;
	for (i = 0; i <= vn; i++)
	{
		if (elist[i])
		{
			free(elist[i]);
		}
		free(p[i]);
	}
	free(p);
}