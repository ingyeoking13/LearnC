#include<iostream>
#include<stdio.h>


const int MAX = 16;

int N;
int A[MAX][MAX];
int dp[MAX][1 << (MAX + 1)];
int shortestPath(int here, int visited);
int main() {

	std::cin >> N;

	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			std::cin >> A[i][j];
		}
	}
	for (int i = 0; i < MAX; i++) {
		for (int j = 0; j < (1 << MAX); j++) {
			dp[i][j] = -1;
		}
	}
	int answer = shortestPath(0, 1);

	std::cout << answer;
	return 0;
}


int shortestPath(int here, int visited) {

	if (visited == (1 << N) - 1)
		return A[here][0] ? A[here][0] : 1000000000;

	int ret = dp[here][visited];

	if (ret != -1)
		return ret;

	ret = 1000000000;

	for (int next = 0; next < N; next++) {
		if (visited & (1 << next))
			continue;

		if (A[here][next] == 0)
			continue;

		int candidate = A[here][next] + shortestPath(next, visited | (1 << next));

		if (ret >= candidate) {
			ret = candidate;
		}
	}

	return dp[here][visited] = ret;
}