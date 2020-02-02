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

	pair<int, int> conditions[10];

	for (int i = 1; i <= 9; i++) {
		cin >> conditions[i].first >> conditions[i].second;
	}
	bool check[10];
	for (int i = 1; i <= 9; i++) {
		check[i] = false;
	}

	//i번째 타자가 1루수
	for (int i = 1; i <= 9; i++) {
		//j번째 타자가 거짓말쟁이
		for (int j = 1; j <= 9; j++) {
			//k번째 진술이 거짓이라면 뒤로 넘어간다.
			bool flag = true;
			for (int k = 1; k <= 9; k++) {
				int judge = conditions[k].first;
				int num = conditions[k].second;
				if (j == k) {//거짓을 말하고 있을 때
					judge = 1 - judge;
					if (judge == 1 && num != i) {//찍은 사람이 1루수가 아니므로 모순
						flag = false;
						break;
					}

					if (judge == 0 && num == i) {//아니라는 사람이 1루수이므로 모순
						flag = false;
						break;
					}
				} else {//참을 말하고 있을 때
					if (judge == 1 && num != i) {//찍은 사람이 1루수가 아니므로 모순
						flag = false;
						break;
					}

					if (judge == 0 && num == i) {//아니라는 사람이 1루수이므로 모순
						flag = false;
						break;
					}

				}

			}

			if (flag) {
				check[i] = true;
			}

		}

	}

	int cnt = 0;
	for (int i = 1; i <= 9; i++) {
		if (check[i]) {
			cnt++;
		}
	}

	if (cnt == 1) {
		for (int i = 1; i <= 9; i++) {
			if (check[i]) {
				cout << i;
				break;
			}
		}
	} else {
		cout << -1;
	}


	return 0;
}