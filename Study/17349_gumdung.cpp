#include<bits/stdc++.h>

using namespace std;

struct info {
	int a, b;
};

set<int> ans;
vector<info> player;
int state[2][10];
void search();
void clear();

//조건
//1. 반드시 거짓말을 하고 있는 사람은 1명이어야 된다
//2. 1루수는 반드시 1명만 존재해야 한다.
//3. 1루수를 정확이 몇번 타자인지 알수 있어야 한다.

int main()
{
	int a, b;
	int cur = -1;
	for (int i = 0; i < 9; i++) {
		cin >> a >> b;
		player.push_back({ a, b });
	}
	for (int i = 0; i < 9; i++) {
		int check = 0;
		//현재 사람이 거짓말을 하고 있다고 가정
		//즉,1 A 라고 말했으면 이 사람은 거짓말을 하고 있으니
		//[0][A] 에 상태 체크
		if (player[i].a == 0)
			state[1][player[i].b] = 1;
		else
			state[0][player[i].b] = 1;
		//거짓말을 해야되는 사람은 반드시 1명이어야 되니
		//나머지 사람들은 전부 참을 말함.
		//1 A 라고 말했으면 
		//[1][A] 에 상태 체크
		for (int j = 0; j < 9; j++) {
			int now = player[j].b;
			if (i == j)continue;
			if (player[j].a == 0)
				state[0][now] = 1;
			else
				state[1][now] = 1;
			//조건1
				//만약 모순이 생긴다면 조건이 성립 x 
			if (state[0][now] == 1 && state[1][now] == 1)goto t;
		}
		search();
	t:
		//state 배열 초기화
		clear();
	}
	//조건3
		//정확히 1루수를 지목할 수 없다면 성립x
		//ex)
			//0 1
			//1 1
			//0 2
			//0 3
			//0 4
			//0 5
			//0 6
			//0 7
			//0 7
		//1번 타자가 거짓말을 할 경우 => 1번타자가 1루수
		//2번 타자가 거짓말을 할 경우
			// => 8,9 번 타자가 1루수가 될 수도 있음
		//즉, 1루수를 정확히 지목 하지 못함.
	if (ans.size() != 1)
		cout << -1;
	else {
		auto u = ans.begin();
		cout << *u;
	}
}
void search()
{
	int cnt = 0;
	int ret = -1;
	for (int i = 1; i < 10; i++)
	{
		if (state[1][i] == 1)
		{
			cnt++;
			ret = i;
		}
	}
	//조건2
		//1루수가 여러명이 나타난다면 성립x
	if (cnt > 1)return;
	else if (cnt == 1) {
		ans.insert(ret);
		return;
	}

	for (int i = 1; i < 10; i++)
	{
		if (state[0][i] == 0)
			ans.insert(i);
	}
	return;
}
void clear()
{
	for (int i = 0; i < 10; i++)
		state[0][i] = state[1][i] = 0;
}