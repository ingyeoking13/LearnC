#include <iostream>
#include <algorithm>
#include <stdio.h>
#include <string.h>
#include <vector>
#include <stack>
#include <queue>
#include <string>
#include <math.h>
#include <map>
#include <set>
#include <sstream>

//namespaces
using namespace std;

//global variables

int comparator(int a, int b) {
	if (a > b) {
		return 1;
	} else if (a < b) {
		return -1;
	} else {
		return 0;
	}
}

int solution(int n, vector<int> weak, vector<int> dist) {

	if (weak.size() == 0) {
		return 0;
	}

	//answer는 사람 수보다 많을 수 없다.
	int answer = (int)dist.size() + 1;

	//사이즈 2배의 배열을 만들어서 원형을 구현한다.
	int N = n * 2;
	bool * visited = new bool[N];
	for (int i = 0; i < N; i++) {
		visited[i] = false;
	}
	for (int i = 0; i < weak.size(); i++) {
		visited[weak[i]] = true;
		visited[weak[i] + n] = true;
	}

	//next permutation을 써서 모든 경우의 수를 나열하지 않으면 안 된다
	//dist 3, 6, 4
	//weak 1, 7, 10, 14, 15, 18
	//next permutation을 쓰기 전에 한 번 sort한다
	sort(dist.begin(), dist.end());
	//do while을 써서 처음 한 번은 되게 해준다.
	do {
		for (int i = 0; i < n; i++) {
			int now = i;
			int end = now + n;
			int index = 0;
			int cnt = 0;
			if (visited[now] == false) {
				continue;
			}
			while (now < end) {
				//약한 벽이 아니면 넘어간다
				if (visited[now] == false) {
					now++;
					continue;
				}
				//사람이 없으면 포기한다
				if (index >= dist.size()) {
					break;
				}
				//사람이 갈 수 있을 만큼 가서 외벽을 점검한다
				for (int j = 0; (j <= dist[index]) & (now < end); j++, now++) {
					if (visited[now]) {
						cnt++;
					}
				}
				//다음 사람으로 넘긴다
				index++;

			}
			//점검한 수가 약한 외벽의 수와 같다면
			if (cnt == weak.size()) {
				answer = min(answer, index);
			}
		}
	} while (next_permutation(dist.begin(), dist.end()));

	//정답이 최댓값 곧 갱신이 되지 않았다면
	if (answer == dist.size() + 1) {
		return -1;
	}

	return answer;
}

//main method
int main() {
	//speedy reading option
	cin.tie(NULL);
	ios_base::sync_with_stdio(false);

	int n = 50;
	vector<int> weak(1);
	weak[0] = 1;
	/*weak[1] = 3;
	weak[2] = 10;
	weak[3] = 16;
	weak[4] = 22;
	weak[5] = 25;*/

	vector<int> dist(1);
	dist[0] = 6;
	/*dist[1] = 3;
	dist[2] = 2;
	dist[3] = 1;*/
	/*dist[1] = 1;
	dist[2] = 1;
	dist[3] = 1;
	dist[4] = 100;
	*/
	cout << solution(n, weak, dist) << "\n";


	//정상종료시 반드시 0을 리턴해야합니다.
	return 0;
}
