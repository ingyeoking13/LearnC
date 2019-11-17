#include <iostream>
#include <stdlib.h>
#include <string>

using namespace std;

const int MAX = 15;
int N, K;
string a[MAX];
int length[15];
int remains[15];
int p10[51];
long long dp[100][1 << MAX];
long long p, q;
long long find(int here, int visited);
long long gcd(long long p, long long q);
int main() {

	// idea 
	// 121 % 3 == 100 % 3 + 20 % 3 + 1 % 3

	cin >> N;
	for (int i = 0; i < N; i++) {
		cin >> a[i];
		length[i] = (int)a[i].length();
		//cout << "length[" << i << "] is : " << a[i].length() << "\n";
	}
	cin >> K;

	for (int i = 0; i < 100; i++) {
		for (int j = 0; j < (1 << MAX); j++) {
			dp[i][j] = -1;
		}
	}

	// making remains
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < length[i]; j++) {
			remains[i] = (remains[i] * 10 + (a[i][j] - '0')) % K;
		}
		//cout << "remains[" << i << "] is : " << remains[i] << "\n";
	}

	//p10

	p10[0] = 1 % K;
	for (int i = 1; i <= 50; i++) {
		p10[i] = p10[i - 1] * 10 % K;
	}

	// 0부터 시작해서 나머지가 0이 되는 것들의 개수
	p = find(0, 0);
	q = 1;
	for (int i = 1; i <= N; i++) {
		q *= i;
	}

	//cout << "p is : " << p << " , and q is : " << q << "\n";
	if (p == 0)
		cout << "0/1";
	else if (p == q)
		cout << "1/1";
	else {
		long long g = gcd(p, q);
		//cout << "g is : " << g << "\n";
		cout << p / g << "/" << q / g;
	}
	return 0;
}

long long find(int k, int visited) {

	long long ret = dp[k][visited];

	//base case : 
	if (ret != -1)
		return ret;

	if (visited == (1 << N) - 1)
		if (k == 0)
			return 1;
		else
			return 0;


	ret = 0;

	for (int i = 0; i < N; i++) {
		if (visited & (1 << i))
			continue;
		ret += find((k * p10[length[i]] + remains[i]) % K, visited | (1 << i));
	}

	return dp[k][visited] = ret;

}

// gcd making
long long gcd(long long p, long long q) {
	if (q == 0) {
		return p;
	}
	else {
		return gcd(q, p%q);
	}
}