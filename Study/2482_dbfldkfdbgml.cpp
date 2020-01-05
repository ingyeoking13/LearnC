#include <iostream>
#include <stdio.h>
#include <string.h>
#include <vector>
#include <algorithm>
#include <stack>
#include <queue>
#include <string>
#include <math.h>

//namespaces
using namespace std;

//variables
int N, K;
int Count;

//pointer variables
int dp[1001][1001];

//comparator

//method
void find(int index, int, int start);

//main method
int main() {
	//speedy reading option
	cin.tie(NULL);
	ios_base::sync_with_stdio(false);

	//new part

	for (int i = 0; i <= 1000; i++) {
		for (int j = 0; j <= 1000; j++) {
			dp[i][j] = 0;
		}
	}

	for (int i = 1; i <= 1000; i++) {
		for (int j = 1; j <= i / 2; j++) {
			if (j == 1) {
				dp[i][j] = i;
				continue;
			}
			if (i >= 4) {
				dp[i][j] = dp[i - 1][j] + dp[i - 2][j - 1];
				dp[i][j] %= 1000000003;
			}
		}
	}

	cin >> N >> K;
	cout << dp[N][K];


	//for (int i = 4; i <= 14; i++) {
	//	for (int j = 1; j <= 10; j++) {
	//		cout << dp[i][j] << " ";
	//	}
	//	cout << "\n";
	//}

	return 0;
}


