#include <string>
#include <vector>

using namespace std;

bool solution(vector<vector<int>> key, vector<vector<int>> lock) {
	bool answer = false;

	const int size = 60;
	int board[size][size];
	for (int i = 0; i < size; i++) {
		for (int j = 0; j < size; j++) {
			board[i][j] = 0;
		}
	}

	int M = key.size();
	int N = lock.size();

	const int keysize = 20;
	int keys[4][20][20];
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 20; j++) {
			for (int k = 0; k < 20; k++) {
				keys[i][j][k] = 0;
			}
		}
	}

	//90 턴
	for (int i = 0; i < M; i++) {
		for (int j = 0; j < M; j++) {
			keys[0][i][j] = key[i][j];
		}
	}
	for (int i = 0; i < M; i++) {
		for (int j = 0; j < M; j++) {
			keys[1][i][j] = keys[0][M - 1 - j][i];
		}
	}
	for (int i = 0; i < M; i++) {
		for (int j = 0; j < M; j++) {
			keys[2][i][j] = keys[1][M - 1 - j][i];
		}
	}
	for (int i = 0; i < M; i++) {
		for (int j = 0; j < M; j++) {
			keys[3][i][j] = keys[2][M - 1 - j][i];
		}
	}

	//그림판 더하기
	for (int i = 20; i < 20 + N; i++) {
		for (int j = 20; j < 20 + N; j++) {
			board[i][j] += lock[i - 20][j - 20];
		}
	}

	//
	for (int i = 0; i <= 40; i++) {
		for (int j = 0; j <= 40; j++) {
			for (int keyindex = 0; keyindex < 4; keyindex++) {
				for (int a = 0; a < M; a++) {
					for (int b = 0; b < M; b++) {
						board[i + a][j + b] += keys[keyindex][a][b];
					}
				}
				bool flag = true;
				for (int a = 20; a < 20 + N; a++) {
					for (int b = 20; b < 20 + N; b++) {
						if (board[a][b] != 1) {
							flag = false;
							break;
						}
					}
					if (flag == false) {
						break;
					}
				}

				//출력부
				/*for (int a = 20; a < 20 + N; a++) {
					for (int b = 20; b < 20 + N; b++) {
						cout << board[a][b] << " ";
					}
					cout << "\n";
				}
				cout << "\n";*/

				if (flag) {
					answer = true;
					break;
				}
				for (int a = 0; a < M; a++) {
					for (int b = 0; b < M; b++) {
						board[i + a][j + b] -= keys[keyindex][a][b];
					}
				}	
			}
			if (answer) {
				break;
			}
		}
		if (answer) {
			break;
		}
	}
	return answer;
}