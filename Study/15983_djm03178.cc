// subtask 1
#include <stdio.h>
#include <vector>
#include <queue>
#include <algorithm>
#include <iostream>
#include <string>
#include <bitset>
#include <map>
#include <set>
#include <tuple>
#include <string.h>
#include <math.h>
#include <random>
#include <functional>
#include <assert.h>
#include <math.h>
#include <numeric>
using namespace std;
using i64 = long long int;
using ii = pair<int, int>;
using ii64 = pair<i64, i64>;
vector<int> plane[1000005];
vector<int> pos[105];
int dist[105][52];
int main()
{
  int n, e;
  scanf("%d %d", &n, &e);
  memset(dist, -1, sizeof(dist));
  for (int i = 0; i < n; i++)
  {
    int k;
    scanf("%d", &k);
    pos[i].resize(k);
    for (int j = 0; j < k; j++)
    {
      scanf("%d", &pos[i][j]);
      plane[pos[i][j]].push_back(i);
    }
  }
  queue<ii> q;
  q.emplace(0, 0);
  dist[0][0] = 0;
  while (!q.empty())
  {
    auto now = q.front();
    q.pop();
    vector<int> p;
    int nowd = dist[now.first][now.second];
    int nowp = pos[now.first][now.second];
    if (nowp == e)
    {
      printf("%d\n", nowd);
      return 0;
    }
    int nidx = (nowd + 1) % pos[now.first].size();
    if (plane[nowp].size() == 2)
    {
      int px = plane[nowp][0] == now.first ? plane[nowp][1] : plane[nowp][0];
      if (dist[px][nidx] == -1 && pos[px][now.second] == pos[now.first][now.second])
      {
        dist[px][nidx] = nowd + 1;
        q.emplace(px, nidx);
      }
    }
    if (dist[now.first][nidx] != -1)
      continue;
    dist[now.first][nidx] = nowd + 1;
    q.emplace(now.first, nidx);
  }
  printf("-1\n");
  return 0;
}
// subtask 2
#include <stdio.h>
#include <vector>
#include <queue>
#include <algorithm>
#include <iostream>
#include <string>
#include <bitset>
#include <map>
#include <set>
#include <tuple>
#include <string.h>
#include <math.h>
#include <random>
#include <functional>
#include <assert.h>
#include <math.h>
#include <numeric>
using namespace std;
using i64 = long long int;
using ii = pair<int, int>;
using ii64 = pair<i64, i64>;
vector<int> plane[1000005];
vector<int> pos[105];
bool visited[101][250005];
int main()
{
  int n, e;
  scanf("%d %d", &n, &e);
  int maxk = 0;
  for (int i = 0; i < n; i++)
  {
    int k;
    scanf("%d", &k);
    maxk = max(maxk, k);
    pos[i].resize(k);
    for (int j = 0; j < k; j++)
    {
      scanf("%d", &pos[i][j]);
      plane[pos[i][j]].push_back(i);
    }
  }
  queue<ii> q;
  q.emplace(0, 0);
  while (!q.empty())
  {
    auto now = q.front();
    q.pop();
    vector<int> p;
    int nowd = now.second;
    int idx = nowd % pos[now.first].size();
    int nowp = pos[now.first][idx];
    if (nowd >= n * maxk * maxk)
      break;
    if (nowp == e)
    {
      printf("%d\n", nowd);
      return 0;
    }
    if (plane[nowp].size() == 2)
    {
      int px = plane[nowp][0] == now.first ? plane[nowp][1] : plane[nowp][0];
      if (!visited[px][nowd + 1] &&
          pos[px][nowd % pos[px].size()] == pos[now.first][idx])
      {
        visited[px][nowd + 1] = true;
        q.emplace(px, nowd + 1);
      }
    }
    if (visited[now.first][nowd + 1])
      continue;
    visited[now.first][nowd + 1] = true;
    q.emplace(now.first, nowd + 1);
  }
  printf("-1\n");
  return 0;
}

// subtask 3
#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
using namespace std;
int gcd(int a, int b)
{
  if (a % b == 0)
    return b;
  return gcd(b, a % b);
}
int lcm(int a, int b)
{
  return a / gcd(a, b) * b;
}
const int MAX_N = 100;
const int MAX_E = 1000000;
const int MAX_K = 4000;
const int INF = (int)2e9;
struct visit
{
  int i, t;
  bool operator<(const visit &o) const
  {
    return t > o.t;
  }
};
vector<int> platform[MAX_N];
int cycle[MAX_N];
bool visited[MAX_N];
int dist[MAX_N];
int n, e;
vector<visit> on[MAX_E + 1];
int main()
{
  int i, j;
  ios::sync_with_stdio(false);
  cin.tie(NULL);
  cin >> n >> e;
  for (i = 0; i < n; i++)
  {
    cin >> cycle[i];
    platform[i].resize(cycle[i]);
    for (j = 0; j < cycle[i]; j++)
    {
      cin >> platform[i][j];
      on[platform[i][j]].push_back({i, j});
    }
  }
  fill(dist, dist + n, INF);
  priority_queue<visit> pq;
  pq.push({0, 0});
  dist[0] = 0;
  while (!pq.empty())
  {
    visit cur = pq.top();
    pq.pop();
    if (visited[cur.i])
      continue;
    visited[cur.i] = true;
    for (i = 1; i < cycle[cur.i]; i++)
    {
      int t = cur.t + i;
      int index = t % cycle[cur.i];
      int pos = platform[cur.i][index];
      if (pos == e)
      {
        cout << t << endl;
        return 0;
      }
      if ((int)on[pos].size() != 2)
        continue;
      visit other = on[pos][0].i == cur.i ? on[pos][1] : on[pos][0];
      if (visited[other.i])
        continue;
      int l = lcm(cycle[cur.i], cycle[other.i]);
      for (j = 0; cycle[cur.i] * j < l; j++)
        if ((cycle[cur.i] * j + t) % cycle[other.i] == other.t)
          break;
      if (cycle[cur.i] * j == l)
        continue;
      int nt = cycle[cur.i] * j + t;
      if (dist[other.i] <= nt)
        continue;
      dist[other.i] = nt;
      pq.push({other.i, nt});
    }
  }
  cout << -1 << endl;
  return 0;
}