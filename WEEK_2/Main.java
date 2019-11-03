import java.io.BufferedReader;
import java.io.BufferedWriter;
import java.io.InputStreamReader;
import java.io.OutputStreamWriter;

public class Main {

	static int C;
	static int directions[][] = { { 1, 0 }, { -1, 0 }, { 0, 1 }, { 0, -1 }, { 1, -1 }, { 1, 1 }, { -1, 1 },
			{ -1, -1 } };
	static char[][] map;
	static int[][][] dp;
	static char[] query;
	static String answer;

	// 보글 게임
	// 보글 게임판( 5 X 5 )과 알고 있는 단어들의 목록이 주어질 때,
	// 보글 게임판에서 각 단어를 찾을 수 있는지 여부를 출력하는 프로그램을 작성하세요.
	// 보글 게임판의 펜은 상하좌우, 혹은 대각선으로 인접한 칸으로 이동할 수 있으며 글자를 건너뛸 수는 없습니다.
	// 지나간 글자를 다시 지나가는 것은 가능하지만, 펜을 이동하지 않고 같은 글자를 여러 번 쓸 수는 없습니다.
	//
	// 예제 입력
	// 1
	// URLPM
	// XPRET
	// GIAET
	// XTNZY
	// XOQRS
	// 6
	// PRETTY
	// GIRL
	// REPEAT
	// KARA
	// PANDORA
	// GIAZAPX
	//
	// 예제 출력
	// PRETTY YES
	// GIRL YES
	// REPEAT YES
	// KARA NO
	// PANDORA NO
	// GIAZAPX YES

	public static void main(String[] args) throws Exception {
		BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
		BufferedWriter bw = new BufferedWriter(new OutputStreamWriter(System.out));

		C = Integer.parseInt(br.readLine());
		for (int test = 0; test < C; test++) {
			map = new char[5][5];
			for (int i = 0; i < 5; i++) {
				map[i] = br.readLine().toCharArray();
			}

			int N = Integer.parseInt(br.readLine());
			for (int i = 0; i < N; i++) {
				//
				query = br.readLine().toCharArray();
				int length = query.length;
				// 1. 3차원 dp 만들기
				// 2. length, 보글 게임판으로 3차원 dp를 만든다.
				dp = new int[length][5][5];
				answer = "NO";

				for (int j = 0; j < 5; j++) {
					for (int k = 0; k < 5; k++) {
						if (map[j][k] == query[0]) {
							dp[0][j][k] = 1;
						}
					}
				}
				// 두 번째 길이부터는
				for (int a = 1; a < length; a++) {
					// map의 가로
					for (int j = 0; j < 5; j++) {
						// map의 세로
						for (int k = 0; k < 5; k++) {
							// map의 이동 방향
							for (int l = 0; l < 8; l++) {
								int newRow = j + directions[l][0];
								int newCol = k + directions[l][1];
								//만약 이전까지 가능한 곳이었다면
								if (newRow >= 0 && newRow < 5 && newCol >= 0 && newCol < 5
										&& dp[a - 1][newRow][newCol] == 1 && map[j][k] == query[a]) {
									dp[a][j][k] = 1;
								}
							}
						}
					}
				}

				FORC: for (int j = 0; j < 5; j++) {
					for (int k = 0; k < 5; k++) {
						if (dp[length - 1][j][k] == 1) {
							answer = "YES";
							break FORC;
						}
					}
				}

				for (int j = 0; j < length; j++) {
					bw.write(query[j]);
				}
				bw.write(" " + answer + "\n");
			}

		}

		bw.flush();
		bw.close();
		br.close();
	}

}
