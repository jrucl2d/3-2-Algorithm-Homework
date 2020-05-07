#include <iostream> // 2015112083 유성근
#include <vector>
#include <fstream>
#include <string>
using namespace std;
#define NOWAY -1
int dp[5][5]; // 출발지에서 (i,j)까지 가는데 본 최대 관광지 개수 저장

struct map {
	int right;
	int down;
};
void GetInfo(map** tour) {
	ifstream file; // 입력 스트림
	file.open("map_info.txt"); // 파일 열기

	// 맵 정보 입력받기
	char info[50]; // 5*5 = 25개의 맵에 대해서 right, down 정보 입력
	int index = 0;
	while (!file.eof()) {
		string s;
		getline(file, s); // 한 줄을 읽어옴. 
		info[index++] = s[0]; // s[0]에는 right의 정보
		info[index++] = s[2]; // s[2]에는 down의 정보가 들어있다.
	}
	index = 0;
	for (int i = 0; i < 5; i++) {
		for (int j = 0; j < 5; j++) {
			char tmp1 = info[index++];
			char tmp2 = info[index++];
			if (tmp1 >= '0' && tmp1 <= '9') // right 정보가 숫자이면 집어넣고
				tour[i][j].right = tmp1 - '0';
			else // 길이 없다는 뜻으로 'n'이 들어가 있으면 -1 넣어줌
				tour[i][j].right = NOWAY;

			if (tmp2 >= '0' && tmp2 <= '9')
				tour[i][j].down = tmp2 - '0';
			else
				tour[i][j].down = NOWAY;
		}
	}
}

void DP(map** tour) { // O(n^2) 시간복잡도
	// 사전 정보 입력(최적의 길을 찾는 경우의 수가 딱 1개밖에 없는 경우)
	dp[0][0] = 0;
	for (int i = 1; i < 5; i++) {
		dp[i][0] = dp[i - 1][0] + tour[i - 1][0].down;
		dp[0][i] = dp[0][i - 1] + tour[0][i - 1].right;
	}
	// 모든 노드에 대해 반복
	for (int i = 1; i < 5; i++) {
		for (int j = 1; j < 5; j++) {
			// 가능한 이전 노드(좌측 or 위)에서 현 노드로 이동했을 때 더 큰값을 가지는 경우를 현 노드 dp값으로 설정
			if (dp[i - 1][j] + tour[i - 1][j].down > dp[i][j - 1] + tour[i][j - 1].right)
				dp[i][j] = dp[i - 1][j] + tour[i - 1][j].down;
			else dp[i][j] = dp[i][j - 1] + tour[i][j - 1].right;
		}
	}
	for (int i = 0; i < 5; i++) {
		for (int j = 0; j < 5; j++)
			cout << dp[i][j] << "\t";
		cout << endl;
	}
}

int main() {
	map** tour = new map * [5]; // map 이차원 배열 동적 할당
	for (int i = 0; i < 5; i++)
		tour[i] = new map[5];
	GetInfo(tour); // 파일에서 정보를 입력받음
	DP(tour); // 알고리즘 수행
}