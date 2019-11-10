# 4주차 발표 191109  

## fisher-yates shuffling algorithm 
### gaelim

n 개의 원소를 무작위로 셔플하는 `naive approach`
```cpp
#include <iostream>
#include <set>
#include <stdlib.h>
#include <time.h>
#include <vector>

using namespace std;
vector<int> ans;
set<int> s;
int main()
{
    srand(time(0));
    int n;
    n = 10;
    while( ans.size()<10)
    {
        for (int i=1; i<=n; i++)
        {
            if ( rand()%2)
            {
                if ( s.find(i) == s.end()) 
                {
                    ans.push_back(i);
                    s.insert(i);
                }
            }
        }
    }

    for (int a : ans)
        cout << a << " ";
        cout <<"\n";
}
```
확률적으로 공평하게 셔플하는 `fihser-yates shuffling` 
```cpp
#include <iostream>
#include <random>
#include <vector>
using namespace std;

vector<int> v, ans;
int main()
{
    int n = (int)2e7;
    for (int i=1; i<=n; i++)
        v.push_back(i);
    
    mt19937_64 eng(random_device{}());

    int m = n;
    for (int i=0; i<n; i++)
    {
        uniform_int_distribution<> dist(0, m-1);
        int j = dist(eng);
        ans.push_back(v[j]);
        v.erase(v.begin()+j, v.begin()+j+1);
        m--;
    }

    for (int i : ans)
        cout << i << " ";
    cout << "\n";
}
```

`swap`을 활용한 더 나은 수행복잡도.
```cpp
#include <iostream>
#include <random>
#include <vector>
using namespace std;

vector<int> v, ans;
int main()
{
    int n = (int)2e5;
    for (int i=1; i<=n; i++)
        v.push_back(i);
    
    mt19937_64 eng(random_device{}());

    for (int i=n-1; i>0; i--)
    {
        uniform_int_distribution<> dist(0, i-1);

        int j = dist(eng);

        int tmp = v[j];
        v[ j ] = v[ i ];
        v[ i ]  = tmp;
    }

    for (int i : v)
        cout << i << " ";
    cout << "\n";
}
```

## 코포 369 div.2 D Directed Raods
### djm03178

[문제링크](https://codeforces.com/contest/711/problem/D)  

**아이디어**

관찰 1: 간선의 방향을 마음대로 바꿀 수 있다. -> 방향에 의미가 없다!
즉, 간선을 양방향이라고 생각하면 된다.

관찰 2: 각 연결 컴포넌트에는 정확히 1개의 사이클이 존재한다.
증명: 하나의 연결 컴포넌트 내의 정점의 수가 x이라면, 각 정점으로부터 나가는 간선이 하나씩이므로 컴포넌트의 간선의 수도 x이다. 이는 트리에서 간선을 하나 추가한 것과 같으므로 정확히 하나의 사이클이 생긴다.

관찰 3: 각 연결 컴포넌트에서 confusing하는 상황이 생기려면, 해당 루프의 간선이 모두 원형으로 연결되어 있어야 하고, 이 경우에는 그 루프가 특정 방향으로 도는 것과 그 반대 방향으로 도는 것 두 가지가 있다. 따라서 어떤 루프에 속하는 정점의 수가 y라면 2^y - 2가지의 confusing하지 않은 경우가 존재한다. 또한 루프에 속하지 않는 간선은 어떤 방향이어도 상관 없다.

따라서 어떤 루프에도 속하지 않는 간선의 수가 k이고, 루프에 속한 간선이 각 루프에 a1, a2, a3, ... 개 라면, 정답은 2^k * (2^a1 - 2) * (2^a2 - 2) * (2^a3 - 2) * ...이다.

Cycle detection하는 방법  
1. 아직 방문되지 않은 아무 정점에서부터 DFS를 시작한다.  
2. DFS가 현재 정점을 방문하지 않았다면, 현재 정점을 현재 depth에서 방문했다는 것을 기록하고, 연결된 간선들의 다른 정점들을 방문한다. (이미 사용한 간선은 제외)  
3. DFS가 현재 정점을 방문했었다면, 현재 depth와 현재 정점에 기록되어 있는 depth의 차이만큼이 cycle에 속한 정점의 수이다.  

[source_code](https://codeforces.com/contest/711/submission/64470967)  

## 백준 16724 피리부는 사나이
### eovh1962

[문제링크](https://www.acmicpc.net/problem/16724)

**아이디어**

`ccs`를 활용한 해결법. 그 외로 `bfs/dfs` 를 활용한 탐색법도 있음.   
비슷한 문제들  
[내 선물을 받아줘](https://www.acmicpc.net/problem/15559)  
[내 선물을 받아줘2](https://www.acmicpc.net/problem/15886)  
