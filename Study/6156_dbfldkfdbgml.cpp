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

int main() {

	int N, M;

	cin >> N >> M;

	bool graph[101][101];
	for (int i = 1; i <= 100; i++)
		for (int j = 1; j <= 100; j++)
			graph[i][j] = false;
			 
	for (int i = 0; i < M; i++) {
		int from, to;
		cin >> from >> to;
		graph[from][to] = true;
	}

	for (int k = 1; k <= N; k++) {
		for (int i = 1; i <= N; i++) {
			for (int j = 1; j <= N; j++) {
				graph[i][j] |= graph[i][k] & graph[k][j];
			}
		}
	}

	int answer = 0;
	for (int i = 1; i <= N; i++) {
		bool flag = true;
		for (int j = 1; j <= N; j++) {
			if (i != j && (!graph[i][j] && !graph[j][i])) {
				flag = false;
				break;
			}
		}
		if (flag == false) {
			continue;
		}
		answer++;
	}

	cout << answer;

	return 0;
}