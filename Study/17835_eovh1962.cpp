#include<stdio.h>
#include<malloc.h>
struct e
{
	int num;
	long long cost;
};
struct e* elist[100010], heap[500050];
int answer, eindex[100010], vn, en, k, start[100010], hidx, v[100010];
long long memo[100010];
void input();
void pb(int, int, long long);
void di();
void push(int, long long);
struct e pop();
int get_mode(int);
struct e calc();
void fin();
void make_answer();
int main(void)
{
	make_answer();
	return 0;
}
void make_answer()
{
	struct e ret;
	input();
	di();
	ret = calc();
	fin();
	printf("%d\n", ret.num);
	printf("%lld\n", ret.cost);
}
void input()
{
	int a, b;
	long long c;
	scanf("%d %d %d", &vn, &en, &k);
	while (en--)
	{
		scanf("%d %d %lld", &a, &b, &c);
		pb(b, a, c);
	}
	for (a = 0; a < k; a++)
	{
		scanf("%d", &start[a]);
	}
	for (a = 1; a <= vn; a++)
	{
		memo[a] = 0x7fffffffffffffff;
	}
}
void di()
{
	int d, next;
	long long ncost;
	struct e pnode;
	for (d = 0; d < k; d++)
	{
		push(start[d], 0);
		memo[start[d]] = 0;
	}
	while (hidx)
	{
		pnode = pop();
		if (v[pnode.num])
		{
			continue;
		}
		for (d = 0; d < eindex[pnode.num]; d++)
		{
			next = elist[pnode.num][d].num;
			ncost = elist[pnode.num][d].cost;
			if (memo[next] > memo[pnode.num] + ncost)
			{
				memo[next] = memo[pnode.num] + ncost;
				push(next, memo[next]);
			}
		}
		v[pnode.num] = 1;
	}
}
struct e calc()
{
	int num, d;
	long long cost;
	struct e ret;
	for (d = 1, num = 111111, cost = -1; d <= vn; d++)
	{
		if (cost < memo[d])
		{
			cost = memo[d];
			num = d;
		}
	}
	ret.cost = cost;
	ret.num = num;
	return ret;
}
void pb(int a, int b, long long c)
{
	elist[a] = (struct e*)realloc(elist[a], sizeof(struct e) * (eindex[a] + 1));
	elist[a][eindex[a]].num = b;
	elist[a][eindex[a]++].cost = c;
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
	}
}
void push(int num, long long cost)
{
	int cidx, tidx;
	struct e temp;
	hidx++;
	heap[hidx].cost = cost;
	heap[hidx].num = num;
	cidx = hidx;
	tidx = cidx / 2;
	while (!(!tidx || heap[tidx].cost < heap[cidx].cost))
	{
		temp = heap[cidx];
		heap[cidx] = heap[tidx];
		heap[tidx] = temp;
		cidx = tidx;
		tidx = cidx / 2;
	}
}
struct e pop()
{
	int cidx, mode;
	struct e ret, left, temp, right;
	ret = heap[1];
	heap[1] = heap[hidx];
	hidx--;
	cidx = 1;
	while (1)
	{
		mode = get_mode(cidx);
		if (!mode)
		{
			break;
		}
		else if (mode == 1)
		{
			left = heap[cidx * 2];
			if (left.cost < heap[cidx].cost)
			{
				temp = heap[cidx];
				heap[cidx] = heap[cidx * 2];
				heap[cidx * 2] = temp;
				cidx *= 2;
			}
			else
			{
				break;
			}
		}
		else
		{
			left = heap[cidx * 2];
			right = heap[cidx * 2 + 1];
			if (left.cost < right.cost)
			{
				if (left.cost < heap[cidx].cost)
				{
					temp = heap[cidx];
					heap[cidx] = heap[cidx * 2];
					heap[cidx * 2] = temp;
					cidx *= 2;
				}
				else
				{
					break;
				}
			}
			else
			{
				if (right.cost < heap[cidx].cost)
				{
					temp = heap[cidx];
					heap[cidx] = heap[cidx * 2 + 1];
					heap[cidx * 2 + 1] = temp;
					cidx *= 2;
					cidx++;
				}
				else
				{
					break;
				}
			}
		}
	}
	return ret;
}
int get_mode(int idx)
{
	if (idx * 2 + 1 <= hidx)
	{
		return 2;
	}
	if (idx * 2 == hidx)
	{
		return 1;
	}
	return 0;
}