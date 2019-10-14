//bfs문제에서 맵은 좌표가 아닌 상태로 보자!

//1.S,X,E 순서대로 list에 넣어준다
//2.S->Xi 거리 , Xi 들끼리 거리, Xi->E 까지 거리를 순차적으로 구해준다.(S:0 , X1~Xi : 1~i , E : i+1) = > bfs 이용
//3.S부터 next permutation 시작 -> 만일 Xi의 마지막에 도달했다면,Xi->E 까지 거리를 더해준 값을 기존 ans 와 비교해주어 작으면 ans=value 처리 = > dfs 이용

#include<iostream>
#include<queue>
#include<vector>
#include<cstring>

using namespace std;

struct info {
	int x, y;
	int num;
};

int n, m;
int cnt = 0;
int ans = 1e9;

char map[50][51]; //입력 map
int number_map[50][50];//Xi 들의 위치를 나타내는 map
int dfs_visit[6]; //next permutation 진행시 방문체크 (Xi들 끼리)


//S,Xi,E 들끼리 방문체크
int visit[50][50];
//S->Xi 까지 거리저장
int s_value[6];
//각 Xi들끼리 거리를 저장.[x][y] =>x에서 y까지의 거리
int x_value[6][6];
//Xi->E 까지 거리저장
int e_value[6];
//S,Xi,E 들의 정점들을 vector에 저장
vector<info> v;
//상,하,좌,우
int dx[] = { -1,1,0,0 }, dy[] = { 0,0,-1,1 };

void dfs(int cur, int val, int c_cnt); //next_permutation
void bfs(int x, int y, int num);//bfs 거리 탐색
void init();//초기화

int main()
{	
	int a, b;
	cin >> n >> m;
	
	for (int i = 0; i < m; i++) {
		cin >> map[i];		
		for (int j = 0; j < n; j++) {
			//시작시점(S)은 제일 먼저 리스트에 추가
			if (map[i][j] == 'S')
				v.push_back({ i,j,cnt++ });
			if (map[i][j] == 'E') {
				a = i;
				b = j;
			}
		}
	}
    //3x3 의 크기라면 1칸밖에 못움직임.
	if (n == 3 && m == 3) {
		cout << 1;
		return 0;
	}
	//Xi들 위치를 리스트에 저장
	for (int i = 0; i < m; i++)
	{
		for (int j = 0; j < n; j++)
			if (map[i][j] == 'X') {
				//각 정점의 위치에 number를 부여
				//cnt=1 부터 시작
				number_map[i][j] = cnt;
				//리스트에 하나씩 저장
				v.push_back({ i,j,cnt++ });
			}
	}
	//나가는 문(E)의 위치는 맨 마지막에 저장
	v.push_back({ a,b,cnt++ });

	//S->Xi 까지의 거리 저장
	bfs(v[0].x,v[0].y, 0);
	//모든 정점에 대해 bfs를 통해 다른 정점까지
	//거리를 계산
	for (int i = 1; i < v.size()-1; i++){
		init();
        bfs(v[i].x, v[i].y, v[i].num);
    }
	//next permutation 실행
	//찾아야 될 물건이 존재 하면
	if (v.size() > 2) {
		for (int i = 1; i < v.size() - 1; i++) {
			dfs_visit[i] = 1;
			//S에서 Xi 까지의 거리를 넘겨줌
			dfs(i, s_value[i], 1);
			dfs_visit[i] = 0;
		}
	}
	//존재하지 않으면 S->E 까지의 거리가 정담
	else 
		ans = e_value[0];
	
	cout << ans;

	return 0;
}
//Xi에서 E까지의 거리 계산
void dfs(int cur, int val,int c_cnt)
{	
    //Xi 들끼리 전부 연결이 된 상태이면
    //Xi -> S 까지의 거리를 더해줘서 비교 후 ans 갱신
	if (c_cnt >= (v.size()-2)) {
		val += e_value[cur];
		if (val < ans)
			ans = val;
		return;
	}
	for (int i = 1; i < v.size()-1; i++)
	{
		if (!dfs_visit[i])
		{
			dfs_visit[i] = 1;
			dfs(i, val + x_value[cur][i], c_cnt + 1);
			dfs_visit[i] = 0;
		}
	}
}
//num=0 이면 S->Xi,E 까지의 거리를 구해라!
void bfs(int x, int y, int num)
{
	int dis = 0;
	queue<info> q;
	visit[x][y] = 1;
	q.push({ x,y,num });

	while (!q.empty())
	{
		int size = q.size();
		for (int s = 0; s < size; s++)
		{
			info in = q.front();
			q.pop();

			for (int i = 0; i < 4; i++)
			{
				int tx = in.x + dx[i];
				int ty = in.y + dy[i];

				if (map[tx][ty]=='#' || tx < 0 || tx >= m || ty < 0 || ty >= n)continue;

				if (!visit[tx][ty] && (map[tx][ty] == '.' || map[tx][ty]=='S')) {
					visit[tx][ty] = 1;
					q.push({ tx,ty,num });
				}
				if (!visit[tx][ty] && map[tx][ty] == 'X') {
                    //S->Xi 까지의 거리를 저장
					if (num == 0) 
						s_value[number_map[tx][ty]] = dis + 1;
                    //Xi->Xj 까지의 거리를 저장
					//전에 미리 정점에 대해 저장해 놓았던 number를 통해
					//value 라는 이차원 배열에다가 [현재 나의 Xi 정점][내가 아닌 Xj 정점]= '각각의 거리' 를 저장(number map 이용)
					else					
						x_value[num][number_map[tx][ty]] = dis+1;
					visit[tx][ty] = 1;
					q.push({ tx,ty,num });
				}
				//S,Xi 에서부터 E 까지의 거리 저장
				if (!visit[tx][ty] && map[tx][ty] == 'E') {
					e_value[num] = dis + 1;
					visit[tx][ty] = 1;
				}				
			}
		}
		dis++;
	}
}
void init()
{
    memset(visit,0,sizeof(visit));
}