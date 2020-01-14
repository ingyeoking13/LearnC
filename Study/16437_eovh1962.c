#include <stdio.h>
#include <malloc.h>
#define MAX 123466
long long answer;
int vn;
int *elist[MAX], eindex[MAX], v[MAX];
long long size[MAX];
void input();
void pb(int, int);
long long go(int);
void fin();
long long make_answer();
int main(void)
{
  answer = make_answer();
  printf("%lld\n", answer);
  return 0;
}
long long make_answer()
{
  long long ans;
  input();
  ans = go(1);
  fin();
  return ans;
}
void input()
{
  int vn, i, b;
  char kind[2];
  long long s;
  scanf("%d", &vn);
  for (i = v[1] = 2; i <= vn; i++)
  {
    scanf("%s %lld %d", kind, &s, &b);
    pb(i, b);
    pb(b, i);
    size[i] = kind[0] == 'S' ? s : s * -1;
  }
}
void pb(int a, int b)
{
  elist[a] = (int *)realloc(elist[a], sizeof(int) * (eindex[a] + 1));
  elist[a][eindex[a]++] = b;
}
long long go(int cur)
{
  long long ret;
  int d, next;
  ret = size[cur];
  for (d = 0; d < eindex[cur]; d++)
  {
    next = elist[cur][d];
    if (!v[next])
    {
      v[next] = 1;
      ret += go(next);
    }
  }
  return ret > 0 ? ret : 0;
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